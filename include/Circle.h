#ifndef CIRCLE_H
#define CIRCLE_H

#include "Coord.h"
#include "Color.h"
#include "Drawable.h"
#include "Context.h"

class Circle : Drawable
{
public:
    int r;
    Coord coords;
    Color color;

    Circle(int radius, int x, int y, Color color);

    void setCoords(int x, int y);

    void addCoords(int x, int y);

    void setRadius(int radius);

    void addRadius(int radius);

    void draw(const Context &context) override;
};


#endif //CIRCLE_H
