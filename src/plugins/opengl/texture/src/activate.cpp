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


#include "../activate.hpp"
#include "../base.hpp"
#include "../bind_context.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/texture/base.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>

void
sge::opengl::texture::activate(
	opengl::context::object &_context,
	sge::renderer::texture::const_base_ptr const _texture,
	sge::renderer::stage_type const _stage
)
{
	opengl::texture::bind_context &context(
		context::use<
			opengl::texture::bind_context
		>(
			_context
		)
	);

	if(
		_texture
	)
		context.bind_for_rendering(
			_context,
			fcppt::dynamic_pointer_cast<
				opengl::texture::base const
			>(
				_texture
			),
			_stage
		);
	else
		context.unbind_for_rendering(
			_context,
			_stage
		);
}