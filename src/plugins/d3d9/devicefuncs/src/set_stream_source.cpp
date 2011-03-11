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


#include "../set_stream_source.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void
sge::d3d9::devicefuncs::set_stream_source(
	IDirect3DDevice9 *const _device,
	renderer::vf::dynamic::part_index const _part,	
	IDirect3DVertexBuffer9 *const _buffer,
	renderer::vf::vertex_size const _stride
)
{
	if(
		_device->SetStreamSource(
			_part.get(),
			_buffer,
			0u, // offset
			static_cast<
				UINT
			>(
				_stride
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetStreamSource() failed!")
		);
}