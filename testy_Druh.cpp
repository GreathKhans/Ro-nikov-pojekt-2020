//
// Created by marek on 11/29/19.
//

#include "gtest/gtest.h"
#include "Druh.h"

using namespace std;
using namespace ::testing;

TEST(TestyDruh, konstruktorNazov)
{
    Druh druh( "liska ano male");
    ASSERT_EQ(druh.getNazov(), "liska");
}

TEST(TestyDruh, konstruktorVelkost)
{
    Druh druh( "liska ano male");
    ASSERT_EQ(druh.getVelkost(), small);
}

TEST(TestyDruh, velkostDruhuVynimka)
{
    ASSERT_THROW(Druh( "liska ano mini"), std::logic_error);
}

TEST(TestyDruh, NieJeDravec)
{
    Druh druh( "ovca nie stredne");
    ASSERT_FALSE(druh.getJeDravec());
}

TEST(TestyDruh, Ulozenie1)
{
    Druh druh( "slon nie velke");
    ASSERT_EQ(druh.str(), "slon nie velke");
}

TEST(TestyDruh, dravecVynimka)
{
    ASSERT_THROW(Druh( "kanec cojaviem stredne"), std::logic_error);
}

