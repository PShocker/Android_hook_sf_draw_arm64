#include <stdlib.h>
#include <EGL/egl.h>

#include "tools.h"
#include "elf_reader.h"
#include "gl_code.h"
#include "draw.h"

#if defined(__arm__)
#define LIBSF_PATH "/system/lib/libsurfaceflinger.so"
#elif defined(__aarch64__)
#define LIBSF_PATH "/system/lib64/libsurfaceflinger.so"
#else
#error "unknown architecture!"
#endif

typedef EGLBoolean (*t_eglSwapBuffers_fun)(EGLDisplay dpy, EGLSurface surf);
typedef void (*t_glDrawArrays_fun)(GLenum mode, GLint first, GLsizei count);

static t_eglSwapBuffers_fun ori_eglSwapBuffers = NULL;
static t_glDrawArrays_fun ori_glDrawArrays = NULL;

GLuint gProgram;
GLuint gvPositionHandle;

char *gVertexShader =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

char *gFragmentShader =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

EGLint w, h;

static EGLBoolean new_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    LOGW("new_eglSwapBuffers()");
    if (NULL == ori_eglSwapBuffers)
    {
        LOGE("failed to get original eglSwapBuffers");
        return EGL_FALSE;
    }

    eglQuerySurface(dpy, surface, EGL_WIDTH, &w);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &h);
    // LOGD("EGL_WIDTH:%d\n",w);
    // LOGD("EGL_HEIGHT:%d\n",h);

    glUseProgram(gProgram);
    glLineWidth(2);
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    // glEnableVertexAttribArray(gvPositionHandle);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    // glDrawArrays(GL_LINE_LOOP, 0, 4);
    // drawRect(100,10,200,200);
    drawRect(0, 0, 200, 200);

    return ori_eglSwapBuffers(dpy, surface);
}

static void new_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    LOGW("new_glDrawArrays()");
    if (NULL == ori_glDrawArrays)
    {
        LOGE("failed to get original new_glDrawArrays");
        return;
    }
    return ori_glDrawArrays(mode, first, count);
}

void init_gl()
{
    gProgram = createProgram(gVertexShader, gFragmentShader);
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
}

extern "C" int hook_entry()
{
    void *start = ElfHooker::get_module_base(getpid(), LIBSF_PATH);
    if (NULL == start)
    {
        return -1;
    }

    init_gl();

    ElfReader elfReader(LIBSF_PATH, start);
    if (0 != elfReader.parse())
    {
        LOGE("failed to parse %s in %d maps at %p", LIBSF_PATH, getpid(), start);
        return -1;
    }
    elfReader.hook("eglSwapBuffers", reinterpret_cast<void *>(new_eglSwapBuffers),
                   reinterpret_cast<void **>(&ori_eglSwapBuffers));
    // elfReader.hook("glDrawArrays", reinterpret_cast<void *>(new_glDrawArrays),
    //                reinterpret_cast<void **>(&ori_glDrawArrays));
    // elfReader.dumpElfHeader();
    // elfReader.dumpProgramHeaders();
    // elfReader.dumpDynamicSegment();
    // elfReader.dumpDynamicRel();
    return 0;
}
