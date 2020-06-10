cmake_minimum_required(VERSION 3.15)
project(MarekovaZoo)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-fpermissive")
find_package(Threads)

set(SOURCE_FILES
        #Druh.cpp
        #Zviera.cpp
        config.cpp
        HashTable.cpp   #toto potrebujeme kvoli definicii operatora % pre string
        #Vybeh.cpp
        #Zoo.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc testy_Druh.cpp testy_Vybeh.cpp testy_hashtable.cpp test_Zoo.cpp)

include_directories(GoogleTest)
add_executable(MarekovaZoo ${SOURCE_FILES})
target_link_libraries(MarekovaZoo ${CMAKE_THREAD_LIBS_INIT})