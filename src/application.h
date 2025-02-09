#pragma once
#include "internals.h"

#include "imgui/imgui.h"

#include <SDL_video.h>
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>

namespace BirdCPP {
    class BirdCPPApplication {
        public:
            bool running;

            BirdCPPApplication();
            ~BirdCPPApplication();

            bool setup();
            bool setup_imgui();

            void render(ImVec4 clear_color);
            void update();

            std::string get_glsl_version();
            BirdCPPContext* get_context();
            SDL_Window* get_main_window();
            SDL_GLContext get_sdl_context();
            ImGuiIO* get_imgui_io();

            bool startMainWindow();
        private:
            BirdCPPContext context;
            std::string glsl_version;
            SDL_Window* main_window;
            SDL_GLContext sdl_context;
            ImGuiIO* imgui_io;
    };
}
