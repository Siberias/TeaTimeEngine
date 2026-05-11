#include "Services/ServiceLocator.h"

ServiceLocator* ServiceLocator::_instance = nullptr;

ServiceLocator::ServiceLocator()
{
	if (_instance != nullptr)
	{
		throw std::runtime_error("ServiceLocator is a singleton and an"
			" instance already exists");
	}

	_instance = this;
}