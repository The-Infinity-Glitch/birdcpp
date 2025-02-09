#pragma once
#include <string>
#include <vector>

namespace BirdCPP {
    class BirdCPPFileInfo {
        public:
            std::string fileName;
            std::string filePath;
            bool modified;
            std::string currentData;

            BirdCPPFileInfo(std::string filePath);
        private:
            std::string originalData;
    };

    class BirdCPPContext {
        public:
            bool open_file_dialog;
            std::vector<std::string> loaded_targets;
            int current_target;
            std::vector<BirdCPPFileInfo> openedFiles;

            BirdCPPContext();

            void openFile(std::string filePath);
    };

    const float BirdCPPToobarHeight = 48;
}
