//
// Created by marek on 11/24/19.
//

#ifndef MAREKOVAZOO_DRUH_H
#define MAREKOVAZOO_DRUH_H

#include <string>
#include "config.h"
#include <list>


class Druh
{
protected:
    std::string nazov;
    AnimalSize velkost;
    bool jeDravec;

public:
    /**
     * Tovaren ktora skonstruuje druhy z daneho vstupneho streamu a vrati ich v zozname
     * @param input vstupny stream
     * @param vybehy zoznam kam sa ulozia skonstruovane druhy
     * @return referenciu na vstupny zoznam
     * @throws std::logic_error ak je vo vstupnom streame chyba
     */
    static std::list<Druh> & factory(std::istream & input, std::list<Druh> & druhy)
    {
        while(!input.eof())
        {
            std::stringbuf sb;
            input.get( sb );
            std::string def = sb.str();
            if ( def.size() && (def[0] != '#' ))
                druhy.emplace_back( Druh(def ));
            input.get();    //tymto vytiahneme zo streamu koniec riadku, lebo ten tam pri get() zostava
        }
    }

    Druh() = default;
    explicit Druh(const std::string & definicia)
    {
        //rozparsujeme vstupny string pomocou std::istringstream
        std::istringstream iss(definicia);
        std::string nazov;
        std::string jedravec;
        std::string velkost;
        bool jedravec_bool = false;
        AnimalSize velkost_as;
        iss >> nazov >> jedravec >> velkost;
        //zistime ci je to dravec
        if( jedravec == "ano" )
            jedravec_bool = true;
        else if(  jedravec == "nie" )
            jedravec_bool = false;
        else
            throw std::logic_error("Neznama logicka hodnota pre dravca, poznam len \"ano\" a \"nie\"");
        //zistime si zo stringu velkost
        velkost_as = getAnimalSizeByString(velkost);

        this->velkost = velkost_as;
        this->jeDravec = jedravec_bool;
        this->nazov = nazov;
    }

    Druh(std::string nazov, AnimalSize velkost, bool jeDravec) : nazov(nazov), velkost(velkost), jeDravec(jeDravec) {}
    virtual ~Druh() {}
    std::string str() const
    {
        std::ostringstream oss;
        oss << getNazov() << " " << (getJeDravec() ? "ano" : "nie" ) << " " << getAnimalSizeString(getVelkost());
        return oss.str();
    }
    std::string getNazov() const { return nazov;}
    AnimalSize getVelkost() const {return velkost;}
    bool getJeDravec() const { return jeDravec;}
};


#endif //MAREKOVAZOO_DRUH_H
