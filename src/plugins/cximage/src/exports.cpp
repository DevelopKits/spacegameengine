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
#include "../image_loader.hpp"

extern "C"
{
	void dll_version_info(sge::plugin_info* const p)
	{
		if(!p)
			return;
		p->name = "cxImage image loader plugin";
		p->description = "";
		p->min_core_version = 0x1;
		p->plugin_version = 0x1;
		p->type = sge::PT_Image;
	}

	sge::image_loader* create_pic_loader()
	{
		return new sge::cximage::image_loader();
	}
}
