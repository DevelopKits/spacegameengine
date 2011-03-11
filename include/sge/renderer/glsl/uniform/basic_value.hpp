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


#ifndef SGE_RENDERER_GLSL_UNIFORM_BASIC_VALUE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_BASIC_VALUE_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/basic_value_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/symbol.hpp>
#include <fcppt/container/raw_vector_decl.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

template<
	typename Value,
	typename Type
>
class basic_value
{
public:
	typedef fcppt::container::raw_vector<
		Value
	> data_type;

	typedef Value value_type;
	typedef Type element_type;

	typedef typename data_type::pointer pointer;
	typedef typename data_type::const_pointer const_pointer;

	SGE_SYMBOL basic_value(
		data_type const &,
		renderer::size_type elements,
		Type
	);

	SGE_SYMBOL const_pointer
	data() const;

	SGE_SYMBOL pointer
	data();

	SGE_SYMBOL renderer::size_type
	elements() const;

	SGE_SYMBOL Type
	type() const;
private:
	data_type data_;

	renderer::size_type elements_;

	Type type_;
};

}
}
}
}

#endif