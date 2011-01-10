/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../system.hpp"
#include "../metrics.hpp"
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/tr1/functional.hpp>

sge::freetype::system::system(
	sge::charconv::system_ptr const _conv_system
)
:
	conv_system_(_conv_system)
{
}

sge::freetype::system::~system()
{
}

sge::font::metrics_ptr const
sge::freetype::system::create_font(
	fcppt::filesystem::path const &_font_name,
	font::size_type const _font_size
)
{
	return
		fcppt::make_shared_ptr<
			freetype::metrics
		>(
			std::tr1::ref(
				library_
			),
			conv_system_,
			_font_name,
			_font_size
		);
}
