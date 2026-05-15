#include "Entities/EntityFactories.h"

#include <stdexcept>

#include <plog/Log.h>

#include "Entities/FPSDisplayEntity.h"
#include "Entities/TextEntity.h"
#include "Services/IFontService.h"
#include "Services/ServiceLocator.h"

IGameEntityPtr TextEntityFactory::Create(const Json& data)
{
  if (!data.contains("font") || !data["font"].is_string())
  {
    PLOG_ERROR << "TextEntityFactory: Missing or invalid 'font' parameter";
    throw std::runtime_error("TextEntityFactory: Missing or invalid 'font' "
      "parameter");
  }

  std::string fontName = data["font"];

  auto fontService = ServiceLocator::GetInstance()->GetService<IFontService>();
  if (!fontService)
  {
    PLOG_ERROR << "TextEntityFactory: FontService not available";
    throw std::runtime_error("TextEntityFactory: FontService not available to "
      "retrieve fonts");
  }

  const sf::Font& font = fontService->GetFont(fontName);

  std::string text = "";
  if (data.contains("text") && data["text"].is_string())
  {
    text = data["text"];
  }

  auto textEntity = std::make_shared<TextEntity>(font, text);
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(textEntity, data);
  return textEntity;
}

IGameEntityPtr FPSDisplayEntityFactory::Create(const Json& data)
{
  if (!data.contains("font") || !data["font"].is_string())
  {
    PLOG_ERROR << "FPSDisplayEntityFactory: Missing or invalid 'font' "
      "parameter";
    throw std::runtime_error("FPSDisplayEntityFactory: Missing or invalid "
      "'font' parameter");
  }

  std::string fontName = data["font"];

  auto fontService = ServiceLocator::GetInstance()->GetService<IFontService>();
  if (!fontService)
  {
    PLOG_ERROR << "FPSDisplayEntityFactory: FontService not available";
    throw std::runtime_error("FPSDisplayEntityFactory: FontService not "
      "available to retrieve fonts");
  }

  const sf::Font& font = fontService->GetFont(fontName);

  auto fpsDisplayEntity = std::make_shared<FPSDisplayEntity>(font, "");
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(fpsDisplayEntity, data);
  return fpsDisplayEntity;
}