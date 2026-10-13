**(WIP PROJECT)**

**Build and run using CMake:**

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target library_app --parallel
./build/library_app
```

*API:*
  Google books API is used in this project
  Get an API from: https://developers.google.com/books/docs/v1/getting_started
  In the .env file add this: API_KEY = GOOGLE_BOOKS_API_KEY