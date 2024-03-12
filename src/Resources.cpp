#include "Resources.hpp"

Resources::Resources() :
    m_TextureRes(),
    m_SoundRes(),
    m_FontRes() {
        m_TextureRes.emplace("raylib", raylib::Texture2D("../res/raylib-cpp_256x256.png"));
        m_TextureRes.emplace("EasterHunt_Background1", raylib::Texture2D("../res/txt/EasterHunt_Background1.png"));
        m_TextureRes.emplace("EasterHunt_BrokenEgg", raylib::Texture2D("../res/txt/EasterHunt_BrokenEgg.png"));
        m_TextureRes.emplace("EasterHunt_Bunny", raylib::Texture2D("../res/txt/EasterHunt_Bunny.png"));
        m_TextureRes.emplace("EasterHunt_Egg", raylib::Texture2D("../res/txt/EasterHunt_Egg.png"));
        m_TextureRes.emplace("EasterHunt_Icon", raylib::Texture2D("../res/txt/EasterHunt_Icon.png"));
        m_TextureRes.emplace("EasterHunt_Logo", raylib::Texture2D("../res/txt/EasterHunt_Logo.png"));

        m_SoundRes.emplace("EasterHunt_SoundBounce", raylib::Sound("../res/sfx/EasterHunt_SoundBounce.wav"));
        m_SoundRes.emplace("EasterHunt_SoundPickup", raylib::Sound("../res/sfx/EasterHunt_SoundPickup.wav"));

        m_FontRes.emplace("VarelaRound", raylib::Font("../res/font/Varela_Round/VarelaRound-Regular.ttf"));

        for(auto& i : m_TextureRes) {
            i.second.SetFilter(TEXTURE_FILTER_BILINEAR);
        } for(auto& i : m_FontRes) {
            i.second.GetTexture().SetFilter(TEXTURE_FILTER_BILINEAR);
        }
    }

raylib::Texture2D& Resources::GetTexture(const std::string name) {
    return m_TextureRes[name];
}

raylib::Sound& Resources::GetSound(const std::string name) {
    return m_SoundRes[name];
}

raylib::Font& Resources::GetFont(const std::string name) {
    return m_FontRes[name];
}
