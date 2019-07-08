
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <iostream>
namespace util
{
    void init() {
        srand(time(0));
    }
    unsigned int random(unsigned int min, unsigned int max) {
        return (rand() % max) + min;
    }
    void log(std::string input) {
        std::cout << input;
    }
    long map(long x, long in_min, long in_max, long out_min, long out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
} // namespace util
