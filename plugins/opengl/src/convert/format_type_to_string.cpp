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


#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/format_type_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sge::opengl::convert::format_type_to_string(
	opengl::color_format_type const _format_type
)
{
	switch(
		_format_type.get()
	)
	{
	case GL_UNSIGNED_BYTE:
		return FCPPT_TEXT("UNSIGNED_BYTE");
	case GL_BYTE:
		return FCPPT_TEXT("BYTE");
	case GL_BITMAP:
		return FCPPT_TEXT("BITMAP");
	case GL_UNSIGNED_SHORT:
		return FCPPT_TEXT("UNSIGNED SHORT");
	case GL_SHORT:
		return FCPPT_TEXT("SHORT");
	case GL_UNSIGNED_INT:
		return FCPPT_TEXT("UNSIGNED INT");
	case GL_INT:
		return FCPPT_TEXT("INT");
	case GL_FLOAT:
		return FCPPT_TEXT("FLOAT");
	}

	FCPPT_ASSERT_UNREACHABLE;
}