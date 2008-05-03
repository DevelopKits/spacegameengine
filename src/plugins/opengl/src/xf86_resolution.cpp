/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config.h>
#ifdef SGE_HAVE_X11
#include "../xf86_resolution.hpp"
#include <sge/exception.hpp>

sge::ogl::xf86_resolution::xf86_resolution(const x_display_ptr dsp, const int screen, const XF86VidModeModeInfo& new_mode, const XF86VidModeModeInfo& old_mode)
: dsp(dsp),
  screen(screen),
  old_mode(old_mode)
{
	if(XF86VidModeSwitchToMode(dsp->get(), screen, const_cast<XF86VidModeModeInfo*>(&new_mode)) == False)
		throw exception(SGE_TEXT("XF86VidModeSwitchToMode() failed!"));
	XF86VidModeSetViewPort(dsp->get(),screen,0,0);
}

sge::ogl::xf86_resolution::~xf86_resolution()
{
	XF86VidModeSwitchToMode(dsp->get(), screen, const_cast<XF86VidModeModeInfo*>(&old_mode));
}

#endif
