#ifndef VAST_UTIL_MATHTYPE
#define VAST_UTIL_MATHTYPE

#include "util/type.h"

#include "glm/glm.hpp"

namespace Vast
{
	typedef glm::mat4	mat4;
	typedef glm::mat3	mat3;
	typedef glm::mat2	mat2;
	typedef glm::quat	quat;
	
	typedef glm::vec4	v4;
	typedef glm::vec3	v3;
	typedef glm::vec2	v2;
	
	typedef glm::ivec4	iv4;
	typedef glm::ivec3	iv3;
	typedef glm::ivec2	iv2;
	
	typedef glm::dmat4	dmat4;
	typedef glm::dmat3	dmat3;
	typedef glm::dmat2	dmat2;
	typedef glm::dquat	dquat;
	
	typedef glm::dvec4	dv4;
	typedef glm::dvec3	dv3;
	typedef glm::dvec2	dv2;
}

#endif
