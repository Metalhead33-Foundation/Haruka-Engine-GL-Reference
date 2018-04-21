#include "ProxyModel.hpp"
#include "../GameSystem.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <sstream>

ModelProxy::RenderMesh::RenderMesh()
	: mesh(nullptr), shader(nullptr), textures(0)
{
	;
}
ModelProxy::RenderMesh::RenderMesh(const RenderMesh& cpy)
	: mesh(cpy.mesh), createInfo(cpy.createInfo),
	  textures(cpy.textures), shader(cpy.shader)
{
	;
}
ModelProxy::RenderMesh::RenderMesh(Abstract::sMesh nmesh)
	: mesh(nmesh), shader(nullptr), textures(0)
{
	;
}
void ModelProxy::RenderMesh::draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &model) const
{
	if(shader && mesh)
	{
		std::cout << "[SYSTEM] Drawing mesh [" << mesh.get() << "] with the shader [" << shader.get()
				  << "]." << std::endl;
		mesh->draw(shader,textures,projection,view,model);
	}
}
void ModelProxy::draw(const glm::mat4 &projection, const glm::mat4 &view) const
{
	std::cout << "[SYSTEM] Drawing model \"" << Id << "\"." << std::endl;
	for(auto it = meshes.begin(); it != meshes.end(); ++it)
	{
		it->second.draw(projection, view, modelPosition);
	}
}
void ModelProxy::RenderMesh::attachTexture(TextureReference tex)
{
	ReadReference<TextureProxy> texture(tex);
	textures.push_back(texture->getTexture());
	std::cout << "[MODELS/TEXTURES] Attached texture \"" << texture->getId() << "\" ("
			  << texture->getTexture().get() << ") to mesh." << std::endl;
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
	std::cout << "[MODELS/SHADERS] Attached shader \"" << shdr->getId() << "\" ("
			  << shader.get() << ") to mesh." << std::endl;
}
void ModelProxy::RenderMesh::detachShader()
{
	shader = nullptr;
}
void ModelProxy::RenderMesh::construct(aiMesh* rawmesh)
{
	AiModelFactory::ProcessAiMesh(createInfo,rawmesh);
}
void ModelProxy::RenderMesh::build(MeshCreator creator)
{
	mesh = creator(createInfo);
	std::cout << "Shader Address: " << shader.get() << std::endl;
	std::cout << "Texture Addresses:";
	for(auto it = textures.begin(); it != textures.end(); ++it)
		std::cout << " " << (*it).get();
}
const std::string& ModelProxy::getId() const
{
	return Id;
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
ModelProxy::ModelProxy(const ModelProxy& cpy)
	: Id(cpy.Id), loadPath(cpy.loadPath),
	  modelPosition(cpy.modelPosition),
	  meshes(cpy.meshes), isConstructed(cpy.isConstructed)
{
	;
}
ModelProxy::ModelProxy(const std::string& id)
	: Id(id), isConstructed(false)
{
	;
}
ModelProxy::ModelProxy(const std::string& id, const std::string& loadpath)
	: Id(id), isConstructed(false), loadPath(loadpath)
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
	std::cout << "[MODELS/TEXTURES] Attaching texture to " << Id << "." << meshKey << "." << std::endl;
	auto it = meshes.find(meshKey);
	if(it != meshes.end())
	{
		it->second.attachTexture(tex);
	}
	else
	{
		auto bah = meshes.emplace(meshKey, nullptr);
		if(bah.second) bah.first->second.attachTexture(tex);
	}
	std::cout << "[MODELS/TEXTURES] Attached texture to " << Id << "." << meshKey << "." << std::endl;
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
	std::cout << "[MODELS/SHADERS] Attaching shader to " << Id << "." << meshKey << "." << std::endl;
	auto it = meshes.find(meshKey);
	if(it != meshes.end())
	{
		it->second.attachShader(progref);
	}
	else
	{
		auto bah = meshes.emplace(meshKey, nullptr);
		if(bah.second) bah.first->second.attachShader(progref);
	}
	std::cout << "[MODELS/SHADERS] Attached shader to " << Id << "." << meshKey << "." << std::endl;
}
void ModelProxy::detachShader(const std::string& meshKey)
{
	auto it = meshes.find(meshKey);
	if(it != meshes.end())
	{
		it->second.detachShader();
	}
}
bool ModelProxy::constuct(Assimp::IOSystem* importer)
{
	if(isConstructed) return true;
	Assimp::Importer import;
	import.SetIOHandler(importer);
	const aiScene* scen = import.ReadFile(loadPath,aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_PreTransformVertices |
											aiProcess_CalcTangentSpace |
											aiProcess_GenSmoothNormals |
											aiProcess_Triangulate |
											aiProcess_FixInfacingNormals |
											aiProcess_FindInvalidData |
											aiProcess_ValidateDataStructure | 0);
	std::cout << "[MODELS] Loaded scene: [" << scen << "]." << std::endl;
	if(scen) {
		std::cout << "[MODELS] Model: \"" << loadPath << "\" contains " << scen->mNumMeshes << " meshes." << std::endl;
		for(unsigned int i = 0; i < scen->mNumMeshes; ++i)
		{
			// Take the mesh from Assimp
			aiMesh* cmesh = scen->mMeshes[i];
			std::string meshname;
			if(cmesh->mName.length)
				meshname = std::string(cmesh->mName.C_Str(),cmesh->mName.length);
			else
				meshname = std::to_string(i);
			std::cout << "[MODELS] Mesh name: " << meshname << std::endl;
			// Find the associated properties from the proxy, hopefully
			auto crt = meshes.find(meshname);
			// Associate the textures that are pre-set inside the proxy
			if(crt == meshes.end()) {
				auto crt2 = meshes.emplace(meshname, nullptr);
				if(crt2.second) crt = crt2.first;
				else crt = meshes.end();
			}
			if(crt != meshes.end()) crt->second.construct(cmesh);
			else std::cout << "[MODELS] Failed to load mesh!" << std::endl;
		}
	}
	isConstructed = true;
	return scen != nullptr;
}



bool ModelManager::loadModel(ModelProxy &model)
{
	return model.constuct(SYS->getModelImporter().get());
}
void ModelManager::draw(const glm::mat4& projection, const glm::mat4& view)
{
	for(auto it = modmp.begin(); it != modmp.end(); ++it)
	{
		ReadReference<ModelProxy> model(it->second);
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
ModelReference ModelManager::query(const std::string& key)
{
	auto it = modmp.find(key);
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
ModelReference ModelManager::commit(ModelProxy& proxy)
{
	auto ref = query(proxy.Id);
	if(ref) {
		//// The model is already loaded, so we just need to update the properties
		auto ref2 = modmp.getEntry(proxy.Id);
		Storage<ModelProxy> &prxy = *ref2;
		prxy.invalidate(); // Invalidate the current stored value so it locks

		// Async update the new shaders and textures
		pushCommand([proxy,ref2,this](pGameSystem sys) {
			// Get the actual rendering model
			Storage<ModelProxy> &prxy = *ref2;

			// Start setting the new properties
			prxy.beginSet();

			// Loop through all actual meshes that are rendering
			for(auto it = prxy->meshes.begin(); it != prxy->meshes.end(); it++) {
				// Find the associated properties from the proxy, hopefully
				auto crt = proxy.meshes.find(it->first);

				// If found, update the properties inside the rendering mesh
				if(crt != proxy.meshes.end()) {
					it->second.shader = crt->second.shader;
					it->second.textures = crt->second.textures;
				}
			}

			// Done setting
			prxy.endSet();
		});

		// Return the reference which points to the actual rendering Model
		return ref2;
	} else {
		//// Create a new mesh
		if(loadModel(proxy)) {
			auto ref2 = modmp.getEntry(proxy.Id);
			pushCommand( [proxy, ref2, this](pGameSystem sys) {
				// If it went ok, fill in the actual data
				Storage<ModelProxy> &prxy = *ref2;
				prxy.beginSet();
				prxy->meshes = proxy.meshes;
				for(auto it = prxy->meshes.begin(); it != prxy->meshes.end();++it) {
					it->second.build(sys->getEngine()->getMeshCreator());
				}
				std::cout << "[MODELS] Model \"" << prxy->Id << "\" initialized." << std::endl;
				prxy.endSet();
			});
			return ref2;
		}
		else return ref;
	}
}

