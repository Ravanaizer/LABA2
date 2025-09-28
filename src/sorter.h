#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <iostream>
#include <tuple>

void revers_sort(std::vector<std::tuple<std::string, std::string, std::string, std::string>>& list);

std::vector<std::tuple<std::string, std::string, std::string, std::string>> filter_of_ref(const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& list, std::string reference);
std::vector<std::tuple<std::string, std::string, std::string, std::string>> filter_of_ref_spec (const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& list, std::string reference);

#endif