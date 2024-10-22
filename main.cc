#include "include/raylib.h"
#include "emu.h" 

#include <string.h>
#include <stdint.h>
#include <chrono>

int main(int argc, char *argv[]) {
  constexpr int32_t screen_w = 64 * 10; // scale 10x 
  constexpr int32_t screen_h = 32 * 10;
  constexpr uint8_t instructions_per_frame = 10;

  if (strcmp(argv[1], "-w") == 0) {
    Chip chip(argv[2]);

    InitWindow(screen_w, screen_h, "chipzz");
    SetTargetFPS(60);
    
    auto last_time = std::chrono::high_resolution_clock::now();

    while (!WindowShouldClose()) {
      chip.keypad[0x1] = IsKeyDown(KEY_ONE);
      chip.keypad[0x2] = IsKeyDown(KEY_TWO);
      chip.keypad[0x3] = IsKeyDown(KEY_THREE);
      chip.keypad[0xC] = IsKeyDown(KEY_FOUR);
      chip.keypad[0x4] = IsKeyDown(KEY_Q);
      chip.keypad[0x5] = IsKeyDown(KEY_W);
      chip.keypad[0x6] = IsKeyDown(KEY_E);
      chip.keypad[0xD] = IsKeyDown(KEY_R);
      chip.keypad[0x7] = IsKeyDown(KEY_A);
      chip.keypad[0x8] = IsKeyDown(KEY_S);
      chip.keypad[0x9] = IsKeyDown(KEY_D);
      chip.keypad[0xE] = IsKeyDown(KEY_F);
      chip.keypad[0xA] = IsKeyDown(KEY_Z);
      chip.keypad[0x0] = IsKeyDown(KEY_X);
      chip.keypad[0xB] = IsKeyDown(KEY_C);
      chip.keypad[0xF] = IsKeyDown(KEY_V);
      
      auto current_time = std::chrono::high_resolution_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count();

      if (elapsed >= 16) {
        if (chip.dt > 0) chip.dt--;
        if (chip.st > 0) {
          chip.st--;
        }

        last_time = current_time;
      }       
      
      for (int i = 0; i < instructions_per_frame; i++) chip.step();
      BeginDrawing();
      ClearBackground(BLACK);
      for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            int index = y * 64 + x;  
            bool pixel = chip.screen[index];
            if (pixel == true) {
              DrawRectangle(x * 10, y * 10, 10, 10, RAYWHITE);
            }
        }
      }
      EndDrawing();
    }

    CloseWindow();

  }
  
  return 0;
}
