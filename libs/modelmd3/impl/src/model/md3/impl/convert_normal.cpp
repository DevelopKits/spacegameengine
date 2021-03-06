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


#include <sge/model/md3/scalar.hpp>
#include <sge/model/md3/impl/convert_normal.hpp>
#include <sge/model/md3/impl/s16.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sge::model::md3::impl::vec3
sge::model::md3::impl::convert_normal(
	sge::model::md3::impl::s16 const _normal
)
{
	sge::model::md3::scalar const
		lat(
			fcppt::cast::int_to_float<
				sge::model::md3::scalar
			>(
				(_normal >> 8)
				& 255
			)
			*
			fcppt::math::twopi<
				sge::model::md3::scalar
			>()
			/ 255
		),
		lng(
			fcppt::cast::int_to_float<
				sge::model::md3::scalar
			>(
				_normal & 255
			)
			*
			fcppt::math::twopi<
				sge::model::md3::scalar
			>()
			/ 255
		);

	return
		sge::model::md3::impl::vec3(
			std::cos(lat) * std::sin(lng),
			std::sin(lat) * std::sin(lng),
			std::cos(lng)
		);
}
