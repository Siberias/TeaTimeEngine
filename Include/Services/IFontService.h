#pragma once

#include <SFML/Graphics/Font.hpp>

class IFontService
{
public:
	virtual ~IFontService() = default;

	virtual void LoadFonts() = 0;
	virtual const sf::Font& GetFont(const std::string& fontName) const = 0;
};