#include "application.h"
#include "internals.h"

#include "imgui/imgui.h"
#include "backends/imgui/imgui_impl_opengl3.h"
#include "backends/imgui/imgui_impl_sdl2.h"

#include "IconFontCppHeaders/IconsCodicons.h"

#include <SDL_video.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>

namespace BirdCPP {
    BirdCPPApplication::BirdCPPApplication() {
        running = false;
        context = BirdCPPContext();
    }

    BirdCPPApplication::~BirdCPPApplication() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(sdl_context);
        SDL_DestroyWindow(main_window);
        SDL_Quit();
    }

    bool BirdCPPApplication::setup() {
        // Setup SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
            std::cout << "Error: %s\n" << SDL_GetError() << std::endl;

            return false;
        }

        // Decide GL+GLSL versions
        #if defined(IMGUI_IMPL_OPENGL_ES3)
            // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
            glsl_version = "#version 300 es";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #elif defined(__APPLE__)
            // GL 3.2 Core + GLSL 150
            glsl_version = "#version 150";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        #else
            // GL 3.0 + GLSL 130
            glsl_version = "#version 130";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #endif

        // From 2.0.18: Enable native IME.
        #ifdef SDL_HINT_IME_SHOW_UI
            SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
        #endif

        if (!startMainWindow()) {
            return false;
        }

        if (!setup_imgui()) {
            return false;
        }

        return true;
    }

    bool BirdCPPApplication::setup_imgui() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        imgui_io = &ImGui::GetIO();

        imgui_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        imgui_io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        imgui_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(main_window, sdl_context);
        ImGui_ImplOpenGL3_Init(glsl_version.c_str());

        // Load Fonts
        float fontSize = 16.0f;

        imgui_io->Fonts->AddFontFromFileTTF("resources/fonts/DroidSans.ttf", fontSize);

        static const ImWchar icons_range[] = { ICON_MIN_CI, ICON_MAX_16_CI, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;

        imgui_io->Fonts->AddFontFromFileTTF("resources/fonts/codicon.ttf", fontSize, &icons_config, icons_range);

        return true;
    }

    void BirdCPPApplication::render(ImVec4 clear_color) {
        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)imgui_io->DisplaySize.x, (int)imgui_io->DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void BirdCPPApplication::update() {
        SDL_GL_SwapWindow(main_window);
    }

    void BirdCPPApplication::quit() {
        running = false;
    }

    std::string BirdCPPApplication::get_glsl_version() {
        return glsl_version;
    }

    BirdCPPContext* BirdCPPApplication::get_context() {
        return &context;
    }

    ImGuiIO* BirdCPPApplication::get_imgui_io() {
        return imgui_io;
    }

    bool BirdCPPApplication::startMainWindow() {
        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_ALLOW_HIGHDPI);

        main_window = SDL_CreateWindow("BirdCPP - C/C++ Simple IDE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

        if (main_window == nullptr) {
            std::cout << "Error: SDL_CreateWindow(): %s\n" << SDL_GetError() << std::endl;

            return false;
        }

        sdl_context = SDL_GL_CreateContext(main_window);

        if (sdl_context == nullptr) {
            std::cout << "Error: SDL_GL_CreateContext(): %s\n" << SDL_GetError() << std::endl;

            return false;
        }

        SDL_GL_MakeCurrent(main_window, sdl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        return true;
    }

    SDL_Window* BirdCPPApplication::get_main_window() {
        return main_window;
    }

    SDL_GLContext BirdCPPApplication::get_sdl_context() {
        return sdl_context;
    }
}
