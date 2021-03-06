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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/depth_stencil.hpp>
#include <sge/opengl/texture/depth_stencil_basic.hpp>
#include <sge/opengl/texture/surface_context.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>


sge::opengl::texture::depth_stencil::depth_stencil(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::depth_stencil_parameters const &_parameters
)
:
	sge::opengl::texture::depth_stencil_basic(
		_basic_parameters,
		sge::opengl::texture::convert::make_type(
			GL_TEXTURE_2D
		),
		_parameters,
		sge::opengl::context::use<
			sge::opengl::texture::surface_context
		>(
			_basic_parameters.context()
		).config()
	)
{
}

sge::opengl::texture::depth_stencil::~depth_stencil()
{
}
