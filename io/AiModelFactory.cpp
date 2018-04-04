#include "AiModelFactory.hpp"

void AiModelFactory::ProcessAiMesh(MeshCreateInfo &constr, aiMesh* mesh)
{
	constr.vec = Abstract::Mesh::sVertexVector(new Abstract::Mesh::VertexVector());
	for(size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex tmp;
		tmp.Position.x = mesh->mVertices[i].x;
		tmp.Position.y = mesh->mVertices[i].y;
		tmp.Position.z = mesh->mVertices[i].z;
		tmp.Normal.x = mesh->mNormals[i].x;
		tmp.Normal.y = mesh->mNormals[i].y;
		tmp.Normal.z = mesh->mNormals[i].z;
		tmp.Tangent.x = mesh->mTangents[i].x;
		tmp.Tangent.y = mesh->mTangents[i].y;
		tmp.Tangent.z = mesh->mTangents[i].z;
		tmp.Bitangent.x = mesh->mBitangents[i].x;
		tmp.Bitangent.y = mesh->mBitangents[i].y;
		tmp.Bitangent.z = mesh->mBitangents[i].z;
		if(mesh->mTextureCoords[0])
		{
			tmp.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tmp.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else tmp.TexCoords = glm::vec2(0.0f, 0.0f);
		constr.vec->push_back(tmp);
	}
	constr.ind = Abstract::Mesh::sIndexVector(new Abstract::Mesh::IndexVector());
	for(size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace* face = &mesh->mFaces[i];
		for(size_t j = 0; j < face->mNumIndices; j++) constr.ind->push_back(face->mIndices[j]);
	}
}
Abstract::sMesh AiModelFactory::buildMesh(aiMesh* mesh,MeshCreator createFunction, TextureVector& textures)
{
	MeshCreateInfo info;
	info.tex = textures;
	ProcessAiMesh(info, mesh);
	return createFunction(info);
}
