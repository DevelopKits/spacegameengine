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
#include <sge/opengl/cg/program/replace_index.hpp>
#include <sge/opengl/vf/extra_index.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>
#include <fcppt/insert_to_string.hpp>


sge::cg::string
sge::opengl::cg::program::replace_index(
	sge::cg::program::extra_index const _index
)
{
	return
		"ATTR"
		+
		fcppt::insert_to_string<
			sge::cg::string
		>(
			sge::opengl::vf::extra_index(
				sge::renderer::vf::dynamic::index(
					_index.get()
				)
			)
		)
		;
}
