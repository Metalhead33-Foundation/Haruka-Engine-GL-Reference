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
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void Mesh::bind()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
const GLuint& Mesh::getVAO() const
{
	return VAO;
}
const GLuint& Mesh::getVBO() const
{
	return VBO;
}
const GLuint& Mesh::getEBO() const
{
	return EBO;
}
void Mesh::setupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, GLsizei(vertices.size() * Abstract::Vertex::vertexSize()), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizei(indices.size() * sizeof(unsigned int)), indices.data(), GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getPositionOffset() ) );
	// vertex colours
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getColourOffset() ) );
	// vertex normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getNormalOffset() ) );
	// vertex texture coords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getTexCoordoffset() ) );
	// vertex tangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getTangentOffset() ) );
	// vertex bitangent
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getBitangentOffset() ) );
	// vertex bone ID
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_INT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getBoneIdOffset()));
	// vertex bone weight
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Abstract::Vertex),reinterpret_cast<void*>(Abstract::Vertex::getBoneWeightOffset()));

	glBindVertexArray(0);
	indexSize = GLsizei(indices.size());
	indices.clear();
	vertices.clear();
}
void Mesh::applySkeleton(const Abstract::Skeleton& skeleton) const
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLint size = 0;
	Abstract::pVertex vertices = reinterpret_cast<Abstract::pVertex>(glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE));
	const size_t vertexCount = size_t(size) / sizeof(Abstract::Vertex);
	std::vector<uint8_t> boneCounter(vertexCount);
	memset(boneCounter.data(),0,boneCounter.size());
	for(size_t i = 0; i < skeleton.size(); ++i)
	{
		for(auto jit = skeleton[i].weights.begin(); jit != skeleton[i].weights.end(); ++jit)
		{
			if(jit->first <= vertexCount)
			{
				if(boneCounter[jit->first] < 3)
				{
					vertices[jit->first].BoneIDs[boneCounter[jit->first]] = i;
					vertices[jit->first].BoneWeights[boneCounter[jit->first]] = jit->second;
					boneCounter[jit->first]++;
				}
			}
		}
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}
