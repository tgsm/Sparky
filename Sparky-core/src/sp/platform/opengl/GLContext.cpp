#include "sp/sp.h"
#include "GLContext.h"

#ifdef SP_PLATFORM_WIN32
#undef NOGDI
#include <Windows.h>
#define NOGDI
#endif

#include "sp/utils/Log.h"

#include "gl.h"

namespace sp { namespace graphics { namespace API {
#ifdef SP_PLATFORM_WIN32
	static HDC hDc;
#endif
	GLContext::GLContext(WindowProperties, void* deviceContext)
	{
#ifdef SP_PLATFORM_WIN32
		hDc = GetDC((HWND)deviceContext);
		HGLRC hrc = wglCreateContext(hDc);
		if (hrc)
		{
			if (!wglMakeCurrent(hDc, hrc))
			{
				SP_ERROR("Failed setting OpenGL context!");
				SP_ASSERT(false);
			}
		}
		else
		{
			SP_ERROR("Failed creating OpenGL context!");
			SP_ASSERT(false);
		}
		if (glewInit() != GLEW_OK)
		{
			SP_FATAL("Could not initialize GLEW!");
			SP_ASSERT(false);
		}
#endif
	}

	void GLContext::Present()
	{
#ifdef SP_PLATFORM_WIN32
		SwapBuffers(hDc);
#endif
	}

} } }
