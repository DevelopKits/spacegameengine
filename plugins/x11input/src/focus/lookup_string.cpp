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


#include <sge/input/exception.hpp>
#include <sge/input/focus/char_type.hpp>
#include <sge/x11input/focus/char_vector.hpp>
#include <sge/x11input/focus/looked_up_string.hpp>
#include <sge/x11input/focus/lookup_string.hpp>
#include <sge/x11input/focus/translate_event.hpp>
#include <sge/x11input/key/translate_sym.hpp>
#include <sge/x11input/xim/context.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

int
do_lookup(
	sge::x11input::xim::context const &_input_context,
	XKeyPressedEvent &_event,
	wchar_t *const _data,
	int const _size,
	KeySym &_key_sym,
	Status &_status
)
{
	return
		::XwcLookupString(
			_input_context.get(),
			&_event,
			_data,
			_size,
			&_key_sym,
			&_status
		);
}

}

sge::x11input::focus::looked_up_string
sge::x11input::focus::lookup_string(
	fcppt::log::object &_log,
	sge::x11input::xim::context const &_input_context,
	XIDeviceEvent const &_event
)
{
	// TODO: Refactor this!

	XKeyPressedEvent xev(
		sge::x11input::focus::translate_event(
			_event
		)
	);

	FCPPT_ASSERT_ERROR(
		xev.type
		==
		KeyPress
	);

	auto const get_size(
		[
			&_input_context,
			&xev
		]
		{
			Status status;

			KeySym key_sym{
				NoSymbol
			};

			// first get the size needed
			int const needed_chars{
				::do_lookup(
					_input_context,
					xev,
					nullptr,
					0,
					key_sym,
					status
				)
			};

			FCPPT_ASSERT_ERROR(
				needed_chars == 0
				||
				status == XBufferOverflow
			);

			return
				needed_chars;
		}
	);

	typedef
	fcppt::container::buffer::object<
		sge::input::focus::char_type
	>
	buffer_type;

	int const needed_chars{
		get_size()
	};

	buffer_type buffer{
		fcppt::cast::size<
			sge::x11input::focus::char_vector::size_type
		>(
			fcppt::cast::to_unsigned(
				needed_chars
			)
		)
	};

	Status status;

	KeySym key_sym{
		NoSymbol
	};

	int const chars_return(
		::do_lookup(
			_input_context,
			xev,
			buffer.write_data(),
			fcppt::cast::size<
				int
			>(
				fcppt::cast::to_signed(
					buffer.write_size()
				)
			),
			key_sym,
			status
		)
	);

	FCPPT_ASSERT_ERROR(
		chars_return >= 0
	);

	// less chars might be returned here if the locale doesn't support it
	buffer.written(
		fcppt::cast::size<
			buffer_type::size_type
		>(
			fcppt::cast::to_unsigned(
				chars_return
			)
		)
	);

	if(
		chars_return
		!=
		needed_chars
	)
	{
		FCPPT_LOG_ERROR(
			_log,
			fcppt::log::_
				<< FCPPT_TEXT("XwcLookupString mismatch of lengths!")
				FCPPT_TEXT(" This usually happens if your locale is not set.")
		);
	}

	switch(
		status
	)
	{
	case XBufferOverflow:
		throw sge::input::exception(
			FCPPT_TEXT("XwcLookupString(): XBufferOverflow!")
		);
	case XLookupChars:
		return
			sge::x11input::focus::looked_up_string(
				fcppt::container::buffer::to_raw_vector(
					std::move(
						buffer
					)
				),
				sge::input::key::code::unknown
			);
	case XLookupKeySym:
		return
			sge::x11input::focus::looked_up_string(
				sge::x11input::focus::char_vector(),
				sge::x11input::key::translate_sym(
					key_sym
				)
			);
	case XLookupBoth:
		return
			sge::x11input::focus::looked_up_string(
				fcppt::container::buffer::to_raw_vector(
					std::move(
						buffer
					)
				),
				sge::x11input::key::translate_sym(
					key_sym
				)
			);
	case XLookupNone:
		return
			sge::x11input::focus::looked_up_string(
				sge::x11input::focus::char_vector(),
				sge::input::key::code::unknown
			);
	}

	throw sge::input::exception(
		FCPPT_TEXT("XwcLookupString(): Unknown return value!")
	);
}
