#include <iostream>
#include <proj.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Point.h>
#include <cstdlib>
#include <ctime>
#include <memory> // Include for std::unique_ptr

using namespace geos::geom;
// Function to determine the UTM zone based on longitude
std::string getUTMZone(double lon)
{
    int zone = std::floor((lon + 180) / 6) + 1;
    return "EPSG:326" + std::to_string(zone); // Assuming northern hemisphere
}

int main()
{
    PJ_CONTEXT *C = proj_context_create();
    const geos::geom::GeometryFactory *factory = geos::geom::GeometryFactory::getDefaultInstance();

    srand(static_cast<unsigned int>(time(NULL))); // Seed random number generation

    int N = 10; // Number of points to generate and buffer
    for (int i = 0; i < N; ++i)
    {
        double lat = static_cast<double>(rand()) / RAND_MAX * 10.0; // 0 to 10 degrees North
        double lon = static_cast<double>(rand()) / RAND_MAX * 5.0;  // 0 to 5 degrees East

        std::string utmZone = getUTMZone(lon);
        PJ *P = proj_create_crs_to_crs(C, "EPSG:4326", utmZone.c_str(), NULL); // WGS84 to correct UTM zone

        if (P == nullptr)
        {
            std::cerr << "Projection transformation could not be created." << std::endl;
            continue;
        }

        // Project point from WGS84 to the correct UTM zone
        PJ_COORD a = proj_coord(lon, lat, 0, 0);
        PJ_COORD b = proj_trans(P, PJ_FWD, a);

        // Create point geometry in projected coordinates
        std::unique_ptr<Point> point(factory->createPoint(Coordinate(b.enu.e, b.enu.n)));

        // Buffer the point by 5 meters in projected coordinates
        std::unique_ptr<Geometry> bufferGeom(point->buffer(5));

        // Print the WKT representation of the buffered geometry
        std::cout << "Buffered Geometry (Point " << i + 1 << "): " << bufferGeom->toText() << std::endl;

        // No need to manually delete point and bufferGeom, unique_ptr handles it

        proj_destroy(P);
    }

    // Cleanup PROJ
    proj_context_destroy(C);

    return 0;
}
