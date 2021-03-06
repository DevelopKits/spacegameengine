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


#ifndef SGE_SPRITE_DETAIL_ASSIGN_POST_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_ASSIGN_POST_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/detail/config/is_intrusive.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
typename boost::enable_if<
	sge::sprite::detail::config::is_intrusive<
		Choices
	>,
	void
>::type
assign_post(
	sge::sprite::object<
		Choices
	> &_this
)
{
	_this.template get<
		sge::sprite::roles::connection
	>().get().add(
		_this
	);
}

template<
	typename Choices
>
typename boost::disable_if<
	sge::sprite::detail::config::is_intrusive<
		Choices
	>,
	void
>::type
assign_post(
	sge::sprite::object<
		Choices
	> &
)
{
}

}
}
}

#endif
