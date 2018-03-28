#include "AssimpIO.hpp"


AssimpIOStream::AssimpIOStream(PhysFS::sFileHandle nhandle)
	: handle(nhandle)
{
	;
}
AssimpIOStream::~AssimpIOStream(void)
{
	;
}
size_t AssimpIOStream::Read( void* pvBuffer, size_t pSize, size_t pCount)
{
	handle->readBytes(pvBuffer,pSize * pCount);
}
size_t AssimpIOStream::Write( const void* pvBuffer, size_t pSize, size_t pCount)
{
	return 0; // Writing not supported.
}
aiReturn AssimpIOStream::Seek( size_t pOffset, aiOrigin pOrigin)
{
	switch(pOrigin)
	{
	case aiOrigin_SET:
		handle->seek(pOffset);
		return aiReturn_SUCCESS;
		break;
	case aiOrigin_CUR:
		handle->seek(handle->tell() + pOffset);
		return aiReturn_SUCCESS;
		break;
	case aiOrigin_END:
		handle->seek(handle->fileLength() - pOffset);
		return aiReturn_SUCCESS;
		break;
	default:
		return aiReturn_FAILURE;
	};
}
size_t AssimpIOStream::Tell() const
{
	return handle->tell();
}
size_t AssimpIOStream::FileSize() const
{
	return handle->fileLength();
}
void AssimpIOStream::Flush()
{
	;
}

AssimpIOSystem::AssimpIOSystem()
{
	;
}
AssimpIOSystem::~AssimpIOSystem()
{
	;
}
bool AssimpIOSystem::Exists( const std::string& pFile) const
{
	return PHYSFS_exists(pFile.c_str());
}
char AssimpIOSystem::GetOsSeparator() const
{
	return PHYSFS_getDirSeparator()[0];
}
Assimp::IOStream* AssimpIOSystem::Open( const std::string& pFile, const std::string& pMode)
{
	if(Exists(pFile)) return new AssimpIOStream(PhysFS::FileHandle::openRead(pFile));
	else return 0;
}
void AssimpIOSystem::Close(Assimp::IOStream* pFile)
{
	delete pFile;
}
