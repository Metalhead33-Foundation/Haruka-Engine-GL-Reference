#include "PhysFsRead.hpp"

PhysFsRead::PhysFsRead(std::string& str)
	: handle(str, PhysFS::FileHandle::PHYSFS_READ)
{
	;
}
int64_t PhysFsRead::read(void* data, int64_t size)
{
	return handle.readBytes(data,size);
}
int64_t PhysFsRead::seek(int64_t position)
{
	handle.seek(position);
	return 1;
}
int64_t PhysFsRead::tell()
{
	return handle.tell();
}
int64_t PhysFsRead::size()
{
	return handle.fileLength();
}
char PhysFsRead::getc()
{
	char tmp;
	handle.readBytes(&tmp,sizeof(char));
	return tmp;
}
