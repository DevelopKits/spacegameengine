/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MATH_DETAIL_POINT_ROTATE_IMPL_HPP_INCLUDED
#define SGE_MATH_DETAIL_POINT_ROTATE_IMPL_HPP_INCLUDED

#include "../point_rotate.hpp"
#include "../matrix/basic_impl.hpp"
#include "../matrix/rotation_2d.hpp"
#include "../matrix/vector.hpp"
#include "../vector/arithmetic.hpp"
#include "../vector/basic_impl.hpp"

template<
	typename T,
	typename N,
	typename S
>
sge::math::vector::basic<T, N, S> const
sge::math::point_rotate(
	vector::basic<T, N, S> const &point,
	vector::basic<T, N, S> const &around,
	T const rot)
{
	return (matrix::rotation_2d(rot) * (point - around)) + around;
}

#endif
