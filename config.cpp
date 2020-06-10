//
// Created by marek on 11/24/19.
//

#include <stdexcept>
#include "config.h"

/**
 * Konfiguracia priestorovych narokov zivocisnych druhov v ZOO
 */
const SpaceReq animalSpaceRequirements[3] =
        {
                { small, 1, "male"},        //male zvierata -> 1 m2
                { medium, 5, "stredne"},    //stredne zvierata -> 3 m2
                { large, 10, "velke"}       //velke zvierata -> 10 m2

        };

std::string getAnimalSizeString(AnimalSize as)
{
    for(int i = 0; i < sizeof(animalSpaceRequirements) / sizeof(SpaceReq); i ++)
        if(animalSpaceRequirements[i].size == as)
            return animalSpaceRequirements[i].sizeString;
    return "";
}

int getAnimalSpaceRequirements(AnimalSize as)
{
    for(int i = 0; i < sizeof(animalSpaceRequirements) / sizeof(SpaceReq); i ++)
        if(animalSpaceRequirements[i].size == as)
            return animalSpaceRequirements[i].spaceReqM2;
    return -1;
}

AnimalSize getAnimalSizeByString(const std::string & asstr)
{
    for(int i = 0; i < sizeof(animalSpaceRequirements) / sizeof(SpaceReq); i ++)
        if(! animalSpaceRequirements[i].sizeString.compare(asstr))
            return animalSpaceRequirements[i].size;

    throw std::logic_error("Animal size " + asstr + " is undefined");
}
