#include "Resources.hpp"

Resources::Resources() :
    m_TextureRes(),
    m_SoundRes(),
    m_MusicRes(),
    m_FontRes() {
        m_TextureRes.emplace("raylib", raylib::Texture2D("../res/raylib-cpp_256x256.png"));
        m_TextureRes.emplace("EasterHunt_Background1", raylib::Texture2D("../res/txt/EasterHunt_Background1.png"));
        m_TextureRes.emplace("EasterHunt_BrokenEgg", raylib::Texture2D("../res/txt/EasterHunt_BrokenEgg.png"));
        m_TextureRes.emplace("EasterHunt_Bunny", raylib::Texture2D("../res/txt/EasterHunt_Bunny.png"));
        m_TextureRes.emplace("EasterHunt_Egg", raylib::Texture2D("../res/txt/EasterHunt_Egg.png"));
        m_TextureRes.emplace("EasterHunt_Icon", raylib::Texture2D("../res/txt/EasterHunt_Icon.png"));
        m_TextureRes.emplace("EasterHunt_Logo", raylib::Texture2D("../res/txt/EasterHunt_Logo.png"));
        m_TextureRes.emplace("EasterHunt_GameOverScreen", raylib::Texture2D("../res/txt/EasterHunt_GameOverScreen.png"));

        m_SoundRes.emplace("EasterHunt_SoundBounce", raylib::Sound("../res/sfx/EasterHunt_SoundBounce.wav"));
        m_SoundRes.emplace("EasterHunt_SoundPickup", raylib::Sound("../res/sfx/EasterHunt_SoundPickup.wav"));
        m_SoundRes.emplace("egg-shell-crush", raylib::Sound("../res/sfx/348388-egg-shell-crush-004.wav"));

        m_MusicRes.emplace("intro", raylib::Music("../res/ost/intro.mp3"));

        m_FontRes.emplace("VarelaRound", raylib::Font("../res/font/Varela_Round/VarelaRound-Regular.ttf"));

        for(auto& i : m_TextureRes) {
            i.second.SetFilter(TEXTURE_FILTER_BILINEAR);
            i.second.SetWrap(TEXTURE_WRAP_CLAMP);
        } for(auto& i : m_FontRes) {
            i.second.GetTexture().SetFilter(TEXTURE_FILTER_BILINEAR);
            i.second.GetTexture().SetWrap(TEXTURE_WRAP_CLAMP);
        }
    }

raylib::Texture2D& Resources::GetTexture(const std::string name) {
    return m_TextureRes[name];
}

raylib::Sound& Resources::GetSound(const std::string name) {
    return m_SoundRes[name];
}

raylib::Music& Resources::GetMusic(const std::string name) {
    return m_MusicRes[name];
}

raylib::Font& Resources::GetFont(const std::string name) {
    return m_FontRes[name];
}
