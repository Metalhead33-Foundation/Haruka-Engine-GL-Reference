#include "GlMesh.hpp"

namespace Gl {
Abstract::sMesh Mesh::createMesh(ConstructorReference constr)
{
	return Abstract::sMesh(new Mesh(constr));
}
Mesh::Mesh(ConstructorReference constr)
{
	this->vertices = constr.vec;
	this->indices = constr.ind;
	this->textures = *(constr.tex);
	setupMesh();
}
void Mesh::draw(Abstract::sShaderProgram shader)
{
	ShaderProgram* gshdr = dynamic_cast<ShaderProgram*>(shader.get());
	if(!gshdr) return;
	uint32_t texNum = 0;
	Texture* tex;
	for(TextureIterator it = textures.begin(); it != textures.end(); ++it,++texNum)
	{
		tex = dynamic_cast<Texture*>(it->get());
		if(tex) {
			glActiveTexture(GL_TEXTURE0 + texNum); // active proper texture unit before binding
			glUniform1i(glGetUniformLocation(gshdr->getShaderID(), tex->stringizeType()), texNum);
			glBindTexture(GL_TEXTURE_2D, tex->getTextureId());
		}
	}
	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
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
	glBufferData(GL_ARRAY_BUFFER, vertices->size() * Vertex::vertexSize(), vertices->data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getPositionOffset() ) );
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getNormalOffset() ) );
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getTexCoordoffset() ) );
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getTangentOffset() ) );
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getBitangentOffset() ) );

	glBindVertexArray(0);
	vertices = 0;
	indices = 0;
}
}
