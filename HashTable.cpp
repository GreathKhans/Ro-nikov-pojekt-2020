//
// Created by marek on 11/24/19.
//

#include "HashTable.h"
#include <functional>

/**
 * Hesovacia funkcia nasej tabulky. Vyuzivame standardne hesovacie funktory* std::hash z <functional> headeru,
 * vid https://en.cppreference.com/w/cpp/utility/hash
 * Ak chceme ako kluc pouzit nasu vlastnu triedu pre ktoru nie je specializacia std::hash, musime spravit vlastny
 * funktor ako je ukazane v https://stackoverflow.com/questions/8157937/how-to-specialize-stdhashkeyoperator-for-user-defined-type-in-unordered
 *
 * Priklad:
 * namespace std {  //nas funktor musime vlozit do menneho priestoru std, lebo odtial sa beru hesovacie funktory
 *   template <> struct hash<MojaTrieda>    //nas funktor bude struktura
 *   {
 *     size_t operator()(const MojaTrieda & x) const    //pretazenie operatora () znamena ze strukturu vieme volat ako funkciu
 *     {
 *       moj kod, napr. "return hash<int>()(x.hodnota);"    //tento kod sa vykona ked zavolame nas funktor pomocou ()
 *     }
 *   };
 * }
 *
 *  * - funktor je nejaky objekt (instancia triedy alebo struktury) ktory sa vola rovnako ako funkcia pomocou (), cize
 *      ma pretazeny operator (). Jeho zmyslom je dodat funkciu ktora berie urcity konstantny pocet argumentov, ale pritom
 *      sa da nejako parametrizovat. Kedze parametrizacia pomocou globalnych premennych je hlupa a nebezpecna, robime
 *      to pomocou triedy (alebo struktury) v ktorej si nastavime parametre ako chceme, a potom ju vieme volat rovnako
 *      ako funkciu kvoli pretazeniu operatora (). Vyborne vysvetlenie je: https://www.geeksforgeeks.org/functors-in-cpp/
 *
 * @tparam T1 trieda kluca
 * @tparam T2 trieda hodnoty
 * @param key kluc pre ktory chceme hash
 * @return hash pre zadany kluc key
 */
 /*
template <class T1, class T2> int HashTable<T1,T2>::hash(T1 key)
{
    return hashFunctor(key);
}
  */

int operator % (const std::string & str, const int & x )
{
    return std::hash<std::string>{}(str)% x;
}


