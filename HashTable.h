//
// Created by marek on 11/24/19.
//

#ifndef MAREKOVAZOO_HASHTABLE_H
#define MAREKOVAZOO_HASHTABLE_H

#include <set>
#include "hashtable.h"
#include <map>
#include <cstring>
#include <list>
#include <functional>

/**
 * Asociativne pole pomocou hesovacej tabulky.
 *
 * Kluc musi byt pouzitelny v troch operaciach: == (porovnanie), % (modulo cize zvysok po deleni) a < (mensi)
 * Takze v pripade ak typ kluc nie je jednoduchy typ (ako napr. int), musi typ kluc implementovat tieto operatory
 * nasledovnym sposobom:
 * bool operator ==(const myclass & other) const { return value == other.value; }
 *    tento je potrebny pre porovnavanie klucov v HashTable
 * int operator %(const int x) const { return value % x;}
 *    tento je potrebny pre vypocet hashu kluca
 * bool operator <(const myclass & other) const { return value < other.value; }
 *    tento je potrebny v HashTable.keys, aby sa dal kluc zaradit do zoznamu - std::set vyzaduje aby jeho prvky
 *    boli porovnatelne

 * @tparam Key typ klucov
 * @tparam Value typ hodnot
 */
template <class Key, class Value> class HashTable
{
public:
    /**
     * Typ poloziek tabulky - dvojic (kluc, hodnota)
     */
    typedef std::tuple<Key, Value> ItemType;
    /**
     * Typ zoznamu s ktorym pracuje metoda values
     */
    typedef std::list<std::reference_wrapper<Value>> ValueList;
    /**
     * Typ zoznamu s ktorym pracuje metoda data
     */
    typedef std::list<std::pair<Key, std::reference_wrapper<Value>>> DataList;

private:
    typedef struct BucketNode
    {
        BucketNode * next;
        Key key;
        Value value;
        BucketNode(Key key, Value value) : key(key), value(value), next( nullptr) {}
        BucketNode() {memset(this, sizeof(BucketNode), 0 );}
    } BucketNode;

    int size;
    BucketNode ** table;
    int buckets;

public:
    /**
     * Vytvori prazdnu hesovaciu tabulku
     */
    HashTable( int tableSize = 20)
    : size(tableSize)
    , buckets(0)
    {
        table = new BucketNode*[size](); //zatvorky na konci zabezpecia inicializaciu na NULL
    }

    /**
     * destruktor
     */
    virtual ~HashTable()
    {
        delete table;
    }

    /**
     * Prida dvojicu (kluc,hodnota) do tabulky, alebo zmeni hodnotu ak uz kluc existuje
     * @param key kluc
     * @param value hodnota
     */
    virtual void add(const Key & key, const Value & value)
    {
        int hashKey = hash(key);
        //prehladame buckety, najdeme kluc alebo pridame za posledny
        auto bucket = table[hashKey];
        BucketNode * prevBucket = nullptr;
        while(bucket != nullptr)
        {
            if(bucket->key == key)
            {
                bucket->value = value;
                break;
            }
            prevBucket = bucket;
            bucket = bucket->next;
        }
        if(bucket == nullptr)
        {
            BucketNode * newBucket = new BucketNode(key, value);
            buckets ++;
            if(prevBucket == nullptr)   //znamena ze v table[hashKey] je nullptr -> zoznam bucketov je prazdny
                table[hashKey] = newBucket;
            else
                prevBucket->next = newBucket;
        }
    }

    /**
     * Vymaze dvojicu(kluc, hodnota) z tabulky pre zadany hluc
     * @param key zadany kluc
     */
    virtual void del(const Key & key)
    {
        int hashKey = hash(key);
        auto bucket = table[hashKey];
        BucketNode * prevBucket = nullptr;
        while(bucket != nullptr)
        {
            if(bucket->key == key)
            {
                if(prevBucket == nullptr)
                    table[hashKey] = bucket->next;
                else
                    prevBucket->next = bucket->next;
                delete bucket;
                buckets --;
                break;
            }
            prevBucket = bucket;
            bucket = bucket->next;
        }
    }

    /**
     * Vrati hodnotu pre zadany kluc
     * @param key zadany kluc
     * @return
     */
    virtual Value get(const Key & key) const
    {
        int hashKey = hash(key);
        auto bucket = table[hashKey];
        while(bucket != nullptr)
            if(bucket->key == key)
                return bucket->value;
        throw std::logic_error("No such key");
    }

    /**
     * Vrati pocet prvkov asociativneho pola
     * @return pocet prvkov asociativneho pola
     */
    virtual int len() const { return buckets; }

    /**
     * Vrati zoznam vsetkych klucov v asoc.poli
     * @param keys mnozina do ktorej sa nakopiruju kluce
     */
    virtual void keys(std::set<Key> & keys) const
    {
        for(int i = 0; i < size; i ++)
        {
            for(auto bucket = table[i]; bucket != nullptr; bucket = bucket->next)
                keys.insert(bucket->key);
        }
    }

    /**
     * Metoda ktora vrati *hodnoty* z nasho asociativneho pola vo forme referencii, takze sa nekopiruju a zaroven sa daju menit
     * @param values zoznam do ktoreho sa ulozia referencie (vo forme std::reference_wrapper) na vsetky hodnoty pola
     */
    virtual ValueList & values(ValueList & val)
    {
        for(int i = 0; i < size; i ++)
        {
            for(auto bucket = table[i]; bucket != nullptr; bucket = bucket->next)
                val.push_back(std::ref(bucket->value));
        }
        return val;
    }

    virtual DataList & data(DataList & dat)
    {
        for(int i = 0; i < size; i ++)
        {
            for(auto bucket = table[i]; bucket != nullptr; bucket = bucket->next)
                dat.push_back(std::make_pair(bucket->key, std::ref(bucket->value)));
        }
        return dat;
    }

    /**
     * Zisti ci daky kluc existuje v tabulke.
     * @param key kluc ktory sa hlada
     * @return true ak sa kluc v tabulke nachadza, false ak sa v nej nenachadza
     */
    bool exists(const Key & key)
    {
        int hashKey = hash(key);
        auto bucket = table[hashKey];
        while(bucket != nullptr)
            if(bucket->key == key)
                return true;
            else
                bucket = bucket->next;
        return false;
    }

    bool checkConsistency()
    {
        int countedKeys = 0;
        for(int i = 0; i < size; i ++)
        {
            for(BucketNode * bucket = table[i]; bucket != nullptr; bucket = bucket->next)
            {
                countedKeys ++;
                if(hash(bucket->key) != i)
                    return false;
            }
        }
        return countedKeys == buckets;
    }

    /**
     * Vrati referenciu na hodnotu daneho kluca. Ak kluc neexistuje, vytvori zaznam s tymto klucom a prazdnou hodnotou
     * (inicializovanou na 0). Toto je standardny sposob akym pracuje aj operator [] v std::map. Umoznuje to pouzit
     * operator [] na citanie i zapis, ale ak sa pokusime citat neexistujuci prvok, bude automaticky vytvoreny - pretoze
     * nevieme, ci sa volajuci kod snazi o citanie alebo zapis. Ak by sme v pripade neexistujuceho kluca vyvolali
     * vynimku, znemoznimi by sme pridavat nove kluce pomocou operatora [].
     * @param key kluc ktoreho hodnotu chceme referencovat
     * @return referencia na hodnotu patriacu k danemu klucu, alebo na prazdnu hodnotu (ak zaznam s danym klucom
     * neexistoval)
     */
    Value &operator [](const Key & key)
    {
        int hashKey = hash(key);
        auto bucket = table[hashKey];
        BucketNode * prevBucket = nullptr;
        while(bucket != nullptr)
        {
            if ( bucket->key == key )
                return bucket->value;
            else
            {
                prevBucket = bucket;
                bucket = bucket->next;
            }
        }
        auto * newBucket = new BucketNode();
        newBucket->key = key;
        newBucket->next = nullptr;
        buckets ++;
        if(prevBucket == nullptr)
            table[hashKey] = newBucket;
        else
            prevBucket->next = newBucket;
        return newBucket->value;
    }

protected:
    /**
     * Vypocita hash pre zadany kluc
     * @param key zadany kluc
     * @return vypocitana hodnota hashu
     */
    int hash(const Key & key) const {return key % size;}
};

int operator % (const std::string & str, const int & x );


#endif //MAREKOVAZOO_HASHTABLE_H
