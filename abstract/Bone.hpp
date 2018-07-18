#ifndef BONE_HPP
#define BONE_HPP
#include "Global.hpp"
#include "Vertex.hpp"
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
	sBoneWeightVector weights;
	int id;
	std::unordered_map<uint32_t,sBone> children;
	~Bone()
	{
		children.clear();
	}
	void applyBone(pVertex vertices, size_t vertexCount) const
	{
		for(size_t i = 0; i < weights->size(); ++i)
		{
			const Abstract::pVertex curVertex = &vertices[(*weights)[i].first];
			if((*weights)[i].first <= vertexCount)
			{
				char smallestId = 0;
				float smallestWeight = 1.0f;
				for(char vId = 0; vId < 4; ++vId)
				{
					if(curVertex->BoneWeights[vId] < smallestWeight)
					{
						smallestId = vId;
						smallestWeight = curVertex->BoneWeights[vId];
					}
				}
				if((*weights)[i].second > smallestWeight)
				{
					curVertex->BoneIDs[smallestId] = id;
					curVertex->BoneWeights[smallestId] = (*weights)[i].second;
				}
			}
		}
	}
};
DEFINE_STRUCT(Skeleton)
struct Skeleton
{
	std::vector<glm::mat4> offsetMatrices;
	std::vector<sBone> bones;
	~Skeleton()
	{
		bones.clear();
	}
	void offsetOffsetMatrix(uint32_t id, const glm::mat4& offset)
	{
		offsetMatrices[id] += offset;
		for(auto it = bones[id]->children.begin(); it != bones[id]->children.end();++it)
		{
			offsetOffsetMatrix(it->first,offset);
		}
	}
	void setOffsetMatrix(uint32_t id, const glm::mat4& offset)
	{
		const glm::mat4 diff = offset - offsetMatrices[id];
		offsetMatrices[id] = offset;
		for(auto it = bones[id]->children.begin(); it != bones[id]->children.end();++it)
		{
			offsetOffsetMatrix(it->first,diff);
		}
	}
	void applyToVertices(pVertex vertices, size_t vertexCount) const
	{
		for(auto it = bones.begin(); it != bones.end(); ++it)
		{
			(*it)->applyBone(vertices,vertexCount);
		}
	}
};

/*typedef std::unordered_map<std::string,Bone> NamedSkeleton;
typedef std::shared_ptr<NamedSkeleton> sNamedSkeleton;
typedef std::weak_ptr<NamedSkeleton> wNamedSkeleton;*/
}

#endif // BONE_HPP
