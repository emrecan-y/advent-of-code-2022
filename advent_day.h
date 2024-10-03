#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class AdventDay
{
public:
    AdventDay(int day)
    {
        this->day_number = day;
        read_day_input();
    };
    std::vector<std::string> input;
    virtual void part_one() = 0;
    virtual void part_two() = 0;

private:
    int day_number;
    void read_day_input()
    {
        std::ifstream file("./inputs/day_" + std::to_string(this->day_number) + ".txt");
        std::string line;
        while (getline(file, line))
        {
            input.push_back(line);
        }
    }
};