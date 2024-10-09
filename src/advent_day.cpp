#include "advent_day.h"

AdventDay::AdventDay(int day)
{
    this->day_number = day;

    // read day input
    std::ifstream file("../inputs/day_" + std::to_string(this->day_number) + ".txt");
    std::string line;
    while (getline(file, line))
    {
        input.push_back(line);
    }
}

std::vector<std::string> AdventDay::get_input()
{
    return this->input;
}
