#ifndef H_geometry
#define H_geometry
#include <math.h>
#include <vector>
#include <iostream>

class Point
{
public:
    explicit Point(int x = 0, int y = 0)
        : x_(x), y_(y){};
    Point(const Point &);
    Point &operator=(const Point &);

    int getX() const;
    int getY() const;

private:
    int x_;
    int y_;
};
double getLenghtVector(const Point &A, const Point &B);
unsigned long int getLenghtVectorpow2 (const Point &A, const Point &B);
double det(int, int, int, int);

class PolygonalChain
{
public:
    PolygonalChain();
    explicit PolygonalChain(int, Point *);
    PolygonalChain(const PolygonalChain &);
    PolygonalChain &operator=(const PolygonalChain &);
    virtual ~PolygonalChain() = default;

    int getN() const { return Points.size(); };
    Point getPoint(int i) const { return Points[i]; };

    virtual double perimeter() const;

protected:
    std::vector<Point> Points;
};

class ClosedPolygonalChain : public PolygonalChain
{
public:
    ClosedPolygonalChain();
    explicit ClosedPolygonalChain(int, Point *);
    ~ClosedPolygonalChain() = default;

    virtual double area() const;
    virtual double perimeter() const;
};

class Polygon : public ClosedPolygonalChain
{
public:
    Polygon();
    explicit Polygon(int, Point *);
    ~Polygon() = default;
};
//what???
//u should do it fixed
class Triangle : public Polygon
{
public:
    Triangle(int, Point *);
    ~Triangle() = default;
    bool hasRightAngle() const;
};

class Trapezoid : public Polygon
{
public:
    explicit Trapezoid(int, Point *);
    ~Trapezoid() = default;
    double height() const;
};

class RegularPolygon : public Polygon
{
public:
    explicit RegularPolygon(int, Point *);
    ~RegularPolygon() = default;

    double area() const;
    double perimeter() const;
};

#endif