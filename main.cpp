#include <iostream>
#include "config.h"
#include "HashTable.h"
#include "Vybeh.h"
#include "Druh.h"

int main()
{
    //HashTable<int, Vybeh> vybehy;

    try
    {
        Druh d1(0, "liska ano male");

    }
    catch(std::logic_error e)
    {
        std::cerr << "Vynimka: " << e.what() << std::endl;
    }
}