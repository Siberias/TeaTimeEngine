#pragma once

#include <memory>

class IGameEntity;
using IGameEntityPtr = std::shared_ptr<IGameEntity>;

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

class IGameEntityFactory
{
public:
  virtual ~IGameEntityFactory() = default;

  virtual IGameEntityPtr Create(const Json& data) = 0;

  static void ParseAndSetCommonParams(IGameEntityPtr entity, const Json& data);
};