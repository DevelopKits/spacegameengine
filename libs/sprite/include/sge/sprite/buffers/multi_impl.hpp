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


#ifndef SGE_SPRITE_BUFFERS_MULTI_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_MULTI_IMPL_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/allocate.hpp>
#include <sge/sprite/buffers/multi_decl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/option_to_resource_flags.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/zero_offset.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>


template<
	typename Choices
>
sge::sprite::buffers::multi<
	Choices
>::multi(
	sge::sprite::buffers::parameters const &_parameters,
	sge::sprite::buffers::option const _buffers_option
)
:
	parameters_(
		_parameters
	),
	buffers_option_(
		_buffers_option
	),
	buffers_()
{
}

template<
	typename Choices
>
sge::sprite::buffers::multi<
	Choices
>::~multi()
{
}

template<
	typename Choices
>
typename
sge::sprite::buffers::multi<
	Choices
>::slice_type
sge::sprite::buffers::multi<
	Choices
>::allocate(
	sge::sprite::count const _num_sprites
)
{
	buffers_.push_back(
		fcppt::make_unique_ptr<
			buffers_object
		>(
			sge::sprite::buffers::allocate<
				Choices
			>(
				parameters_,
				_num_sprites,
				sge::sprite::buffers::option_to_resource_flags(
					buffers_option_
				)
			)
		)
	);

	return
		slice_type(
			fcppt::make_cref(
				*buffers_.back()
			),
			sge::sprite::buffers::zero_offset<
				Choices
			>()
		);
}

template<
	typename Choices
>
sge::sprite::buffers::parameters const &
sge::sprite::buffers::multi<
	Choices
>::parameters() const
{
	return
		parameters_;
}

#endif
