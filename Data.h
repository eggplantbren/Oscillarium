#ifndef Oscillarium_Data_h
#define Oscillarium_Data_h

#include <string>
#include <vector>

namespace Oscillarium
{


class Data
{
    private:
        std::vector<double> t, y, err;

    public:
        Data() = delete;
        Data(const std::string& filename);


};

} // namespace

#endif
