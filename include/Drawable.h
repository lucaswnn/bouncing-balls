#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Context.h"

class Drawable
{
public:
    virtual ~Drawable() = default;

protected:
    virtual void draw(const Context &context) = 0;
};


#endif //DRAWABLE_H
