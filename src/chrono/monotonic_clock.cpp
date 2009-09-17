/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/chrono/monotonic_clock.hpp>
#include <sge/config.h>
#ifdef SGE_WINDOWS_PLATFORM
#include "performance_counter_time.hpp"
#elif SGE_POSIX_PLATFORM
#include "clock_gettime_impl.hpp"
#include <time.h>
#else
#error "monotonic_clock implementation missing"
#endif

sge::chrono::monotonic_clock::time_point
sge::chrono::monotonic_clock::now()
{
#ifdef SGE_WINDOWS_PLATFORM
	return performance_counter_time<
		time_point
	>();
#elif SGE_POSIX_PLATFORM
	return clock_gettime_impl<
		time_point	
	>(
		CLOCK_MONOTONIC
	);
#endif
}
