#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "Global.hpp"
#include <glm/glm.hpp>
namespace Abstract {
DEFINE_STRUCT(Vertex)
struct Vertex {
	// position
	glm::vec3 Position;
	// colour
	glm::vec4 Colour;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	// bone IDs
	glm::ivec4 BoneIDs;
	// bone weights
	glm::vec4 BoneWeights;

	static __enforce_inlining size_t vertexSize() { return sizeof(Vertex); }
	static __enforce_inlining size_t getPositionOffset() { return offsetof(Vertex,Position); }
	static __enforce_inlining size_t getColourOffset() { return offsetof(Vertex,Colour); }
	static __enforce_inlining size_t getNormalOffset() { return offsetof(Vertex,Normal); }
	static __enforce_inlining size_t getTexCoordoffset() { return offsetof(Vertex,TexCoords); }
	static __enforce_inlining size_t getTangentOffset() { return offsetof(Vertex,Tangent); }
	static __enforce_inlining size_t getBitangentOffset() { return offsetof(Vertex,Bitangent); }
	static __enforce_inlining size_t getBoneIdOffset() { return offsetof(Vertex,BoneIDs); }
	static __enforce_inlining size_t getBoneWeightOffset() { return offsetof(Vertex,BoneWeights); }
};

}

#endif // VERTEX_HPP
