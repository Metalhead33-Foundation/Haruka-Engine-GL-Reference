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
typedef std::vector<Bone> Skeleton;
typedef std::shared_ptr<Skeleton> sSkeleton;
typedef std::weak_ptr<Skeleton> wSkeleton;
typedef std::unordered_map<std::string,Bone> NamedSkeleton;
typedef std::shared_ptr<NamedSkeleton> sNamedSkeleton;
typedef std::weak_ptr<NamedSkeleton> wNamedSkeleton;
}

#endif // BONE_HPP
