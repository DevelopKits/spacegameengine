/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_BULLET_SYSTEM_HPP_INCLUDED
#define SGE_BULLET_SYSTEM_HPP_INCLUDED

#include <sge/collision/system.hpp>

class btManifoldPoint;
class btCollisionObject;

namespace sge
{
namespace bullet
{
class system
:
	public sge::collision::system
{
public:
	system();
	
	collision::world_ptr const
	create_world(
		collision::optional_box const &,
		collision::constraint::type);
private:
	static bool
	collision_begin(
		btManifoldPoint& cp,
		btCollisionObject const *colObj0,
		int partId0,
		int index0,
		btCollisionObject const *colObj1,
		int partId1,
		int index1);
	
	static bool
	collision_processed(
		btManifoldPoint &,
		void* body0,
		void* body1);
	
	static bool
	collision_end(
		void*);
};
}
}

#endif