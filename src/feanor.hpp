#pragma once

class geos_wrapper
{
private:
    int original;
    int transformed;

public:
    geos_wrapper();
    void print_data();
    int return_original();
    int return_transformed();
};
