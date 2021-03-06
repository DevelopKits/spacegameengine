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


#ifndef SGE_PROJECTILE_IMPL_BODY_DETAIL_MOTION_STATE_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_BODY_DETAIL_MOTION_STATE_HPP_INCLUDED

#include <sge/projectile/body/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btMotionState.h>
#include <LinearMath/btTransform.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
namespace body
{
namespace detail
{

// This is just a trampoline class because I couldn't derive
// body::object itself from btMotionState (since then I would break
// the pimpl stuff).
class motion_state
:
	public btMotionState
{
	FCPPT_NONCOPYABLE(
		motion_state
	);
public:
	explicit
	motion_state(
		sge::projectile::body::object &
	);

	~motion_state()
	override;
private:
	sge::projectile::body::object &body_;

	// @override
	void
	getWorldTransform(
		btTransform &
	) const
	override;

	// @override
	void
	setWorldTransform(
		btTransform const &
	)
	override;
};

}
}
}
}

#endif
