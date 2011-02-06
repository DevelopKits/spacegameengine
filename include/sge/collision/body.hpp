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


#ifndef SGE_COLLISION_BODY_HPP_INCLUDED
#define SGE_COLLISION_BODY_HPP_INCLUDED

#include <sge/collision/body_fwd.hpp>
#include <sge/collision/shapes/base_ptr.hpp>
#include <sge/collision/point.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace collision
{

class SGE_CLASS_SYMBOL body
{
	FCPPT_NONCOPYABLE(
		body
	);
protected:
	SGE_SYMBOL body();
public:
	virtual point const 
	position() const = 0;
	
	virtual void 
	position(
		point const &
	) = 0;
		
	virtual point const 
	linear_velocity() const = 0;
	
	virtual void 
	linear_velocity(
		point const &
	) = 0;
	
	virtual void
	add_shape(
		shapes::base_ptr
	) = 0;
		
	SGE_SYMBOL virtual ~body();
};

}
}

#endif
