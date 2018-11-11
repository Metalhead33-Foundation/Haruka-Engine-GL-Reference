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

}
