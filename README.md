**(WIP PROJECT)**

*Compile:*
``
    g++ main.cpp src/categories_functions.cpp src/jsonFile.cpp src/treenode_class.cpp src/rentBook.cpp src/getBookInfo.cpp -I. -o library_app #-ggdb #optional for debugging with gdb 
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