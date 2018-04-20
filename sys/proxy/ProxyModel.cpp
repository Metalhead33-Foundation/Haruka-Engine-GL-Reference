#include "ProxyModel.hpp"
#include "../GameSystem.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <sstream>

void ModelProxy::RenderMesh::draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &model) const
{
	if(shader && mesh)
	{
		mesh->draw(shader,textures,projection,view,model);
	}
}
void ModelProxy::draw(const glm::mat4 &projection, const glm::mat4 &view) const
{
	for(auto it = meshes.begin(); it != meshes.end(); ++it)
	{
		it->second.draw(projection, view, modelPosition);
	}
}
void ModelProxy::RenderMesh::attachTexture(TextureReference tex)
{
	ReadReference<TextureProxy> texture(tex);
	textures.push_back(texture->getTexture());
}
void ModelProxy::RenderMesh::detachTexture(TextureReference tex)
{
	ReadReference<TextureProxy> texture(tex);
	for(auto it = textures.begin(); it != textures.end();++it)
	{
		if( (*it) == texture->getTexture() )
		{
			textures.erase(it);
			break;
		}
	}
}
void ModelProxy::RenderMesh::attachShader(ShaderProgramReference progref)
{
	ReadReference<ShaderProgramProxy> shdr(progref);
	shader = shdr->getProgram();
}
void ModelProxy::RenderMesh::detachShader()
{
	shader = nullptr;
}


const std::string& ModelProxy::getLoadPath()
{
	return loadPath;
}
void ModelProxy::setLoadPath(const std::string& path)
{
	loadPath = path;
}
ModelProxy::ModelProxy()
	: Id("")
{
	;
}
ModelProxy::ModelProxy(const std::string& id)
	: Id(id)
{
	;
}
glm::mat4& ModelProxy::getModelPosition()
{
	return modelPosition;
}
void ModelProxy::setModelPosition(glm::mat4& npos)
{
	modelPosition = npos;
}
void ModelProxy::attachTexture(const std::string& meshKey, TextureReference tex)
{
	auto it = meshes.find(meshKey);
	if(it != meshes.end())
	{
		it->second.attachTexture(tex);
	}
}
void ModelProxy::detachTexture(const std::string& meshKey, TextureReference tex)
{
	auto it = meshes.find(meshKey);
	if(it != meshes.end())
	{
		it->second.detachTexture(tex);
	}
}
void ModelProxy::attachShader(const std::string& meshKey, ShaderProgramReference progref)
{
	auto it = meshes.find(meshKey);
	if(it != meshes.end())
	{
		it->second.attachShader(progref);
	}
}
void ModelProxy::detachShader(const std::string& meshKey)
{
	auto it = meshes.find(meshKey);
	if(it != meshes.end())
	{
		it->second.detachShader();
	}
}
void ModelManager::draw(const glm::mat4& projection, const glm::mat4& view)
{
	for(auto it = modmp.begin(); it != modmp.end(); ++it)
	{
		ReadReference<ModelProxy> model(*it);
		model->draw(projection, view);
	}
	modmp.finish();
}
ModelReference ModelManager::query(const ModelProxy& proxy)
{
	auto it = modmp.find(proxy.Id);
	ModelReference ref;
	if(it == modmp.end())
	{
		ref = ModelReference();
	}
	else
	{
		ref = it->second;
	}
	modmp.finish();
	return ref;
}
ModelReference ModelManager::commit(const ModelProxy& proxy)
{
	auto ref = modmp.getEntry(proxy.Id);
	if(ref->isInitialized()) return ref;
	std::shared_ptr<Assimp::Importer> importer = std::shared_ptr<Assimp::Importer>(new Assimp::Importer());
	importer->SetIOHandler(SYS->getModelImporter().get());
	const aiScene* scen = importer->ReadFile(proxy.loadPath,aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_PreTransformVertices |
											aiProcess_CalcTangentSpace |
											aiProcess_GenSmoothNormals |
											aiProcess_Triangulate |
											aiProcess_FixInfacingNormals |
											aiProcess_FindInvalidData |
											aiProcess_ValidateDataStructure | 0);
	if(scen) {
		pushCommand(
				[importer,ref,scen](pGameSystem sys)
			{
			const std::shared_ptr<Assimp::Importer> port = importer;
			Storage<ModelProxy> proxy = *ref;
			proxy.beginSet();
			for(unsigned int i = 0; i < scen->mNumMeshes;++i)
			{
				aiMesh* cmesh = scen->mMeshes[i];
				Abstract::sMesh mesh = AiModelFactory::buildMesh(cmesh,
									sys->getEngine()->getMeshCreator());
				if(cmesh->mName.length)
				{
					proxy->meshes.emplace(std::string(cmesh->mName.C_Str(),cmesh->mName.length), mesh);
				}
				else
				{
					proxy->meshes.emplace(std::to_string(i), mesh);
				}
			}
			proxy.endSet();
			}
		);
	}
	return ref;
}
