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


#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/all_levels.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::scenic::texture_manager::texture_manager(
	sge::renderer::device::core &_renderer,
	sge::image2d::system &_image_loader)
:
	renderer_(
		_renderer),
	image_loader_(
		_image_loader),
	path_to_texture_()
{
}

sge::renderer::texture::planar &
sge::scenic::texture_manager::texture_for_path(
	boost::filesystem::path const &_path)
{
	path_to_texture_map::iterator it =
		path_to_texture_.find(
			_path);

	if(it != path_to_texture_.end())
		return *(it->second);

	return
		*path_to_texture_.insert(
			std::make_pair(
				_path,
				sge::renderer::texture::create_planar_from_path(
					_path,
					renderer_,
					image_loader_,
					sge::renderer::texture::mipmap::all_levels(
						sge::renderer::texture::mipmap::auto_generate::yes),
					sge::renderer::resource_flags_field::null(),
					sge::renderer::texture::emulate_srgb::no))).first->second;
}

sge::scenic::texture_manager::~texture_manager()
{
}
