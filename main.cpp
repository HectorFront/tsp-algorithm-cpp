#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono>

using namespace std;

using Coord = vector<double>;

const double REarth = 6371;

double distanceLatLng(const Coord& p1, const Coord& p2) {
    double lat1 = p1[0], lng1 = p1[1];
    double lat2 = p2[0], lng2 = p2[1];

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLng = (lng2 - lng1) * M_PI / 180.0;
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLng/2) * sin(dLng/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return REarth * c;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Coord originCoords = {-23.5505, -46.6333};

    vector<Coord> coords = {
        {-15.7938, -47.8827},
        {-3.7172, -38.5433},
        {-12.9714, -38.5014},
        {-22.9068, -43.1729},
        {-3.1190, -60.0217},
        {-16.6868, -49.2648},
        {-8.0476, -34.8770},
        {-25.4296, -49.2711},
        {-30.0346, -51.2177},
        {-19.9167, -43.9345},
        {-10.1833, -48.3333},
        {-5.0892, -42.8019},
        {-2.5307, -44.3068},
        {-15.5961, -56.0969},
        {-6.1843, -36.5746},
        {-28.2667, -52.4167},
        {-13.5000, -50.5000},
        {-9.5000, -65.5000},
        {-21.5000, -45.5000}
    };

    vector<Coord> tspDistances = {originCoords};

    for (size_t i = 0; i < coords.size(); i++) {
        if (tspDistances.empty()) {
            tspDistances.push_back(coords[i]);
        } else {
            double minDistance = numeric_limits<double>::infinity();
            Coord closestCoord;
            for (size_t j = 0; j < coords.size(); j++) {
                if (coords[j] != coords[i]) {
                    double dist = distanceLatLng(coords[i], coords[j]);
                    if (dist < minDistance) {
                        minDistance = dist;
                        closestCoord = coords[j];
                    }
                }
            }
            tspDistances.push_back(closestCoord);
        }
    }

    for (const auto& c : tspDistances) {
        cout << "[" << c[0] << ", " << c[1] << "]\n";
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
    return 0;
}