**(WIP PROJECT)**

*Build and run using CMake:*
``
    cmake -B build
    cmake --build build
    #cmake --build build -j$(nproc) #for multi core compiling   
    ./build/myapp   
``

*API:*
  Google books API is used in this project
  Get an API from: https://developers.google.com/books/docs/v1/getting_started
  In the .env file add this: API_KEY = GOOGLE_BOOKS_API_KEY