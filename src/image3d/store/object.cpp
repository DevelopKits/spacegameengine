/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image3d/store/element.hpp>
#include <sge/image3d/store/elements_wrapper.hpp>
#include <sge/image3d/store/object.hpp>
#include <sge/src/image/color/instantiate_format.hpp>
#include <sge/src/image/store/instantiate_object.hpp>


#define SGE_IMAGE3D_STORE_OBJECT_INSTANTIATE_ARGS ( \
	sge::image3d::store::elements_wrapper, \
	sge::image3d::store::element, \
	sge::image::color \
)

SGE_SRC_IMAGE_STORE_INSTANTIATE_OBJECT(
	SGE_IMAGE3D_STORE_OBJECT_INSTANTIATE_ARGS,
	SGE_SRC_IMAGE_COLOR_INSTANTIATE_FORMAT
);

#undef SGE_IMAGE3D_STORE_OBJECT_INSTANTIATE_ARGS
