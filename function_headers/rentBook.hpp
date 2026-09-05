#pragma once

#include "../classes/treenode_class.hpp"
#include <memory>

std::unique_ptr<TreeNode> findBook(std::unique_ptr<TreeNode> node, NodeData value);
void rentBook(std::unique_ptr<TreeNode> node);