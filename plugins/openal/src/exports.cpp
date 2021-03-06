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


#include <sge/audio/player.hpp>
#include <sge/audio/player_unique_ptr.hpp>
#include <sge/audio/player_plugin/traits.hpp>
#include <sge/openal/player.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/description.hpp>
#include <sge/plugin/flags_field.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/name.hpp>
#include <sge/plugin/version.hpp>
#include <sge/plugin/library/make_interface.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace
{

sge::plugin::info const info(
	sge::plugin::name(
		FCPPT_TEXT("openal")
	),
	sge::plugin::description(
		FCPPT_TEXT("Implements audio playback via OpenAL.")
	),
	sge::plugin::version(0x1u),
	sge::plugin::min_core_version(0x1u),
	sge::plugin::capabilities_field{
		sge::plugin::capabilities::audio_player
	},
	sge::plugin::flags_field::null()
);

sge::audio::player_unique_ptr
create_audio_player(
	fcppt::log::context &_log_context
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::player
		>(
			fcppt::make_unique_ptr<
				sge::openal::player
			>(
				_log_context
			)
		);
}

}

SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(
	info,
	(
		(
			sge::audio::player,
			create_audio_player
		)
	)
)
