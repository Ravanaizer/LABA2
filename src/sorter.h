#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <iostream>

void revers_sort(std::vector< std::vector<std::string> >& list);

std::vector< std::vector<std::string> > filter_of_ref(std::vector< std::vector<std::string> >& list, std::string reference);
std::vector< std::vector<std::string> > filter_of_ref_spec (std::vector< std::vector<std::string> >& list, std::string reference);

#endif