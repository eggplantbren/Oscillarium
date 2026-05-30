#include "Data.h"
#include <fstream>
#include <iostream>

namespace Oscillarium
{

Data::Data(const std::string& filename)
{
    std::fstream fin(filename.c_str(), std::ios::in);

    double _t, _y, _err;
    while(fin >> _t && fin >> _y && fin >> _err)
    {
        t.push_back(_t);
        y.push_back(_y);
        err.push_back(_err);
    }
    std::cout << "# Loaded " << t.size() << " data points from file ";
    std::cout << filename << "." << std::endl;

    fin.close();
}









} // namespace
