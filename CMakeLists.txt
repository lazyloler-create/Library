cmake_minimum_required(VERSION 3.14)
project(library_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

add_subdirectory(cpp-dotenv)

find_package(OpenSSL REQUIRED)

include(FetchContent)
FetchContent_Declare(
  cpp-httplib
  GIT_REPOSITORY git@github.com:yhirose/cpp-httplib.git
  GIT_TAG v0.18.5
)

FetchContent_MakeAvailable(cpp-httplib)

add_executable(library_app
    main.cpp
    src/categories_functions.cpp
    src/treenode_class.cpp
    src/jsonFile.cpp
    src/rentBook.cpp
    src/getBookInfo.cpp
    src/file_functions.cpp
)


target_include_directories(library_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp-dotenv/include)

target_compile_definitions(library_app PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
target_link_libraries(library_app PRIVATE httplib::httplib OpenSSL::SSL OpenSSL::Crypto cpp_dotenv)