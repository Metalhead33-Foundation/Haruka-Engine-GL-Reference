#ifndef ABSTRACT_SKELETON_HPP
#define ABSTRACT_SKELETON_HPP
#include "Global.hpp"
#include "Vertex.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

namespace Abstract {
typedef std::pair<uint32_t, float> VertexWeight;

DEFINE_CLASS(Skeleton)
class Skeleton
{
	public:
	virtual ~Skeleton() = default;
	virtual size_t getBoneCount() const = 0;
	virtual const glm::mat4* getOffsetMatrices() const = 0;
	virtual void setOffsetMatrix(size_t id, const glm::mat4& newMatrix) = 0;
	virtual void addOffsetMatrix(size_t id, const glm::mat4& newMatrix, bool recursive) = 0;
	virtual void multiplyOffsetMatrix(size_t id, const glm::mat4& newMatrix, bool recursive) = 0;
	virtual const glm::mat4& getOffsetMatrix(size_t id) const = 0;
	virtual void applyToVertices(Vertex* vertices, size_t vertexCount) const = 0;
};

/*typedef std::unordered_map<std::string,Bone> NamedSkeleton;
typedef std::shared_ptr<NamedSkeleton> sNamedSkeleton;
typedef std::weak_ptr<NamedSkeleton> wNamedSkeleton;*/
}

#endif // ABSTRACT_SKELETON_HPP
