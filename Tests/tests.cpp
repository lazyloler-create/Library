#include <gtest/gtest.h>
#include <vector>

#include "../classes/treenode_class.hpp"
#include "../function_headers/categories_functions.hpp"
#include "../function_headers/jsonFile.hpp"
#include "../function_headers/rentBook.hpp"


/*
What needs to be tested:
1.Book insertion
2.Caching
3.API
*/

/*
Books breakdown (each category has exactly 2 books):
- Fiction: To Kill a Mockingbird, The Great Gatsby
- Mystery: And Then There Were None, Murder on the Orient Express
- Romance: Pride and Prejudice, Jane Eyre
- Science: A Brief History of Time, Cosmos
- Fantasy: The Hobbit, Harry Potter and the Sorcerer's Stone
- Poetry: Leaves of Grass, The Raven
- Thriller: Gone Girl, The Da Vinci Code
- Horror: It, Dracula
- History: Sapiens: A Brief History of Humankind, Guns, Germs, and Steel
- Biography: Steve Jobs, Becoming
*/
std::vector<std::string> bookList = {
  "To Kill a Mockingbird",
  "The Great Gatsby",
  "And Then There Were None",
  "Murder on the Orient Express",
  "Pride and Prejudice",
  "Jane Eyre",
  "A Brief History of Time",
  "Cosmos",
  "The Hobbit",
  "Harry Potter and the Sorcerer's Stone",
  "Leaves of Grass",
  "The Raven",
  "Gone Girl",
  "The Da Vinci Code",
  "It",
  "Dracula",
  "Sapiens: A Brief History of Humankind",
  "Guns, Germs, and Steel",
  "Steve Jobs",
  "Becoming"
};

