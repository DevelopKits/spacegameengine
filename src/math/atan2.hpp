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


#ifndef SGE_MATH_ATAN2_HPP_INCLUDED
#define SGE_MATH_ATAN2_HPP_INCLUDED

#include "vector.hpp"
#include "constants.hpp"
#include <boost/optional.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <cmath>

namespace sge
{
namespace math
{
template<typename T>
inline typename boost::enable_if<
	boost::is_floating_point<T>,
	boost::optional<T>
	>::type
atan2(const sge::math::basic_vector<T,2> &v)
{
	if (v.is_null())
		return boost::optional<T>();
	
	const T t = std::atan2(v.y(), v.x());

	if (t > pi<T>())
		return -static_cast<T>(2)*pi<T>()+t;
	
	return t+pi<T>()/static_cast<T>(2);
}
}
}

#endif
