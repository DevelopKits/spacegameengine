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


#include <sge/pango/extents.hpp>
#include <sge/pango/get_extents.hpp>
#include <sge/pango/ink_rect.hpp>
#include <sge/pango/logical_rect.hpp>
#include <sge/pango/convert/from_rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


sge::pango::extents
sge::pango::get_extents(
	PangoLayout &_layout
)
{
	PangoRectangle ink_result;

	PangoRectangle logical_result;

	::pango_layout_get_pixel_extents(
		&_layout,
		&ink_result,
		&logical_result
	);

	return
		sge::pango::extents(
			sge::pango::ink_rect(
				sge::pango::convert::from_rect(
					ink_result
				)
			),
			sge::pango::logical_rect(
				sge::pango::convert::from_rect(
					logical_result
				)
			)
		);
}
