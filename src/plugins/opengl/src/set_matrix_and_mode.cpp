/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../set_matrix_and_mode.hpp"
#include "../set_matrix.hpp"
#include "../matrix_mode.hpp"

void
sge::opengl::set_matrix_and_mode(
	context::object &_context,
	GLenum const _mode,
	renderer::matrix4 const &_matrix
)
{
	opengl::matrix_mode(
		_mode
	);

	opengl::set_matrix(
		_context,
		_matrix
	);
}