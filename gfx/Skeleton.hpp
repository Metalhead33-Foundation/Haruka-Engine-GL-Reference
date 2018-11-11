#ifndef SKELETON_HPP
#define SKELETON_HPP
#include "../abstract/AbstractSkeleton.hpp"
#include <unordered_map>

namespace GFX {

class Skeleton : public Abstract::Skeleton
{
private:
	std::vector<std::vector<Abstract::VertexWeight>> weights;
	std::vector<glm::mat4> offsetMatrices;
	std::unordered_map<int,std::vector<int>> connections;
public:
	Skeleton();
	size_t getBoneCount() const;
	const glm::mat4* getOffsetMatrices() const;
	void setOffsetMatrix(size_t id, const glm::mat4& newMatrix);
	void addOffsetMatrix(size_t id, const glm::mat4& newMatrix, bool recursive);
	void multiplyOffsetMatrix(size_t id, const glm::mat4& newMatrix, bool recursive);
	const glm::mat4& getOffsetMatrix(size_t id) const;
	void applyToVertices(Abstract::Vertex *vertices, size_t vertexCount) const;
};

}
#endif // SKELETON_HPP
