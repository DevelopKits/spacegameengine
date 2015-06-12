/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/convert/projection.hpp>
#include <sge/opengl/state/convert/matrix_mode.hpp>
#include <sge/opengl/state/ffp/transform/matrix_mode.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix_and_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>


void
sge::opengl::state::ffp::transform::set_matrix_and_mode(
	sge::opengl::context::system::object &_context,
	sge::renderer::state::ffp::transform::mode const _mode,
	sge::renderer::matrix4 const &_matrix
)
{
	sge::opengl::state::ffp::transform::matrix_mode(
		sge::opengl::state::convert::matrix_mode(
			_mode
		)
	);

	sge::opengl::state::ffp::transform::set_matrix(
		_context,
		_mode
		==
		sge::renderer::state::ffp::transform::mode::projection
		?
			sge::opengl::convert::projection(
				_matrix
			)
		:
			_matrix
	);
}
