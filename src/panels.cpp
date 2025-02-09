#include "panels.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "IconFontCppHeaders/IconsCodicons.h"

#include "internals.h"

#include <string>

void BirdCPPPanels::management_panel() {
    ImGui::Begin("Management");
    ImGui::End();
}

void BirdCPPPanels::toolbar_panel(BirdCPP::BirdCPPContext *context) {
    float menuBarHeight = ImGui::GetFrameHeight();
    ImGui::SetNextWindowPos(ImVec2(0, menuBarHeight));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, BirdCPP::BirdCPPToobarHeight));

    ImGuiWindowFlags flags = (ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking);

    ImGui::Begin("Toolbar", nullptr, flags);

    if (ImGui::Button(ICON_CI_FILE, ImVec2(32, 32))) {
        context->open_file_dialog = true;
    }

    ImGui::SetItemTooltip("Open a single file");

    ImGui::SameLine();

    if (ImGui::Button(ICON_CI_FOLDER, ImVec2(32, 32))) {}

    ImGui::SetItemTooltip("Open a folder");

    ImGui::SameLine();

    if (ImGui::Button(ICON_CI_FILE_CODE, ImVec2(32, 32))) {}

    ImGui::SetItemTooltip("Open a CMake project");

    ImGui::SameLine();

    if (ImGui::Button(ICON_CI_SAVE, ImVec2(32, 32))) {}

    ImGui::SetItemTooltip("Save current file");

    ImGui::SameLine();

    if (ImGui::Button(ICON_CI_SAVE_ALL, ImVec2(32, 32))) {}

    ImGui::SetItemTooltip("Save all files");

    ImGui::SameLine();

    ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);

    ImGui::SameLine();

    std::string preview_target_value;

    if (context->loaded_targets.empty()) {
        preview_target_value = "Empty";
    } else {
        preview_target_value = context->loaded_targets[context->current_target];
    }

    if (ImGui::BeginCombo("##", preview_target_value.c_str(), ImGuiComboFlags_WidthFitPreview)) {
        if (!context->loaded_targets.empty()) {
            for (int n = 0; n < context->loaded_targets.size(); n++) {
                const bool is_selected = (context->current_target == n);

                if (ImGui::Selectable(context->loaded_targets[n].c_str(), is_selected)) {
                    context->current_target = n;
                }

                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
        }

        ImGui::EndCombo();
    }

    ImGui::SetItemTooltip("The target to build, run or debug");

    ImGui::SameLine();

    ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);

    ImGui::SameLine();

    if (ImGui::Button(ICON_CI_TOOLS, ImVec2(32, 32))) {}
    ImGui::SetItemTooltip("Build");
    
    ImGui::SameLine();

    if (ImGui::Button(ICON_CI_PLAY, ImVec2(32, 32))) {}
    ImGui::SetItemTooltip("Run");

    ImGui::SameLine();

    if (ImGui::Button(ICON_CI_PLAY_CIRCLE, ImVec2(32, 32))) {}
    ImGui::SetItemTooltip("Build and Run");

    ImGui::SameLine();

    if (ImGui::Button(ICON_CI_DEBUG_ALT, ImVec2(32, 32))) {}
    ImGui::SetItemTooltip("Debug Run");

    ImGui::End();
}
