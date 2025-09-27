#ifndef ip_sort_filt_FILEPATH_H
#define ip_sort_filt_FILEPATH_H

#define FILE_PATH "/home/ravana/TPU/CPP/3 sem/2/GIT/data/ip_filter.tsv"

#ifdef FILE_PATH
    constexpr const char* IP_DATA_FILE = FILE_PATH;
#else
    constexpr const char* IP_DATA_FILE = "default_data.tsv";
#endif

#endif
