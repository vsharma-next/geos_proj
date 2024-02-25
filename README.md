## Purpose

Tests for combining geos and proj

## Pre-requisites

1. Install Google Test Libraries

#### on Ubuntu
```bash

sudo apt-get install libgtest-dev
cd /usr/src/gtest/
sudo mkdir build
cd build/
sudo cmake ..
sudo make
sudo cp *.a /usr/lib/
sudo cp *.a /usr/local/lib/
```

## Description

- example_01.cpp : create a point and transform it from WGS84 to EPSG:3857
- example_02.cpp : create N random points in WGS84, detect the appropriate UTM, transform to that UTM, buffer the points by 5 meters and print to WKT. 
- example_03.cpp : 