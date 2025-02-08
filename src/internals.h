#pragma once
#include <string>
#include <vector>

namespace BirdCPP {
    struct BirdCPPContext {
        bool done;
        bool open_file_dialog;
        std::vector<std::string> loaded_targets;
        int current_target;
    };

    const float BirdCPPToobarHeight = 48;
}
