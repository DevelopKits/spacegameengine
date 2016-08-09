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


#include <sge/log/default_parameters.hpp>
#include <sge/opencl/exception.hpp>
#include <sge/opencl/log_location.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/program/build_error.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/gcc_version_at_least.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opencl::program::object::object(
	fcppt::log::context &_log_context,
	sge::opencl::context::object &_context,
	sge::opencl::program::device_blob_map const &_blobs,
	sge::opencl::program::optional_build_parameters const &_opt_params)
:
	object(
		_log_context
	)
{
	typedef
	fcppt::container::raw_vector<unsigned char const *>
	blob_ptr_vector;

	typedef
	fcppt::container::raw_vector<size_t>
	length_vector;

	blob_ptr_vector blobs;

	blobs.reserve(
		static_cast<blob_ptr_vector::size_type>(
			_blobs.size()));

	length_vector lengths;

	lengths.reserve(
		static_cast<length_vector::size_type>(
			_blobs.size()));

	device_id_vector devices;

	devices.reserve(
		static_cast<device_id_vector::size_type>(
			_blobs.size()));

	// TODO: map
	for(
		program::device_blob_map::const_iterator current_blob =
			_blobs.begin();
		current_blob != _blobs.end();
		++current_blob)
	{
		blobs.push_back(
			&(*current_blob->second.begin()));
		lengths.push_back(
			static_cast<size_t>(
				current_blob->second.size()));
		devices.push_back(
			current_blob->first->device_id_);
	}

	FCPPT_PP_PUSH_WARNING
	#if FCPPT_CONFIG_GCC_VERSION_AT_LEAST(6,0)
	// Alignment does not matter here
	FCPPT_PP_DISABLE_GCC_WARNING(-Wignored-attributes)
	#endif

	typedef
	fcppt::container::raw_vector<
		cl_int
	>
	return_status_vector;

	FCPPT_PP_POP_WARNING

	// statuuus, with a long 'u' ;)
	return_status_vector return_status(
		static_cast<return_status_vector::size_type>(
			_blobs.size()));

	cl_int error_code;
	program_ =
		clCreateProgramWithBinary(
			_context.context_,
			static_cast<cl_uint>(
				_blobs.size()),
			devices.data(),
			lengths.data(),
			blobs.data(),
			return_status.data(),
			&error_code);

	for(
		auto const &current_return_status
		:
		return_status
	)
		opencl::impl::handle_error(
			current_return_status,
			FCPPT_TEXT("clCreateProgramWithBinary"));

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateProgramWithBinary"));

	fcppt::optional::maybe_void(
		_opt_params,
		[
			this
		](
			sge::opencl::program::build_parameters const &_params
		)
		{
			this->build(
				_params
			);
		}
	);
}

sge::opencl::program::object::object(
	fcppt::log::context &_log_context,
	sge::opencl::context::object &_context,
	sge::opencl::program::source_string_sequence const &_source_strings,
	sge::opencl::program::optional_build_parameters const &_opt_params)
:
	object(
		_log_context
	)
{
	typedef
	fcppt::container::raw_vector<char const *>
	string_ptr_vector;

	typedef
	fcppt::container::raw_vector<size_t>
	length_vector;

	string_ptr_vector strings;

	strings.reserve(
		static_cast<string_ptr_vector::size_type>(
			_source_strings.size()));

	length_vector lengths;

	lengths.reserve(
		static_cast<length_vector::size_type>(
			_source_strings.size()));

	// TODO: map
	for(
		program::source_string_sequence::const_iterator source_string =
			_source_strings.begin();
		source_string != _source_strings.end();
		++source_string)
	{
		strings.push_back(
			source_string->c_str());
		lengths.push_back(
			static_cast<size_t>(
				source_string->length()));
	}

	cl_int error_code;

	program_ =
		clCreateProgramWithSource(
			_context.context_,
			static_cast<cl_uint>(
				_source_strings.size()),
			strings.data(),
			lengths.data(),
			&error_code);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateProgramWithSource"));

	FCPPT_ASSERT_POST(
		program_,
		sge::opencl::exception);

	fcppt::optional::maybe_void(
		_opt_params,
		[
			this
		](
			sge::opencl::program::build_parameters const &_params
		)
		{
			this->build(
				_params
			);
		}
	);
}

cl_program
sge::opencl::program::object::impl() const
{
	return program_;
}

void
sge::opencl::program::object::build(
	program::build_parameters const &params)
{
	device_id_vector const devices(
		fcppt::optional::maybe(
			params.devices(),
			[
				this
			]{
				return
					this->program_devices();
			},
			[](
				sge::opencl::device::object_ref_sequence const &_devices
			)
			{
				return
					fcppt::algorithm::map<
						device_id_vector
					>(
						_devices,
						[](
							// TODO: Don't use pointers
							sge::opencl::device::object *const _device
						)
						{
							return
								_device->device_id_;
						}
					);
			}
		)
	);

	notification_callback_ =
		params.notification_callback();

	//cl_int const error_code3 =
		clBuildProgram(
			program_,
			static_cast<cl_uint>(
					devices.size()),
			devices.data(),
			params.build_options().empty()
			?
				nullptr
			:
				params.build_options().c_str(),
			params.notification_callback().has_value()
			?
				&object::notification_callback
			:
				nullptr,
			params.notification_callback().has_value()
			?
				this
			:
				nullptr
		);

	// One of the rare cases where we explicitly handle the error
//	if(error_code3 == CL_SUCCESS)
//		return;

	this->check_program_return_values();
}

sge::opencl::program::device_blob_map
sge::opencl::program::object::binaries() const
{
	// Problem with this function: We have to
	// - Query for the number of devices
	// - Query the devices themselves
	// - Resolve the device_ids to the sgeopencl device objects
	// The last step is the problem. The devices associated with a
	// program is a subset of all devices belonging to
	// the context. We'd have to query all these devices (and the
	// context). But I'm too lazy for that right now
	throw sge::opencl::exception(FCPPT_TEXT("Not supported right now"));

#if 0
	sge::opencl::program::device_blob_map result;

	cl_uint number_of_devices;

	clGetProgramInfo(
		program_,
		CL_PROGRAM_NUM_DEVICES,
		sizeof(cl_uint),
		&number_of_devices,
		0);

	device_id_vector devices;

	clGetProgramInfo(
		program_,
		CL_PROGRAM_DEVICES,
		static_cast<size_t>(
			sizeof(cl_device_id) * devices.size()),
		devices.data(),
		0);

	fcppt::container::raw_vector<size_t> sizes;

	clGetProgramInfo(
		program_,
		CL_PROGRAM_BINARY_SIZES,
		static_cast<size_t>(
			sizeof(size_t) * sizes.size()),
		sizes.data(),
		0);

	program::device_blob_map device_to_blob(
		static_cast<program::device_blob_map::size_type>(
			number_of_devices));

	for(program::device_blob_map::size_type i = 0; i < device_to_blob.size(); ++i)
		device_to_blob[i].first = devices[i];

	return result;
#endif
}

sge::opencl::program::object::~object()
{
	if(!program_)
		return;

	cl_int const error_code =
		clReleaseProgram(
			program_);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseProgram"));
}

sge::opencl::program::object::object(
	fcppt::log::context &_log_context
)
:
	log_{
		_log_context,
		sge::opencl::log_location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("program::object")
			}
		)
	},
	program_(0),
	notification_callback_()
{
}

sge::opencl::program::object::device_id_vector
sge::opencl::program::object::program_devices() const
{
	device_id_vector devices;

	// We need the device vector anyway when we handle the
	// errors, so we get it here. Hope it's not too much
	// of a performance penalty.
	cl_uint number_of_devices;

	cl_int const error_code =
		clGetProgramInfo(
			program_,
			CL_PROGRAM_NUM_DEVICES,
			sizeof(cl_uint),
			&number_of_devices,
			0);

	sge::opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clGetProgramInfo(CL_PROGRAM_NUM_DEVICES)"));

	devices.resize(
		static_cast<device_id_vector::size_type>(
			number_of_devices));

	cl_int const error_code2 =
		clGetProgramInfo(
			program_,
			CL_PROGRAM_DEVICES,
			static_cast<size_t>(
				sizeof(cl_device_id) * devices.size()),
			devices.data(),
			0);

	sge::opencl::impl::handle_error(
		error_code2,
		FCPPT_TEXT("clGetProgramInfo(CL_PROGRAM_DEVICES)"));

	return
		devices;
}

void
sge::opencl::program::object::check_program_return_values()
{
	device_id_vector const devices =
		this->program_devices();

	for(
		device_id_vector::const_iterator it =
			devices.begin();
		it != devices.end();
		++it)
	{
		cl_build_status return_status;

		cl_int const error_code4 =
			clGetProgramBuildInfo(
				program_,
				*it,
				CL_PROGRAM_BUILD_STATUS,
				sizeof(
					cl_build_status),
				&return_status,
				0);

		opencl::impl::handle_error(
			error_code4,
			FCPPT_TEXT("clGetProgramBuildInfo(Build status of a device)"));

		FCPPT_ASSERT_ERROR(
			return_status != CL_BUILD_NONE);

		// This will only be sent if we specify a callback
		FCPPT_ASSERT_ERROR(
			notification_callback_.has_value() ||
			return_status != CL_BUILD_IN_PROGRESS);

		if(return_status == CL_BUILD_SUCCESS)
			continue;

		std::size_t program_build_log_size;
		cl_int const error_code5 =
			clGetProgramBuildInfo(
				program_,
				*it,
				CL_PROGRAM_BUILD_LOG,
				0,
				0,
				&program_build_log_size);

		opencl::impl::handle_error(
			error_code5,
			FCPPT_TEXT("clGetProgramBuildInfo(Build log size)"));

		std::string build_log;
		build_log.resize(
			static_cast<std::string::size_type>(
				program_build_log_size));

		cl_int const error_code6 =
			clGetProgramBuildInfo(
				program_,
				*it,
				CL_PROGRAM_BUILD_LOG,
				program_build_log_size,
				&build_log[0],
				0);

		opencl::impl::handle_error(
			error_code6,
			FCPPT_TEXT("clGetProgramBuildInfo(Build log string)"));

		if(!build_log.empty())
		{
			// TODO: error?
			FCPPT_LOG_VERBOSE(
				log_,
				fcppt::log::_
					<< FCPPT_TEXT("Program build failed, build log:\n")
					<< fcppt::from_std_string(build_log));
		}

		/*
		if(error_code3 != CL_SUCCESS)
			throw
				program::build_error(
					fcppt::from_std_string(
						build_log));
		*/
	}
}

void
sge::opencl::program::object::notification_callback(
	cl_program,
	void *user_data)
{
	sge::opencl::program::object * const program =
		static_cast<sge::opencl::program::object *>(
			user_data);

	program->check_program_return_values();

	FCPPT_ASSERT_OPTIONAL_ERROR(
		program->notification_callback_
	)();
}
