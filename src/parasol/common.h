#ifndef PARASOL_COMMON_H
#define PARASOL_COMMON_H

//standard
#include "string"

//library
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Parasol
{
	typedef std::string ResourceID;
	
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
	
	typedef glm::ivec4 iv4;
	typedef glm::ivec3 iv3;
	typedef glm::ivec2 iv2;
	typedef int iv1;
}

#endif
