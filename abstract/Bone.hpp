#ifndef BONE_HPP
#define BONE_HPP
#include "Global.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

namespace Abstract {
typedef std::pair<uint32_t, float> VertexWeight;
typedef std::vector<VertexWeight> BoneWeightVector;
typedef std::shared_ptr<BoneWeightVector> sBoneWeightVector;
typedef std::weak_ptr<BoneWeightVector> wBoneWeightVector;
DEFINE_STRUCT(Bone)
struct Bone {
	std::vector<VertexWeight> weights;
	glm::mat4 offsetMatrix;
};

typedef std::vector<Bone> BoneVector;
typedef std::shared_ptr<BoneVector> sBoneVector;
typedef std::weak_ptr<BoneVector> wBoneVector;


/*typedef std::unordered_map<std::string,Bone> NamedSkeleton;
typedef std::shared_ptr<NamedSkeleton> sNamedSkeleton;
typedef std::weak_ptr<NamedSkeleton> wNamedSkeleton;*/
}

#endif // BONE_HPP
