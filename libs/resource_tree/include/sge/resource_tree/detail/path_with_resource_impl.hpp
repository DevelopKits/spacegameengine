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


#ifndef SGE_RESOURCE_TREE_DETAIL_PATH_WITH_RESOURCE_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_PATH_WITH_RESOURCE_IMPL_HPP_INCLUDED

#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/path_with_resource_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename T
>
sge::resource_tree::detail::path_with_resource<
	T
>::path_with_resource(
	sge::resource_tree::path &&_path,
	T const _resource
)
:
	path_(
		std::move(
			_path
		)
	),
	resource_(
		_resource
	)
{
}

template<
	typename T
>
sge::resource_tree::path const &
sge::resource_tree::detail::path_with_resource<
	T
>::path() const
{
	return
		path_;
}

template<
	typename T
>
T const &
sge::resource_tree::detail::path_with_resource<
	T
>::resource() const
{
	return
		resource_;
}

#endif
