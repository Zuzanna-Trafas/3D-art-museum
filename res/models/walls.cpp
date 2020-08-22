
#include "walls.h"

namespace Models {

    Walls walls;

    Walls::Walls() {
        vertices = WallsInternal::vertices;
        normals = WallsInternal::normals;
        vertexNormals = WallsInternal::vertexNormals;
        texCoords = WallsInternal::texCoords;
        colors = WallsInternal::colors;
        vertexCount = WallsInternal::vertexCount;
    }

    Walls::~Walls() {
    }

    void Walls::drawSolid(bool smooth) {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);


        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices);
        if (!smooth) glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);
        else glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, vertexNormals);
        glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords);
        glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, colors);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
    }

    void Walls::drawWalls(GLuint walls,GLuint floors,GLuint ceilings) {
        // walls

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, texCoords);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, colors);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, walls);

        glEnableVertexAttribArray(4);
        glUniform1i(4, 0);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);

        //floors

        unsigned int floorVertexCount = 12;

        float floorVertices[] = {
                -1.0f, -1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, -1.0f, 1.0f,

                -1.0f, -1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f, 1.0f,


                0.15f, -1.0f, -2.0f, 1.0f,
                -0.15f, -1.0f, -1.0f, 1.0f,
                -0.15f, -1.0f, -2.0f, 1.0f,

                0.15f, -1.0f, -2.0f, 1.0f,
                0.15f, -1.0f, -1.0f, 1.0f,
                -0.15f, -1.0f, -1.0f, 1.0f,
        };

        float floorColors[] = {
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

        };

        float floorNormals[] = {
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,

                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,

                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,

                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,

        };


        float floorVertexNormals[] = {
                -1.0f, -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 0.0f,
                1.0f, -1.0f, -1.0f, 0.0f,

                -1.0f, -1.0f, -1.0f, 0.0f,
                -1.0f, -1.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 0.0f,

                0.15f, -1.0f, -2.0f, 0.0f,
                -0.15f, -1.0f, -1.0f, 0.0f,
                -0.15f, -1.0f, -2.0f, 0.0f,

                0.15f, -1.0f, -2.0f, 0.0f,
                0.15f, -1.0f, -1.0f, 0.0f,
                -0.15f, -1.0f, -1.0f, 0.0f,
        };


        float floorTexCoords[] = {
                1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                0.575f, 0.0f, 0.425f, 1.0f, 0.425f, 0.0f,
                0.575f, 0.0f, 0.575f, 1.0f, 0.425f, 1.0f,
        };

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, floorVertices);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, floorNormals);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, floorTexCoords);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, floorColors);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, floors);

        glEnableVertexAttribArray(4);
        glUniform1i(4, 0);

        glDrawArrays(GL_TRIANGLES, 0, floorVertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);

        // ceiling

        unsigned int ceilingVertexCount = 12;

        float ceilingVertices[] = {
                -1.0f, 1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, -1.0f, 1.0f,

                -1.0f, 1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,


                0.15f, 0.5f, -2.0f, 1.0f,
                -0.15f, 0.5f, -1.0f, 1.0f,
                -0.15f, 0.5f, -2.0f, 1.0f,

                0.15f, 0.5f, -2.0f, 1.0f,
                0.15f, 0.5f, -1.0f, 1.0f,
                -0.15f, 0.5f, -1.0f, 1.0f,
        };

        float ceilingColors[] = {
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

        };

        float ceilingNormals[] = {
                0.0f, -1.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 0.0f,

                0.0f, -1.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 0.0f,

                0.0f, -1.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 0.0f,

                0.0f, -1.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f, 0.0f,

        };


        float ceilingVertexNormals[] = {
                -1.0f, 1.0f, -1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, -1.0f, 0.0f,

                -1.0f, 1.0f, -1.0f, 0.0f,
                -1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 0.0f,

                0.15f, 0.5f, -2.0f, 0.0f,
                -0.15f, 0.5f, -1.0f, 0.0f,
                -0.15f, 0.5f, -2.0f, 0.0f,

                0.15f, 0.5f, -2.0f, 0.0f,
                0.15f, 0.5f, -1.0f, 0.0f,
                -0.15f, 0.5f, -1.0f, 0.0f,

        };


        float ceilingTexCoords[] = {
                1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                0.575f, 0.0f, 0.425f, 1.0f, 0.425f, 0.0f,
                0.575f, 0.0f, 0.575f, 1.0f, 0.425f, 1.0f,
        };

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, ceilingVertices);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, ceilingNormals);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, ceilingTexCoords);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, ceilingColors);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ceilings);

        glEnableVertexAttribArray(4);
        glUniform1i(4, 0);

        glDrawArrays(GL_TRIANGLES, 0, ceilingVertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);
    }

    namespace WallsInternal {
        unsigned int vertexCount = 60;

        float vertices[] = {
                -0.15f, -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f, 1.0f,

                -0.15f, -1.0f, -1.0f, 1.0f,
                -0.15f, 1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f, 1.0f,

                1.0f, -1.0f, -1.0f, 1.0f,
                0.15f, 1.0f, -1.0f, 1.0f,
                0.15f, -1.0f, -1.0f, 1.0f,

                1.0f, -1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, -1.0f, 1.0f,
                0.15f, 1.0f, -1.0f, 1.0f,


                0.15f, 0.5f, -1.0f, 1.0f,
                -0.15f, 1.0f, -1.0f, 1.0f,
                -0.15f, 0.5f, -1.0f, 1.0f,

                0.15f, 0.5f, -1.0f, 1.0f,
                0.15f, 1.0f, -1.0f, 1.0f,
                -0.15f, 1.0f, -1.0f, 1.0f,


                -1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f, 1.0f,

                -1.0f, -1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,



                1.0f, -1.0f, -0.15f, 1.0f,
                1.0f, 1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, -1.0f, 1.0f,

                1.0f, -1.0f, -0.15f, 1.0f,
                1.0f, 1.0f, -0.15f, 1.0f,
                1.0f, 1.0f, -1.0f, 1.0f,


                1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 0.15f, 1.0f,
                1.0f, -1.0f, 0.15f, 1.0f,

                1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 0.15f, 1.0f,


                1.0f, 0.5f, 0.15f, 1.0f,
                1.0f, 1.0f, -0.15f, 1.0f,
                1.0f, 0.5f, -0.15f, 1.0f,

                1.0f, 0.5f, 0.15f, 1.0f,
                1.0f, 1.0f, 0.15f, 1.0f,
                1.0f, 1.0f, -0.15f, 1.0f,

                -1.0f, -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f, 1.0f,

                -1.0f, -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, 1.0f,

                // korytarz

                -0.15f, -1.0f, -1.0f, 1.0f,
                -0.15f, 0.5f, -2.0f, 1.0f,
                -0.15f, -1.0f, -2.0f, 1.0f,

                -0.15f, -1.0f, -1.0f, 1.0f,
                -0.15f, 0.5f, -1.0f, 1.0f,
                -0.15f, 0.5f, -2.0f, 1.0f,

                0.15f, -1.0f, -1.0f, 1.0f,
                0.15f, 0.5f, -2.0f, 1.0f,
                0.15f, -1.0f, -2.0f, 1.0f,

                0.15f, -1.0f, -1.0f, 1.0f,
                0.15f, 0.5f, -1.0f, 1.0f,
                0.15f, 0.5f, -2.0f, 1.0f,
        };

        float colors[] = {
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 0.0f, 1.0f,

                0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 0.0f, 1.0f,

                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                1.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.0f, 1.0f,

                1.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.0f, 1.0f,

                0.0f, 1.0f, 1.0f, 1.0f,
                0.0f, 1.0f, 1.0f, 1.0f,
                0.0f, 1.0f, 1.0f, 1.0f,

                0.0f, 1.0f, 1.0f, 1.0f,
                0.0f, 1.0f, 1.0f, 1.0f,
                0.0f, 1.0f, 1.0f, 1.0f,

                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,

                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,

                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,

                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,

                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,

                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,


                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
        };

        float normals[] = {
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,

                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,

                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,

                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,

                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,

                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,

                0.0f, 0.0f, -1.0f, 0.0f,
                0.0f, 0.0f, -1.0f, 0.0f,
                0.0f, 0.0f, -1.0f, 0.0f,

                0.0f, 0.0f, -1.0f, 0.0f,
                0.0f, 0.0f, -1.0f, 0.0f,
                0.0f, 0.0f, -1.0f, 0.0f,

                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,

                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,

                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,

                // korytarz

                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,

                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,

                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, 0.0f, 0.0f,
        };

        float vertexNormals[] = {
                -0.15f, -1.0f, -1.0f, 0.0f,
                -1.0f, 1.0f, -1.0f, 0.0f,
                -1.0f, -1.0f, -1.0f, 0.0f,

                -0.15f, -1.0f, -1.0f, 0.0f,
                -0.15f, 1.0f, -1.0f, 0.0f,
                -1.0f, 1.0f, -1.0f, 0.0f,


                1.0f, -1.0f, -1.0f, 0.0f,
                0.15f, 1.0f, -1.0f, 0.0f,
                0.15f, -1.0f, -1.0f, 0.0f,

                1.0f, -1.0f, -1.0f, 0.0f,
                1.0f, 1.0f, -1.0f, 0.0f,
                0.15f, 1.0f, -1.0f, 0.0f,


                0.15f, 0.5f, -1.0f, 0.0f,
                -0.15f, 1.0f, -1.0f, 0.0f,
                -0.15f, 0.5f, -1.0f, 0.0f,

                0.15f, 0.5f, -1.0f, 0.0f,
                0.15f, 1.0f, -1.0f, 0.0f,
                -0.15f, 1.0f, -1.0f, 0.0f,


                -1.0f, -1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 0.0f,

                -1.0f, -1.0f, 1.0f, 0.0f,
                -1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 0.0f,

                1.0f, -1.0f, -0.15f, 0.0f,
                1.0f, 1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, -1.0f, 0.0f,

                1.0f, -1.0f, -0.15f, 0.0f,
                1.0f, 1.0f, -0.15f, 0.0f,
                1.0f, 1.0f, -1.0f, 0.0f,

                1.0f, -1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.15f, 0.0f,
                1.0f, -1.0f, 0.15f, 0.0f,

                1.0f, -1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.15f, 0.0f,

                1.0f, 0.5f, 0.15f, 0.0f,
                1.0f, 1.0f, -0.15f, 0.0f,
                1.0f, 0.5f, -0.15f, 0.0f,

                1.0f, 0.5f, 0.15f, 0.0f,
                1.0f, 1.0f, 0.15f, 0.0f,
                1.0f, 1.0f, -0.15f, 0.0f,


                -1.0f, -1.0f, -1.0f, 0.0f,
                -1.0f, 1.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 1.0f, 0.0f,

                -1.0f, -1.0f, -1.0f, 0.0f,
                -1.0f, 1.0f, -1.0f, 0.0f,
                -1.0f, 1.0f, 1.0f, 0.0f,

                // korytarz

                -0.15f, -1.0f, -1.0f, 0.0f,
                -0.15f, 0.5f, -2.0f, 0.0f,
                -0.15f, -1.0f, -2.0f, 0.0f,

                -0.15f, -1.0f, -1.0f, 0.0f,
                -0.15f, 0.5f, -1.0f, 0.0f,
                -0.15f, 0.5f, -2.0f, 0.0f,

                0.15f, -1.0f, -1.0f, 0.0f,
                0.15f, 0.5f, -2.0f, 0.0f,
                0.15f, -1.0f, -2.0f, 0.0f,

                0.15f, -1.0f, -1.0f, 0.0f,
                0.15f, 0.5f, -1.0f, 0.0f,
                0.15f, 0.5f, -2.0f, 0.0f,
        };

        float texCoords[] = {
                0.425f, 0.0f, 0.f, 1.0f, 0.0f, 0.0f,
                0.425f, 0.0f, 0.425f, 1.0f, 0.0f, 1.0f,

                1.0f, 0.0f, 0.575f, 1.0f, 0.575f, 0.0f,
                1.0f, 0.0f, 1.0f, 1.0f, 0.575f, 1.0f,

                0.575f, 0.75f, 0.425f, 1.0f, 0.425f, 0.75f,
                0.575f, 0.75f, 0.575f, 1.0f, 0.425f, 1.0f,

                1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                0.425f, 0.0f, 0.f, 1.0f, 0.0f, 0.0f,
                0.425f, 0.0f, 0.425f, 1.0f, 0.0f, 1.0f,

                1.0f, 0.0f, 0.575f, 1.0f, 0.575f, 0.0f,
                1.0f, 0.0f, 1.0f, 1.0f, 0.575f, 1.0f,

                0.575f, 0.75f, 0.425f, 1.0f, 0.425f, 0.75f,
                0.575f, 0.75f, 0.575f, 1.0f, 0.425f, 1.0f,

                1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                //korytarz

                1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

                1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        };
    }
}