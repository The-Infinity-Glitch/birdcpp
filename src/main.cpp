#include "imgui/imgui.h"
#include "backends/imgui/imgui_impl_sdl2.h"
#include "backends/imgui/imgui_impl_opengl3.h"

#include "dialogs.h"
#include "internals.h"
#include "application.h"
#include "panels.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <iterator>

// Draw the main menu bar -> [File, Edit, View, Search, Project, Build, Debug, Settings, About]
void draw_main_window_menu_bar(BirdCPP::BirdCPPApplication *app) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::BeginMenu("Open")) {
                if (ImGui::MenuItem("File", "Ctrl+O")) {
                    app->get_context()->open_file_dialog = true;
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
                app->running = false;
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
    BirdCPP::BirdCPPApplication application;
    application.setup();
    application.running = true;

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Disable ImGui init file
    // io.InitFilename = nullptr;

    // Main loop
    while (application.running) {
        // Poll and handle events (inputs, window resize, etc.)
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT)
                application.running = false;

            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(application.get_main_window()))
                application.running = false;
        }

        if (SDL_GetWindowFlags(application.get_main_window()) & SDL_WINDOW_MINIMIZED) {
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
        ImGui::SetNextWindowSize(ImVec2(application.get_imgui_io()->DisplaySize.x, application.get_imgui_io()->DisplaySize.y - totalTopHeight));
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
        draw_main_window_menu_bar(&application);

        if (application.get_context()->open_file_dialog) {
            BirdCPPDialogs::open_file_dialog(application.get_context());
        }

        BirdCPPPanels::management_panel();
        BirdCPPPanels::toolbar_panel(application.get_context());
        ImGui::ShowDemoWindow();

        for (int i = 0; i < application.get_context()->openedFiles.size(); i++) {
            {
                bool tabOpen = true;
                ImGui::Begin(application.get_context()->openedFiles[i].fileName.c_str(), &tabOpen);
                ImGui::Text("%s", application.get_context()->openedFiles[i].currentData.c_str());
                ImGui::End();

                if (!tabOpen) {
                    application.get_context()->openedFiles.erase(std::next(application.get_context()->openedFiles.begin(), i));
                }
            }
        }

        // ImGui things here

        // Render and update
        application.render(clear_color);
        application.update();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
