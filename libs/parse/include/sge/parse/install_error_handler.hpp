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


#ifndef SGE_PARSE_INSTALL_ERROR_HANDLER_HPP_INCLUDED
#define SGE_PARSE_INSTALL_ERROR_HANDLER_HPP_INCLUDED

#include <sge/parse/error_string.hpp>
#include <sge/parse/info_to_string.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/core/value.hpp>
#include <boost/phoenix/object/construct.hpp>
#include <boost/phoenix/operator/arithmetic.hpp>
#include <boost/phoenix/operator/self.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/nonterminal/error_handler.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{

template<
	typename Rule
>
void
install_error_handler(
	fcppt::reference<
		Rule
	> const _rule,
	fcppt::reference<
		sge::parse::optional_error_string
	> const _error_string
)
{
	boost::spirit::qi::on_error<
		boost::spirit::qi::fail
	>(
		_rule.get(),
		boost::phoenix::ref(
			_error_string.get()
		) =
			boost::phoenix::construct<
				sge::parse::optional_error_string
			>(
				boost::phoenix::construct<
					sge::parse::error_string
				>(
					boost::phoenix::val(
						FCPPT_TEXT("Parsing failed: \"")
					)
					+
					boost::phoenix::construct<
						fcppt::string
					>(
						boost::spirit::qi::labels::_3,
						boost::spirit::qi::labels::_2
					)
					+
					FCPPT_TEXT("\" - expected ")
					+
					boost::phoenix::bind(
						&sge::parse::info_to_string,
						boost::spirit::qi::labels::_4
					)
					+
					FCPPT_TEXT(" here.")
				)
			)
	);
}

}
}


#endif
