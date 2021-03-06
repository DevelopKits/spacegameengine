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


#ifndef SGE_WLINPUT_INITIAL_OBJECTS_HPP_INCLUDED
#define SGE_WLINPUT_INITIAL_OBJECTS_HPP_INCLUDED

#include <sge/wlinput/create_function.hpp>
#include <sge/wlinput/map.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/backends/wayland/system/seat/set.hpp>
#include <awl/backends/wayland/system/seat/shared_ptr.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace wlinput
{

template<
	typename Type,
	awl::backends::wayland::system::seat::caps Caps
>
sge::wlinput::map<
	Type
>
initial_objects(
	sge::wlinput::create_function<
		Type
	> const _create_function,
	awl::backends::wayland::system::seat::set const &_seats
)
{
	typedef
	sge::wlinput::map<
		Type
	>
	result_type;

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)

	return
		fcppt::algorithm::map_optional<
			result_type
		>(
			_seats,
			[
				&_create_function
			](
				awl::backends::wayland::system::seat::shared_ptr const &_seat
			)
			{
				return
					fcppt::optional::make_if(
						_seat->caps()
						&
						Caps,
						[
							&_create_function,
							&_seat
						]{
							typedef
							typename
							result_type::value_type
							value_type;

							return
								value_type{
									_seat->name(),
									_create_function(
										_seat->get()
									)
								};
						}
					);
			}
		);

	FCPPT_PP_POP_WARNING
}

}
}

#endif
