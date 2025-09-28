#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>

#include "sorter.h"
#include "parse.h"

void revers_sort(std::vector<std::tuple<std::string, std::string, std::string, std::string>>& list) {
  std::sort(list.begin(), list.end(), 
                        [](const std::tuple<std::string, std::string, std::string, std::string>& elem, const std::tuple<std::string, std::string, std::string, std::string>& next_elem) {
                          if (std::get<0>(elem) == std::get<0>(next_elem)) {
                            if (std::get<1>(elem) == std::get<1>(next_elem)) {
                              if (std::get<2>(elem) == std::get<2>(next_elem)) {
                                if (std::get<3>(elem) == std::get<3>(next_elem)) {
                                  return false;
                                }
                                return std::atoi(std::get<3>(elem).c_str()) > std::atoi(std::get<3>(next_elem).c_str());
                              }
                              return std::atoi(std::get<2>(elem).c_str()) > std::atoi(std::get<2>(next_elem).c_str());
                            }
                            return std::atoi(std::get<1>(elem).c_str()) > std::atoi(std::get<1>(next_elem).c_str());
                          }
                          return std::atoi(std::get<0>(elem).c_str()) > std::atoi(std::get<0>(next_elem).c_str());
                        }
  );
}

std::vector<std::tuple<std::string, std::string, std::string, std::string>> filter_of_ref(const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& list, std::string reference) {
  std::vector<std::tuple<std::string, std::string, std::string, std::string>> return_list{};

  auto ref_list = split_ip(reference, '.');
  
  for (size_t posit = 0; posit < list.size(); posit++) {

    bool matches = [&list, posit, &ref_list]() { 
      if (std::get<0>(list[posit]) == std::get<0>(ref_list) || std::get<0>(ref_list) == "*") {
        if (std::get<1>(list[posit]) == std::get<1>(ref_list) || std::get<1>(ref_list) == "*") {
          if (std::get<2>(list[posit]) == std::get<2>(ref_list) || std::get<2>(ref_list) == "*") {
            if (std::get<3>(list[posit]) == std::get<3>(ref_list) || std::get<3>(ref_list) == "*") {
              return true;
            }
          }
        }
      }
      return false; 
    }();
    
    if (matches) {
        return_list.push_back(list[posit]);
    }
    
  }

  return return_list;
}


std::vector<std::tuple<std::string, std::string, std::string, std::string>> filter_of_ref_spec (const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& list, std::string reference) {

  std::vector<std::tuple<std::string, std::string, std::string, std::string>> return_list{};
  
  for (size_t posit = 0; posit < list.size(); posit++) {

    bool matches = [&list, posit, &reference]() { 
      if (std::get<0>(list[posit]) == reference || std::get<1>(list[posit]) == reference || 
                  std::get<2>(list[posit]) == reference || std::get<3>(list[posit]) == reference ) {
        return true;
      }
      return false; 
    }();
    
    if (matches) {
        return_list.push_back(list[posit]);
    }
    
  }

  return return_list;
}