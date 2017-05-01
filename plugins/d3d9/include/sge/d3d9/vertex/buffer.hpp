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


#ifndef SGE_D3D9_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_D3D9_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/renderer/dim1_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/lock_segment_fwd.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/dynamic/const_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/converter.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_cref.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/renderer/vf/dynamic/view_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace d3d9
{
namespace vertex
{

class buffer
:
	public sge::renderer::vertex::buffer,
	public sge::d3d9::resource
{
	FCPPT_NONCOPYABLE(
		buffer
	);
public:
	buffer(
		IDirect3DDevice9 &,
		sge::renderer::vf::dynamic::part const &,
		sge::renderer::vertex::buffer_parameters const &
	);

	~buffer()
	override;

	sge::renderer::vf::dynamic::view
	lock(
		sge::renderer::lock_segment const &,
		sge::renderer::lock_mode
	)
	override;

	sge::renderer::vf::dynamic::const_view
	lock_c(
		sge::renderer::lock_segment const &
	) const
	override;

	void
	unlock() const
	override;

	sge::renderer::dim1
	size() const
	override;

	sge::renderer::resource_flags_field
	resource_flags() const
	override;

	sge::renderer::vf::dynamic::part_cref
	format() const
	override;

	sge::renderer::vf::dynamic::part_index
	format_part_index() const
	override;

	sge::renderer::vf::dynamic::stride
	stride() const;

	IDirect3DVertexBuffer9 &
	get() const;
private:
	void
	init();

	void
	on_loss()
	override;

	void
	on_reset()
	override;

	template<
		typename View
	>
	View
	do_lock(
		sge::renderer::lock_segment const &,
		sge::renderer::lock_flags::method
	) const;

	IDirect3DDevice9 &device_;

	sge::renderer::vf::dynamic::part const format_part_;

	sge::renderer::vf::dynamic::part_index const format_part_index_;

	sge::renderer::vertex::count const size_;

	sge::renderer::resource_flags_field const resource_flags_;

	mutable sge::renderer::vf::dynamic::converter converter_;

	typedef
	fcppt::unique_ptr<
		IDirect3DVertexBuffer9,
		fcppt::com_deleter
	>
	d3d_vertex_buffer_unique_ptr;

	typedef
	fcppt::optional::object<
		d3d_vertex_buffer_unique_ptr
	>
	optional_d3d_vertex_buffer_unique_ptr;

	optional_d3d_vertex_buffer_unique_ptr buffer_;

	mutable sge::renderer::raw_pointer lock_dest_;
};

}
}
}

#endif
