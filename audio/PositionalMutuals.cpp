#include "PositionalMutuals.hpp"
namespace Audio {

void Cascader::onGlobalUpdate()
{
	for(auto it = cascadeds.begin(); it != cascadeds.end();)
	{
		if(it->expired()) it = cascadeds.erase(it);
		else
		{
			auto lit = it->lock();
			lit->onCascade(global);
			++it;
		}
	}
}
const glm::vec3& Cascader::getGlobalPosition() const
{
	return global;
}
void Cascader::setGlobalPosition(const glm::vec3& pos)
{
	if(global != pos)
	{
		global = pos;
		onGlobalUpdate();
	}
}
void Cascader::addCascaded(sCascaded cascaded)
{
	if(cascaded)
	{
		cascaded->cascader = shared_from_this();
		cascadeds.push_back(cascaded);
	}
}
const sCascader Cascaded::getCascader() const
{
	return cascader;
}
void Cascaded::setCascader(const sCascader cascader)
{
	this->cascader = cascader;
	if(cascader) cascader->cascadeds.push_back(shared_from_this());
}
void Cascaded::onCascade(const glm::vec3& newGlobal)
{
	onPositionChange(newGlobal+relative);
}
const glm::vec3& Cascaded::getLocalPosition() const
{
	return relative;
}
void Cascaded::setLocalPosition(const glm::vec3& pos)
{
	if(relative != pos)
	{
		relative = pos;
		if(cascader) onPositionChange(relative + cascader->global);
		else onPositionChange(relative);
	}
}

}
