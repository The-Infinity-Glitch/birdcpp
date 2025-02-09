#include <iostream>

#include "ImGuiFileDialog/ImGuiFileDialog.h"

#include "dialogs.h"
#include "internals.h"
// #include "file_manager.h"

void BirdCPPDialogs::open_file_dialog(BirdCPP::BirdCPPContext *context) {
    // open Dialog Simple
    IGFD::FileDialogConfig config;
    config.path = ".";

    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp,.txt", config);

    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            context->open_file_dialog = false;
            // action
            context->openFile(filePathName);
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}

void BirdCPPDialogs::open_folder_dialog(BirdCPP::BirdCPPContext *context) {
    // open Dialog Simple
    IGFD::FileDialogConfig config;
    config.path = ".";

    ImGuiFileDialog::Instance()->OpenDialog("ChooseDirDlgKey", "Choose a Directory", nullptr, config);

    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            context->open_file_dialog = false;
            // action
            std::cout << filePath << "\n";
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}
