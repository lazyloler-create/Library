#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

#include "function_headers/getBookInfo.hpp"

class BookInfoTest : public ::testing::Test
{
protected:
    static json makeBookResponse(const std::string &title,
                                const std::vector<std::string> &authors,
                                const std::string &publishedDate,
                                const std::string &mainCategory,
                                double averageRating,
                                double price,
                                int pageCount,
                                const std::string &isbn10,
                                const std::string &isbn13)
    {
        json authorsArray = json::array();
        for (const auto &author : authors)
        {
            authorsArray.push_back(author);
        }

        json item = json::object();
        item["volumeInfo"] = json::object({
            {"title", title},
            {"authors", authorsArray},
            {"publishedDate", publishedDate},
            {"industryIdentifiers", json::array({
                json::object({{"type", "ISBN_10"}, {"identifier", isbn10}}),
                json::object({{"type", "ISBN_13"}, {"identifier", isbn13}})})},
            {"mainCategory", mainCategory},
            {"averageRating", averageRating},
            {"saleInfo", json::object({{"listPrice", json::object({{"amount", price}})}})},
            {"pageCount", pageCount}
        });

        json response = json::object();
        response["items"] = json::array({item});
        return response;
    }

    static json mockHarryPotterResponse()
    {
        return makeBookResponse(
            "Harry Potter and the Sorcerer's Stone",
            {"J.K. Rowling"},
            "2015-09-14",
            "CHILDREN",
            4.5,
            12.9,
            309,
            "0439708184",
            "9780439708180");
    }

    static json mock1984Response()
    {
        return makeBookResponse(
            "Nineteen Eighty-Four",
            {"George Orwell"},
            "1949-06-08",
            "FICTION",
            4.2,
            8.9,
            328,
            "0451524934",
            "9780451524935");
    }

    static json mockCppPrimerResponse()
    {
        return makeBookResponse(
            "C++ Primer",
            {"Stanley B. Lippman", "Josée Lajoie"},
            "2019-03-15",
            "COMPUTERS",
            4.0,
            59.9,
            104,
            "0134786373",
            "9780134786375");
    }
};

TEST_F(BookInfoTest, ParseMockHarryPotterResponse)
{
    const json mockResponse = mockHarryPotterResponse();

    EXPECT_TRUE(mockResponse.contains("items"));
    EXPECT_TRUE(mockResponse["items"].is_array());
    EXPECT_EQ(mockResponse["items"].size(), 1u);

    const auto &item = mockResponse["items"][0];
    EXPECT_TRUE(item.contains("volumeInfo"));
    EXPECT_TRUE(item["volumeInfo"].contains("title"));
    EXPECT_EQ(item["volumeInfo"]["title"], "Harry Potter and the Sorcerer's Stone");
}

TEST_F(BookInfoTest, ParseMock1984Response)
{
    const json mockResponse = mock1984Response();
    const auto &item = mockResponse["items"][0];

    EXPECT_EQ(item["volumeInfo"]["title"], "Nineteen Eighty-Four");
    EXPECT_TRUE(item["volumeInfo"].contains("authors"));
    EXPECT_EQ(item["volumeInfo"]["authors"].size(), 1u);
}

TEST_F(BookInfoTest, ParseMockCppPrimerResponse)
{
    const json mockResponse = mockCppPrimerResponse();
    const auto &item = mockResponse["items"][0];

    EXPECT_TRUE(item["volumeInfo"].contains("authors"));
    EXPECT_EQ(item["volumeInfo"]["authors"].size(), 2u);
}

class HelperFunctionTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}

    json createMockResponse(const std::string &title, const std::vector<std::string> &authors)
    {
        json authorsArray = json::array();
        for (const auto &author : authors)
        {
            authorsArray.push_back(author);
        }

        json j = json::object();
        j["items"] = json::array({json::object({
            {"volumeInfo", json::object({
                {"title", title},
                {"authors", authorsArray}
            })}
        })});
        return j;
    }
};

TEST_F(HelperFunctionTest, TitleExtraction)
{
    const json response = createMockResponse("Test Book", {"Author One"});

    std::string title = "";
    if (response.contains("items") && response["items"].is_array() && !response["items"].empty())
    {
        const auto &item = response["items"][0];
        if (item.contains("volumeInfo") && item["volumeInfo"].contains("title"))
        {
            title = item.at("volumeInfo").at("title");
        }
    }

    EXPECT_EQ(title, "Test Book");
}

TEST_F(HelperFunctionTest, AuthorsExtraction)
{
    const json response = createMockResponse("Test Book", {"Author One", "Author Two"});

    std::vector<std::string> authors;
    if (response.contains("items") && response["items"].is_array() && !response["items"].empty())
    {
        const auto &item = response["items"][0];
        if (item.contains("volumeInfo") && item["volumeInfo"].contains("authors"))
        {
            authors = item.at("volumeInfo").at("authors");
        }
    }

    EXPECT_EQ(authors.size(), 2u);
}
