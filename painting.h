#ifndef MUZEUM_PAINTING_H
#define MUZEUM_PAINTING_H

#include "model.h"

namespace Models {
    namespace PaintingInternal {
        extern float vertices[];
        extern float normals[];
        extern float vertexNormals[];
        extern float texCoords[];
        extern float colors[];
        extern unsigned int vertexCount;
    }

    class Painting: public Model {
    public:
        Painting();
        virtual ~Painting();
        virtual void drawSolid(bool smooth=false);
    };

    extern Painting painting;
}



#endif //MUZEUM_PAINTING_H
