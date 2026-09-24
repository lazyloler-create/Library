#include <string>
#include <filesystem>
#include <iostream>
#include "../classes/open_file.hpp"

namespace fs = std::filesystem;


std::string getDir(OpenFile& f){
     return f.path.parent_path();
}

void moveToDir(const std::string& src, const std::string& dest){
    fs::path source = src;
    fs::path destination = dest;
    std::error_code ec;
    
    fs::rename(source, destination, ec);
    if(ec){
        std::cerr << "Error moving file to: " << dest << "\n error code: " << ec.message() << std::endl;
        return;
    }

    std::cout << "File moved successfully to: " << dest << std::endl;
}
