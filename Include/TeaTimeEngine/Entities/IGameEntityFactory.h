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
};

#define IGAMEENTITYFACTORY_SET_COMMON_PARAMS(entity, data) \
  const std::string position = "position"; \
  const std::string isEnabled = "isEnabled"; \
\
  if (data.contains(isEnabled) && data[isEnabled].is_boolean()) \
  { \
    entity->SetIsEnabled(data[isEnabled]); \
  } \
\
  if (data.contains(position) && data[position].is_object() && \
    data[position].contains("x") && data[position].contains("y") && \
    data[position]["x"].is_number() && data[position]["y"].is_number()) \
  { \
    float x = data[position]["x"]; \
    float y = data[position]["y"]; \
    entity->SetPosition(sf::Vector2f(x, y)); \
  }