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
		if(mesh->HasTangentsAndBitangents())
		{
			tmp.Tangent.x = mesh->mTangents[i].x;
			tmp.Tangent.y = mesh->mTangents[i].y;
			tmp.Tangent.z = mesh->mTangents[i].z;
			tmp.Bitangent.x = mesh->mBitangents[i].x;
			tmp.Bitangent.y = mesh->mBitangents[i].y;
			tmp.Bitangent.z = mesh->mBitangents[i].z;
		}
		else
		{
			tmp.Tangent.x = 0;
			tmp.Tangent.y = 0;
			tmp.Tangent.z = 0;
			tmp.Bitangent.x = 0;
			tmp.Bitangent.y = 0;
			tmp.Bitangent.z = 0;
		}
		if(mesh->mTextureCoords[0])
		{
			tmp.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tmp.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			tmp.TexCoords.x = 0;
			tmp.TexCoords.y = 0;
		}
		constr.vec->push_back(tmp);
	}
	constr.ind = Abstract::Mesh::sIndexVector(new Abstract::Mesh::IndexVector());
	for(size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace* face = &mesh->mFaces[i];
		for(size_t j = 0; j < face->mNumIndices; j++) constr.ind->push_back(face->mIndices[j]);
	}
}
Abstract::sMesh AiModelFactory::buildMesh(aiMesh* mesh,MeshCreator createFunction)
{
	MeshCreateInfo info;
	ProcessAiMesh(info, mesh);
	return createFunction(info);
}
void AiModelFactory::prepMeshHashmap(MeshBaseMap& meshmap, aiScene* scen)
{
	if(scen) {
		for(unsigned int i = 0; i < scen->mNumMeshes; ++i)
		{
			// Take the mesh from Assimp
			aiMesh* cmesh = scen->mMeshes[i];
			std::string meshname;
			if(cmesh->mName.length)
				meshname = std::string(cmesh->mName.C_Str(),cmesh->mName.length);
			else
				meshname = std::to_string(i);
			MeshCreateInfo info;
			ProcessAiMesh(info,cmesh);
			meshmap[meshname] = info;
		}
	}
}
