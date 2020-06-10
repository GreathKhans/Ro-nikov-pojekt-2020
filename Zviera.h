//
// Created by marek on 11/24/19.
//

#ifndef MAREKOVAZOO_ZVIERA_H
#define MAREKOVAZOO_ZVIERA_H

#include <string>
#include <set>
#include <sstream>
#include "Druh.h"

class Zviera
{
protected:
    std::string meno;
    std::string druh;
    std::string vybeh;
public:
    /**
 * Tovaren ktora skonstruuje zvierata z daneho vstupneho streamu a vrati ich v zozname
 * @param input vstupny stream
 * @param vybehy zoznam kam sa ulozia skonstruovane zvierata
 * @return referenciu na vstupny zoznam
 * @throws std::logic_error ak je vo vstupnom streame chyba
 */
    static std::list<Zviera> & factory(std::istream & input, std::list<Zviera> & zvierata)
    {
        while(!input.eof())
        {
            std::stringbuf sb;
            input.get( sb );
            std::string def = sb.str();
            if ( def.size() && (def[0] != '#' ))
                zvierata.emplace_back( Zviera(def ));
            input.get();    //tymto vytiahneme zo streamu koniec riadku, lebo ten tam pri get() zostava
        }
    }

    Zviera() = default;

    explicit Zviera(const std::string & definicia)
    {
        std::stringstream ss(definicia);
        ss >> meno >> druh >> vybeh;
    }
    virtual ~Zviera() = default;
    Zviera( const std::string meno, const std::string druh, const std::string vybeh )
    : meno(meno)
    , druh(druh)
    , vybeh(vybeh)
    {}

    std::string getDruh() const { return druh;}
    std::string getMeno() const { return meno;}
    std::string getVybeh() const {return vybeh; }

    /**
     * Vrati textovu reprezentaciu zvierata
     * @return string obsahujuci definiciu zvierata, z ktorej sa da zviera zase skonstruovat
     */
    std::string str()
    {   //meno druh vybeh
        std::stringstream ss;
        ss << getMeno() << " " << getDruh() << " " << getVybeh();
        return ss.str();
    }

    bool operator ==(const Zviera & other) const { return meno == other.meno; }
    int operator %(const int x) const { return ( std::hash<std::string>{}(meno) ) % x; }
    bool operator <(const Zviera & other) const { return meno < other.meno; }
};


#endif //MAREKOVAZOO_ZVIERA_H
