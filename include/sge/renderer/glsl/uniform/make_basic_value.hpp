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


#ifndef SGE_RENDERER_GLSL_UNIFORM_MAKE_BASIC_VALUE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_MAKE_BASIC_VALUE_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/basic_value_fwd.hpp>
#include <sge/renderer/glsl/uniform/make_enum_type.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

/**
\brief Metafunction which maps a value type to its corresponding
glsl::basic_value type

\tparam T The value type, which can be either glsl::int_type or
renderer::scalar
*/
template<
	typename T
>
struct make_basic_value
{
	typedef sge::renderer::glsl::uniform::basic_value<
		T,
		typename sge::renderer::glsl::uniform::make_enum_type<
			T
		>::type
	> type;
};

}
}
}
}

#endif
