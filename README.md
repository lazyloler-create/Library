**(WIP PROJECT)**

*Build and run using CMake:*
``
    cmake -B build
    cmake --build build
    #cmake --build build -j$(nproc) #for multi core compiling   
    ./build/myapp   
``

*API:*
    Open Library API is used
    To use the API you need to create a json file like this for e.g:
        ``
    [
        {
            "api_url": "link to open library api"
        }
    ]``