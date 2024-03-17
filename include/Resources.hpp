#pragma once

#include <unordered_map>
#include <string>

#include "raylib-cpp.hpp"

class Resources {
private:
    std::unordered_map<std::string, raylib::Texture2D> m_TextureRes;
    std::unordered_map<std::string, raylib::Sound> m_SoundRes;
    std::unordered_map<std::string, raylib::Music> m_MusicRes;
    std::unordered_map<std::string, raylib::Font> m_FontRes;

public:
    Resources();

    raylib::Texture2D& GetTexture(const std::string name);
    raylib::Sound& GetSound(const std::string name);
    raylib::Music& GetMusic(const std::string name);
    raylib::Font& GetFont(const std::string name);
};