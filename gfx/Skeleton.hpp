#ifndef SKELETON_HPP
#define SKELETON_HPP
#include "../abstract/Skeleton.hpp"
#include <unordered_map>
#include <assimp/scene.h>

namespace GFX {

DEFINE_CLASS(Skeleton)
class Skeleton : public Abstract::Skeleton
{
public:
	typedef std::unordered_map<std::string,unsigned int> BoneMap;
	typedef std::unordered_map<aiNode*,bool> NodeMap;
	typedef std::unordered_map<int,std::vector<int>> BoneHierarchy;
private:
	std::vector<std::vector<Abstract::VertexWeight>> weights;
	std::vector<glm::mat4> offsetMatrices;
	BoneHierarchy connections;
public:
	Skeleton();
	size_t getBoneCount() const;
	const glm::mat4* getOffsetMatrices() const;
	void setOffsetMatrix(size_t id, const glm::mat4& newMatrix);
	void addOffsetMatrix(size_t id, const glm::mat4& newMatrix, bool recursive);
	void multiplyOffsetMatrix(size_t id, const glm::mat4& newMatrix, bool recursive);
	const glm::mat4& getOffsetMatrix(size_t id) const;
	void applyToVertices(Abstract::Vertex *vertices, size_t vertexCount) const;

	void importFromAiMesh(aiMesh* mesh,aiNode* rootNode);
	static void preTraverseNode(aiNode* node, BoneHierarchy& nodeMap, BoneMap& boneMap);
};

}
#endif // SKELETON_HPP
