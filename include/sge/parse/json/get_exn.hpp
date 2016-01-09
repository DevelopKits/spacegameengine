/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_JSON_GET_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_GET_EXN_HPP_INCLUDED

#include <sge/parse/json/get_exn_message.hpp>
#include <sge/parse/json/detail/get_return_type.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename T,
	typename Arg
>
inline
sge::parse::json::detail::get_return_type<
	T,
	Arg
>
get_exn(
	Arg &_val
)
{
	return
		sge::parse::json::get_exn_message<
			T
		>(
			_val,
			[]{
				return
					fcppt::string{
						FCPPT_TEXT("")
					};
			}
		);
}

}
}
}

#endif
