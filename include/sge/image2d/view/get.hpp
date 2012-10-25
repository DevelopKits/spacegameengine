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


#ifndef SGE_IMAGE2D_VIEW_GET_HPP_INCLUDED
#define SGE_IMAGE2D_VIEW_GET_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/object_fwd.hpp>


namespace sge
{
namespace image2d
{
namespace view
{

SGE_IMAGE2D_SYMBOL
sge::image::color::any::object const
get(
	sge::image2d::view::object const &,
	sge::image2d::dim const &
);

SGE_IMAGE2D_SYMBOL
sge::image::color::any::object const
get(
	sge::image2d::view::const_object const &,
	sge::image2d::dim const &
);

}
}
}

#endif