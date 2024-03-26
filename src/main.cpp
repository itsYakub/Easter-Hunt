#include <string>

#include "raylib-cpp.hpp"

#include "Display.hpp"

#include "SceneMenager.hpp"
#include "SceneSplashScreen.hpp"

#include "Resources.hpp"

class Game {
private:
    const int WINDOW_WIDTH, DISPLAY_WIDTH;
    const int WINDOW_HEIGHT, DISPLAY_HEIGHT;
    const std::string TITLE;

    raylib::Window window;
    raylib::AudioDevice audio;
    Display display;
    Resources resources;
    SceneMenager sceneMenager;

public:
    Game() :
        WINDOW_WIDTH(768), DISPLAY_WIDTH(768),
        WINDOW_HEIGHT(768), DISPLAY_HEIGHT(768),
        TITLE("Raylib 5.0.0 - Easter Hunt 1.0.0"),
        window(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_MAXIMIZED),
        audio(),
        display(window, DISPLAY_WIDTH, DISPLAY_HEIGHT, TEXTURE_FILTER_BILINEAR),
        resources(),
        sceneMenager() {
            window.SetExitKey(0);
            window.Maximize();
            sceneMenager.LoadScene(new SceneSplashScreen(display, resources, sceneMenager));

            while(!window.ShouldClose() && !display.ShouldClose()) {
                Update();
                Render();
            }
        }

private:
    void Update() {
        window.SetTitle(TextFormat("%s (%iFPS)", TITLE.c_str(), window.GetFPS()));

        sceneMenager.Update();
    }

    void Render() {
        display.Begin();

        sceneMenager.Render();

        display.End();
    }
};

int main(int, char**) {
    Game game;

    return 0;
}
