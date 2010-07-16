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


#include "../set_program.hpp"
#include "../context.hpp"
#include "../program.hpp"
#include "../../context/use.hpp"

void
sge::opengl::glsl::set_program(
	opengl::context::object &_context,
	renderer::glsl::program_ptr const _prog
)
{
#if 0
	if(
		opengl::context::use<
			glsl::context
		>(
			_context
		).is_native()
	)
		program<true>::use(
			_prog
		);
	else
		program<false>::use(
			_prog
		);
#endif
}
