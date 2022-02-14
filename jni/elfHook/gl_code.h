#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <stdio.h>
#include <stdlib.h>

GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);
