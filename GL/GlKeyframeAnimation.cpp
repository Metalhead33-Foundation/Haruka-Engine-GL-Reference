#include "GlKeyframeAnimation.hpp"

namespace Gl {

KeyframeAnimation::KeyframeAnimation()
	: bound(false)
{
	glGenVertexArrays(1,&VAO);
}
KeyframeAnimation::~KeyframeAnimation()
{
	glDeleteVertexArrays(1,&VAO);
}
const KeyframeAnimation::FrameVector& KeyframeAnimation::getFrameVector() const
{
	return frames;
}
void KeyframeAnimation::bindAnimation()
{
	if(bound)
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
void KeyframeAnimation::bindFrames(size_t frame1, size_t frame2)
{
	Gl::pMesh mesh1 = dynamic_cast<Gl::pMesh>(frames[frame1].get());
	Gl::pMesh mesh2 = dynamic_cast<Gl::pMesh>(frames[frame2].get());
	if(mesh1 && mesh2)
	{
		glBindVertexArray(VAO);
		// set the vertex attribute pointers - for the first mesh
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh1->EBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh1->VBO);
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

		// set the vertex attribute pointers - for the second mesh
		glBindBuffer(GL_ARRAY_BUFFER, mesh2->VBO);
		// vertex Positions
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getPositionOffset() ) );
		// vertex normals
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getNormalOffset() ) );
		// vertex texture coords
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getTexCoordoffset() ) );
		// vertex tangent
		glEnableVertexAttribArray(8);
		glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getTangentOffset() ) );
		// vertex bitangent
		glEnableVertexAttribArray(9);
		glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),reinterpret_cast<void*>(Vertex::getBitangentOffset() ) );
		glBindVertexArray(0);
		indexSize = mesh1->indexSize;
		bound = true;
	} else bound = false;
}

}

