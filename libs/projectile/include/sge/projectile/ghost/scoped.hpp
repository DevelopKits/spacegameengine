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


#ifndef SGE_PROJECTILE_GHOST_SCOPED_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_SCOPED_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/ghost/object_fwd.hpp>
#include <sge/projectile/ghost/scoped_fwd.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace projectile
{
namespace ghost
{
class scoped
{
FCPPT_NONCOPYABLE(
	scoped);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL explicit
	scoped(
		world &,
		object &,
		group::sequence const &);

	SGE_PROJECTILE_DETAIL_SYMBOL ~scoped();
private:
	world &world_;
	object &object_;
};
}
}
}

#endif
