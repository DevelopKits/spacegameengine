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


#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/config/media_path.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_audio_loader.hpp>
#include <sge/systems/with_audio_player.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	sge::systems::instance<
		brigand::list<
			sge::systems::with_audio_loader,
			sge::systems::with_audio_player
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::audio_player_default()
		)
		(
			sge::systems::audio_loader(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("wav")
						)
					}
				)
			)
		)
	);

	sge::audio::file_unique_ptr const file(
		sge::audio::load_exn(
			sys.audio_loader(),
			sge::config::media_path()
			/ FCPPT_TEXT("sounds")
			/ FCPPT_TEXT("ding.wav")
		)
	);

	sge::audio::buffer_unique_ptr const buffer(
		sys.audio_player().create_buffer(
			*file
		)
	);

	sge::audio::sound::base_unique_ptr const sound(
		buffer->create_nonpositional(
			sge::audio::sound::nonpositional_parameters()
		)
	);

	sound->play(
		sge::audio::sound::repeat::loop
	);

	for(;;)
		sound->update();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
