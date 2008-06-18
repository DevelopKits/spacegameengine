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


#ifndef SGE_ATLASING_HPP_INCLUDED
#define SGE_ATLASING_HPP_INCLUDED

#include "../renderer/texture.hpp"
#include "../renderer/device.hpp"

namespace sge
{
namespace texture
{

bool need_atlasing(
	renderer::texture::size_type);

bool need_atlasing(
	const renderer::texture::dim_type&);

renderer::texture::size_type
atlased_bound(
	renderer::texture::size_type);

const renderer::texture::dim_type
atlased_bounds(
	const renderer::texture::dim_type&);

renderer::texture::size_type atlased_gap();

renderer::texture::size_type
atlased_size(
	renderer::texture::size_type,
	bool force_atlasing = false);

const renderer::texture::dim_type
atlased_size(
	const renderer::texture::dim_type&,
	bool force_atlasing = false);

const renderer::texture::dim_type
atlased_texture_dim(
	renderer::device_ptr rend);

const renderer::texture_ptr
atlased_texture(
	renderer::device_ptr rend,
	const renderer::filter_args& filter);

const renderer::lock_rect
inner_atlased_rect(
	renderer::lock_rect,
	bool need_atlasing_w,
	bool need_atlasing_h);

void atlas_w(
	renderer::texture_ptr,
	renderer::image_view const &src,
	renderer::lock_rect const &outer_area);
	
void atlas_h(
	renderer::texture_ptr,
	renderer::image_view const &src,
	renderer::lock_rect const &outer_area);

}
}

#endif
