#pragma once

#include <string>

int levenshteinMemo(const std::string& a, const std::string& b);
bool didYouMean(const std::string& query, const std::string& candidate, int threshold );