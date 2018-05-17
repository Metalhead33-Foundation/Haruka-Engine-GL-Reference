#ifndef BONE_HPP
#define BONE_HPP
#include "Global.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

namespace Abstract {
typedef std::pair<uint32_t, float> VertexWeight;
DEFINE_STRUCT(Bone)
struct Bone {
	std::vector<VertexWeight> weights;
	glm::mat4 offsetMatrix;
};
typedef std::unordered_map<std::string,Bone> Skeleton;
typedef std::shared_ptr<Skeleton> sSkeleton;
typedef std::weak_ptr<Skeleton> wSkeleton;
}

#endif // BONE_HPP
