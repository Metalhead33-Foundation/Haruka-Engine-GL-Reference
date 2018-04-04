#pragma once
#include "../abstract/Model.hpp"
#include <assimp/mesh.h>

class AiModelFactory
{
public:
	typedef Abstract::Mesh::MeshCreatorFunction MeshCreator;
	typedef Abstract::Mesh::TextureVector TextureVector;
	typedef Abstract::Model::EmptyModelCreator ModelCreator;
	typedef Abstract::Mesh::MeshConstructor MeshCreateInfo;
	static void ProcessAiMesh(MeshCreateInfo& constr, aiMesh* mesh);
	static Abstract::sMesh buildMesh(aiMesh* mesh,MeshCreator createFunction, TextureVector& textures);
};


