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


#include "../create_program.hpp"
#include "../program.hpp"
#include "../context.hpp"
#include "../../context/use.hpp"
#include "../../common.hpp"
#include "../../on_not_supported.hpp"
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sge::renderer::glsl::program_ptr const
sge::opengl::glsl::create_program(
	opengl::context::object &_context,
	renderer::glsl::optional_string const &_vs_source,
	renderer::glsl::optional_string const &_ps_source
)
{
	glsl::context &glsl_context(
		opengl::context::use<
			glsl::context
		>(
			_context
		)
	);

	if(
		!glsl_context.is_supported()
	)
		sge::opengl::on_not_supported(
			FCPPT_TEXT("shader"),
			FCPPT_TEXT("2.0"),
			FCPPT_TEXT("gl_arb_vertex_shader && gl_arb_fragment_shader")
		);

	return
		glsl_context.is_native()
		?
			renderer::glsl::program_ptr(
				fcppt::make_shared_ptr<
					program<true>
				>(
					_vs_source,
					_ps_source
				)
			)
		:
			renderer::glsl::program_ptr(
				fcppt::make_shared_ptr<
					program<false>
				>(
					_vs_source,
					_ps_source
				)
			)
		;
}
