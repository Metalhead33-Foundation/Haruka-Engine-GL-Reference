#ifndef FILEHANDLE_HPP
#define FILEHANDLE_HPP
#include <physfs.h>
#include <vector>
#include <string>
#include <cstdint>
#include <memory>
namespace PhysFS {

typedef std::vector<uint8_t> byteBuffer;
typedef std::vector<std::string> stringBuffer;

class FileHandle;
typedef std::shared_ptr<FileHandle> sFileHandle;

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
	static std::string getPrefDir(std::string& org, std::string& app);
	static std::string getWriteDir();
	static std::string getLastError();
	static void setWriteDir(std::string& newDir);
	static void addToSearchPath(std::string& newDir, std::string& mountPoint, bool appendToPath);
	static void removeFromSearchPath(std::string& oldDir);

	static stringBuffer enumerateFiles(std::string& path);
	static stringBuffer enumerateFilesFullpath(std::string& path);
	static byteBuffer loadFileIntoBuffer(std::string& path);
	static std::string stringizeFile(std::string& path);
	static PHYSFS_Stat stat(std::string& path);

	FileHandle(std::string& path,OpenMode mode);
	~FileHandle();
	static sFileHandle openRead(std::string& path);
	static sFileHandle openWrite(std::string& path);
	static sFileHandle openAppend(std::string& path);

	PHYSFS_sint64 readBytes(void * buffer, PHYSFS_uint64 len);
	PHYSFS_sint64 writeBytes(void * buffer, PHYSFS_uint64 len);
	PHYSFS_sint64 tell();
	void seek(PHYSFS_uint64 pos);
	void flush();
	PHYSFS_sint64 fileLength();
};

}
#endif // FILEHANDLE_HPP
