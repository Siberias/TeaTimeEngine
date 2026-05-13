#include "Entities/EntityFactories.h"

#include <stdexcept>

#include <plog/Log.h>

#include "Entities/TextEntity.h"
#include "Services/IFontService.h"
#include "Services/ServiceLocator.h"

IGameEntityPtr TextEntityFactory::Create(const Json& data)
{
  if (!data.contains("font") || !data["font"].is_string())
  {
    PLOG_ERROR << "TextEntityFactory: Missing or invalid 'font' parameter";
    throw std::runtime_error("TextEntityFactory: Missing or invalid 'font' parameter");
  }

  std::string fontName = data["font"];

  auto fontService = ServiceLocator::GetInstance()->GetService<IFontService>();
  if (!fontService)
  {
    PLOG_ERROR << "TextEntityFactory: FontService not available";
    throw std::runtime_error("TextEntityFactory: FontService not available to retrieve fonts");
  }

  const sf::Font& font = fontService->GetFont(fontName);

  std::string text = "";
  if (data.contains("text") && data["text"].is_string())
  {
    text = data["text"];
  }

  auto textEntity = std::make_shared<TextEntity>(font, text);
  IGameEntityFactory::ParseAndSetCommonParams(textEntity, data);
  return textEntity;
}