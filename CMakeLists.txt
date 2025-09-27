cmake_minimum_required(VERSION 3.10)
project(ip_sort_filt)

set(PROJECT_NAME "ip_sort_filt")

set(PROJECT_VERSION "1.0.0" CACHE STRING "Project version")

string(REPLACE "." ";" VERSION_LIST ${PROJECT_VERSION})
list(GET VERSION_LIST 0 PROJECT_VERSION_MAJOR)
list(GET VERSION_LIST 1 PROJECT_VERSION_MINOR)
list(GET VERSION_LIST 2 PROJECT_VERSION_PATCH)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

set(DEFAULT_TSV_FILE "./ip_filter.tsv" CACHE FILEPATH "Path to default TSV file")
set(INPUT_DIR "${CMAKE_SOURCE_DIR}/data/input" CACHE PATH "Directory for input files") 
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/data/output" CACHE PATH "Directory for output files")
set(FILE_PATH "./ip_filter.tsv")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


set(DATA_DIR ./data)
set(INCLUDE_DIR ./include)
set(SRC_DIR ./src)
set(TEST_DIR ./tests)


#add_subdirectory(src)
#add_subdirectory(test)


configure_file(
    ${INCLUDE_DIR}/config.h.in
    ${CMAKE_BINARY_DIR}/generated/config.h
    @ONLY
)

configure_file(
  ${SRC_DIR}/params.h.in
  ${SRC_DIR}/params.h
)

include_directories(${CMAKE_BINARY_DIR}/generated)

add_executable(ip_sort_filt 
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/parse.cpp
  ${SRC_DIR}/sorter.cpp
)
if(MSVC)
    target_compile_options(ip_sort_filt PRIVATE /W4 /WX)
else()
    target_compile_options(ip_sort_filt PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(ip_sort_filt PRIVATE ${INCLUDE_DIR})


find_package(Boost 1.65.0 REQUIRED COMPONENTS unit_test_framework)

if(Boost_FOUND)
    add_executable(ip_sort_filt_tests
      ${TEST_DIR}/test_main.cpp  
      ${SRC_DIR}/parse.cpp
      ${SRC_DIR}/sorter.cpp
    )
    
    target_link_libraries(ip_sort_filt_tests Boost::unit_test_framework)
    
    target_include_directories(ip_sort_filt_tests PRIVATE 
        ${INCLUDE_DIR} 
        ${SRC_DIR}
        ${CMAKE_BINARY_DIR}/generated
    )
    
    if(MSVC)
        target_compile_options(ip_sort_filt_tests PRIVATE /W4 /WX)
    else()
        target_compile_options(ip_sort_filt_tests PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()

    target_compile_definitions(ip_sort_filt_tests PRIVATE BOOST_TEST_DYN_LINK)
    
    add_test(NAME ip_sort_filt_tests COMMAND ip_sort_filt_tests)
endif()

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "Ravanaizer")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IP sorting and filtering utility")
set(CPACK_PACKAGE_CONTACT "wasja1117@gmail.com")

install(TARGETS ip_sort_filt RUNTIME DESTINATION bin)

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_FILE_NAME "filt-${PROJECT_VERSION}-win64")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB;TGZ")
    set(CPACK_PACKAGE_FILE_NAME "filt-${PROJECT_VERSION}-linux")
endif()

include(CPack)