#include "internals.h"
#include "file_manager.h"
#include <string>

namespace BirdCPP {
    BirdCPPFileInfo::BirdCPPFileInfo(std::string filePath) {
        std::string fileContent = BirdCPPFileManager::read_file(filePath) + "\0";

        fileName = filePath.substr(filePath.find_last_of("/\\") + 1);
        filePath = filePath;
        modified = false;
        currentData = fileContent;
        originalData = fileContent;
    }

    BirdCPPContext::BirdCPPContext() {
        open_file_dialog = false;
        current_target = 0;

        // For testing purposes, remove later
        loaded_targets.push_back("Engine");
        loaded_targets.push_back("Sandbox");
    }

    void BirdCPP::BirdCPPContext::openFile(std::string filePath) {
        openedFiles.push_back(BirdCPPFileInfo(filePath));
    }
}
