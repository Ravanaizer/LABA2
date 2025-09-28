#include "params.h"
#include "parse.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <stdexcept>

std::tuple<std::string, std::string, std::string, std::string> split_ip(const std::string &str, char d) {
    std::vector<std::string> parts;
    
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        parts.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    parts.push_back(str.substr(start));

    if (parts.size() != 4) {
        throw std::invalid_argument("Invalid IP address format: " + str);
    }

    return std::make_tuple(
        parts[0], parts[1], parts[2], parts[3]
    );
}

std::vector<std::tuple<std::string, std::string, std::string, std::string>> read_file_lines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<std::tuple<std::string, std::string, std::string, std::string>> lines;
    std::string line;

    while (std::getline(file, line)) {
        size_t tab_pos = line.find('\t');
        if (tab_pos != std::string::npos) {
            std::string ip_str = line.substr(0, tab_pos);
            lines.push_back(split_ip(ip_str, '.'));
        }
    }

    file.close();
    return lines;
}
