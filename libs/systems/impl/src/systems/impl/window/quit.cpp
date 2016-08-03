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


#include <sge/systems/impl/window/quit.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/window/event/destroy_callback.hpp>
#include <awl/window/event/destroy_fwd.hpp>
#include <awl/window/event/processor.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::systems::impl::window::quit::quit(
	sge::window::system &_system,
	sge::window::object &_window
)
:
	system_(
		_system
	),
	destroy_connection_(
		_window.awl_window_event_processor().destroy_callback(
			awl::window::event::destroy_callback{
				std::bind(
					&sge::systems::impl::window::quit::on_destroy,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}
FCPPT_PP_POP_WARNING

sge::systems::impl::window::quit::~quit()
{
}

void
sge::systems::impl::window::quit::on_destroy(
	awl::window::event::destroy const &
)
{
	system_.quit(
		awl::main::exit_success()
	);
}