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


#include <sge/input/processor.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/cursor/relative_movement/difference.hpp>
#include <sge/input/cursor/relative_movement/event.hpp>
#include <sge/input/impl/cursor/relative_movement/detail/object.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/optional/apply.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::relative_movement::detail::object::object(
	sge::input::processor &_processor
)
:
	positions_{
		fcppt::algorithm::map<
			position_map
		>(
			_processor.cursors(),
			[](
				sge::input::cursor::shared_ptr const &_cursor
			)
			{
				return
					std::make_pair(
						_cursor,
						_cursor->position()
					);
			}
		)
	},
	connection_{
		_processor.window().event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				->
				awl::event::container
				{
					return
						this->on_event(
							_event
						);
				}
			}
		)
	}
{
}

sge::input::cursor::relative_movement::detail::object::~object()
{
}

awl::event::container
sge::input::cursor::relative_movement::detail::object::on_event(
	awl::window::event::base const &_event
)
{
	return
		fcppt::optional::to_container<
			awl::event::container
		>(
			fcppt::optional::bind(
				fcppt::cast::dynamic<
					sge::input::cursor::event::move const
				>(
					_event
				),
				[
					this
				](
					fcppt::reference<
						sge::input::cursor::event::move const
					> const _move_event
				)
				{
					return
						fcppt::optional::map(
							this->update_pos(
								_move_event.get()
							),
							[
								_move_event
							](
								sge::input::cursor::relative_movement::difference const _difference
							)
							{
								return
									fcppt::unique_ptr_to_base<
										awl::event::base
									>(
										fcppt::make_unique_ptr<
											sge::input::cursor::relative_movement::event
										>(
											_move_event.get().cursor(),
											_difference
										)
									);

							}
						);
				}
			)
		);
}

sge::input::cursor::relative_movement::detail::object::optional_difference
sge::input::cursor::relative_movement::detail::object::update_pos(
	sge::input::cursor::event::move const &_move_event
)
{
	optional_difference const difference{
		fcppt::optional::apply(
			[](
				sge::input::cursor::position const _old_pos,
				sge::input::cursor::position const _new_pos
			)
			{
				return
					sge::input::cursor::relative_movement::difference{
						_old_pos
						-
						_new_pos
					};
			},
			this->positions_[
				_move_event.cursor()
			],
			_move_event.position()
		)
	};

	this->positions_[
		_move_event.cursor()
	] =
		_move_event.position();

	return
		difference;
}
