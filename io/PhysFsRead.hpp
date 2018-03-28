#ifndef PHYSFSREAD_HPP
#define PHYSFSREAD_HPP
#include "../abstract/AbstractFread.hpp"
#include "FileHandle.hpp"

DEFINE_CLASS(PhysFsRead)
class PhysFsRead
{
private:
	PhysFS::FileHandle handle;
public:
	PhysFsRead(const std::string& str);
	virtual int64_t read(void* data, int64_t size);
	virtual int64_t seek(int64_t position);
	virtual int64_t tell();
	virtual int64_t size();
	virtual char getc();
};

#endif // PHYSFSREAD_HPP
