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


#ifndef SGE_PLUGIN_IMPL_CONTEXT_BASE_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_CONTEXT_BASE_HPP_INCLUDED

#include <sge/plugin/context_base_fwd.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/object_fwd.hpp>
#include <sge/plugin/library/object_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/weak_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{

class context_base
{
	FCPPT_NONCOPYABLE(
		context_base
	);
public:
	context_base(
		sge::plugin::optional_cache_ref const &,
		boost::filesystem::path const &
	);

	~context_base();

	SGE_PLUGIN_DETAIL_SYMBOL
	boost::filesystem::path const &
	path() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::info const &
	info() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::library::object_shared_ptr
	load();
private:
	sge::plugin::optional_cache_ref const cache_;

	boost::filesystem::path const path_;

	sge::plugin::info const info_;

	typedef
	fcppt::weak_ptr<
		sge::plugin::library::object
	>
	library_weak_ptr;

	library_weak_ptr library_ptr_;
};

}
}

#endif
