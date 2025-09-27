#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "parse.h"
#include "params.h"
#include "sorter.h"

void print(std::vector<std::vector<std::string> > pool);

int main(int argc, char const *argv[]) {
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

void print(std::vector<std::vector<std::string> > pool) {
    for(std::vector<std::vector<std::string> >::const_iterator ip = pool.cbegin(); ip != pool.cend(); ++ip)
        {
            for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
    }
}