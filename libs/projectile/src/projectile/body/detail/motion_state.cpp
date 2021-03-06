/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/projectile/body/object.hpp>
#include <sge/projectile/impl/body/detail/motion_state.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btMotionState.h>
#include <LinearMath/btTransform.h>
#include <fcppt/config/external_end.hpp>


sge::projectile::body::detail::motion_state::motion_state(
	sge::projectile::body::object &_body
)
:
	btMotionState(),
	body_(
		_body
	)
{
}

sge::projectile::body::detail::motion_state::~motion_state()
{
}

void
sge::projectile::body::detail::motion_state::getWorldTransform(
	btTransform &_transform
) const
{
	body_.getWorldTransform(
		_transform
	);
}

void
sge::projectile::body::detail::motion_state::setWorldTransform(
	btTransform const &_transform
)
{
	body_.setWorldTransform(
		_transform
	);
}
