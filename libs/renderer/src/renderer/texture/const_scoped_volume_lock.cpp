/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image3d/tag.hpp>
#include <sge/renderer/impl/texture/instantiate_const_basic_scoped_lock.hpp>
#include <sge/renderer/texture/const_scoped_volume_lock.hpp>
#include <sge/renderer/texture/volume.hpp>


SGE_RENDERER_IMPL_TEXTURE_INSTANTIATE_CONST_BASIC_SCOPED_LOCK(
	sge::image3d::tag
);
