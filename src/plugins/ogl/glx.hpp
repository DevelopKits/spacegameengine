/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GLX_HPP_INCLUDED
#define SGE_GLX_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>

namespace sge
{



struct glx_current_guard : boost::noncopyable {
	glx_current_guard(Display* const d = 0) : d(d) {}
	~glx_current_guard() { if(d) glXMakeCurrent(d,None,NULL); }
	Display* d;
};

class xf86_resolution_guard : boost::noncopyable {
public:
	xf86_resolution_guard(Display* const dsp, const int screen, const XF86VidModeModeInfo& mode) : dsp(dsp), screen(screen), mode(mode) {}
	~xf86_resolution_guard() { XF86VidModeSwitchToMode(dsp,screen,const_cast<XF86VidModeModeInfo*>(&mode)); 
	}
private:
	Display* dsp;
	int screen;
	const XF86VidModeModeInfo& mode;
};

}

#endif
