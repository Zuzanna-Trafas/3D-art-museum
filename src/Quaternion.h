//
// Created by ztrafas on 28.08.2020.
//

#ifndef MUZEUM_QUATERNION_H
#define MUZEUM_QUATERNION_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Quaternion {
private:
    float x, y, z, w;
public:
    Quaternion();
    Quaternion(float _x, float _y, float _z, float _w);
    void normalize();
    glm::mat4 toRotationMatrix();
    Quaternion fromMatrix(glm::mat4 matrix);
    Quaternion interpolate(Quaternion a, Quaternion b, float blend);
};


#endif //MUZEUM_QUATERNION_H
