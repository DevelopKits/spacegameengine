/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../convert_vertex_colors.hpp"
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/image/algorithm/convert_conditional.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <boost/assign/list_of.hpp>

void
sge::opengl::convert_vertex_colors(
	renderer::vf::dynamic::ordered_element const &e,
	renderer::size_type const vertex_stride,
	renderer::size_type const num_vertices,
	renderer::raw_pointer const data
)
{
	sge::renderer::vf::dynamic::color const dcolor(
		e.element().info().get<
			sge::renderer::vf::dynamic::color
		>()
	);

	sge::image::algorithm::convert_conditional(
		data + e.offset(),
		sge::image::dim_type(
			1,
			num_vertices
		),
		dcolor.color_format(),
		vertex_stride,
		boost::assign::list_of
			(sge::image::color::format::rgba8)
			(sge::image::color::format::rgba32f)
	);
}
