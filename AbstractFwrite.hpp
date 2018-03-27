#pragma once
#include <cstdint>
#include <memory>
class AbstractFwrite;
typedef std::shared_ptr<AbstractFwrite> sAbstractFwrite;
typedef AbstractFwrite* pAbstractFwrite;

class AbstractFwrite {
public:
	virtual ~AbstractFwrite() = default;
	virtual int64_t write(void* data, int64_t size) = 0;
	virtual int64_t rel_rewind(int64_t position) = 0;
	virtual int64_t abs_rewind(int64_t position) = 0;
private:

};
