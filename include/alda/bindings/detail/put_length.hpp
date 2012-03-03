/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef ALDA_BINDINGS_DETAIL_PUT_LENGTH_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_PUT_LENGTH_HPP_INCLUDED

#include <alda//endianness.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/endianness/copy_n_from_host.hpp>


namespace alda
{
namespace bindings
{
namespace detail
{

template<
	typename Concept,
	typename Type
>
void
put_length(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	Concept const *const _concept,
	Type const &_value,
	majutsu::raw_pointer &_memory
)
{
	typedef typename Concept::length_type length_type;

	length_type const sz(
		fcppt::truncation_check_cast<
			length_type
		>(
			needed_size(
				_tag,
				_concept,
				_value
			)
		)
	);

	fcppt::endianness::copy_n_from_host(
		reinterpret_cast<
			majutsu::const_raw_pointer
		>(
			&sz
		),
		sizeof(length_type),
		_memory,
		sizeof(length_type),
		alda::endianness()
	);

	_memory += sizeof(length_type);
}

}
}
}

#endif

