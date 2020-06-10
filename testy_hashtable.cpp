//
// Created by marek on 1/22/20.
//

#include "gtest/gtest.h"
#include "HashTable.h"
#include <ostream>

TEST(testyHashTable, test1)
{
    HashTable<int, int> ht;
    ASSERT_EQ(ht.len(), 0);
}

/**
 * Ukazka ako sa da pouzit vlastna trieda ako kluc (Key) pre HashTable
 * Je treba definovat operatory == (porovnanie), % (modulo) a < (mensi):
 * bool operator ==(const myclass & other) const { return value == other.value; }
 *    tento je potrebny pre porovnavanie klucov v HashTable
 * int operator %(const int x) const { return value % x;}
 *    tento je potrebny pre vypocet hashu kluca
 * bool operator <(const myclass & other) const { return value < other.value; }
 *    tento je potrebny v HashTable.keys, aby sa dal kluc zaradit do zoznamu - std::set vyzaduje aby jeho prvky
 *    boli porovnatelne
 *
 */
class myclass
{
protected:
    int value;
public:
    explicit myclass(int s) : value(s) {}
    //operatory ktore je treba definovat na to, aby sa trieda dala pouzit ako Key pre HashTable
    bool operator ==(const myclass & other) const { return value == other.value; }
    int operator %(const int x) const { return value % x;}
    bool operator <(const myclass & other) const { return value < other.value; }
    //tu je ukazka ako sa definuje operator vystupu do std::ostream
    //definuje sa nie ako metoda triedy, ale ako friend funkcia (ma pristup k private clenom triedy)
    friend std::ostream& operator <<(std::ostream& os, const myclass & mc)
    {
        os << mc.value;
    }
};

TEST(testyHashTable, test2)
{

    HashTable<myclass, int> ht;
    ASSERT_TRUE(ht.checkConsistency());
    ASSERT_EQ(ht.len(), 0);
    ht.add(myclass(7), 5);
    ASSERT_TRUE(ht.checkConsistency());
    ASSERT_EQ(ht.len(), 1);
    ht.add(myclass(7), 6);
    ASSERT_TRUE(ht.checkConsistency());
    ASSERT_EQ(ht.len(), 1);
    ht.add(myclass(8), 11);
    ASSERT_TRUE(ht.checkConsistency());
    ASSERT_EQ(ht.len(), 2);
    ht.add(myclass(9), 12);
    ASSERT_TRUE(ht.checkConsistency());
    ASSERT_EQ(ht.len(), 3);
    ASSERT_TRUE(ht.exists(myclass(7)));
    ht.del(myclass(7));
    ASSERT_FALSE(ht.exists(myclass(7)));
    ASSERT_TRUE(ht.checkConsistency());
    ASSERT_EQ(ht.len(), 2);
    std::set<myclass> keys;
    ht.keys(keys);
    ASSERT_TRUE(ht.checkConsistency());
    ASSERT_EQ(2, keys.size());
    ASSERT_EQ(ht.get(myclass(8)), 11);
    ASSERT_THROW(ht.get(myclass(55)), std::logic_error);
    ASSERT_FALSE(ht.exists(myclass(77)));
    ASSERT_TRUE(ht.exists(myclass(9)));
    ht.del(myclass(8));
    ht.del(myclass(9));
    ASSERT_TRUE(ht.checkConsistency());
    ASSERT_EQ(ht.len(), 0);
}

TEST(testyHashTable, test3)
{

    HashTable<int, int> ht;
    ASSERT_FALSE(ht.exists(1));
    ht.add(1, 2);
    ASSERT_TRUE(ht.exists(1));
    ASSERT_FALSE(ht.exists(2));
    ht.add(11, 22);
    ht.add(111, 222);
    ASSERT_FALSE(ht.exists(3));
    ht.add(3, 333);
    ASSERT_TRUE(ht.exists(3));
    ASSERT_TRUE(ht.checkConsistency());
}

TEST(testyHashTable, test4)
{
    HashTable<int, int> ht;
    ht[1] = 2;
    ASSERT_EQ(ht.get(1), 2);
    //std::cout << ht[2] << std::endl;
    ht[2] = 5;
    ASSERT_TRUE(ht.checkConsistency());
    //std::cout << ht[2] << std::endl;
    ASSERT_EQ(ht[2], 5);
    //ASSERT_EQ(ht[2], 0);

}

TEST(testyHashTable, testValues)
{   //testujeme metodu values()
    HashTable<int, char> ht;
    ht[1] = 'a';
    ht[2] = 'b';
    ht[3] = 'c';
    ht[4] = 'd';

    HashTable<int, char>::ValueList vl;
    ht.values(vl);
    //otestujeme ci vratila spravny pocet prvkov
    ASSERT_EQ(vl.size(), 4);
    vl.sort();  //zoradime si ich a,b,c,d
    //testujeme jednotlive prvky ktore values() vratila
    ASSERT_EQ(vl.front().get(), 'a');
    vl.pop_front();
    ASSERT_EQ(vl.front().get(), 'b');
    vl.pop_front();
    ASSERT_EQ(vl.front().get(), 'c');
    vl.pop_front();
    ASSERT_EQ(vl.front().get(), 'd');
    //testujeme zmenu hodnoty referenciou
    vl.front().get() = 'e';
    ASSERT_EQ(ht[4], 'e');
    ASSERT_TRUE(ht.checkConsistency());
}

TEST(testyHashTable, testData)
{   //testujeme metodu data()
    HashTable<int, char> ht;
    ht[1] = 'a';
    ht[2] = 'b';
    ht[3] = 'c';
    ht[4] = 'd';
    HashTable<int, char>::DataList dl;
    ht.data(dl);
    //testujeme spravnost dodanych dat
    for(auto a: dl)
        ASSERT_EQ(a.first - 1 + 'a', a.second.get());
    dl.front().second.get() = 'z';
    ASSERT_EQ(ht[dl.front().first], 'z');
    ASSERT_TRUE(ht.checkConsistency());
}