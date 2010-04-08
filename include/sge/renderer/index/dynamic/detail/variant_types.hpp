/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_INDEX_DYNAMIC_DETAIL_VARIANT_TYPES_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_DETAIL_VARIANT_TYPES_HPP_INCLUDED

#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/type_traits/add_const.hpp>

namespace sge
{
namespace renderer
{
namespace index
{
namespace dynamic
{
namespace detail
{

template<
	bool IsConst
>
struct variant_types
:
boost::mpl::transform<
	boost::mpl::vector2<
		index::i16,
		index::i32
	>,
	boost::mpl::if_<
		boost::mpl::bool_<
			IsConst
		>,
		boost::mpl::lambda<
			boost::add_const<
				boost::mpl::_1
			>
		>,
		boost::mpl::identity<
			boost::mpl::_1
		>
	>
>
{};

}
}
}
}
}

#endif

