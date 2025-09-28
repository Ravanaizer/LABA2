#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>
#include <tuple>

std::vector<std::tuple<std::string, std::string, std::string, std::string>> read_file_lines(const std::string& filename);
std::tuple<std::string, std::string, std::string, std::string> split_ip(const std::string &str, char d);

#endif