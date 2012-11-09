/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>


sge::renderer::texture::emulate_srgb::type
sge::renderer::texture::emulate_srgb_from_caps(
	sge::renderer::caps::device const &_caps
)
{
	// TODO: We need to find a way to test this properly
	return
		_caps.srgb_framebuffer().get()
		?
			sge::renderer::texture::emulate_srgb::no
		:
			sge::renderer::texture::emulate_srgb::yes
		;
}