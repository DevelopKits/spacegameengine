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


#include "../log.hpp"
#include <sge/log/global_context.hpp>
#include <fcppt/log/parameters/root.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sge::openal::log()
{
	static fcppt::log::object global_(
		fcppt::log::parameters::root(
			fcppt::io::clog)
		.prefix(
			FCPPT_TEXT("openal"))
		.enabled(
			true)
		.level(
			fcppt::log::level::warning)
		.context(
			sge::log::global_context())
		.create());
	return global_;
}
