//
// Created by marek on 11/24/19.
//

#include <string>
#include <set>
#include <stdexcept>
#include <sstream>
#include <functional>
#include <list>
#include "config.h"

#ifndef MAREKOVAZOO_VYBEH_H
#define MAREKOVAZOO_VYBEH_H


/**
 * Stav vybehu v ZOO
 */
class Vybeh
{
private:
    /**
     * Velkost vybehu v m2
     */
    int velkost;
    /**
     * Nazov vybehu
     */
    std::string nazov;
    /**
     * S ktorymi vybehmi tento vybeh susedi
     */
    std::set<std::string> susedia;
    /**
     * Ci je vybeh vycisteny
     */
    bool cisty;
public:
    /**
     * Tovaren ktora skonstruuje vybehy z daneho vstupneho streamu a vrati ich v zozname
     * @param input vstupny stream
     * @param vybehy zoznam kam sa ulozia skonstruovane vybehy
     * @return referenciu na vstupny zoznam
     * @throws std::logic_error ak je vo vstupnom streame chyba
     */
    static std::list<Vybeh> & factory(std::istream & input, std::list<Vybeh> & vybehy)
    {
        while(!input.eof())
        {
            std::stringbuf sb;
            input.get( sb );
            std::string def = sb.str();
            if ( def.size() && (def[0] != '#' ))
                vybehy.emplace_back( Vybeh(def ));
            input.get();    //tymto vytiahneme zo streamu koniec riadku, lebo ten tam pri get() zostava
        }
    }
    Vybeh() {};
    /**
     * Vytvori objekt triedy Vybeh z jeho konfiguracie
     * @param definicia #meno velkost_m2 je_cisty susedia...
     */
    Vybeh(const std::string & definicia)
            : cisty(true)
    {
        //meno velkost_m2 je_cisty susedia...
        //rozparsujeme vstupny string pomocou std::istringstream
        std::istringstream iss(definicia);
        std::string jecisty;
        AnimalSize velkost_as;
        iss >> nazov >> velkost >> jecisty;
        while(!iss.eof())
        {
            std::string tmp;
            iss >> tmp;
            susedia.insert(tmp);
        }
        //skontrolujeme si ci vybeh nema viac susedov ako je dovolene -> nekonzistentna konfiguracia
        if( susedia.size() > VYBEH_MAX_SUSEDOV)
            throw std::logic_error("Vybeh moze mat najviac 3 susedov");
        //zistime ci je to dravec
        if( jecisty == "ano" )
            cisty = true;
        else if( jecisty == "nie")
            cisty = false;
        else
            throw std::logic_error("Neznama logicka hodnota pre cistotu vybehu, poznam len \"ano\" a \"nie\"");
    }
    /**
     * Destruktor
     */
    virtual ~Vybeh() {};
    /**
     * Vrati velkost vybehu v m2
     * @return velkost vybehu
     */
    int getVelkost() const {return velkost;}
    /**
     * Vrati nazov vybehu
     * @return nazov vybehu
     */
    std::string getNazov() const {return nazov;}
    /**
     * Vrati zoznam susednych vybehov
     * @param susedia mnozina do ktorej sa skopiruje zoznam susedov tohto vybehu
     */
    std::set<std::string> & getSusedia(std::set<std::string> & susedia) const {susedia = this->susedia; return susedia; }
    /**
     * Ak sa da (ak je vybeh prazdny), nastavi stav vybehu ako "cisty"
     */
    void vycisti() { cisty = true;}
    /**
     * Zisti ci je vybeh cistu alebo nie
     * @return ci je vybeh cisty
     */
    bool getCisty() const { return cisty;}
    /**
     * Porovna dva vybehy podla ich cisla
     * @param v druhy vybeh
     * @return true ak je nas vybeh mensi, false ak nie je mensi
     */
    bool operator < (const Vybeh & v) const
    {
        return nazov < v.nazov;
    }
    /**
     * Nastavi vybeh ako spinavy
     */
    void zaspin() {cisty = false;}

    /**
     * Metoda ktora vrati textovu reprezentaciu vybehu
     * @return string z ktoreho sa da vybez opat skonstruovat vybeh
     */
    std::string str() const
    {   //meno velkost_m2 je_cisty susedia...
        std::stringstream ss;
        ss << getNazov() << " " << getVelkost() << " " << ( getCisty() ? "ano" : "nie" );
        for(auto a: susedia)
            ss << " " << a;
        return ss.str();
    }

};

#endif //MAREKOVAZOO_VYBEH_H
