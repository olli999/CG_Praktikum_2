#include "vector.h"
#include <assert.h>
#include <math.h>
#include <iostream>

#define EPSILON 1e-6

Vector::Vector(float x, float y, float z) {
    this->X = x;
    this->Y = y;
    this->Z = z;
}

Vector::Vector() {
}

float Vector::dot(const Vector &v) const {
    return ((X * v.X)
            + (Y * v.Y)
            + (Z * v.Z));
}

Vector Vector::cross(const Vector &v) const {
    return Vector(((Y * v.Z) - (Z * v.Y)),
                  ((Z * v.X) - (X * v.Z)),
                  ((X * v.Y) - (Y * v.X)));
}

Vector Vector::operator+(const Vector &v) const {
    return Vector(X + v.X,
                  Y + v.Y,
                  Z + v.Z);
}

Vector Vector::operator-(const Vector &v) const {
    return Vector(X - v.X,
                  Y - v.Y,
                  Z - v.Z);
}

Vector Vector::operator*(float c) const {
    return Vector(X * c,
                  Y * c,
                  Z * c);
}

Vector Vector::operator-() const {
    return Vector(X * -1,
                  Y * -1,
                  Z * -1);
}

Vector &Vector::operator+=(const Vector &v) {
    X = X + v.X;
    Y = Y + v.Y;
    Z = Z + v.Z;
    return *this;
}


Vector &Vector::normalize() {
    float length = this->length();
    X = X / length;
    Y = Y / length;
    Z = Z / length;
    return *this;
}

float Vector::length() const {
    return sqrtf(this->lengthSquared());
}

float Vector::lengthSquared() const {
    return X * X + Y * Y + Z * Z;
}

Vector Vector::reflection(const Vector &normal) const {

    return *this - (normal * ((normal.dot(*this)) * 2));
}

bool Vector::triangleIntersection(const Vector &d, const Vector &a, const Vector &b, const Vector &c, float &s) const {
    Vector n = ((b - a).cross(c - a)).normalize();


    if (n.dot(d) == 0) return false; // Senkrecht

    float distance = n.dot(a);


    s = (distance - n.dot(*this))/n.dot(d); // wenn n.dot(d) hier 0 = Paralell zur Ebene

    Vector p = (*this) + (d * s);


    if (s < 0) return false; // Wenn Fläche "hinter" dem Strahl liegt

    if (areaCalc(a, b, c) + EPSILON >= areaCalc(a, b, p) + areaCalc(a, c, p) + areaCalc(b, c, p)) {
        return true;
    }
    return false;
}

float Vector::areaCalc(const Vector &u, const Vector &v, const Vector &w) const {
    return ((((v - u).cross(w - u)).length()) / 2);
}
