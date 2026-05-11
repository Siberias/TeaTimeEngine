#pragma once

#include "IGameEntity.h"

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

class IGameEntityFactory
{
public:
	~IGameEntityFactory() = default;

	virtual IGameEntityPtr Create(Json data) = 0;
};