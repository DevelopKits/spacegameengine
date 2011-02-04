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


#include "../depth_stencil_texture_surface.hpp"
#include "../basic_texture_surface_impl.hpp"
#include <sge/renderer/depth_stencil_surface.hpp>
#include <sge/renderer/stage_type.hpp>

sge::opengl::depth_stencil_texture_surface::depth_stencil_texture_surface(
	GLenum const _texture_type,
	GLuint const _id,
	renderer::depth_stencil_format::type const _format
)
:
	base(
		_texture_type,
		_id,
		renderer::stage_type(
			0u
		)
	),
	format_(_format)
{
}
	

sge::opengl::depth_stencil_texture_surface::~depth_stencil_texture_surface()
{
}

sge::renderer::depth_stencil_format::type
sge::opengl::depth_stencil_texture_surface::format() const
{
	return format_;
}

template class
sge::opengl::basic_texture_surface<
	sge::renderer::depth_stencil_surface
>;
