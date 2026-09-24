#pragma once

#include "../classes/treenode_class.hpp"
#include <memory>

void rentBook(std::unique_ptr<TreeNode> node);
std::string getDate();
std::string getReturnDate();