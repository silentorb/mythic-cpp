#pragma once

//#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

//#define glBindVertexArray glBindVertexArrayOES
//#define glGenVertexArrays glGenVertexArraysOES

//GL_APICALL void GL_APIENTRY glBindVertexArray (GLuint array);
//GL_APICALL void GL_APIENTRY glDeleteVertexArrays (GLsizei n, const GLuint *arrays);
//GL_APICALL void GL_APIENTRY glGenVertexArrays (GLsizei n, GLuint *arrays);
//GL_APICALL GLboolean GL_APIENTRY glIsVertexArray (GLuint array);

extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray;
extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays;