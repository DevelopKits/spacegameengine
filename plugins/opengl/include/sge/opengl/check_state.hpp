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


#ifndef SGE_OPENGL_CHECK_STATE_HPP_INCLUDED
#define SGE_OPENGL_CHECK_STATE_HPP_INCLUDED

#include <sge/core/check_state.hpp>
#include <sge/opengl/check_state_always.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/error_string.hpp>


#if defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
#define SGE_OPENGL_CHECK_STATE(\
	message,\
	exception\
)\
SGE_CORE_CHECK_STATE(\
	exception,\
	message,\
	GLenum,\
	::glGetError(),\
	GL_NO_ERROR,\
	sge::opengl::error_string\
)
#else
#define SGE_OPENGL_CHECK_STATE(\
	message,\
	exception\
)
#endif

#endif
