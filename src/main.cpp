#include "imgui/imgui.h"
#include "backends/imgui/imgui_impl_sdl2.h"
#include "backends/imgui/imgui_impl_opengl3.h"

#include "IconFontCppHeaders/IconsCodicons.h"

#include "dialogs.h"
#include "internals.h"
#include "panels.h"

#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>

// Draw the main menu bar -> [File, Edit, View, Search, Project, Build, Debug, Settings, About]
void draw_main_window_menu_bar(BirdCPP::BirdCPPContext *context) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::BeginMenu("Open")) {
                if (ImGui::MenuItem("File", "Ctrl+O")) {
                    context->open_file_dialog = true;
                }
                if (ImGui::MenuItem("Folder", "Ctrl+Shift+O")) {}
                if (ImGui::MenuItem("CMake solution")) {}

                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Save file", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save file as")) {}
            if (ImGui::MenuItem("Save all", "Ctrl+Shift+S")) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Close file", "Ctrl+W")) {}
            if (ImGui::MenuItem("Close all", "Ctrl+Shift+W")) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
                context->done = true;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
            if (ImGui::MenuItem("Redo", "Ctrl+Shift+Z")) {}
            if (ImGui::MenuItem("Clear change history")) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
            if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
            if (ImGui::MenuItem("Paste", "Ctrl+V")) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Swap header/source files", "F11")) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Select all", "Ctrl+A")) {}
            if (ImGui::MenuItem("Select next occurrence", "Ctrl+E")) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Toggle comment", "Ctrl+;")) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Code completion", "Ctrl+Space")) {}

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Search")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Project")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Build")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Build")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Debug")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Settings")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About")) {
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

int main(int, char**) {
    BirdCPP::BirdCPPContext birdcpp_context;

    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cout << "Error: %s\n" << SDL_GetError() << std::endl;

        return -1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Window* window = SDL_CreateWindow("BirdCPP - C/C++ Simple IDE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

    if (window == nullptr) {
        std::cout << "Error: SDL_CreateWindow(): %s\n" << SDL_GetError() << std::endl;

        return -1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    if (gl_context == nullptr) {
        std::cout << "Error: SDL_GL_CreateContext(): %s\n" << SDL_GetError() << std::endl;

        return -1;
    }

    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void) io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    float fontSize = 16.0f;

    io.Fonts->AddFontFromFileTTF("resources/fonts/DroidSans.ttf", fontSize);

    static const ImWchar icons_range[] = { ICON_MIN_CI, ICON_MAX_16_CI, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;

    io.Fonts->AddFontFromFileTTF("resources/fonts/codicon.ttf", fontSize, &icons_config, icons_range);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Disable ImGui init file
    // io.InitFilename = nullptr;

    // Main loop
    while (!birdcpp_context.done) {
        // Poll and handle events (inputs, window resize, etc.)
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT)
                birdcpp_context.done = true;

            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                birdcpp_context.done = true;
        }

        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Create a dockspace
        float menuBarHeight = ImGui::GetFrameHeight();
        float toolbarHeight = BirdCPP::BirdCPPToobarHeight;
        float totalTopHeight = menuBarHeight + toolbarHeight;
        
        ImGui::SetNextWindowPos(ImVec2(0, totalTopHeight));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y - totalTopHeight));
        ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);

        ImGuiWindowFlags dockspace_frame_flags = (ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground);

        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Dockspace", nullptr, dockspace_frame_flags);
        
            ImGuiID dockspaceID = ImGui::GetID("BirdCPPDockspace");

            ImGui::DockSpace(dockspaceID, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

            ImGui::End();
            ImGui::PopStyleVar();
        }

        // Render the main menu bar
        draw_main_window_menu_bar(&birdcpp_context);

        if (birdcpp_context.open_file_dialog) {
            BirdCPPDialogs::open_file_dialog(&birdcpp_context);
        }

        BirdCPPPanels::management_panel();
        BirdCPPPanels::toolbar_panel(&birdcpp_context);
        ImGui::ShowDemoWindow();

        for (int i = 0; i < birdcpp_context.openedFiles.size(); i++) {
            {
                ImGui::Begin(birdcpp_context.openedFiles[i].fileName.c_str());
                ImGui::Text("%s",  birdcpp_context.openedFiles[i].currentData.c_str());
                ImGui::End();
            }
        }

        // ImGui things here

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
