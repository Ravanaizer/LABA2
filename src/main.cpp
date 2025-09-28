#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "parse.h"
#include "params.h"
#include "sorter.h"

void print(const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& pool);

int main(int argc, char const *argv[]) {
    (void)argc;
    (void)argv;
    try {
        std::string filename = FILE_PATH;
        auto ip_pool = read_file_lines(filename);

        revers_sort(ip_pool);

        print(ip_pool);

        print(filter_of_ref(ip_pool, "1.*.*.*"));

        print(filter_of_ref(ip_pool, "46.70.*.*"));

        print(filter_of_ref_spec(ip_pool, "46"));

    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

void print(const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& pool) {
    for(size_t posit = 0; posit < pool.size(); posit++) {
        std::cout << std::get<0>(pool[posit]) << ".";
        std::cout << std::get<1>(pool[posit]) << ".";
        std::cout << std::get<2>(pool[posit]) << ".";
        std::cout << std::get<3>(pool[posit]);
        std::cout << std::endl;
    }
}