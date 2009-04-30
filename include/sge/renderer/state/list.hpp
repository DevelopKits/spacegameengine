/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_RENDERER_STATE_LIST_HPP_INCLUDED
#define SGE_RENDERER_STATE_LIST_HPP_INCLUDED

#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/state/trampoline_fwd.hpp>
#include <sge/renderer/state/any.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/export.hpp>
#include <boost/function.hpp>
#include <set>

namespace sge
{
namespace renderer
{
namespace state
{

class list {
public:
	typedef std::set<
		any,
		boost::function<
			bool(
				any const &,
				any const &
			)
		>
	> set_type;

	SGE_SYMBOL explicit list(
		any const &);
	
	SGE_SYMBOL list const operator()(
		any const &) const;

	SGE_SYMBOL void overwrite(
		any const &);

	template<
		typename T
	>
	SGE_SYMBOL T
	get() const;

	template<
		typename T,
		typename States
	>
	SGE_SYMBOL T
	get(
		trampoline<T, States> const &) const;

	SGE_SYMBOL set_type const &
	values() const;
private:
	set_type set_;
};

}
}
}

#endif
