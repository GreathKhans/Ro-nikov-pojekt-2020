//
// Created by marek on 11/24/19.
//

#ifndef MAREKOVAZOO_ZOO_H
#define MAREKOVAZOO_ZOO_H

#include <iostream>
#include "HashTable.h"
#include "Vybeh.h"
#include "Druh.h"
#include "Zviera.h"

/**
 * Trieda implementujuca stav zoologickej zahrady.
 * Zahrada obsahuje vybehy a zvierata. Zvierata patraia k zivocisnym druhom.
 */
class Zoo
{
protected:
    /*
    HashTable<int, Vybeh> vybehy;
    HashTable<int, Zviera> zvierata;
    HashTable<int, Druh> druhy;
     */

    HashTable<std::string, Zviera> zvierata;
    HashTable<std::string, Vybeh> vybehy;
    HashTable<std::string, Druh> druhy;
    HashTable<Zviera, Druh> druhyZvierat;   // meno_zvierata -> meno_druhu
    HashTable<Zviera, Vybeh> umiestnenieZvierat; //meno_zvierata -> meno_vybehu

public:
    /**
     * Vytvori ZOO nacitanim vybehov, druhov zvierat a samotnych zvierat zo vstupnych streamov.
     * @param vybehy stream s konfiguraciou vybehov
     * @param druhy stream s konfiguraciou zivocisnych druhov
     * @param zvierata stream s konfiguraciou existujucich zvierat
     */
    Zoo( std::istream & isv, std::istream & isd, std::istream & isz)
    {
        std::list<Vybeh> lv;
        Vybeh::factory(isv, lv);
        for(const auto & v: lv)
            vybehy[v.getNazov()] = v;

        std::list<Druh> ld;
        Druh::factory(isd, ld);
        for(const auto & d: ld)
            druhy[d.getNazov()] = d;

        std::list<Zviera> lz;
        Zviera::factory(isz, lz);
        for(const auto & z: lz)
            pridajZviera(z);
    }

    /**
     * Destruktor.
     */
    virtual ~Zoo() {};

    /**
     * Ulozi aktualny stav ZOO do vystupnych prudov tak, ze je ho z nich mozne neskor nacitat.
     * @param vybehy vystupny prud pre vybehy
     * @param druhy vystupny prud pre zivocisne druhy
     * @param zvierata vystupny prud pre zvierata vo vybehoch
     */
    virtual void ulozZoo(std::ostream & vybehyOs, std::ostream & druhyOs, std::ostream & zvierataOs)
    {
        std::list<std::reference_wrapper<Vybeh>> v;
        vybehy.values(v);
        for(auto a: v)
            vybehyOs << a.get().str() << std::endl;
        std::list<std::reference_wrapper<Druh>> d;
        druhy.values(d);
        for(auto a: d)
            druhyOs << a.get().str() << std::endl;
        std::list<std::reference_wrapper<Zviera>> z;
        zvierata.values(z);
        for(auto a: z)
            zvierataOs << a.get().str() << std::endl;
    }

    /**
     * Prida zviera urceneho zivocisneho druhu do zadaneho vybehu
     * @param meno meno zvierata ktore pridavame
     * @param druh zivocisny druh zvierata
     * @param vybeh vybeh do ktoreho sa ma zviera pridat
     */
    void pridajZviera( const std::string & meno, const std::string & druh, const std::string & vybeh )
    {
        if(!zvierata.exists(meno))
        {
            Zviera z( meno, druh, vybeh );
            pridajZviera( z );
        }
        else
            throw std::logic_error("Dane zviera uz existuje");
    }

    /**
     * Prida zviera urceneho zivocisneho druhu do zadaneho vybehu. Ak zviera do daneho vybehu nie je mozne pridat, hodi
     * vynimku std::logic_error
     * Zviera mozno pridat:
     * - ak nie je dravec tak do vybehu s ne-dravcami ak sa don zmesti, alebo cisteho vybehu ak sa don zmesti
     * - ak je dravec tak do vybehu s rovnakym druhom ak sa don zmesti, alebo cisteho vybehu ktory nema suseda obsahujuceho dravca, ak sa don zmesti
     * @param zviera definicia pridavaneho zvierata
     * @throws std::logic_error ak zviera nie je mozne pridat
     */
    void pridajZviera(Zviera zviera)
    {
        //1. test - duplicitne meno zvierata

        //2. test - nedravec do cisteho vybehu alebo vybehu s nedravcami

        //3. test - dravec do vybehu s rovnakym druhom alebo cisteho vybehu ktory nema suseda s dravcami

        //4. test - ci sa zmesti do vybehu kam ho davame

        //testy uspesne prejdene - pridavame zviera
        zvierata[zviera.getMeno()] = zviera;
        umiestnenieZvierat[zviera] = najdiVybehPodlaMena(zviera.getVybeh());
        druhyZvierat[zviera] = najdiDruhPodlaMena(zviera.getDruh());
    }

    /**
     * Odoberie zadane zviera zo ZOO. Ak sa to neda, napr. ak zviera neexistuje, hodi std::logic_error
     * @param zviera meno zvierata na odobranie
     */
    void odoberZviera( const std::string & meno )
    {
        //1. odstranit z druhov
        druhyZvierat.del(zvierata[meno]);
        //2. odstranit z vybehov
        umiestnenieZvierat.del(zvierata[meno]);
        //3. odstranit zo zvierata
        zvierata.del(meno);
    }

    /**
     * Zisti v ktorom vybehu sa dane zviera nachadza
     * @param zviera meno zvierata ktoreho vybeh chceme zistit
     * @return meno vybehu v ktorom je dane zviera, alebo prazdy retazec ak take zviera nie je v ziadnom vybehu
     */
    std::string dajVybehPreZviera( const std::string meno);

    /**
     * Najde referenciu na zadany vybeh
     * @param menoVybehu meno daneho vybehu
     * @return vybeh zodpovedajuci menu, ak existuje
     * @throws std::logic error ak vybeh s danym menom neexistuje
     */
    const Vybeh najdiVybehPodlaMena(const std::string & menoVybehu)
    {
        return vybehy.get(menoVybehu);
    }
    /**
     * Najde referenciu na zadany vybeh
     * @param menoVybehu meno daneho vybehu
     * @return vybeh zodpovedajuci menu, ak existuje
     * @throws std::logic error ak vybeh s danym menom neexistuje
     */
    const Druh najdiDruhPodlaMena(const std::string & menoDruhu)
    {
        return druhy.get(menoDruhu);
    }
};


#endif //MAREKOVAZOO_ZOO_H
