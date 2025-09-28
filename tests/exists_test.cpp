#include <iostream>
#include <fstream>
#include "../src/params.h"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

bool file_exists(const std::string& full_path) {
    return fs::exists(full_path);
}

bool test_file_exists() {
    std::string file_path = FILE_PATH;
    
    if (file_exists(file_path)) {
        return true;
    } else {
        return false;
    }
}