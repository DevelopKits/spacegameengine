/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../handle_error.hpp"
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/device/object.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <GL/glx.h>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <fcppt/config/external_end.hpp>

sge::opencl::context::object::object(
	opencl::context::parameters const &_params)
:
	context_(0),
	error_callback_(
		_params.error_callback())
{
	cl_int error_code;

	cl_context_properties props[] =
	{
		CL_CONTEXT_PLATFORM,
		reinterpret_cast<cl_context_properties>(
			_params.platform().platform_id_),
		_params.shared_renderer()
		?
			CL_GL_CONTEXT_KHR
		:
			static_cast<cl_context_properties>(0),
		_params.shared_renderer()
		?
			reinterpret_cast<cl_context_properties>(
				glXGetCurrentContext())
		:
			static_cast<cl_context_properties>(0),
		CL_GLX_DISPLAY_KHR,
		_params.shared_renderer()
		?
			reinterpret_cast<cl_context_properties>(
				glXGetCurrentDisplay())
		:
			static_cast<cl_context_properties>(0),
		0
	};

	typedef
	fcppt::container::raw_vector<cl_device_id>
	raw_device_sequence;

	raw_device_sequence raw_devices;

	for(
		opencl::device::object_ref_sequence::const_iterator current_device =
			_params.device_refs().begin();
		current_device != _params.device_refs().end();
		++current_device)
		raw_devices.push_back(
			(*current_device)->device_id_);

	context_ =
		clCreateContext(
			props,
			static_cast<cl_uint>(
				raw_devices.size()),
			raw_devices.data(),
			&object::error_callback,
			// user data to the callback
			this,
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateContext"));
}

cl_context
sge::opencl::context::object::impl() const
{
	return context_;
}

sge::opencl::context::object::~object()
{
	if(!context_)
		return;

	cl_int const error_code =
		clReleaseContext(
			context_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseContext"));
}


void
sge::opencl::context::object::error_callback(
	char const *error_info_string,
	void const *bindata,
	size_t const size_of_bindata,
	void *user_data)
{
	opencl::context::object &ctx =
		*static_cast<opencl::context::object *>(
			user_data);
	if(ctx.error_callback_)
		ctx.error_callback_(
			opencl::error_information_string(
				error_info_string),
			opencl::binary_error_data(
				static_cast<unsigned char const *>(
					bindata),
				static_cast<unsigned char const *>(
					bindata) +
				size_of_bindata));
}