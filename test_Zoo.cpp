//
// Created by marek on 1/29/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "Druh.h"
#include "Zoo.h"

using namespace std;
using namespace ::testing;

TEST(TestyZoo, konstruktor)
{
    std::ifstream druhy = std::ifstream("/home/ondrej/CLionProjects/MarekovaZoo/druhy.txt");
    std::ifstream vybehy = std::ifstream("/home/ondrej/CLionProjects/MarekovaZoo/vybehy.txt");
    std::ifstream zvierata = std::ifstream("/home/ondrej/CLionProjects/MarekovaZoo/zvierata.txt");
    Zoo zoo(vybehy, druhy, zvierata);
    druhy.close();
    vybehy.close();
    zvierata.close();
    druhy = std::ifstream("/home/ondrej/CLionProjects/MarekovaZoo/druhy_novy.txt");
    vybehy = std::ifstream("/home/ondrej/CLionProjects/MarekovaZoo/vybehy_novy.txt");
    zvierata = std::ifstream("/home/ondrej/CLionProjects/MarekovaZoo/zvierata_novy.txt");
}