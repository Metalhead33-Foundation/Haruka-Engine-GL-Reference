#include "AssimpIO.hpp"
#include <iostream>

AssimpIOStream::AssimpIOStream(Abstract::sFIO nhandle)
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
	return handle->read(pvBuffer,pSize * pCount);
}
size_t AssimpIOStream::Write( const void* pvBuffer, size_t pSize, size_t pCount)
{
	return handle->write(const_cast<void*>(pvBuffer), pSize * pCount);
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
		handle->seek(handle->size() - pOffset);
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
	return handle->size();
}
void AssimpIOStream::Flush()
{
	;
}

AssimpPhysFS::AssimpPhysFS()
{
	;
}
AssimpPhysFS::~AssimpPhysFS()
{
	;
}
bool AssimpPhysFS::Exists(const char *pFile) const
{
	return PHYSFS_exists(pFile);
}
char AssimpPhysFS::getOsSeparator() const
{
	return PHYSFS_getDirSeparator()[0];
}
Assimp::IOStream* AssimpPhysFS::Open(const char *pFile, const char *pMode)
{
	if(Exists(pFile))
	{
		/*Abstract::sFIO ftmp = PhysFS::FileHandle::openRead(pFile);
		sAssimpIOStream tmp = sAssimpIOStream(new AssimpIOStream(ftmp));
		streams.push_back(tmp);
		return tmp.get();*/
		Abstract::sFIO tmp = PhysFS::FileHandle::openRead(pFile);
		if(tmp)	return new AssimpIOStream(tmp);
		else return 0;
	}
	else
	{
		std::cout << "Couldn't find file!" << std::endl;
		return 0;
	}
}
void AssimpPhysFS::Close(Assimp::IOStream* pFile)
{
	/*for(streamIterator it = streams.begin(); it != streams.end(); ++it)
	{
		if(it->get() == pFile)
		{
			streams.erase(it);
			break;
		}
	}*/
	delete pFile;
}
