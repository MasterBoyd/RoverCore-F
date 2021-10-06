#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <math.h>
#include <stdint.h>

#define PI 3.14159

struct Euler
{
    double X, Y, Z;
};


struct Quaternion
{
    double W, X, Y, Z;
    Quaternion(double w = 0, double x = 0, double y = 0, double z = 0) : W(w), X(x), Y(y), Z(z) {}

    double magnitude() const
    {
        return sqrt(W * W + X * X + Y * Y + Z * Z);
    }

    void normalize()
    {
        *this =  *this * (1/magnitude());
    }

    Quaternion conjugate() const
    {
        return Quaternion(W, -X, -Y, -Z);
    }

    Quaternion inverse() const
    {
        return conjugate() / (W * W + X * X + Y * Y + Z * Z);
    }

    Quaternion operator*(const Quaternion& q) const
    {
        return Quaternion(
                W*q.W - X*q.X - Y*q.Y - Z*q.Z,
                W*q.X + X*q.W + Y*q.Z - Z*q.Y,
                W*q.Y - X*q.Z + Y*q.W + Z*q.X,
                W*q.Z + X*q.Y - Y*q.X + Z*q.W
                );
    }

    Quaternion operator+(const Quaternion& q) const
    {
        return Quaternion(
                W + q.W,
                X + q.X,
                Y + q.Y,
                Z + q.Z
                );
    }

    Quaternion operator-(const Quaternion& q) const
    {
        return Quaternion(
                W - q.W,
                X - q.X,
                Y - q.Y,
                Z - q.Z
                );
    }

    Quaternion operator/(double scalar) const
    {
        return Quaternion(
                W / scalar,
                X / scalar,
                Y / scalar,
                Z / scalar
                );
    }

    Quaternion operator*(double scalar) const
    {
        return Quaternion(
                W * scalar,
                X * scalar,
                Y * scalar,
                Z * scalar
                );
    }

    Euler toEuler() const
    {
        Euler ret;
        double sqW = W * W;
        double sqX = X * X;
        double sqY = Y * Y;
        double sqZ = Z * Z;

        ret.Z = atan2(2.0 * (X * Y + Z * W), (sqX - sqY - sqZ + sqW));
        ret.Y = asin(-2.0 * (X * Z - Y * W) / (sqX + sqY + sqZ + sqW));
        ret.X = atan2(2.0 * (Y * Z + X * W), (-sqX - sqY + sqZ + sqW));

        ret.X *= (180/PI);
        ret.Y *= (180/PI);
        ret.Z *= (180/PI);

        return ret;
    }

};


#endif
