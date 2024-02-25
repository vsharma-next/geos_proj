#include <iostream>
#include <proj.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Point.h>

using namespace geos::geom;

class geos_wrapper
{
private:
    int original;
    int transformed;

public:
    geos_wrapper();
    void print_data();
};
