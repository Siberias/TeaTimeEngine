#include "Services/FontService.h"

#include <filesystem>

#include <plog/Log.h>

FontService::FontService()
{
}

FontService::~FontService()
{
}

void FontService::LoadFonts()
{
  std::string fontsDirectory = "Assets/Fonts";

  if (!std::filesystem::exists(fontsDirectory))
  {
    PLOG_WARNING << "Fonts directory does not exist: " << fontsDirectory << ". Fonts will not be loaded";
    return;
  }

  for (const auto& entry : std::filesystem::directory_iterator(fontsDirectory))
  {
    if (entry.is_regular_file())
    {
      LoadFont(entry.path().string());
    }
  }
}

const sf::Font& FontService::GetFont(const std::string& fontName) const
{
  auto it = _loadedFonts.find(fontName);
  if (it == _loadedFonts.end())
  {
    throw std::runtime_error("Font not found: " + fontName);
  }
  return it->second;
}

void FontService::LoadFont(const std::string& fontPath)
{
  sf::Font font;
  if (!font.openFromFile(fontPath))
  {
    throw std::runtime_error("Failed to load font: " + fontPath);
  }

  std::string fontName = std::filesystem::path(fontPath).stem().string();
  _loadedFonts[fontName] = font;

  PLOG_INFO << "Loaded Font: " << fontName;
}