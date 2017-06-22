//
// Created by fer on 13/06/17.
//

#ifndef PROYECTO_TERRAINMAP_H
#define PROYECTO_TERRAINMAP_H


#include "Terrain/TerrainList.h"
#include "Terrain/Terrain.h"
#include <vector>

class TerrainMap {
    vector<vector<Terrain *>> tMap;
    int height;
    int width;
public:
    //Carga el mapa de terrenos, inicilizándolo to.do a plains y colocando rocas en lugares prefijados.
    void loadTerrainMap1();

    //Devuelve el tipo de terreno que hay en la pos enviada como atributo.
    Terrain *getTMap(int x, int y);

    //Sets el tipo de terreno que hay en la pos enviada como atributo.
    void setTMap(int x, int y, TerrainTypes type);

    //Devuelve un string con el mapa de tereno pintado.
    string showTMap();


    virtual ~TerrainMap();
};


#endif //PROYECTO_TERRAINMAP_H
