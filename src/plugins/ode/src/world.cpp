/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../world.hpp"
#include "../body.hpp"
#include "../group.hpp"
#include "../joint.hpp"
#include "../shapes/sphere.hpp"
#include "../shapes/box.hpp"
#include "../shapes/container.hpp"
#include "../transformer_impl.hpp"
#include <sge/collision/group_overflow.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/null.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/text.hpp>
#include <functional>
#include <utility>
#include <cmath>

sge::ode::world::world(
	collision::optional_box const &_r,
	collision::constraint::type const _c
)
:
	world_(
		dWorldCreate()),
	begin_signal_(),
	end_signal_(),
	test_signal_(
		std::logical_and<bool>()),
	group_id_(
		static_cast<group_id>(
			1)),
	time_remainder_(
		fcppt::math::null<dReal>()),
	collisions_(),
	transformer_(
		collision::optional_box()
	),
	body_count_(
		0
	),
	plane_joint_(
		_c == collision::constraint::constrain_2d
		? 
			new joint(
				dJointCreatePlane2D(
					world_, 
					0
				)
			)
		: 
			0
		)
{
// FIXME
#if 0
	if (!_r)
		throw sge::exception(FCPPT_TEXT("ode needs the optional box in the world"));

	point const center(
		fcppt::math::vector::structure_cast<
			point
		>(
			_r.pos() + 
			fcppt::math::dim::structure_cast<
				collision::point
			>(
				static_cast<collision::unit>(0.5)*_r.dim()
			)
		)
	);

	dim const extents(
		fcppt::math::dim::structure_cast<
			dim
		>(
			_r.dim()
		)
	);

	space_ =
		dQuadTreeSpaceCreate(
			0,
			center.data(),
			extents.data(),
			10);
#endif
	/*
	dWorldSetAutoDisableFlag(
		world_,
		1);
		*/
}

fcppt::signal::auto_connection
sge::ode::world::register_test_callback(
	collision::test_callback const &_c)
{
	return
		test_signal_.connect(
			_c);
}

void
sge::ode::world::test_callback_combiner(
	collision::test_callback_combiner const &_c)
{
	test_signal_.combiner(
		_c);
}

fcppt::signal::auto_connection
sge::ode::world::register_begin_callback(
	collision::callback const &_c)
{
	return
		begin_signal_.connect(
			_c);
}

fcppt::signal::auto_connection
sge::ode::world::register_end_callback(
	collision::callback const &_c)
{
	return
		end_signal_.connect(
			_c);
}

sge::collision::body_ptr const
sge::ode::world::create_body(
	collision::shapes::container const &,
	collision::point const &,
	collision::point const &
)
{
#if 0
	return
		collision::body_ptr(
			new body(
				*this,
				transformer_,
				world_,
				_satellite,
				_shapes,
				_position,
				_linear_velocity));
#endif
}

sge::collision::shapes::sphere_ptr const
sge::ode::world::create_sphere(
	collision::satellite_ptr,
	collision::unit radius,
	collision::solidity::type,
	collision::point const &
)
{
#if 0
		collision::shapes::sphere_ptr(
			new shapes::sphere(
				transformer_,
				space_,
				_radius));
#endif
}

sge::collision::shapes::box_ptr const
sge::ode::world::create_box(
	collision::satellite_ptr,
	collision::dim const &,
	collision::solidity::type,
	collision::point const &
)
{
#if 0
	return 
		collision::shapes::box_ptr(
			new shapes::box(
				transformer_,
				space_,
				_dim));
#endif
}

sge::collision::group_ptr const 
sge::ode::world::create_group()
{
	return
		collision::group_ptr(
			new group(
				next_group_id()));
}

void
sge::ode::world::update(
	collision::time_unit const deltan)
{
	dReal const delta =
		static_cast<dReal>(deltan)+
		time_remainder_;

	dReal const time_step =
		static_cast<dReal>(
			0.001);

	unsigned const iterations =
		static_cast<unsigned>(
			delta/
			time_step);

	for (unsigned i = 0; i < iterations; ++i)
		step(
			time_step);

	time_remainder_ =
		std::fmod(
			delta,
			time_step);
}

void
sge::ode::world::collides_with(
	collision::group_ptr const a,
	collision::group_ptr const b)
{
	dynamic_cast<group &>(*a).collides_with(
		dynamic_cast<group &>(*b));
	dynamic_cast<group &>(*b).collides_with(
		dynamic_cast<group &>(*a));
}

sge::ode::world::~world()
{
	FCPPT_ASSERT_MESSAGE(
		!body_count_,
		FCPPT_TEXT("You've tried to delete a world before all of its bodys are dead")
	);

	dSpaceDestroy(
		space_);
	dWorldDestroy(
		world_);
}

void sge::ode::world::step(
	dReal const _time_step)
{
	dSpaceCollide(
		space_,
		this,
		&static_collide);

	dWorldQuickStep(
	//dWorldStep(
		world_,
		_time_step);
	check_end_signals();
}

void sge::ode::world::check_end_signals()
{
	for (object_map::iterator it(collisions_.begin()),next(it); it != collisions_.end(); it = next)
	{
		++next;
		if (it->second)
		{
			it->second = false;
			continue;
		}

		call_signal(
			end_signal_,
			it->first.first,
			it->first.second);

		collisions_.erase(
			it);
	}
}

sge::ode::group_id sge::ode::world::next_group_id()
{
	if (group_id_ == static_cast<group_id>(1 << 31))
		throw collision::group_overflow();
	group_id const old =
		group_id_;
	group_id_ <<= 1;
	return
		old;
}

void sge::ode::world::static_collide(
	void * const ptr,
	dGeomID const g0,
	dGeomID const g1)
{
	static_cast<world *>(ptr)->collide(
		g0,
		g1);
}

void sge::ode::world::collide(
	dGeomID const g0,
	dGeomID const g1)
{
	dBodyID const
		b0 =
			dGeomGetBody(
				g0),
		b1 =
			dGeomGetBody(
				g1);

	collision::satellite
		&s0 =
			*static_cast<body*>(
				dBodyGetData(
					b0))->satellite_,
		&s1 =
			*static_cast<body*>(
				dBodyGetData(
					b1))->satellite_;

	if (!test_signal_(s0,s1))
	{
		return;
	}

	// manual states that the contact array has to contain at least 1 element,
	// so to be sure, allocate one dContactGeom here
	dContactGeom g;
	if (dCollide(g0,g1,1,&g,sizeof(dContactGeom)) == 0)
	{
		return;
	}

	std::pair<object_map::iterator,bool>
		result =
			collisions_.insert(
				std::make_pair(
					std::make_pair(
						b1 > b0 ? b0 : b1,
						b1 > b0 ? b1 : b0),
					true));

	// insertion was successful, so this collision is new. we then send a collision_begin
	if (result.second)
	{
		call_signal(
			begin_signal_,
			b0,
			b1);
	}
	// if it wasn't successful, then we shall update the timestamp for the later end-check
	else
	{
		result.first->second = true;
	}
}

void sge::ode::world::call_signal(
	collision::callback_signal &s,
	dBodyID const b0,
	dBodyID const b1)
{
	collision::satellite
		&s0 =
			*static_cast<body*>(
				dBodyGetData(
					b0))->satellite_,
		&s1 =
			*static_cast<body*>(
				dBodyGetData(
					b1))->satellite_;

	s(
		std::tr1::ref(
			s0),
		std::tr1::ref(
			s1));
}

void sge::ode::world::destroy_body(
	dBodyID const _body)
{
	for (object_map::iterator it(collisions_.begin()),next(it); it != collisions_.end(); it = next)
	{
		++next;

		if (it->first.first == _body || it->first.second == _body)
		{
			call_signal(
				end_signal_,
				it->first.first,
				it->first.second);
			collisions_.erase(
				it);
		}
	}
}
