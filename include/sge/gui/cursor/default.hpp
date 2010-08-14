/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_CURSOR_DEFAULT_HPP_INCLUDED
#define SGE_GUI_CURSOR_DEFAULT_HPP_INCLUDED

#include <sge/gui/cursor/base.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/sprite/object.hpp>
#include <sge/gui/sprite/point.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/math/dim/basic_decl.hpp>

namespace sge
{
namespace gui
{
namespace cursor
{
class SGE_CLASS_SYMBOL default_
:
	public base
{
public:
	SGE_GUI_SYMBOL default_(
		sge::image::multi_loader &,
		sge::renderer::device_ptr
	);

	SGE_GUI_SYMBOL void pos(point const &);

	SGE_GUI_SYMBOL point const pos() const;

	SGE_GUI_SYMBOL sge::gui::sprite::object const sprite() const;

	SGE_GUI_SYMBOL void widget_z(depth_type);

	SGE_GUI_SYMBOL sge::gui::sprite::object &mutable_sprite();

	SGE_GUI_SYMBOL virtual ~default_();
private:
	sge::renderer::device_ptr const rend_;
	sge::texture::no_fragmented texture_;
	sge::gui::sprite::object sprite_;
	sge::gui::sprite::point const click_;
};
}
}
}

#endif
