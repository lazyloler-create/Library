#include <fstream>
#include <gtest/gtest.h>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

#include "../classes/treenode_class.hpp"
#include "../function_headers/categories_functions.hpp"
#include "../function_headers/jsonFile.hpp"
#include "../function_headers/rentBook.hpp"
#include "../function_headers/checkInput.hpp"
#include "../function_headers/getBookInfo.hpp"

/*
What needs to be tested:
1.Book insertion
2.Caching
3.API
*/

TEST(CacheCategoriesTest, CachedCorrectly){
  json j;
  auto val = cacheCategories("categories_cache", j);

  EXPECT_EQ(val.contains("Categories"), j.contains("Categories"));
}
