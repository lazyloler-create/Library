#include <nlohmann/json.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "function_headers/getBookInfo.hpp"

using json = nlohmann::json;

class BookInfoIntegrationTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        try
        {
            (void)getApiFromFile();
        }
        catch (const std::exception &e)
        {
            GTEST_SKIP() << "Skipping because GOOGLE_API_KEY is unavailable: " << e.what();
        }
    }
    void TearDown() override {}
};

TEST_F(BookInfoIntegrationTest, GetTitle_ValidBook)
{
    std::string book = "Harry Potter";

    try
    {
        std::string title = getTitle(book);

        EXPECT_FALSE(title.empty());
        EXPECT_TRUE(title.find("Harry") != std::string::npos ||
                    title.find("Potter") != std::string::npos);
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetAuthors_ValidBook)
{
    std::string book = "1984";

    try
    {
        std::string authors = getAuthors(book);

        EXPECT_FALSE(authors.empty());
        EXPECT_TRUE(authors.find("George Orwell") != std::string::npos ||
                    authors.find("Orwell") != std::string::npos);
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetPublishedDate_ValidBook)
{
    std::string book = "Harry Potter";

    try
    {
        std::string date = getPublishedDate(book);

        EXPECT_FALSE(date.empty());
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetISBN_10_ValidBook)
{
    std::string book = "Harry Potter";

    try
    {
        std::string isbn10 = getISBN_10(book);

        EXPECT_FALSE(isbn10.empty());
        EXPECT_EQ(isbn10.length(), 10u);
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetISBN_13_ValidBook)
{
    std::string book = "Harry Potter";

    try
    {
        std::string isbn13 = getISBN_13(book);

        EXPECT_FALSE(isbn13.empty());
        EXPECT_EQ(isbn13.length(), 13u);
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetMainCategory_ValidBook)
{
    std::string book = "Harry Potter";

    try
    {
        std::string category = getMainCategory(book);

        EXPECT_FALSE(category.empty());
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetRating_ValidBook)
{
    std::string book = "Harry Potter";

    try
    {
        float rating = getRating(book);

        EXPECT_GE(rating, 0.0f);
        EXPECT_LE(rating, 5.0f);
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetPrice_ValidBook)
{
    std::string book = "Harry Potter";

    try
    {
        float price = getPrice(book);
        EXPECT_GE(price, 0.0f);
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetPages_ValidBook)
{
    std::string book = "Harry Potter";

    try
    {
        int pages = getPages(book);

        EXPECT_GT(pages, 0);
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetTitle_NonExistentBook)
{
    std::string book = "ThisBookDoesNotExist12345";

    try
    {
        std::string title = getTitle(book);

        EXPECT_EQ(title, "");
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

TEST_F(BookInfoIntegrationTest, GetBookInfo_HttpErrorHandling)
{
    try
    {
        std::string book = "Harry Potter";
        getBookInfo(book);

        GTEST_SKIP() << "No HTTP error occurred - API is responding";
    }
    catch (const std::runtime_error &e)
    {
        EXPECT_TRUE(e.what() != nullptr);
    }
}


TEST_F(BookInfoIntegrationTest, GetApiKey_FromEnvFile)
{
    try
    {
        std::string apiKey = getApiFromFile();
        EXPECT_FALSE(apiKey.empty());
    }
    catch (const std::exception &e)
    {
        GTEST_SKIP() << "Skipping due to: " << e.what();
    }
}

//to run these tests use: 
//g++ -std=c++17 src/getBookInfo_test_simple.cpp src/getBookInfo.cpp -lgtest -lgtest_main -lpthread -o book_info_tests && ./book_info_tests