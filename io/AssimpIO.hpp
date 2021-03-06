#ifndef ASSIMPIO_HPP
#define ASSIMPIO_HPP
#include <assimp/IOStream.hpp>
#include <assimp/IOSystem.hpp>
#include "../abstract/Global.hpp"
#include "PhysFsFileHandle.hpp"
#include <deque>

DEFINE_CLASS(AssimpIOStream)
DEFINE_CLASS(AssimpPhysFS)

class AssimpIOStream : public Assimp::IOStream
{
	friend class AssimpPhysFS;
private:
	const Abstract::sFIO handle;
public:
	AssimpIOStream(Abstract::sFIO nhandle);
	~AssimpIOStream(void);
	size_t Read( void* pvBuffer, size_t pSize, size_t pCount);
	size_t Write( const void* pvBuffer, size_t pSize, size_t pCount);
	aiReturn Seek( size_t pOffset, aiOrigin pOrigin);
	size_t Tell() const;
	size_t FileSize() const;
	void Flush();
};
class AssimpPhysFS : public Assimp::IOSystem
{
private:
	typedef std::deque<sAssimpIOStream> streamContainer;
	typedef streamContainer::iterator streamIterator;
	std::deque<sAssimpIOStream> streams;
public:
	AssimpPhysFS();
	~AssimpPhysFS();
	bool Exists( const char* pFile) const;
	char getOsSeparator() const;
	Assimp::IOStream* Open( const char* pFile, const char* pMode);
	void Close(Assimp::IOStream* pFile);
};



#endif // ASSIMPIO_HPP
