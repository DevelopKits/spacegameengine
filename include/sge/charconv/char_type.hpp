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


#ifndef SGE_CHARCONV_CHAR_TYPE_HPP_INCLUDED
#define SGE_CHARCONV_CHAR_TYPE_HPP_INCLUDED

#include <sge/charconv/encoding.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace charconv
{

template<
	sge::charconv::encoding::type
>
struct char_type;

template<>
struct char_type<
	sge::charconv::encoding::utf8
>
{
	typedef boost::uint8_t type;
};

template<>
struct char_type<
	sge::charconv::encoding::utf16
>
{
	typedef boost::uint16_t type;
};

template<>
struct char_type<
	sge::charconv::encoding::utf32
>
{
	typedef boost::uint32_t type;
};

template<>
struct char_type<
	sge::charconv::encoding::wchar
>
{
	typedef wchar_t type;
};

}
}

#endif