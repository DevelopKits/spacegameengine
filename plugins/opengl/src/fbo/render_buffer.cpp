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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/render_buffer.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>


sge::opengl::fbo::render_buffer::render_buffer(
	sge::opengl::fbo::config const &_context,
	sge::opengl::internal_color_format const _internal_format,
	sge::renderer::dim2 const &_dim
)
:
	context_(
		_context
	),
	holder_(
		_context
	)
{
	this->bind();

	context_.renderbuffer_storage()(
		context_.renderbuffer_target(),
		fcppt::cast::to_unsigned(
			_internal_format.get()
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_dim.w()
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_dim.h()
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Setting the storage of a render buffer failed."),
		sge::renderer::exception
	)

}

sge::opengl::fbo::render_buffer::~render_buffer()
{
}

GLuint
sge::opengl::fbo::render_buffer::id() const
{
	return
		holder_.id();
}

void
sge::opengl::fbo::render_buffer::bind() const
{
	context_.bind_renderbuffer()(
		context_.renderbuffer_target(),
		this->id()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Binding a render buffer failed."),
		sge::renderer::exception
	)
}
