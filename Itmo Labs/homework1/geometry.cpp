#include "geometry.h"
#ifndef CPP_geometry
#define CPP_geometry

double getLenghtVector(const Point &A, const Point &B)
{
    return sqrt(getLenghtVectorpow2(A, B));
};

unsigned long int getLenghtVectorpow2(const Point &A, const Point &B)
{
    return (A.getX() - B.getX()) * (A.getX() - B.getX()) + (A.getY() - B.getY()) * (A.getY() - B.getY());
}

double det(int a, int b, int c, int d)
{
    return a * d - b * c;
};

Point :: Point(const Point &other)
    : x_(other.x_)
    , y_(other.y_){};

Point &Point ::operator=(const Point &other)
{
    if (&other == this)
        return *this;

    x_ = other.x_;
    y_ = other.y_;
    return *this;
};
int Point ::getX() const { return x_; };
int Point ::getY() const { return y_; };

PolygonalChain ::PolygonalChain()
    : Points(){};

PolygonalChain ::PolygonalChain(int N, Point *points_)
    : Points()
{
    for (int i = 0; i < N; i++)
        Points.push_back(points_[i]);
};

PolygonalChain ::PolygonalChain(const PolygonalChain &other)
    : Points(other.Points){};

PolygonalChain &PolygonalChain ::operator=(const PolygonalChain &other)
{
    if (&other == this)
        return *this;
    Points = other.Points;
    return *this;
};

double PolygonalChain ::perimeter() const
{
    Point last;
    double result = 0;
    last = Points[0];
    for (unsigned long i = 1; i < Points.size(); i++)
    {
        result += getLenghtVector(last, Points[i]);
        last = Points[i];
    }
    return result;
};

ClosedPolygonalChain ::ClosedPolygonalChain()
    : PolygonalChain(){};

ClosedPolygonalChain ::ClosedPolygonalChain(int N, Point *points_)
    : PolygonalChain(N, points_){};

double ClosedPolygonalChain ::area() const
{
    //Fixed double is bad
    //It should be double, because return result / 2;
    //fixed nope, return value should be double, not result
    int result = 0;
    unsigned long N = Points.size();
    for (unsigned long i = 0; i < N - 1; i++)
        result += det(Points[i].getX(), Points[i].getY(), Points[i + 1].getX(), Points[i + 1].getY());
    result += det(Points[N - 1].getX(), Points[N - 1].getY(), Points[0].getX(), Points[0].getY());
    if (result < 0)
        result *= -1;
    return (double)result / 2;
};

double ClosedPolygonalChain ::perimeter() const
{
    Point last;
    long long result;
    result = PolygonalChain::perimeter();
    result += getLenghtVector(Points[0], Points[Points.size() - 1]);
    return result;
};

Polygon ::Polygon()
    : ClosedPolygonalChain(){};

Polygon ::Polygon(int N, Point *points_)
    : ClosedPolygonalChain(N, points_){};

Triangle ::Triangle(int N, Point *Points)
    : Polygon(N, Points){};

bool Triangle ::hasRightAngle() const
{
    unsigned long int AB, BC, AC;
    AB = getLenghtVectorpow2(Points[0], Points[1]);
    BC = getLenghtVectorpow2(Points[1], Points[2]);
    AC = getLenghtVectorpow2(Points[2], Points[0]);

    //take sqrt and then pow it at 2 fixed
    if (AB == BC + AC)
        return true;
    if (BC == AB + AC)
        return true;
    if (AC == BC + AB)
        return true;
    return false;
};

Trapezoid ::Trapezoid(int N, Point *Points)
    : Polygon(N, Points){};

double Trapezoid ::height() const
{
    double BC, AD;
    BC = getLenghtVector(Points[1], Points[2]);
    AD = getLenghtVector(Points[0], Points[3]);
    return 2 * area() / (BC + AD);
};

RegularPolygon ::RegularPolygon(int N, Point *Points)
    : Polygon(N, Points){};

double RegularPolygon ::perimeter() const
{
    long long side = getLenghtVector(Points[0], Points[1]);
    return side * Points.size();
}

double RegularPolygon ::area() const
{
    long long side = getLenghtVector(Points[0], Points[1]);
    return (Points.size() * side * side) / (4 * tan((2 * M_PI) / (2 * Points.size())));
}
#endif