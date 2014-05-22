#ifndef SGE_OPENGL_EGL_X11_VISUAL_HPP_INCLUDED
#define SGE_OPENGL_EGL_X11_VISUAL_HPP_INCLUDED

#include <sge/opengl/egl/visual/base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/visual/wrapped.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{
namespace x11
{

class visual
:
	public sge::opengl::egl::visual::base,
	public awl::backends::x11::visual::wrapped
{
	FCPPT_NONCOPYABLE(
		visual
	);
public:
	visual(
		awl::backends::x11::display const &,
		EGLDisplay,
		sge::renderer::pixel_format::object const &
	);

	~visual()
	override;
};

}
}
}
}

#endif
