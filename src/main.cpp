// External links:
// > Color Palette: https://lospec.com/palette-list/vanilla-milkshake

#include <string>

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"
#include "SceneSplashScreen.hpp"

int main(int argc, char** argv) {
    const std::string title = "Raylib 5.0.0 - Easter Hunt 1.0.0";

    raylib::Window window(786, 786, title.c_str(), FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

    SceneMenager sceneMenager(new SceneSplashScreen(window, sceneMenager));
    
    while(!WindowShouldClose()) {
        window.SetTitle(TextFormat("%s (%iFPS)", title.c_str(), window.GetFPS()));

        sceneMenager.Update();
 
        window.BeginDrawing();

        sceneMenager.Render();

        window.EndDrawing();
    }

    return 0;
}
