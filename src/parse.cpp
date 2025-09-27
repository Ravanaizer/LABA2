#include "params.h"
#include "parse.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector< std::vector<std::string> > read_file_lines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector< std::vector<std::string> > lines;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> elem = split(line, '\t');
        lines.push_back(split(elem.at(0), '.'));
    }

    file.close();
    return lines;
}

