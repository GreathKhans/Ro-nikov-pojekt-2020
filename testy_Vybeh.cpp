//
// Created by marek on 12/7/19.
//

#include "gtest/gtest.h"
#include "Vybeh.h"
#include "HashTable.h"
#include <map>
#include <functional>

using namespace std;
using namespace ::testing;

TEST(TestyVybeh, konstruktorNazov)
{
    Vybeh vybeh( "V1 25 ano V2 V3 V4");
    ASSERT_EQ(vybeh.getNazov(), "V1");
}

TEST(TestyVybeh, konstruktorVelaSusedov)
{
    ASSERT_THROW(Vybeh vybeh( "V1 25 ano V2 V3 V4 V5"), std::logic_error);
}

TEST(TestyVybeh, konstruktorZleAnoNie)
{
    ASSERT_THROW(Vybeh vybeh( "V1 25 jasnezeano V2 V3"), std::logic_error);
}

TEST(TestyVybeh, konstruktorCista)
{
    Vybeh vybeh( "V1 25 ano V2 V3 V4");
    ASSERT_EQ(vybeh.getCisty(), true);
    Vybeh vybeh2( "V1 25 nie V2 V3 V4");
    ASSERT_EQ(vybeh2.getCisty(), false);
}

TEST(TestyVybeh, konstruktorPlocha)
{
    Vybeh vybeh( "V1 25 ano V2 V3 V4");
    ASSERT_EQ(vybeh.getVelkost(), 25);
}

TEST(TestyVybeh, operatorMensi)
{
    Vybeh v1( "V1 25 ano V2 V3 V4");
    Vybeh v2( "V2 25 ano V1 V3 V4");
    ASSERT_LT(v1, v2);
}

TEST(TestyVybeh, ulozVybehOK)
{
    std::set<Vybeh> vybehy;
    vybehy.insert(Vybeh( "V1 10 ano V2 V3 V4"));
    vybehy.insert(Vybeh( "V2 10 ano V1"));
    vybehy.insert(Vybeh( "V3 10 ano V1"));
    vybehy.insert(Vybeh( "V4 10 ano V1 V5"));
    vybehy.insert(Vybeh( "V5 10 ano V4"));

    ASSERT_EQ((*vybehy.begin()).str(), "V1 10 ano V2 V3 V4");
}

TEST(TestyVybeh, cistySpinavy)
{
    Vybeh vybeh( "V1 25 nie V2 V3 V4");
    ASSERT_EQ(vybeh.getCisty(), false);
    vybeh.vycisti();
    ASSERT_EQ(vybeh.getCisty(), true);
    vybeh.zaspin();
    ASSERT_EQ(vybeh.getCisty(), false);
}

TEST(TestyVybeh, pocetSusedov)
{
    std::set<Vybeh> vybehy;
    vybehy.insert( Vybeh( "V1 10 ano V2 V3 V4"));
    vybehy.insert( Vybeh( "V2 10 ano V1"));
    vybehy.insert( Vybeh( "V3 10 ano V1"));
    vybehy.insert( Vybeh( "V4 10 ano V1 V5"));
    vybehy.insert( Vybeh( "V5 10 ano V4"));
    vybehy.insert( Vybeh( "V6 10 ano"));


    for(auto vybeh: vybehy)
    {
        std::set<std::string> susedia;
        if(vybeh.getNazov() == "V1")
            ASSERT_EQ(vybeh.getSusedia(susedia).size(), 3);
        susedia.clear();
        if(vybeh.getNazov() == "V2")
            ASSERT_EQ(vybeh.getSusedia(susedia).size(), 1);
        susedia.clear();
        if(vybeh.getNazov() == "V3")
            ASSERT_EQ(vybeh.getSusedia(susedia).size(), 1);
        susedia.clear();
        if(vybeh.getNazov() == "V4")
            ASSERT_EQ(vybeh.getSusedia(susedia).size(), 2);
        susedia.clear();
        if(vybeh.getNazov() == "V5")
            ASSERT_EQ(vybeh.getSusedia(susedia).size(), 1);
        susedia.clear();
        if(vybeh.getNazov() == "V6")
            ASSERT_EQ(vybeh.getSusedia(susedia).size(), 0);
        susedia.clear();
    }
}