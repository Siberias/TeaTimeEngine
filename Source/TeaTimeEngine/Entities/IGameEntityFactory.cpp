#include "Entities/IGameEntityFactory.h"

#include "Entities/IGameEntity.h"

void IGameEntityFactory::ParseAndSetCommonParams(IGameEntityPtr entity, 
  const nlohmann::json& data)
{
  const std::string position = "position";

  if (data.contains(position) && data[position].is_object() &&
    data[position].contains("x") && data[position].contains("y") &&
    data[position]["x"].is_number() && data[position]["y"].is_number())
  {
    float x = data[position]["x"];
    float y = data[position]["y"];
    entity->SetPosition(sf::Vector2f(x, y));
  }
}