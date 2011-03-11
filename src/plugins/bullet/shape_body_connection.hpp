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


#ifndef SGE_BULLET_SHAPE_BODY_CONNECTION_HPP_INCLUDED
#define SGE_BULLET_SHAPE_BODY_CONNECTION_HPP_INCLUDED

#include "shapes/base_fwd.hpp"
#include "body_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace bullet
{
class shape_body_connection
{
	FCPPT_NONCOPYABLE(
		shape_body_connection
	);
public:
	explicit
	shape_body_connection(
		shapes::base &,
		body &);
	
	sge::bullet::body &
	body() const;
	
	~shape_body_connection();
private:
	shapes::base &shape_;
	sge::bullet::body &body_;
};
}
}

#endif