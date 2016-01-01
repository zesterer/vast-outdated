#ifndef VAST_COMMON_BASICTYPES_H
#define VAST_COMMON_BASICTYPES_H

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

typedef char int8;
typedef short int16;
typedef int int32;
typedef long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

typedef gl::GLuint glid;
typedef gl::GLenum glenum;

typedef glm::mat4 mat4;
typedef glm::mat3 mat3;
typedef glm::quat quat;

typedef glm::vec4 v4;
typedef glm::vec3 v3;
typedef glm::vec2 v2;
typedef float v1;

#endif
