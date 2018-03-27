#ifndef PHYSFSREAD_HPP
#define PHYSFSREAD_HPP
#include "AbstractFread.hpp"
#include "FileHandle.hpp"

class PhysFsRead
{
private:
	PhysFS::FileHandle handle;
public:
	PhysFsRead(std::string& str);
	virtual int64_t read(void* data, int64_t size);
	virtual int64_t seek(int64_t position);
	virtual int64_t tell();
	virtual int64_t size();
	virtual char getc();
};

#endif // PHYSFSREAD_HPP
