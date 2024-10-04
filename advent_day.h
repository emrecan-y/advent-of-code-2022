#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class AdventDay
{
public:
    AdventDay(int day);
    virtual void part_one() = 0;
    virtual void part_two() = 0;
    std::vector<std::string> get_input();

private:
    int day_number;
    std::vector<std::string> input;
};