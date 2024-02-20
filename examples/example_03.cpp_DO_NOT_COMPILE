#include <iostream>
#include <proj.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Point.h>
#include <geos/io/GeoJSONWriter.h>
#include <cstdlib>
#include <ctime>
#include <memory>  // For std::unique_ptr
#include <vector>  // For storing multiple geometries
#include <fstream> // For writing to a file

std::string getUTMZone(double lon)
{
    int zone = std::floor((lon + 180) / 6) + 1;
    return "EPSG:326" + std::to_string(zone); // Assuming northern hemisphere
}

void writeGeometriesToGeoJSON(
    const std::vector<std::unique_ptr<geos::geom::Geometry>> &original_geoms,
    const std::vector<std::unique_ptr<geos::geom::Geometry>> &buffered_geoms,
    const std::string &epsg,
    const std::string &filename)
{

    geos::io::GeoJSONWriter writer;
    std::ofstream file(filename);
    file << "{ \"type\": \"FeatureCollection\", \"crs\": { \"type\": \"name\", \"properties\": { \"name\": \"urn:ogc:def:crs:"
         << epsg << "\" } }, \"features\": [";

    for (size_t i = 0; i < original_geoms.size(); ++i)
    {
        if (i > 0)
            file << ", ";
        file << writer.write(original_geoms[i].get());
    }

    for (size_t i = 0; i < buffered_geoms.size(); ++i)
    {
        file << ", ";
        file << writer.write(buffered_geoms[i].get());
    }

    file << "] }";
    file.close();
}

int main()
{
    PJ_CONTEXT *C = proj_context_create();
    const geos::geom::GeometryFactory *factory = geos::geom::GeometryFactory::getDefaultInstance();
    std::vector<std::unique_ptr<geos::geom::Geometry>> original_geoms;
    std::vector<std::unique_ptr<geos::geom::Geometry>> buffered_geoms;

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

        PJ_COORD a = proj_coord(lon, lat, 0, 0);
        PJ_COORD b = proj_trans(P, PJ_FWD, a);

        std::unique_ptr<geos::geom::Point> original_point(factory->createPoint(geos::geom::Coordinate(lon, lat)));
        original_geoms.push_back(std::move(original_point));

        std::unique_ptr<geos::geom::Point> point(factory->createPoint(geos::geom::Coordinate(b.enu.e, b.enu.n)));
        std::unique_ptr<geos::geom::Geometry> bufferGeom(point->buffer(5));
        buffered_geoms.push_back(std::move(bufferGeom));

        proj_destroy(P);
    }

    std::string epsg = "urn:ogc:def:crs:EPSG::4326"; // Assuming WGS84 for simplicity
    std::string filename = "geometries.geojson";
    writeGeometriesToGeoJSON(original_geoms, buffered_geoms, epsg, filename);

    proj_context_destroy(C);

    return 0;
}
