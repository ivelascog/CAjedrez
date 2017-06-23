//
// Created by fer on 15/06/17.
//

#ifndef PROYECTO_TERRAIN_H
#define PROYECTO_TERRAIN_H

#include <stdlib.h>
#include <string>
#include "TerrainNames.h"

using namespace std;

enum TerrainTypes {
    plains = 0, rocks = 1
};

class Terrain {
protected:
    bool obstacle;
    TerrainTypes type;
    char icon = '?';
    int penMov = 0;
    int height = 0;
    bool horizontal = true;
    bool vertical = true;
public:
    //Devuelve si el mapa de terreno es horizontal.
    bool isHorizontal() const;

    //Devuelve si el mapa de terreno es vertical.
    bool isVertical() const;

    //Devuelve la altura del mapa de terreno.
    int getHeight() const;

    //Devuelve la penalización de movimiento.
    int getPenMov() const;

    //Devuelve el icono del terreno.
    char getIcon();

    //Devuelve si ese terreno es un obstáculo.
    bool isObstacle() const;

    string terrainStats();
};


#endif //PROYECTO_TERRAIN_H
