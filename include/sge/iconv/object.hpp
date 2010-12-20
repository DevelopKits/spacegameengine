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


#ifndef SGE_ICONV_OBJECT_HPP_INCLUDED
#define SGE_ICONV_OBJECT_HPP_INCLUDED

#include <sge/iconv/encoding_string.hpp>
#include <sge/iconv/conversion_status.hpp>
#include <sge/iconv/size_type.hpp>
#include <sge/iconv/raw_pointer.hpp>
#include <sge/iconv/const_raw_pointer.hpp>
#include <sge/iconv/symbol.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace iconv
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	)
public:
	SGE_ICONV_SYMBOL
	object(
		iconv::encoding_string const &source,
		iconv::encoding_string const &dest
	);

	SGE_ICONV_SYMBOL
	~object();

	SGE_ICONV_SYMBOL
	iconv::conversion_status::type
	convert(
		iconv::const_raw_pointer &source,
		iconv::size_type &in_bytes_left,
		iconv::raw_pointer &dest,
		iconv::size_type &out_bytes_left
	);
private:
	class impl;

	fcppt::scoped_ptr<
		impl
	> impl_;
};

}
}

#endif