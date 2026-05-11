#include "Services/FontService.h"

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
	_loadedFonts[fontName] = std::move(font);

	PLOG_INFO << "Loaded Font: " << fontName;
}