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


#include <sge/cg/program/source.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/shader/load_edited_string.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::cg::program::source
sge::shader::load_edited_string(
	sge::renderer::device::core &_renderer,
	sge::renderer::vertex::declaration const &_vd,
	std::istream &_stream
)
{
	return
		_renderer.transform_cg_vertex_program(
			_vd,
			sge::cg::program::source(
				fcppt::io::stream_to_string(
					_stream
				)
			)
		);
}
