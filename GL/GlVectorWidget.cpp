#include "GlVectorWidget.hpp"
#include <cstring>
#include <glm/gtc/matrix_transform.hpp>

namespace Gl {

VectorWidget::RenderableVector::RenderableVector(RbviLayerHeader& layHead, RbviHeader& header, Abstract::sFIO readah)
{
	glGenVertexArrays(1, &imageVAO);
	glGenBuffers(1, &imageVBO);
	glGenBuffers(1, &imageEBO);
	colourA.r = float(layHead.colourA.r) / 255.0f;
	colourA.g = float(layHead.colourA.g) / 255.0f;
	colourA.b = float(layHead.colourA.b) / 255.0f;
	colourA.a = float(layHead.colourA.a) / 255.0f;
	colourB.r = float(layHead.colourB.r) / 255.0f;
	colourB.g = float(layHead.colourB.g) / 255.0f;
	colourB.b = float(layHead.colourB.b) / 255.0f;
	colourB.a = float(layHead.colourB.a) / 255.0f;
	if(layHead.colourMode == 0x10) colourCentering = true;
	else colourCentering = false;
	std::vector<glm::vec2> vertices(layHead.vertexCount);
	if(header.vectorFormat == 0x10)
	{
		std::vector<RbviVertex0x10> tempVertices(layHead.vertexCount);
		readah->read(tempVertices.data(),sizeof(RbviVertex0x10) * tempVertices.size());
		for(size_t i = 0; i < tempVertices.size();++i)
		{
			vertices[i].x = float(tempVertices[i].x) / float(header.canvasWidth);
			vertices[i].y = float(tempVertices[i].y) / float(header.canvasHeight);
		}
	}
	else
	{
		std::vector<RbviVertex0x01> tempVertices(layHead.vertexCount);
		readah->read(tempVertices.data(),sizeof(RbviVertex0x01) * tempVertices.size());
		for(size_t i = 0; i < tempVertices.size();++i)
		{
			vertices[i].x = tempVertices[i].x;
			vertices[i].y = tempVertices[i].y;
		}
	}
	std::vector<int> indices(layHead.indexCount);
	readah->read(indices.data(), indices.size() * sizeof(int));
	glBindVertexArray(imageVAO);
	glBindBuffer(GL_ARRAY_BUFFER, imageVBO);
	glBufferData(GL_ARRAY_BUFFER, GLsizei(vertices.size() * sizeof(glm::vec2)), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, imageEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizei(indices.size() * sizeof(unsigned int)), indices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,nullptr);
	glBindVertexArray(0);
	this->indices = indices.size();
}
VectorWidget::RenderableVector::~RenderableVector()
{
	glDeleteVertexArrays(1, &imageVAO);
	glDeleteBuffers(1, &imageVBO);
	glDeleteBuffers(1, &imageEBO);
}
void VectorWidget::RenderableVector::draw(Abstract::sShaderProgram prog, const glm::mat4& model, const glm::mat4& projection)
{
	prog->useShader();
	prog->setMat4("projection", projection);
	prog->setMat4("model", model);
	prog->setBool("colourCentering",colourCentering);
	prog->setVec4("colourA",colourA);
	prog->setVec4("colourB",colourB);
	std::cout << colourA.r << "-" << colourA.g << "-" << colourA.b << "-" << colourA.a << std::endl;
	std::cout << colourB.r << "-" << colourB.g << "-" << colourB.b << "-" << colourB.a << std::endl;
	glBindVertexArray(imageVAO);
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
Abstract::sVectorWidget VectorWidget::create(Abstract::sFIO readah)
{
	sVectorWidget tmp = sVectorWidget(new VectorWidget(readah));
	if(!tmp->layers.size()) return nullptr;
	else return tmp;
}
VectorWidget::VectorWidget(Abstract::sFIO readah)
{
	RbviHeader header;
	readah->read(&header,sizeof(RbviHeader));
	originalSize.x = float(header.canvasWidth);
	originalSize.y = float(header.canvasHeight);
	if(strcmp(header.magicWord,"RBVI")) return;
	std::vector<RbviLayerHeader> layerHeaders(header.layerCount);
	readah->read(layerHeaders.data(),layerHeaders.size() * sizeof(RbviLayerHeader));
	for(auto it = layerHeaders.begin(); it != layerHeaders.end(); ++it)
	{
		layers.push_back(RenderableVector(*it,header,readah));
	}
}
const glm::vec2& VectorWidget::getSize(void) const
{
	return size;
}
const glm::vec2& VectorWidget::getPos(void) const
{
	return pos;
}
float VectorWidget::getRotation(void) const
{
	return rotation;
}

void VectorWidget::setSize(const glm::vec2& nsize)
{
	size = nsize;
}
void VectorWidget::setPos(const glm::vec2& npos)
{
	pos = npos;
}
void VectorWidget::setRotation(float nrotation)
{
	rotation = nrotation;
}
void VectorWidget::draw(Abstract::sShaderProgram prog, const glm::mat4& projection)
{
	std::cout << "size: " << size.x << "x" << size.y << std::endl;
	std::cout << "pos: " << pos.x << "x" << pos.y << std::endl;
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	for(auto it = layers.begin(); it != layers.end(); ++it) it->draw(prog,model,projection);
}
void VectorWidget::defaultSize()
{
	size = originalSize;
}
void VectorWidget::scale(const glm::vec2& scaler)
{
	size *= scaler;
}
void VectorWidget::snapToWidth(float x)
{
	size.y = (size.y / size.x) * x;
	size.x = x;
}
void VectorWidget::snapToHeight(float y)
{
	size.x = (size.x / size.y) * y;
	size.y = y;
}

}
