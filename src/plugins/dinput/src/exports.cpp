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


#include "../../../plugin.hpp"
#include "../input_system.hpp"

extern "C"
{
	void plugin_version_info(sge::plugin_info* const p)
	{
		if(!p)
			return;
		p->name = "direct input plugin";
		p->description = "";
		p->min_core_version = 0x1;
		p->plugin_version = 0x1;
		p->type = sge::PT_Input;
	}

	sge::input_system* create_input_system(const sge::window_ptr w)
	{
		ptr_cast<win32_window*>(w.get());
		sge::win32_window_ptr ww = boost::dynamic_pointer_cast<win32_window_ptr>(w);
		return new sge::dinput::input_system(w);
	}
}
