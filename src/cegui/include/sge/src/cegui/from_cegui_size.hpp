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


#ifndef SGE_SRC_CEGUI_FROM_CEGUI_SIZE_HPP_INCLUDED
#define SGE_SRC_CEGUI_FROM_CEGUI_SIZE_HPP_INCLUDED

#include <fcppt/math/dim/has_dim.hpp>
#include <fcppt/math/dim/object_fwd.hpp>
#include <fcppt/math/vector/has_dim.hpp>
#include <fcppt/math/vector/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Size.h>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>



namespace sge
{
namespace cegui
{

template<
	typename Container,
	typename ValueType
>
typename
boost::enable_if
<
	boost::mpl::or_<
		fcppt::math::vector::has_dim<
			Container,
			2u
		>,
		fcppt::math::dim::has_dim<
			Container,
			2u
		>
	>,
	Container
>::type
from_cegui_size(
	CEGUI::Size<
		ValueType
	> const &_size
)
{
	return
		Container(
			static_cast<
				typename Container::value_type
			>(
				_size.d_width
			),
			static_cast<
				typename Container::value_type
			>(
				_size.d_height
			)
		);
}

}
}

#endif
