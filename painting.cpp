
#include "painting.h"

namespace Models {

    Painting painting;

    Painting::Painting() {
        vertices=PaintingInternal::vertices;
        normals=PaintingInternal::normals;
        vertexNormals=PaintingInternal::vertexNormals;
        texCoords=PaintingInternal::texCoords;
        colors=PaintingInternal::colors;
        vertexCount=PaintingInternal::vertexCount;
    }

    Painting::~Painting() {}




    namespace PaintingInternal {
        unsigned int vertexCount=36;

        float vertices[]={



        };

        float colors[]={

        };

        float normals[]={

        };

        float vertexNormals[]={

        };

        float texCoords[]={

        };
    }
}