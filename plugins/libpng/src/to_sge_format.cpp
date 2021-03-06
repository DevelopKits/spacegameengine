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


#include <sge/image/color/format.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/to_sge_format.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::color::format
sge::libpng::to_sge_format(
	sge::libpng::format const _format
)
{
#define SGE_LIBPNG_CONVERT_CASE(\
	cur_format\
)\
	case sge::libpng::format::cur_format:\
		return \
			sge::image::color::format::cur_format

	switch(
		_format
	)
	{
		SGE_LIBPNG_CONVERT_CASE(
			l8
		);
		SGE_LIBPNG_CONVERT_CASE(
			la8
		);
		SGE_LIBPNG_CONVERT_CASE(
			srgb8
		);
		SGE_LIBPNG_CONVERT_CASE(
			sbgr8
		);
		SGE_LIBPNG_CONVERT_CASE(
			srgba8
		);
		SGE_LIBPNG_CONVERT_CASE(
			sbgra8
		);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
