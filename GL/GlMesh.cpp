#include "GlMesh.hpp"
#include <cstring>

namespace Gl {
Abstract::sMesh Mesh::createMesh(ConstructorReference constr)
{
	return Abstract::sMesh(new Mesh(constr));
}

Mesh::Mesh(ConstructorReference constr)
{
	this->vertices = *(constr.vec);
	this->indices = *(constr.ind);
	setupMesh();
}
Mesh::~Mesh()
{
	;
}
void Mesh::bind()
{
	VAO.bind();
	EBO.draw();
	VAO.unbind();
}
void Mesh::setupMesh()
{
	VAO.bind();
	VBO.uploadVertices(vertices);
	EBO.uploadIndices(indices);

	// set the vertex attribute pointers
	// vertex Positions - 0
	VAO.setAttribPointer(3, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getPositionOffset() ) );
	// vertex colours - 1
	VAO.setAttribPointer(4, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getColourOffset() ) );
	// vertex normals - 2
	VAO.setAttribPointer(3, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getNormalOffset() ) );
	// vertex texture coords - 3
	VAO.setAttribPointer(2, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getTexCoordoffset() ) );
	// vertex tangent - 4
	VAO.setAttribPointer(3, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getTangentOffset() ) );
	// vertex bitangent -5
	VAO.setAttribPointer(3, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getBitangentOffset() ) );
	// vertex bone ID - 6
	VAO.setAttribPointer(4, GL_INT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getBoneIdOffset()));
	// vertex bone weight -7
	VAO.setAttribPointer(4, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getBoneWeightOffset()));

	VAO.unbind();
	indices.clear();
	vertices.clear();
}
void Mesh::applySkeleton(const Abstract::BoneWeightVector &skeleton) const
{
	Abstract::pVertex vertices = reinterpret_cast<Abstract::pVertex>(VBO.mapBuffer(GL_READ_WRITE));
	std::vector<uint8_t> boneCounter(VBO.getVertexCount());
	memset(boneCounter.data(),0,boneCounter.size());
	for(size_t i = 0; i < skeleton.size(); ++i)
	{
			if(skeleton[i].first <= VBO.getVertexCount())
			{
				if(boneCounter[skeleton[i].first] < 3)
				{
					vertices[skeleton[i].first].BoneIDs[boneCounter[skeleton[i].first]] = i;
					vertices[skeleton[i].first].BoneWeights[boneCounter[skeleton[i].first]] = skeleton[i].second;
					boneCounter[skeleton[i].first]++;
				}
			}
	}
	VBO.unmapBuffer();
	VBO.unbind();
}
}
