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


#include <sge/console/gfx/cursor.hpp>
#include <sge/font/lit.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	console_cursor
)
{
FCPPT_PP_POP_WARNING

	sge::console::gfx::cursor c;

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("")
	);

	BOOST_REQUIRE(
		c.empty()
	);

	c.insert(
		SGE_FONT_LIT('f')
	);

	c.insert(
		SGE_FONT_LIT('o')
	);
	c.insert(
		SGE_FONT_LIT('o')
	);

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("foo_")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("foo")
	);

	c.erase_word();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("")
	);

	c.string(
		SGE_FONT_LIT("bar")
	);

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("bar_")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("bar")
	);

	c.left();
	c.left();
	c.left();
	c.left();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_ar")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("bar")
	);

	c.erase_char();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_r")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("ar")
	);

	c.erase_char();
	c.erase_char();
	c.erase_char();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("")
	);

	c.string(
		SGE_FONT_LIT("foo")
	);

	c.left();
	c.left();

	c.insert(
		SGE_FONT_LIT('b')
	);

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("fb_o")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("fboo")
	);

	c.left();

	c.insert(
		SGE_FONT_LIT('r')
	);

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("fr_oo")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("frboo")
	);

	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("frboo_")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("frboo")
	);

	c.to_start();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_rboo")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("frboo")
	);

	c.to_end();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("frboo_")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("frboo")
	);

	c.string(
		SGE_FONT_LIT("foo bar")
	);

	c.left();
	c.left();
	c.left();
	c.left();
	c.erase_word();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_bar")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT(" bar")
	);

	c.erase_word();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_bar")
	);

	BOOST_REQUIRE(
		c.string()
		==
		SGE_FONT_LIT(" bar")
	);

	c.string(
		SGE_FONT_LIT("foo")
	);

	c.left();
	c.left();

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("f_o")
	);

	c.insert(
		SGE_FONT_LIT('a')
	);

	BOOST_REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("fa_o")
	);

	// TODO: Add complete_word tests
}
