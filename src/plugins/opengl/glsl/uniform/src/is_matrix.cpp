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


#include "../is_matrix.hpp"
#include <sge/renderer/glsl/uniform/float_value_type.hpp>
#include <fcppt/assert/unreachable.hpp>

bool
sge::opengl::glsl::uniform::is_matrix(
	sge::renderer::glsl::uniform::float_value_type::type const _type
)
{
	namespace ft = sge::renderer::glsl::uniform::float_value_type;

	switch(
		_type
	)
	{
	case ft::float1:
	case ft::float2:
	case ft::float3:
	case ft::float4:
		return false;
	case ft::matrix2x2:
	case ft::matrix3x3:
	case ft::matrix4x4:
	case ft::matrix2x3:
	case ft::matrix3x2:
	case ft::matrix2x4:
	case ft::matrix4x2:
	case ft::matrix3x4:
	case ft::matrix4x3:
		return true;
	}

	FCPPT_ASSERT_UNREACHABLE
}
