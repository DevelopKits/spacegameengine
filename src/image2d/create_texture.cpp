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


#include <sge/image2d/create_texture.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::renderer::texture::planar_ptr const
sge::image2d::create_texture(
	renderer::device_ptr const _renderer,
	image2d::file_ptr const _file,
	renderer::texture::filter::object const &_filter,
	renderer::texture::address_mode2 const &_address_mode,
	renderer::resource_flags_field const &_flags
)
{
	return
		renderer::texture::create_planar_from_view(
			_renderer,
			_file->view(),
			_filter,
			_address_mode,
			_flags
		);
}

sge::renderer::texture::planar_ptr const
sge::image2d::create_texture(
	fcppt::filesystem::path const &_file,
	renderer::device_ptr const _renderer,
	image2d::multi_loader &_loader,
	renderer::texture::filter::object const &_filter,
	renderer::texture::address_mode2 const &_address_mode,
	renderer::resource_flags_field const &_flags
)
{
	return
		image2d::create_texture(
			_renderer,
			_loader.load(
				_file
			),
			_filter,
			_address_mode,
			_flags
		);
}