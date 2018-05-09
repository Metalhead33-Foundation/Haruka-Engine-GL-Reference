#pragma once
#include "../abstract/Mesh.hpp"
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

class AiModelFactory
{
public:
	typedef Abstract::Mesh::MeshCreatorFunction MeshCreator;
	typedef Abstract::Mesh::TextureVector TextureVector;
	typedef Abstract::Mesh::MeshConstructor MeshCreateInfo;
	typedef Abstract::Mesh::ConstructorArray MeshBaseMap;
	static void ProcessAiMesh(MeshCreateInfo& constr, aiMesh* mesh);
	static Abstract::sMesh buildMesh(aiMesh* mesh, MeshCreator createFunction);
	static void prepMeshHashmap(MeshBaseMap& meshmap, aiScene* scen);
};


