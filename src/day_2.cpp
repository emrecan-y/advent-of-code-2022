#include "advent_day.h"
#include <map>

class Day_2 : public AdventDay
{
public:
    Day_2() : AdventDay(2) {}

    void part_one()
    {
        std::vector<std::string> input = this->get_input();

        int point_sum = 0;
        for (int i = 0; i < input.size(); i++)
        {
            point_sum += get_points_part_one(input[i][0], input[i][2]);
        }
        std::cout << "The total score is " << std::to_string(point_sum) << std::endl;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();

        int point_sum = 0;
        for (int i = 0; i < input.size(); i++)
        {
            point_sum += get_points_part_two(input[i][0], input[i][2]);
        }
        std::cout << "The total score is " << std::to_string(point_sum) << std::endl;
    }

    int get_points_part_one(char opponent, char me)
    {
        // opponent: A for Rock, B for Paper, and C for Scissors
        // me:       X for Rock, Y for Paper, and Z for Scissors
        // points:   1 for Rock, 2 for Paper, and 3 for Scissors
        //           0 lose, 3 draw,  6 win
        int base_point = 0;
        switch (me)
        {
        case 'X':
            base_point = 1;
            break;
        case 'Y':
            base_point = 2;
            break;
        case 'Z':
            base_point = 3;
            break;
        }
        if (opponent == 'A' && me == 'X' || opponent == 'B' && me == 'Y' || opponent == 'C' && me == 'Z')
        {
            return base_point + 3;
        }
        else if (opponent == 'A' && me == 'Y' || opponent == 'B' && me == 'Z' || opponent == 'C' && me == 'X')
        {
            return base_point + 6;
        }
        else
        {
            return base_point;
        }
    }
    int get_points_part_two(char opponent, char me)
    {
        // opponent: A for Rock, B for Paper, and C for Scissors
        // me:       X lose, Y draw, Z win
        // points:   1 for Rock, 2 for Paper, and 3 for Scissors
        //           0 lose, 3 draw,  6 win
        int base_point = 0;
        switch (me)
        {
        case 'X':
            base_point = 0;
            switch (opponent)
            {
            case 'A':
                return base_point + 3;
            case 'B':
                return base_point + 1;
            case 'C':
                return base_point + 2;
            }
        case 'Y':
            base_point = 3;
            switch (opponent)
            {
            case 'A':
                return base_point + 1;
            case 'B':
                return base_point + 2;
            case 'C':
                return base_point + 3;
            }
            break;
        case 'Z':
            base_point = 6;
            switch (opponent)
            {
            case 'A':
                return base_point + 2;
            case 'B':
                return base_point + 3;
            case 'C':
                return base_point + 1;
            }
            break;
        }
        return 0;
    }
};

int main()
{
    Day_2 day;
    day.part_one();
    day.part_two();
    return 0;
}