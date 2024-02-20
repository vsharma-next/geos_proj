#include <iostream>
#include <proj.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Point.h>

using namespace geos::geom;

int main()
{
    // Initialize PROJ context
    PJ_CONTEXT *C = proj_context_create();
    PJ *P = proj_create_crs_to_crs(C, "EPSG:4326", "EPSG:4978", nullptr);

    if (P == nullptr)
    {
        std::cerr << "Projection transformation could not be created." << std::endl;
        return 1;
    }

    PJ_COORD a, b;
    a = proj_coord(12.0, 55.0, 0, 0); // Longitude, Latitude of Copenhagen in degrees
    b = proj_trans(P, PJ_FWD, a);     // Forward projection: geodetic to projected coordinates

    std::cout << "Projected coordinates: " << b.enu.e << ", " << b.enu.n << std::endl;

    // Cleanup PROJ
    proj_destroy(P);
    proj_context_destroy(C);

    // Using GEOS to create a Point geometry
    const GeometryFactory *factory = GeometryFactory::getDefaultInstance();
    Point *point = factory->createPoint(Coordinate(b.enu.e, b.enu.n));

    std::cout << "Point WKT: " << point->toText() << std::endl;

    // Cleanup GEOS
    delete point;

    return 0;
}
