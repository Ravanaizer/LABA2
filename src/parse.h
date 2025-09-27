#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>

std::vector< std::vector<std::string> > read_file_lines(const std::string& filename);
std::vector<std::string> split(const std::string &str, char d);

#endif