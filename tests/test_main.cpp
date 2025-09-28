#include "../src/sorter.h"
#include "../src/parse.h"
#include <iostream>
#include <fstream>
#include "../src/params.h"
#include <filesystem>
#include <vector>
#include <tuple>

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
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> test = {
        std::make_tuple("1", "1", "1", "1"), 
        std::make_tuple("2", "3", "4", "5"), 
        std::make_tuple("255", "255", "255", "1")
    };
    
    revers_sort(test);

    BOOST_CHECK_EQUAL(std::get<0>(test[0]), "255");
    BOOST_CHECK_EQUAL(std::get<0>(test[1]), "2");
    BOOST_CHECK_EQUAL(std::get<0>(test[2]), "1");
}

BOOST_AUTO_TEST_CASE(TestReverseSortDetailed) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> test = {
        std::make_tuple("1", "1", "1", "1"),
        std::make_tuple("1", "1", "1", "2"),
        std::make_tuple("1", "1", "2", "1"),
        std::make_tuple("1", "2", "1", "1"),
        std::make_tuple("2", "1", "1", "1")
    };
    
    revers_sort(test);

    // Проверяем правильный порядок: от большего к меньшему
    BOOST_CHECK_EQUAL(std::get<0>(test[0]), "2");
    BOOST_CHECK_EQUAL(std::get<0>(test[1]), "1");
    BOOST_CHECK_EQUAL(std::get<1>(test[1]), "2");
    BOOST_CHECK_EQUAL(std::get<0>(test[2]), "1");
    BOOST_CHECK_EQUAL(std::get<1>(test[2]), "1");
    BOOST_CHECK_EQUAL(std::get<2>(test[2]), "2");
    BOOST_CHECK_EQUAL(std::get<0>(test[3]), "1");
    BOOST_CHECK_EQUAL(std::get<1>(test[3]), "1");
    BOOST_CHECK_EQUAL(std::get<2>(test[3]), "1");
    BOOST_CHECK_EQUAL(std::get<3>(test[3]), "2");
    BOOST_CHECK_EQUAL(std::get<0>(test[4]), "1");
    BOOST_CHECK_EQUAL(std::get<1>(test[4]), "1");
    BOOST_CHECK_EQUAL(std::get<2>(test[4]), "1");
    BOOST_CHECK_EQUAL(std::get<3>(test[4]), "1");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FilterTests)

BOOST_AUTO_TEST_CASE(TestFilterWildcard) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> test = {
        std::make_tuple("1", "1", "1", "1"), 
        std::make_tuple("2", "3", "4", "5"), 
        std::make_tuple("255", "255", "255", "1")
    };
    
    auto result = filter_of_ref(test, "*.*.*.1");

    BOOST_CHECK_EQUAL(result.size(), 2);
    
    bool has_first = false, has_third = false;
    for (const auto& ip : result) {
        if (std::get<3>(ip) == "1") {
            if (std::get<0>(ip) == "1") has_first = true;
            if (std::get<0>(ip) == "255") has_third = true;
        }
    }
    BOOST_CHECK(has_first);
    BOOST_CHECK(has_third);
}

BOOST_AUTO_TEST_CASE(TestFilterFirstOctet) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> test = {
        std::make_tuple("1", "1", "1", "1"), 
        std::make_tuple("2", "3", "4", "5"), 
        std::make_tuple("1", "255", "255", "1"),
        std::make_tuple("3", "1", "1", "1")
    };
    
    auto result = filter_of_ref(test, "1.*.*.*");

    BOOST_CHECK_EQUAL(result.size(), 2);
    
    for (const auto& ip : result) {
        BOOST_CHECK_EQUAL(std::get<0>(ip), "1");
    }
}

BOOST_AUTO_TEST_CASE(TestFilterTwoOctets) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> test = {
        std::make_tuple("46", "70", "1", "1"), 
        std::make_tuple("46", "71", "4", "5"), 
        std::make_tuple("47", "70", "255", "1"),
        std::make_tuple("46", "70", "100", "200")
    };
    
    auto result = filter_of_ref(test, "46.70.*.*");

    BOOST_CHECK_EQUAL(result.size(), 2);
    
    for (const auto& ip : result) {
        BOOST_CHECK_EQUAL(std::get<0>(ip), "46");
        BOOST_CHECK_EQUAL(std::get<1>(ip), "70");
    }
}

BOOST_AUTO_TEST_CASE(TestFilterSpecific) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> test = {
        std::make_tuple("1", "1", "1", "1"), 
        std::make_tuple("2", "3", "4", "5"), 
        std::make_tuple("255", "255", "255", "1"),
        std::make_tuple("10", "20", "30", "40")
    };
    
    auto result = filter_of_ref_spec(test, "1");

    BOOST_CHECK_EQUAL(result.size(), 2);
    
    for (const auto& ip : result) {
        bool contains_one = false;
        contains_one = contains_one || (std::get<0>(ip) == "1");
        contains_one = contains_one || (std::get<1>(ip) == "1");
        contains_one = contains_one || (std::get<2>(ip) == "1");
        contains_one = contains_one || (std::get<3>(ip) == "1");
        
        BOOST_CHECK_MESSAGE(contains_one, 
            "IP " << std::get<0>(ip) << "." << std::get<1>(ip) << "." 
                  << std::get<2>(ip) << "." << std::get<3>(ip) << " should contain '1'");
    }
}

BOOST_AUTO_TEST_CASE(TestFilterSpecificMultipleOccurrences) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> test = {
        std::make_tuple("46", "46", "46", "46"), 
        std::make_tuple("1", "46", "2", "3"), 
        std::make_tuple("2", "3", "46", "4"),
        std::make_tuple("1", "2", "3", "4")
    };
    
    auto result = filter_of_ref_spec(test, "46");

    BOOST_CHECK_EQUAL(result.size(), 3);
    
    for (const auto& ip : result) {
        bool contains_46 = false;
        contains_46 = contains_46 || (std::get<0>(ip) == "46");
        contains_46 = contains_46 || (std::get<1>(ip) == "46");
        contains_46 = contains_46 || (std::get<2>(ip) == "46");
        contains_46 = contains_46 || (std::get<3>(ip) == "46");
        
        BOOST_CHECK(contains_46);
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IntegrationTests)

BOOST_AUTO_TEST_CASE(TestEmptyVector) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> empty_test;
    
    BOOST_CHECK_NO_THROW(revers_sort(empty_test));
    BOOST_CHECK_NO_THROW(filter_of_ref(empty_test, "*.*.*.*"));
    BOOST_CHECK_NO_THROW(filter_of_ref_spec(empty_test, "1"));
    
    auto result1 = filter_of_ref(empty_test, "*.*.*.*");
    BOOST_CHECK_EQUAL(result1.size(), 0);
    
    auto result2 = filter_of_ref_spec(empty_test, "1");
    BOOST_CHECK_EQUAL(result2.size(), 0);
}

BOOST_AUTO_TEST_CASE(TestParseFunction) {
    // Тестируем функцию split_ip
    auto result = split_ip("192.168.1.1", '.');
    
    BOOST_CHECK_EQUAL(std::get<0>(result), "192");
    BOOST_CHECK_EQUAL(std::get<1>(result), "168");
    BOOST_CHECK_EQUAL(std::get<2>(result), "1");
    BOOST_CHECK_EQUAL(std::get<3>(result), "1");
    
    // Тестируем исключение для некорректного IP
    BOOST_CHECK_THROW(split_ip("192.168.1", '.'), std::invalid_argument);
    BOOST_CHECK_THROW(split_ip("192.168.1.1.1", '.'), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()