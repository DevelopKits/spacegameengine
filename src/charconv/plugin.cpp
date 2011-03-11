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


#include <sge/charconv/plugin.hpp>
#include <sge/charconv/system.hpp>
#include "../plugin/address_name.hpp"
#include "../plugin/instantiate_types.hpp"

sge::plugin::detail::address_name
sge::plugin::detail::traits<sge::charconv::system>::plugin_loader_name()
{
	return SGE_PLUGIN_ADDRESS_NAME("create_charconv_system");
}

sge::plugin::capabilities::type
sge::plugin::detail::traits<sge::charconv::system>::plugin_type()
{
	return capabilities::char_conv;
}

SGE_PLUGIN_INSTANTIATE_TYPES(sge::charconv::system)