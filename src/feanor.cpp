#include "feanor.hpp"

geos_wrapper::geos_wrapper()
{

    // Initialize PROJ context
    PJ_CONTEXT *C = proj_context_create();
    PJ *P = proj_create_crs_to_crs(C, "EPSG:4326", "EPSG:4978", nullptr);

    if (P == nullptr)
    {
        std::cerr << "Projection transformation could not be created." << std::endl;
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
    std::unique_ptr<Point> point(factory->createPoint(Coordinate(b.enu.e, b.enu.n)));
    std::cout << "Point WKT: " << point->toText() << std::endl;

    original = 1;
    transformed = 2;
}

void geos_wrapper::print_data()
{
    std::cout << original << std::endl;
    std::cout << transformed << std::endl;
}