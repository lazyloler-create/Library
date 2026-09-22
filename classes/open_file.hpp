#pragma once

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class OpenFile{
    public: 
    fs::path path;
    std::ifstream stream;

    explicit OpenFile(const fs::path& p) : path(p), stream(p) {}
};