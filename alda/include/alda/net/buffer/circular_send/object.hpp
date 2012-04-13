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


#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_OBJECT_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_OBJECT_HPP_INCLUDED

#include <alda/symbol.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_send/boost_type.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_send
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef alda::net::size_type size_type;

	ALDA_SYMBOL
	explicit
	object(
		alda::net::buffer::max_size
	);

	ALDA_SYMBOL
	~object();

	ALDA_SYMBOL
	alda::net::buffer::circular_send::boost_type::const_array_range const
	send_part() const;

	ALDA_SYMBOL
	void
	erase_front(
		alda::net::buffer::circular_send::object::size_type
	);

	ALDA_SYMBOL
	bool
	empty() const;
private:
	alda::net::buffer::circular_send::boost_type impl_;
};

}
}
}
}

#endif