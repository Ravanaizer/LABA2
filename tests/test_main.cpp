#include "../src/sorter.h"
#include <iostream>
#include <fstream>
#include "../src/params.h"
#include <filesystem>
#include <vector>

#define BOOST_TEST_MODULE ip_sort_filt_tests
#include <boost/test/unit_test.hpp>

namespace fs = std::filesystem;

bool file_exists(const std::string& full_path) {
    return fs::exists(full_path);
}

BOOST_AUTO_TEST_SUITE(FileTests)

BOOST_AUTO_TEST_CASE(TestFileExists) {
    std::string file_path = FILE_PATH;
    BOOST_CHECK_MESSAGE(file_exists(file_path), 
        "File should exist at path: " << file_path);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SortingTests)

BOOST_AUTO_TEST_CASE(TestReverseSort) {
    std::vector<std::vector<std::string>> test = {
        {"1","1","1","1"}, 
        {"2","3","4","5"}, 
        {"255", "255", "255", "1"}
    };
    
    revers_sort(test);

    BOOST_CHECK_EQUAL(test[0][0], "255");
    BOOST_CHECK_EQUAL(test[1][0], "2");
    BOOST_CHECK_EQUAL(test[2][0], "1");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FilterTests)

BOOST_AUTO_TEST_CASE(TestFilterWildcard) {
    std::vector<std::vector<std::string>> test = {
        {"1","1","1","1"}, 
        {"2","3","4","5"}, 
        {"255", "255", "255", "1"}
    };
    
    auto result = filter_of_ref(test, "*.*.*.1");

    BOOST_CHECK_EQUAL(result.size(), 2);
    

    bool has_first = false, has_third = false;
    for (const auto& ip : result) {
        if (ip[3] == "1") {
            if (ip[0] == "1") has_first = true;
            if (ip[0] == "255") has_third = true;
        }
    }
    BOOST_CHECK(has_first);
    BOOST_CHECK(has_third);
}

BOOST_AUTO_TEST_CASE(TestFilterSpecific) {
    std::vector<std::vector<std::string>> test = {
        {"1","1","1","1"}, 
        {"2","3","4","5"}, 
        {"255", "255", "255", "1"}
    };
    
    auto result = filter_of_ref_spec(test, "1");

    BOOST_CHECK_EQUAL(result.size(), 2);
    
    for (const auto& ip : result) {
        bool contains_one = false;
        for (const auto& octet : ip) {
            if (octet == "1") {
                contains_one = true;
                break;
            }
        }
        BOOST_CHECK_MESSAGE(contains_one, 
            "IP " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << " should contain '1'");
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IntegrationTests)

BOOST_AUTO_TEST_CASE(TestEmptyVector) {
    std::vector<std::vector<std::string>> empty_test;
    

    BOOST_CHECK_NO_THROW(revers_sort(empty_test));
    BOOST_CHECK_NO_THROW(filter_of_ref(empty_test, "*.*.*.*"));
    BOOST_CHECK_NO_THROW(filter_of_ref_spec(empty_test, "1"));
}

BOOST_AUTO_TEST_SUITE_END()