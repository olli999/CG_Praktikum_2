
#ifndef PRAKTIKUM_COLOR_H
#define PRAKTIKUM_COLOR_H

#include <iostream>

class Color
{
public:
    float R;
    float G;
    float B;

    Color();
    Color( float r, float g, float b);
    Color operator*(const Color& c) const;
    Color operator*(const float Factor) const;
    Color operator+(const Color& c) const;
    Color& operator+=(const Color& c);

};

#endif //PRAKTIKUM_COLOR_H
