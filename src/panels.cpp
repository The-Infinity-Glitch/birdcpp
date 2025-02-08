#include "imgui/imgui.h"

#include "panels.h"

void BirdCPPPanels::management_panel() {
    ImGui::Begin("Management");
    ImGui::End();
}

void BirdCPPPanels::toolbar_panel() {
    float menuBarHeight = ImGui::GetFrameHeight();
    ImGui::SetNextWindowPos(ImVec2(0, menuBarHeight));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 40));

    ImGuiWindowFlags flags = (ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking);

    ImGui::Begin("Toolbar", nullptr, flags);

    if (ImGui::Button("Build")) {}

    ImGui::End();
}
