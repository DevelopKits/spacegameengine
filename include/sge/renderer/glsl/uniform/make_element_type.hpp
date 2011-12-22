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


#ifndef SGE_RENDERER_GLSL_UNIFORM_MAKE_ELEMENT_TYPE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_MAKE_ELEMENT_TYPE_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/glsl/uniform/int_type.hpp>
#include <sge/renderer/glsl/uniform/detail/float_arity.hpp>
#include <sge/renderer/glsl/uniform/detail/int_arity.hpp>
#include <sge/renderer/glsl/uniform/detail/matrix_arity.hpp>
#include <fcppt/math/matrix/basic_fwd.hpp>
#include <fcppt/math/vector/basic_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

template<
	typename T
>
struct make_element_type;

/**
\brief Metafunction that maps a static fcppt math vector to its corresponding
uniform::float_value_type
*/
template<
	typename N,
	typename S
>
struct make_element_type<
	fcppt::math::vector::basic<
		sge::renderer::scalar,
		N,
		S
	>
>
:
detail::float_arity<
	N::value
>
{};

/**
\brief Metafunction that maps a static fcppt math vector to its corresponding
uniform::int_value_type
*/
template<
	typename N,
	typename S
>
struct make_element_type<
	fcppt::math::vector::basic<
		sge::renderer::glsl::uniform::int_type,
		N,
		S
	>
>
:
detail::int_arity<
	N::value
>
{};

/**
\brief Metafunction that maps a static fcppt math matrix to its corresponding
uniform::float_value_type
*/
template<
	typename N,
	typename M,
	typename S
>
struct make_element_type<
	fcppt::math::matrix::basic<
		float,
		N,
		M,
		S
	>
>
:
detail::matrix_arity<
	N::value,
	M::value
>
{};

}
}
}
}

#endif
