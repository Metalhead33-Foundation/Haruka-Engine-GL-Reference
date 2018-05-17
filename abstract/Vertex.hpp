#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "Global.hpp"
#include <glm/glm.hpp>
namespace Abstract {
DEFINE_STRUCT(Vertex)
struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;

	static __enforce_inlining size_t vertexSize() { return sizeof(Vertex); }
	static __enforce_inlining size_t getPositionOffset() { return offsetof(Vertex,Position); }
	static __enforce_inlining size_t getNormalOffset() { return offsetof(Vertex,Normal); }
	static __enforce_inlining size_t getTexCoordoffset() { return offsetof(Vertex,TexCoords); }
	static __enforce_inlining size_t getTangentOffset() { return offsetof(Vertex,Tangent); }
	static __enforce_inlining size_t getBitangentOffset() { return offsetof(Vertex,Bitangent); }
};
}

#endif // VERTEX_HPP
