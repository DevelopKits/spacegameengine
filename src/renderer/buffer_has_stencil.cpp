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


#include <sge/renderer/buffer_has_stencil.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

bool
sge::renderer::buffer_has_stencil(
	renderer::depth_stencil_buffer::type const _buffer
)
{
	switch(
		_buffer
	)
	{
	case sge::renderer::depth_stencil_buffer::off:
	case sge::renderer::depth_stencil_buffer::d16:
	case sge::renderer::depth_stencil_buffer::d24:
	case sge::renderer::depth_stencil_buffer::d32:
		return false;
	case sge::renderer::depth_stencil_buffer::d24s8:
		return true;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid depth_stencil_buffer!")
	);
}