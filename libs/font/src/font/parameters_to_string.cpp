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


#include <sge/font/parameters.hpp>
#include <sge/font/parameters_to_string.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>


fcppt::string
sge::font::parameters_to_string(
	sge::font::parameters const &_parameters
)
{
	auto const default_function(
		[]{
			return
				fcppt::string{
					FCPPT_TEXT("default")
				};
		}
	);

	return
		FCPPT_TEXT("( ")
		FCPPT_TEXT("ttf_size: ")
		+
		fcppt::optional::maybe(
			_parameters.ttf_size(),
			default_function,
			[](
				sge::font::ttf_size const _ttf_size
			)
			{
				return
					fcppt::insert_to_fcppt_string(
						_ttf_size
					);
			}
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("family: ")
		+
		fcppt::optional::from(
			_parameters.family(),
			default_function
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("weight: ")
		+
		fcppt::optional::maybe(
			_parameters.weight(),
			default_function,
			[](
				sge::font::weight::unit const _weight
			)
			{
				return
					fcppt::insert_to_fcppt_string(
						_weight
					);
			}
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("italic: ")
		+
		fcppt::insert_to_fcppt_string(
			_parameters.italic()
		)
		+
		FCPPT_TEXT(" )");
}
