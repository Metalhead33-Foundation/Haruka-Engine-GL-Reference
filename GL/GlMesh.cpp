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
	for(size_t i = 0; i < skeleton.size(); ++i)
	{
		const Abstract::pVertex curVertex = &vertices[skeleton[i].first];
		if(skeleton[i].first <= VBO.getVertexCount())
		{
			char smallestId = 0;
			float smallestWeight = 1.0f;
			for(char id = 0; id < 4; ++id)
			{
				if(curVertex->BoneWeights[id] < smallestWeight)
				{
					smallestId = id;
					smallestWeight = curVertex->BoneWeights[id];
				}
			}
			if(skeleton[i].second > smallestWeight)
			{
				curVertex->BoneIDs[smallestId] = i;
				curVertex->BoneWeights[smallestId] = skeleton[i].second;
			}
		}
	}
	VBO.unmapBuffer();
	VBO.unbind();
}
}
