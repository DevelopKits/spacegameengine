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


#ifndef SGE_SYSTEMS_WITH_INPUT_HPP_INCLUDED
#define SGE_SYSTEMS_WITH_INPUT_HPP_INCLUDED

#include <sge/systems/input_fwd.hpp>
#include <sge/systems/with_input_fwd.hpp>
#include <sge/systems/with_window_fwd.hpp>
#include <sge/systems/detail/input_option.hpp>
#include <fcppt/static_assert_statement.hpp>
#include <fcppt/mpl/all_of.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	typename InputOptions
>
struct with_input
{
	FCPPT_STATIC_ASSERT_STATEMENT(
		boost::mpl::is_sequence<
			InputOptions
		>::value
	);

	FCPPT_STATIC_ASSERT_STATEMENT((
		fcppt::mpl::all_of<
			InputOptions,
			boost::is_base_of<
				sge::systems::detail::input_option,
				boost::mpl::_1
			>
		>::value
	));

	typedef InputOptions options;

	typedef boost::mpl::true_ needs_init;

	typedef sge::systems::input parameter_type;

	typedef boost::mpl::vector1<
		sge::systems::with_window
	> needs_before;
};

}
}

#endif