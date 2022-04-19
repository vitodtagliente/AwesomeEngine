#include "text_icon.h"

#include <IconsFontAwesome5.h>

std::string editor::TextIcon::folder(const std::string& name)
{
    return std::string(ICON_FA_FOLDER) + name;
}

std::string editor::TextIcon::minus(const std::string& name)
{
    return std::string(ICON_FA_MINUS) + name;
}

std::string editor::TextIcon::plus(const std::string& name)
{
    return std::string(ICON_FA_PLUS) + name;
}

std::string editor::TextIcon::save(const std::string& name)
{
    return std::string(ICON_FA_SAVE) + name;
}

std::string editor::TextIcon::search(const std::string& name)
{
    return std::string(ICON_FA_SEARCH) + name;
}

std::string editor::TextIcon::eraser(const std::string& name)
{
    return std::string(ICON_FA_ERASER) + name;
}
