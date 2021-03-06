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


#ifndef SGE_CEGUI_IMPL_SCOPED_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_IMPL_SCOPED_SYSTEM_HPP_INCLUDED

#include <sge/cegui/impl/image_codec_fwd.hpp>
#include <sge/cegui/impl/renderer_fwd.hpp>
#include <sge/cegui/impl/resource_provider_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{

class scoped_system
{
	FCPPT_NONCOPYABLE(
		scoped_system
	);
public:
	scoped_system(
		sge::cegui::impl::renderer &,
		sge::cegui::impl::image_codec &,
		sge::cegui::impl::resource_provider &
	);

	~scoped_system();
};

}
}
}

#endif
