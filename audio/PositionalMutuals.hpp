#ifndef POSITIONALMUTUALS_HPP
#define POSITIONALMUTUALS_HPP
#include "../abstract/Global.hpp"
#include <glm/vec3.hpp>
#include <vector>
#include <memory>
namespace Audio {

DEFINE_CLASS(Cascader)
DEFINE_CLASS(Cascaded)

class Cascader : public std::enable_shared_from_this<Cascader>
{
public:
	friend class Cascaded;
protected:
	glm::vec3 global;
	std::vector<wCascaded> cascadeds;
	void onGlobalUpdate();
public:
	virtual ~Cascader() = default;
	void addCascaded(sCascaded cascaded);
	const glm::vec3& getGlobalPosition() const;
	void setGlobalPosition(const glm::vec3& pos);
};
class Cascaded : public std::enable_shared_from_this<Cascaded>
{
public:
	friend class Cascader;
protected:
	glm::vec3 relative;
	sCascader cascader;
	virtual void onPositionChange(const glm::vec3& pos) = 0;
	void onCascade(const glm::vec3& newGlobal);
public:
	virtual ~Cascaded() = default;
	const sCascader getCascader() const;
	void setCascader(const sCascader cascader);
	const glm::vec3& getLocalPosition() const;
	void setLocalPosition(const glm::vec3& pos);

};

}
#endif // POSITIONALMUTUALS_HPP
