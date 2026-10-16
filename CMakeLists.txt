cmake_minimum_required(VERSION 3.14)
project(library_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(CTest)
option(BUILD_BOOK_INFO_INTEGRATION_TESTS
       "Build Google Books API integration tests (requires network access and .env)" OFF)

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
    src/main.cpp
    src/categories_functions.cpp
    src/treenode_class.cpp
    src/jsonFile.cpp
    src/getBookInfo.cpp
    src/file_functions.cpp
)


target_include_directories(library_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp-dotenv/include)

target_compile_definitions(library_app PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
target_link_libraries(library_app PRIVATE httplib::httplib OpenSSL::SSL OpenSSL::Crypto cpp_dotenv)

if(BUILD_TESTING)
  find_package(GTest QUIET)
  if(NOT GTest_FOUND)
    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG v1.15.2
    )
    FetchContent_MakeAvailable(googletest)
  endif()

  add_executable(get_book_info_tests
      src/getBookInfo_test.cpp
      src/getBookInfo.cpp
  )
  target_include_directories(get_book_info_tests PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/cpp-dotenv/include
  )
  target_link_libraries(get_book_info_tests PRIVATE
      GTest::gtest_main
      httplib::httplib
      OpenSSL::SSL
      OpenSSL::Crypto
      cpp_dotenv
  )
  add_test(NAME get_book_info_tests COMMAND get_book_info_tests)

  if(BUILD_BOOK_INFO_INTEGRATION_TESTS)
    add_executable(get_book_info_api_tests
        src/getBookInfo_test_simple.cpp
        src/getBookInfo.cpp
    )
    target_include_directories(get_book_info_api_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp-dotenv/include
    )
    target_link_libraries(get_book_info_api_tests PRIVATE
        GTest::gtest_main
        httplib::httplib
        OpenSSL::SSL
        OpenSSL::Crypto
        cpp_dotenv
    )
    add_test(NAME get_book_info_api_tests COMMAND get_book_info_api_tests)
    set_tests_properties(get_book_info_api_tests PROPERTIES
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        LABELS integration
    )
  endif()
endif()