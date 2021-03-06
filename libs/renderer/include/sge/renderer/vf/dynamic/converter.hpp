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


#ifndef SGE_RENDERER_VF_DYNAMIC_CONVERTER_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_CONVERTER_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/converter_impl_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/lock_interval_set.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class converter
{
	FCPPT_NONCOPYABLE(
		converter
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	converter(
		sge::renderer::vf::dynamic::part const &,
		sge::renderer::vf::dynamic::color_format_vector const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~converter();

	SGE_RENDERER_DETAIL_SYMBOL
	void
	lock(
		sge::renderer::vf::dynamic::locked_part const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	void
	unlock();

	SGE_RENDERER_DETAIL_SYMBOL
	void
	reset();
private:
	sge::renderer::vf::dynamic::part const &part_;

	sge::renderer::vf::dynamic::color_format_vector const accepted_formats_;

	sge::renderer::vf::dynamic::detail::lock_interval_set written_intervals_;

	typedef
	fcppt::optional::object<
		sge::renderer::vf::dynamic::locked_part
	>
	optional_locked_part;

	optional_locked_part locked_part_;

	typedef
	fcppt::unique_ptr<
		sge::renderer::vf::dynamic::detail::converter_impl
	>
	converter_unique_ptr;

	typedef
	fcppt::optional::object<
		converter_unique_ptr
	>
	optional_converter_unique_ptr;

	optional_converter_unique_ptr converter_;
};

}
}
}
}

#endif
