#ifndef ASSIMPIO_HPP
#define ASSIMPIO_HPP
#include <assimp/IOStream.hpp>
#include <assimp/IOSystem.hpp>
#include "../abstract/Global.hpp"
#include "FileHandle.hpp"

DEFINE_CLASS(AssimpIOStream)
DEFINE_CLASS(AssimpIOSystem)

class AssimpIOStream : public Assimp::IOStream
{
	friend class AssimpIOSystem;
private:
	const PhysFS::sFileHandle handle;
public:
	AssimpIOStream(PhysFS::sFileHandle nhandle);
	~AssimpIOStream(void);
	size_t Read( void* pvBuffer, size_t pSize, size_t pCount);
	size_t Write( const void* pvBuffer, size_t pSize, size_t pCount);
	aiReturn Seek( size_t pOffset, aiOrigin pOrigin);
	size_t Tell() const;
	size_t FileSize() const;
	void Flush();
};
class AssimpIOSystem : public Assimp::IOSystem
{
public:
	AssimpIOSystem();
	~AssimpIOSystem();
	bool Exists( const std::string& pFile) const;
	char GetOsSeparator() const;
	Assimp::IOStream* Open( const std::string& pFile, const std::string& pMode);
	void Close(Assimp::IOStream* pFile);
};



#endif // ASSIMPIO_HPP
