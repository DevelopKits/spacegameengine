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


#ifndef SGE_RESOURCE_TREE_DETAIL_ELEMENT_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_ELEMENT_IMPL_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/element_decl.hpp>
#include <sge/resource_tree/detail/path_with_resource_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/wrapper/make_uniform_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
>::element(
	resource_tree::path &&_base_path,
	resource_container &&_resources,
	Rng &_rng
)
:
	base_path_(
		std::move(
			_base_path
		)
	),
	resources_(
		std::move(
			_resources
		)
	),
	rng_(
		fcppt::optional::map(
			fcppt::random::wrapper::make_uniform_container(
				resources_
			),
			[
				&_rng
			](
				fcppt::random::wrapper::uniform_container<
					resource_container
				> const &_distribution
			)
			{
				return
					fcppt::random::make_variate(
						_rng,
						_distribution
					);
			}
		)
	)
{
}

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
>::element(
	element &&
)
= default;

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
> &
sge::resource_tree::detail::element<
	T,
	Rng
>::operator=(
	element &&
)
= default;

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element<
	T,
	Rng
>::~element()
{
}

template<
	typename T,
	typename Rng
>
sge::resource_tree::path const &
sge::resource_tree::detail::element<
	T,
	Rng
>::base_path() const
{
	return
		base_path_;
}

template<
	typename T,
	typename Rng
>
T const &
sge::resource_tree::detail::element<
	T,
	Rng
>::get_random() const
{
	return
		fcppt::optional::to_exception(
			rng_,
			[
				this
			]{
				return
					sge::resource_tree::exception(
						FCPPT_TEXT("No elements in ")
						+
						base_path_.string()
					);
			}
		)().resource();
}

template<
	typename T,
	typename Rng
>
typename
sge::resource_tree::detail::element<
	T,
	Rng
>::optional_type
sge::resource_tree::detail::element<
	T,
	Rng
>::get_opt(
	sge::resource_tree::path const &_path
) const
{
	return
		fcppt::algorithm::find_by_opt(
			resources_,
			[
				&_path,
				this
			](
				sge::resource_tree::detail::path_with_resource<
					T
				> const &_cur
			)
			{
				return
					(
						base_path_
						/
						_cur.path().string()
					)
					==
					_path
					?
						optional_type(
							fcppt::make_cref(
								_cur.resource()
							)
						)
					:
						optional_type()
					;
			}
		);
}

#endif
