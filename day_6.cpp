#include "advent_day.h"
#include <set>

class Day_6 : public AdventDay
{
public:
    Day_6() : AdventDay(6) {}

    void part_one()
    {
        // search for the first substring with 4 unique chars
        std::vector<std::string> input = this->get_input();
        int marker_index = -1;
        for (int i = 4; i < input[0].size(); i++)
        {
            std::set<char> char_buffer;
            char_buffer.insert(input[0][i - 4]);
            char_buffer.insert(input[0][i - 3]);
            char_buffer.insert(input[0][i - 2]);
            char_buffer.insert(input[0][i - 1]);
            if (char_buffer.size() == 4)
            {
                marker_index = i;
                break;
            }
        }
        std::cout << "The first marker is after character number " << std::to_string(marker_index) << std::endl;
    }

    void part_two()
    {
        // search for the first substring with 14 unique chars
        std::vector<std::string> input = this->get_input();
        int marker_index = -1;
        for (int i = 14; i < input[0].size(); i++)
        {
            std::set<char> char_buffer;
            for (int k = 14; k > 0; k--)
            {
                char_buffer.insert(input[0][i - k]);
            }
            if (char_buffer.size() == 14)
            {
                marker_index = i;
                break;
            }
        }
        std::cout << "The first marker is after character number " << std::to_string(marker_index) << std::endl;
    }
};

int main()
{
    Day_6 day;
    day.part_one();
    day.part_two();
    return 0;
}