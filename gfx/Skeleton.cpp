#include "Skeleton.hpp"
namespace GFX {

Skeleton::Skeleton()
{

}
size_t Skeleton::getBoneCount() const
{
	return offsetMatrices.size();
}
const glm::mat4* Skeleton::getOffsetMatrices() const
{
	return offsetMatrices.data();
}
void Skeleton::setOffsetMatrix(size_t id, const glm::mat4& newMatrix)
{
	if(id < offsetMatrices.size()) offsetMatrices[id] = newMatrix;
}
void Skeleton::addOffsetMatrix(size_t id, const glm::mat4& newMatrix, bool recursive)
{
	if(id >= offsetMatrices.size()) return;
	offsetMatrices[id] += newMatrix;
	if(recursive)
	{
		auto it = connections.find(id);
		if(it != connections.end())
		{
			for(auto iter = std::begin(it->second);iter != std::end(it->second);++iter)
			{
				addOffsetMatrix(*iter,newMatrix,recursive);
			}
		}
	}
}
void Skeleton::multiplyOffsetMatrix(size_t id, const glm::mat4& newMatrix, bool recursive)
{
	if(id >= offsetMatrices.size()) return;
	offsetMatrices[id] *= newMatrix;
	if(recursive)
	{
		auto it = connections.find(id);
		if(it != connections.end())
		{
			for(auto iter = std::begin(it->second);iter != std::end(it->second);++iter)
			{
				addOffsetMatrix(*iter,newMatrix,recursive);
			}
		}
	}
}
const glm::mat4& Skeleton::getOffsetMatrix(size_t id) const
{
	assert(id < offsetMatrices.size());
	return offsetMatrices[id];
}
void Skeleton::applyToVertices(Abstract::Vertex* vertices, size_t vertexCount) const
{
	int curId = 0;
	for(auto it = std::begin(weights); it != std::end(weights);++it,++curId)
	{
		for(auto weightIt = std::begin(*it);weightIt != std::end(*it);++weightIt)
		{
			if(weightIt->first >= vertexCount) break;
			const Abstract::pVertex curVertex = &vertices[weightIt->first];
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
			if(weightIt->second > smallestWeight)
			{
				curVertex->BoneIDs[smallestId] = curId;
				curVertex->BoneWeights[smallestId] = weightIt->second;
			}
		}
	}
}
void Skeleton::importFromAiMesh(aiMesh* mesh,aiNode* rootNode)
{
	if(!mesh) return;
	if(!mesh->HasBones()) return;

	weights.resize(mesh->mNumBones);
	offsetMatrices.resize(mesh->mNumBones);
	for(unsigned int i = 0; i < mesh->mNumBones; ++i)
	{
		const aiBone* currBone = mesh->mBones[i];
		for(int x = 0; x < 4; ++x)
		{
			for(int y = 0; y < 4; ++y)
			{
				offsetMatrices[i][x][y] = currBone->mOffsetMatrix[x][y];
			}
		}
		for(unsigned int j = 0; j < currBone->mNumWeights; ++j)
		{
			weights[i].push_back(std::make_pair(currBone->mWeights[j].mVertexId,
												currBone->mWeights[j].mWeight));
		}
	}
	std::unordered_map<std::string,unsigned int> boneMap;
	for(unsigned int i = 0; i < mesh->mNumBones; ++i)
	{
		boneMap.insert(std::make_pair(std::string(mesh->mBones[i]->mName.C_Str()),
									  i));
	}
	preTraverseNode(rootNode,connections,boneMap);

}
void Skeleton::preTraverseNode(aiNode* node, BoneHierarchy &nodeMap, BoneMap& boneMap)
{
	if(!node) return;
	const std::string name(node->mName.C_Str());
	auto boneMapId = boneMap.find(name);
	if(boneMapId != boneMap.end() && node->mParent) // This is a bone!
	{
		const std::string parentName(node->mParent->mName.C_Str());
		auto parentIt = boneMap.find(parentName);
		if(parentIt != boneMap.end()) // The parent is valid!
		{
			auto parentNum = nodeMap.find(parentIt->second);
			if(parentNum == nodeMap.end())
			{
				std::vector<int> tmpvec;
				tmpvec.push_back(boneMapId->second);
				nodeMap.insert(std::make_pair(parentIt->second,
											  tmpvec));
			}
			else
			{
				parentNum->second.push_back(boneMapId->second);
			}
		}
	}
	for(unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		preTraverseNode(node->mChildren[i],nodeMap,boneMap);
	}
}

}
