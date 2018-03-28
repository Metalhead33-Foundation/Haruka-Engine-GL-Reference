#ifndef FILEHANDLE_HPP
#define FILEHANDLE_HPP
#include <physfs.h>
#include <vector>
#include <string>
#include <cstdint>
#include "../abstract/Global.hpp"

namespace PhysFS {

typedef std::vector<uint8_t> byteBuffer;
typedef std::vector<std::string> stringBuffer;

DEFINE_CLASS(FileHandle)

class FileHandle
{
public:
	enum OpenMode
	{
		PHYSFS_READ,
		PHYSFS_WRITE,
		PHYSFS_APPEND
	};
private:
	PHYSFS_File* fhandle;
public:
	static void init(const char *argv0);
	static void deInit();
	static bool isInit();
	static std::string getDirSeparator();
	static std::string getBaseDir();
	static std::string getUserDir();
	static std::string getPrefDir(const std::string& org, const std::string& app);
	static std::string getWriteDir();
	static std::string getLastError();
	static void setWriteDir(const std::string& newDir);
	static void addToSearchPath(const std::string& newDir, const std::string& mountPoint, bool appendToPath);
	static void removeFromSearchPath(const std::string& oldDir);

	static stringBuffer enumerateFiles(const std::string& path);
	static stringBuffer enumerateFilesFullpath(const std::string& path);
	static byteBuffer loadFileIntoBuffer(const std::string& path);
	static std::string stringizeFile(const std::string& path);
	static PHYSFS_Stat stat(const std::string& path);

	FileHandle(const std::string& path,OpenMode mode);
	~FileHandle();
	static sFileHandle openRead(const std::string& path);
	static sFileHandle openWrite(const std::string& path);
	static sFileHandle openAppend(const std::string& path);

	PHYSFS_sint64 readBytes(void * buffer, PHYSFS_uint64 len);
	PHYSFS_sint64 writeBytes(void * buffer, PHYSFS_uint64 len);
	PHYSFS_sint64 tell();
	void seek(PHYSFS_uint64 pos);
	void flush();
	PHYSFS_sint64 fileLength();
};

}
#endif // FILEHANDLE_HPP
