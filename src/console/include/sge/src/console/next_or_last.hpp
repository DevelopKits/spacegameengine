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


#ifndef SGE_SRC_CONSOLE_NEXT_OR_LAST_HPP_INCLUDED
#define SGE_SRC_CONSOLE_NEXT_OR_LAST_HPP_INCLUDED

#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{
template
<
	typename It1,
	typename It2,
	typename Distance
>
It1 const
next_or_last(
	It1 it,
	It2 const last,
	Distance const u)
{
	typedef typename
	std::iterator_traits<It1>::difference_type
	difference_type;

	difference_type const d =
		std::distance(
			it,
			last);

	FCPPT_ASSERT_ERROR(
		d > static_cast<difference_type>(0));

	return
		boost::next(
			it,
			std::min(
				static_cast<difference_type>(
					u),
				d));
}
}
}

#endif
