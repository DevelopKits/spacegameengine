/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_FONT_HPP_INCLUDED
#define SGE_FONT_HPP_INCLUDED

#include <cstddef>
#include "../shared_ptr.hpp"
#include "../types.hpp"
#include "font_types.hpp"
#include "font_drawer.hpp"
#include "../font/font_system.hpp"
#include "../font/font_metrics.hpp"

namespace sge
{

namespace font_align_h
{
	enum type {
		left,
		right,
		center
	};
}

namespace font_align_v
{
	enum type {
		top,
		bottom,
		center
	};
}

namespace font_flags
{
	enum type {
		none           = 0,
		no_multi_line  = 1 << 0,
		no_line_wrap   = 1 << 1,
		default_       = none
	};
}
typedef unsigned font_flag_t;

class font {
public:
	typedef font_char char_type;
	typedef string string_type;
	typedef index_buffer::size_type size_type;

	font(font_metrics_ptr metrics, font_drawer_ptr drawer);

	font_unit height() const;

	class text_size_t {
	public:
		typedef string_type::const_iterator const_iterator;

		text_size_t(font_dim sz, string_type::const_iterator end, string_type::const_iterator next_begin);

		font_dim size() const;
		const_iterator end() const;
		const_iterator next_begin() const;
	private:
		font_dim       size_;
		const_iterator end_,
		               next_begin_;
	};

	const text_size_t draw_text(const string_type& text,
	                            font_pos start_pos,
	                            font_dim max_size,
	                            font_align_h::type = font_align_h::left,
	                            font_align_v::type = font_align_v::top,
	                            font_flag_t flags = font_flags::default_) const;

	const text_size_t draw_text(const string_type& text, pos2 pos, math::dim2 max_size, screen_size_t screen_size, font_align_h::type = font_align_h::left, font_align_v::type = font_align_v::top, font_flag_t flags = font_flags::default_) const;

	const text_size_t line_width(string_type::const_iterator beg, string_type::const_iterator end, font_unit width, font_flag_t tflags) const;

	const text_size_t text_size(string_type::const_iterator beg, string_type::const_iterator end, font_dim max_size, font_flag_t flags = font_flags::default_) const;
	const text_size_t text_size(const string_type& s, font_dim max_size, font_flag_t flags = font_flags::default_) const;

	font_unit char_space(char_type ch) const;

	const font_metrics_ptr metrics() const;
	const font_drawer_ptr drawer() const;
private:
	font_metrics_ptr       metrics_;
	font_drawer_ptr        drawer_;
};

typedef shared_ptr<font> font_ptr;

}

#endif
