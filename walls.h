//
// Created by ztrafas on 26.07.2020.
//

#ifndef MUZEUM_WALLS_H
#define MUZEUM_WALLS_H

#include "model.h"

namespace Models {
    namespace WallsInternal {
        extern float vertices[];
        extern float normals[];
        extern float vertexNormals[];
        extern float texCoords[];
        extern float colors[];
        extern unsigned int vertexCount;
    }

    class Walls: public Model {
    public:
        Walls();
        virtual ~Walls();
        virtual void drawSolid(bool smooth=false);
    };

    extern Walls walls;
}


#endif //MUZEUM_WALLS_H
