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


#ifndef MAJUTSU_CONCEPTS_DYNAMIC_MEMORY_NEEDED_SIZE_HPP_INCLUDED
#define MAJUTSU_CONCEPTS_DYNAMIC_MEMORY_NEEDED_SIZE_HPP_INCLUDED

#include <majutsu/concepts/static_size.hpp>
#include <majutsu/size_type.hpp>

namespace majutsu
{
namespace concepts
{
namespace dynamic_memory
{

template<
	typename Element
>
size_type
needed_size(
	typename Element::type const &value_
)
{
	return
		needed_size(
			static_cast<
				tag const *
			>(0),
			static_cast<
				Element const *
			>(0),
			value_
		);
}

template<
	typename Element
>
typename concepts::static_size<
	Element
>::value_type
needed_size(
	tag const *,
	Element const *,
	typename Element::type const &
)
{
	return static_size<Element>::value; 
}

}
}
}

#endif