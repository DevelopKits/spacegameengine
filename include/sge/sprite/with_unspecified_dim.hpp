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


#ifndef SGE_SPRITE_WITH_UNSPECIFIED_DIM_HPP_INCLUDED
#define SGE_SPRITE_WITH_UNSPECIFIED_DIM_HPP_INCLUDED

#include <sge/sprite/primitives/point_size.hpp>
#include <sge/sprite/roles/point_size.hpp>
#include <majutsu/role.hpp>
#include <majutsu/composite.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace sprite
{

struct with_unspecified_dim
{
	template<
		typename Choices
	>
	struct apply
	{
		typedef majutsu::composite<
			boost::mpl::vector1<
				majutsu::role<
					typename primitives::point_size<
						typename Choices::type_choices::unit_type
					>::type,
					roles::point_size
				>
			>
		> type;
	};
};

}
}

#endif