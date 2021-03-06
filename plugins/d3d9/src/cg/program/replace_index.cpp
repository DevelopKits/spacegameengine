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


#include <sge/cg/string.hpp>
#include <sge/cg/program/extra_index.hpp>
#include <sge/d3d9/cg/program/replace_index.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/d3d9/vf/convert/extra_index.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>
#include <fcppt/insert_to_string.hpp>


sge::cg::string
sge::d3d9::cg::program::replace_index(
	sge::d3d9::vf::texture_coordinate_count const _texture_coordinates,
	sge::cg::program::extra_index const _index
)
{
	return
		"TEXCOORD"
		+
		fcppt::insert_to_string<
			sge::cg::string
		>(
			sge::d3d9::vf::convert::extra_index(
				_texture_coordinates,
				sge::renderer::vf::dynamic::index(
					_index.get()
				)
			)
		);
}
