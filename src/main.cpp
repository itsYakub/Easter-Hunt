// External links:
// > Color Palette: https://lospec.com/palette-list/vanilla-milkshake

#include <string>

#include "raylib-cpp.hpp"

#include "Timer.hpp"
#include "Egg.hpp"
#include "EggController.hpp"
#include "Player.hpp"

int main(int argc, char** argv) {
    const std::string title = "Raylib 5.0.0 - Easter Hunt 1.0.0";

    raylib::Window window(786, 786, title.c_str(), FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    
    Player player(window);
    EggController eggController(window);

    while(!WindowShouldClose()) {
        window.SetTitle(TextFormat("%s (%iFPS)", title.c_str(), window.GetFPS()));

        player.Update();
        eggController.Update();

        for(int i = 0; i < eggController.GetEggList().size(); i++) {
            auto egg = eggController.GetEggList().at(i).get();

            if(player.GetRectangle().CheckCollision(egg->GetRectangle())) {
                eggController.EggListPopAtIndex(i);
            }

            if(egg->GetRectangle().y > window.GetSize().y) {
                eggController.EggListPopAtIndex(i);
            }
        }
 
        window.BeginDrawing().ClearBackground(raylib::Color(172, 204, 228));

        player.Render();
        eggController.Render();

        window.EndDrawing();
    }

    return 0;
}
