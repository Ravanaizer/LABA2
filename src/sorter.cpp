#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "sorter.h"
#include "parse.h"

void revers_sort(std::vector< std::vector<std::string> >& list) {
  std::sort(list.begin(), list.end(), 
                        [](std::vector<std::string>& elem, const std::vector<std::string>& next_elem) {
                          for (int posit = 0; posit < 4; posit++) {
                            if (elem[posit] != next_elem[posit]) return elem[posit] > next_elem[posit];
                          }
                            return false;
                        }
  );
}

std::vector< std::vector<std::string> > filter_of_ref(std::vector< std::vector<std::string> >& list, std::string reference) {
  std::vector< std::vector<std::string> > return_list{};

  std::vector<std::string> ref_list {};
  for (auto elem_ref: split(reference, '.')) {ref_list.push_back(elem_ref);}
  
  for (size_t posit = 0; posit < list.size(); posit++) {

    bool matches = [&list, posit, &ref_list]() { 
        auto& elem = list[posit];
        for (int pos = 0; pos < 4; pos++) {
            if (ref_list[pos] == "*") {
                continue;
            }
            if (elem[pos] != ref_list[pos]) {
                return false;
            }
        }
        return true;
    }();
    
    if (matches) {
        return_list.push_back(list[posit]);
    }
    
  }

  return return_list;
}


std::vector< std::vector<std::string> > filter_of_ref_spec (std::vector< std::vector<std::string> >& list, std::string reference) {

  std::vector< std::vector<std::string> > return_list{};
  
  for (size_t posit = 0; posit < list.size(); posit++) {

    bool matches = [&list, posit, &reference]() { 
        auto& elem = list[posit];
        for (int pos = 0; pos < 4; pos++) {
            if (elem[pos] == reference) {
                return true;
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