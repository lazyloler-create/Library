cmake_minimum_required(VERSION 3.14)
project(library_app)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

include(FetchContent)
FetchContent_Declare(
  cpp-httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
  GIT_TAG v0.18.5
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cpp-httplib googletest)

add_executable(library_app
    main.cpp
    src/categories_functions.cpp
    src/treenode_class.cpp
    src/jsonFile.cpp
    src/checkInput.cpp
    src/rentBook.cpp
    src/getBookInfo.cpp
    src/file_functions.cpp
)

target_compile_definitions(library_app PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
target_link_libraries(library_app PRIVATE httplib::httplib OpenSSL::SSL OpenSSL::Crypto)

enable_testing()

add_executable(library_tests
  Tests/tests.cpp
)

target_link_libraries(library_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(library_tests)