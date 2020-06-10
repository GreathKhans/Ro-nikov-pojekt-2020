//
// Created by marek on 11/24/19.
//

#ifndef MAREKOVAZOO_CONFIG_H
#define MAREKOVAZOO_CONFIG_H

#include <string>

#define VYBEH_MAX_SUSEDOV 3

/**
 * Enumeracia vsetkych moznych velkosti zvierat
 */
typedef enum AnimalSize
{
    small = 0,
    medium = 1,
    large = 2
} AnimalSize;

/**
 * Struktura definujuca priestorove naroky zivocisneho druhu podla jeho velkosti
 */
typedef struct SpaceReq
{
    AnimalSize size;                //velkost zvierata
    int spaceReqM2;                 //priestorove naroky zvierat tejto velkosti
    const std::string sizeString;   //citatelne oznacenie velkosti zvierat
} SpaceReq;

std::string getAnimalSizeString(AnimalSize as);
int getAnimalSpaceRequirements(AnimalSize as);
AnimalSize getAnimalSizeByString(const std::string & asstr);

#endif //MAREKOVAZOO_CONFIG_H
