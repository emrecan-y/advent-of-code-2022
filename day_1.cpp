#include "advent_day.h"
#include <map>

class Day_1 : public AdventDay
{
public:
    Day_1() : AdventDay(1) {}

    void part_one()
    {
        int current_sum = 0;
        int max_calories = 0;
        int max_elf_index = 0;

        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] == "")
            {
                if (current_sum > max_calories)
                {
                    max_calories = current_sum;
                    max_elf_index = i;
                }
                current_sum = 0;
            }
            else
            {
                current_sum += std::stoi(input[i]);
            }
        }

        std::cout << "The elf with the highest calorie count is number " << max_elf_index + 1;
        std::cout << " with " << max_calories << " calories." << std ::endl;
    }

    void part_two()
    {
        std::vector<int> calories;
        int current_sum = 0;
        for (int i = 0; i <= input.size(); i++)
        {
            if (input[i] == "")
            {
                calories.push_back(current_sum);
                current_sum = 0;
            }
            else
            {
                current_sum += std::stoi(input[i]);
            }
        }
        std::sort(calories.begin(), calories.end(), std::greater<int>());

        current_sum = 0;
        for (int i = 0; i < 3; i++)
        {
            current_sum += calories[i];
        }
        std::cout << "The sum of the calories count from the top thrre elfes is " << current_sum << std::endl;
    }
};

int main()
{

    Day_1 day;
    day.part_one();
    day.part_two();
    return 0;
}