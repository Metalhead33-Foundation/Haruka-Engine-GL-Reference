#include "AiModelFactory.hpp"

void AiModelFactory::prepBone(Abstract::Bone& bone, aiBone* aibone)
{
	if(!aibone) return;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			bone.offsetMatrix[i][j] = aibone->mOffsetMatrix[i][j];
		}
	}
	bone.weights.resize(aibone->mNumWeights);
	for(size_t i = 0; i < bone.weights.size();++i)
	{
		bone.weights[i].first = aibone->mWeights[i].mVertexId;
		bone.weights[i].second = aibone->mWeights[i].mWeight;
	}
}
void AiModelFactory::ProcessAiMesh(MeshCreateInfo &constr, aiMesh* mesh)
{
	constr.vec = Abstract::Mesh::sVertexVector(new Abstract::Mesh::VertexVector());
	constr.vec->reserve(mesh->mNumVertices);
	for(size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Abstract::Vertex tmp;
		memset(&tmp,0,sizeof(Abstract::Vertex));
		tmp.Position.x = mesh->mVertices[i].x;
		tmp.Position.y = mesh->mVertices[i].y;
		tmp.Position.z = mesh->mVertices[i].z;
		if(mesh->HasNormals())
		{
			tmp.Normal.x = mesh->mNormals[i].x;
			tmp.Normal.y = mesh->mNormals[i].y;
			tmp.Normal.z = mesh->mNormals[i].z;
		}
		if(mesh->mColors[0])
		{
			tmp.Colour.r = mesh->mColors[0][i].r;
			tmp.Colour.g = mesh->mColors[0][i].g;
			tmp.Colour.b = mesh->mColors[0][i].b;
			tmp.Colour.a = mesh->mColors[0][i].a;
		}
		if(mesh->HasTangentsAndBitangents())
		{
			tmp.Tangent.x = mesh->mTangents[i].x;
			tmp.Tangent.y = mesh->mTangents[i].y;
			tmp.Tangent.z = mesh->mTangents[i].z;
			tmp.Bitangent.x = mesh->mBitangents[i].x;
			tmp.Bitangent.y = mesh->mBitangents[i].y;
			tmp.Bitangent.z = mesh->mBitangents[i].z;
		}
		if(mesh->mTextureCoords[0])
		{
			tmp.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tmp.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		constr.vec->push_back(tmp);
	}
	constr.ind = Abstract::Mesh::sIndexVector(new Abstract::Mesh::IndexVector());
	for(size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace* face = &mesh->mFaces[i];
		for(size_t j = 0; j < face->mNumIndices; j++) constr.ind->push_back(face->mIndices[j]);
	}
	if(mesh->HasBones())
	{
		constr.skl = Abstract::sSkeleton(new Abstract::BoneVector());
		for(size_t i = 0; i < mesh->mNumBones;++i)
		{
			aiBone* aibone = mesh->mBones[i];
			std::string bonename;
			if(aibone->mName.length)
				bonename = std::string(aibone->mName.C_Str(),aibone->mName.length);
			else
				bonename = std::to_string(i);
			auto it = constr.skl->emplace(bonename).first;
			prepBone(it->second,aibone);
		}
	} else constr.skl = nullptr;
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
