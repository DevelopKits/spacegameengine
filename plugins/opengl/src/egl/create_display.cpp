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


#include <sge/opengl/config.hpp>
#include <sge/opengl/egl/create_display.hpp>
#include <sge/opengl/egl/display.hpp>
#include <sge/opengl/egl/display_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/system/object.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/container/array/make.hpp>
#undef Success
#include <fcppt/either/first_success.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <vector>
#include <fcppt/config/external_end.hpp>

#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/egl/x11/display.hpp>
#include <awl/backends/x11/system/object.hpp>
#endif
#if defined(SGE_OPENGL_HAVE_WAYLAND)
#include <sge/opengl/egl/wayland/display.hpp>
#include <awl/backends/wayland/system/object.hpp>
#endif


namespace
{

// TODO: This code is pretty much the same as in sge::opengl::platform::create_system
typedef
fcppt::either::object<
	fcppt::string,
	sge::opengl::egl::display_unique_ptr
>
either_type;

typedef
fcppt::function<
	either_type ()
>
function_type;

template<
	typename Result,
	typename Arg
>
using
create_function
=
fcppt::function<
	fcppt::unique_ptr<
		Result
	>(
		fcppt::reference<
			Arg
		>
	)
>;

template<
	typename Result,
	typename Arg
>
function_type
try_create(
	awl::system::object &_awl_system,
	create_function<
		Result,
		Arg
	> const &_create
)
{
	return
		function_type{
			[
				&_awl_system,
				&_create
			]{
				return
					fcppt::either::from_optional(
						fcppt::optional::map(
							fcppt::cast::dynamic<
								Arg
							>(
								_awl_system
							),
							[
								&_create
							](
								fcppt::reference<
									Arg
								> const _system
							)
							{
								return
									fcppt::unique_ptr_to_base<
										sge::opengl::egl::display
									>(
										_create(
											_system
										)
									);
							}
						),
						[]{
							return
								fcppt::string{
									FCPPT_TEXT("Failed to convert to \"")
									+
									fcppt::type_name_from_info(
										typeid(
											Arg
										)
									)
									+
									FCPPT_TEXT('"')
								};
						}
					);
			}
		};
}

}

sge::opengl::egl::display_unique_ptr
sge::opengl::egl::create_display(
	fcppt::log::object &_log,
	awl::system::object &_awl_system
)
{
	return
		fcppt::either::to_exception(
			fcppt::either::first_success(
				fcppt::container::array::make(
#if defined(SGE_OPENGL_HAVE_X11)
					try_create(
						_awl_system,
						create_function<
							sge::opengl::egl::x11::display,
							awl::backends::x11::system::object
						>{
							[
								&_log
							](
								fcppt::reference<
									awl::backends::x11::system::object
								> const _system
							)
							{
								return
									fcppt::make_unique_ptr<
										sge::opengl::egl::x11::display
									>(
										_log,
										_system.get()
									);
							}
						}
					),
#endif
#if defined(SGE_OPENGL_HAVE_WAYLAND)
					try_create(
						_awl_system,
						create_function<
							sge::opengl::egl::wayland::display,
							awl::backends::wayland::system::object
						>{
							[
								&_log
							](
								fcppt::reference<
									awl::backends::wayland::system::object
								> const _system
							)
							{
								return
									fcppt::make_unique_ptr<
										sge::opengl::egl::wayland::display
									>(
										_log,
										_system.get()
									);
							}
						}
					),
#endif
					function_type{
						[]{
							return
								either_type{
									fcppt::string{
										FCPPT_TEXT("")
									}
								};
						}
					}
				)
			),
			[](
				std::vector<
					fcppt::string
				> const &_failures
			)
			{
				return
					sge::renderer::exception{
						FCPPT_TEXT("Cannot create any egl native displays: ")
						+
						fcppt::algorithm::join_strings(
							_failures,
							fcppt::string{
								FCPPT_TEXT(", ")
							}
						)
					};
			}
		);
}
