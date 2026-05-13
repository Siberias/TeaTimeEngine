#include "IFontService.h"

#include <string>
#include <unordered_map>

class FontService : public IFontService
{
private:
  std::unordered_map<std::string, sf::Font> _loadedFonts;

public:
  FontService();
  ~FontService();

  void LoadFonts() override;
  const sf::Font& GetFont(const std::string& fontName) const override;

private:
  void LoadFont(const std::string& fontPath);
};