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


#ifndef SGE_WLINPUT_CHANGE_CAPS_HPP_INCLUDED
#define SGE_WLINPUT_CHANGE_CAPS_HPP_INCLUDED

#include <sge/wlinput/create_function.hpp>
#include <sge/wlinput/map.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/caps_field.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wlinput
{

template<
	awl::backends::wayland::system::seat::caps Caps,
	typename Discover,
	typename Remove,
	typename Object
>
awl::event::optional_base_unique_ptr
change_caps(
	sge::wlinput::create_function<
		Object
	> const &_create_function,
	sge::wlinput::map<
		Object
	> &_map,
	awl::backends::wayland::system::seat::object const &_seat
)
{
	typedef
	sge::wlinput::map<
		Object
	>
	object_map;

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)

	auto const add_cap(
		[
			&_create_function,
			&_map,
			&_seat
		]()
		->
		awl::event::optional_base_unique_ptr
		{
			return
				fcppt::optional::make_if(
					_map.count(
						_seat.name()
					)
					==
					0u,
					[
						&_create_function,
						&_map,
						&_seat
					]{
						std::pair<
							typename
							object_map::iterator,
							bool
						> const result{
							_map.insert(
								std::make_pair(
									_seat.name(),
									_create_function(
										_seat.get()
									)
								)
							)
						};

						FCPPT_ASSERT_ERROR(
							result.second
						);

						return
							fcppt::unique_ptr_to_base<
								awl::event::base
							>(
								fcppt::make_unique_ptr<
									Discover
								>(
									result.first->second
								)
							);
					}
				);
		}
	);

	auto const remove_cap(
		[
			 &_map,
			 &_seat
		]()
		->
		awl::event::optional_base_unique_ptr
		{
			return
				fcppt::optional::map(
					fcppt::container::find_opt_iterator(
						_map,
						_seat.name()
					),
					[
						&_map
					](
						typename
						object_map::iterator const _iterator
					)
					{
						awl::event::base_unique_ptr result{
							fcppt::unique_ptr_to_base<
								awl::event::base
							>(
								fcppt::make_unique_ptr<
									Remove
								>(
									_iterator->second
								)
							)
						};

						_map.erase(
							_iterator
						);

						return
							result;
					}
				);
		}
	);

	FCPPT_PP_POP_WARNING

	return
		_seat.caps()
		&
		Caps
		?
			add_cap()
		:
			remove_cap()
		;
}

}
}

#endif
