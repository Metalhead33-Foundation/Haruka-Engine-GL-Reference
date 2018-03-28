#include "FileHandle.hpp"
#include <stdexcept>
#define PHYSFS_GetNonNerfedErrorCode() PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())
#define PHYSFS_EXCEPTION throw std::runtime_error(PHYSFS_GetNonNerfedErrorCode())
namespace PhysFS {


FileHandle::FileHandle(const std::string &path, OpenMode mode)
{
	switch(mode)
	{
		case PHYSFS_READ:
		{
			if(!(fhandle=PHYSFS_openRead(path.c_str())))
			PHYSFS_EXCEPTION;
			break;
		}
		case PHYSFS_APPEND:
		{
			if(!(fhandle=PHYSFS_openAppend(path.c_str())))
			PHYSFS_EXCEPTION;
			break;
		}
		case PHYSFS_WRITE:
		{
			if(!(fhandle=PHYSFS_openWrite(path.c_str())))
			PHYSFS_EXCEPTION;
			break;
		}
		default:
		{
			std::runtime_error("Invalid file-opening mode!");
			break;
		}
	};
}
FileHandle::~FileHandle()
{
	if(!PHYSFS_close(fhandle))
		PHYSFS_EXCEPTION;
}
sFileHandle FileHandle::openRead(const std::string &path)
{
	return sFileHandle(new FileHandle(path,PHYSFS_READ));
}
sFileHandle FileHandle::openWrite(const std::string &path)
{
	return sFileHandle(new FileHandle(path,PHYSFS_WRITE));
}
sFileHandle FileHandle::openAppend(const std::string &path)
{
	return sFileHandle(new FileHandle(path,PHYSFS_APPEND));
}

void FileHandle::init(const char *argv0)
{
	if(!PHYSFS_init(argv0))
		PHYSFS_EXCEPTION;
	PHYSFS_permitSymbolicLinks(true);
}
std::string FileHandle::getDirSeparator()
{
	return std::string(PHYSFS_getDirSeparator());
}
std::string FileHandle::getBaseDir()
{
	return std::string(PHYSFS_getBaseDir());
}
std::string FileHandle::getUserDir()
{
	return std::string(PHYSFS_getUserDir());
}
std::string FileHandle::getPrefDir(const std::string &org, const std::string &app)
{
	return std::string(PHYSFS_getPrefDir(org.c_str(),app.c_str()));
}
std::string FileHandle::getWriteDir()
{
	return std::string(PHYSFS_getWriteDir());
}
std::string FileHandle::getLastError()
{
	return std::string(PHYSFS_GetNonNerfedErrorCode());
}
void FileHandle::setWriteDir(const std::string &newDir)
{
	if(!PHYSFS_setWriteDir(newDir.c_str()))
		PHYSFS_EXCEPTION;
}
void FileHandle::addToSearchPath(const std::string &newDir, const std::string &mountPoint, bool appendToPath)
{
	if(!PHYSFS_mount(newDir.c_str(),mountPoint.c_str(),appendToPath))
		PHYSFS_EXCEPTION;
}
void FileHandle::removeFromSearchPath(const std::string &oldDir)
{
	if(!PHYSFS_unmount(oldDir.c_str()))
		PHYSFS_EXCEPTION;
}
PHYSFS_sint64 FileHandle::readBytes(void * buffer, PHYSFS_uint64 len)
{
	PHYSFS_sint64 temp = PHYSFS_readBytes(fhandle, buffer, len);
	if(temp == -1)
		PHYSFS_EXCEPTION;
	else return temp;

}
PHYSFS_sint64 FileHandle::writeBytes(void * buffer, PHYSFS_uint64 len)
{
	PHYSFS_sint64 temp = PHYSFS_readBytes(fhandle, buffer, len);
	if(temp == -1)
		PHYSFS_EXCEPTION;
	else return temp;
}
PHYSFS_sint64 FileHandle::tell()
{
	PHYSFS_sint64 temp = PHYSFS_tell(fhandle);
	if(temp == -1)
		PHYSFS_EXCEPTION;
	else return temp;
}
void FileHandle::seek(PHYSFS_uint64 pos)
{
	if(!PHYSFS_seek(fhandle,pos))
		PHYSFS_EXCEPTION;
}
void FileHandle::flush()
{
	if(!PHYSFS_flush(fhandle))
		PHYSFS_EXCEPTION;
}
PHYSFS_sint64 FileHandle::fileLength()
{
	return PHYSFS_fileLength(fhandle);
}

stringBuffer FileHandle::enumerateFiles(const std::string &path)
{
	stringBuffer tmp;
	char **rc = PHYSFS_enumerateFiles(path.c_str());
	char **i;
	for (i = rc; *i != NULL; i++)
		tmp.push_back(std::string(*i));
	PHYSFS_freeList(rc);
	return tmp;
}
stringBuffer FileHandle::enumerateFilesFullpath(const std::string &path)
{
	stringBuffer tmp;
	char **rc = PHYSFS_enumerateFiles(path.c_str());
	char **i;
	for (i = rc; *i != NULL; i++)
	{
		std::string tpath = path + "/" + std::string(*i);
		tmp.push_back(tpath);
	}
	PHYSFS_freeList(rc);
	return tmp;
}
byteBuffer FileHandle::loadFileIntoBuffer(const std::string &path)
{
	byteBuffer temp;
	sFileHandle tHandle = openRead(path);
	temp.resize(tHandle->fileLength());
	tHandle->readBytes(temp.data(),tHandle->fileLength());
	return temp;
}
std::string FileHandle::stringizeFile(const std::string &path)
{
	byteBuffer temp = loadFileIntoBuffer(path);
	// temp.push_back(0);
	// return std::string(reinterpret_cast<const char*>(temp.data()));
	return std::string(reinterpret_cast<const char*>(temp.data()), temp.size());
}
PHYSFS_Stat FileHandle::stat(const std::string &path)
{
	PHYSFS_Stat temp;
	if(!PHYSFS_stat(path.c_str(),&temp))
		PHYSFS_EXCEPTION;
	else return temp;
}

}
