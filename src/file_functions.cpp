#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "../classes/open_file.hpp"

namespace fs = std::filesystem;


std::string getDir(OpenFile& f){
     return f.path.parent_path();
}

bool checkIfOpen(OpenFile& f){
    if(!f.stream.is_open()){
        std::cout<<"Couldn't open file at: " << getDir(f) << std::endl;
        return false;
    }
    return true;
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
