
#include "advent_day.h"
#include <set>

class Day_3 : public AdventDay
{
public:
    Day_3() : AdventDay(3) {};

    void part_one()
    {
        std::vector<std::string> input = this->get_input();

        int priority_sum = 0;
        for (std::string s : input)
        {
            int s_middle_index = s.size() / 2;
            std::set<char> chars_from_first_item;
            for (char c : s.substr(0, s_middle_index))
            {
                chars_from_first_item.insert(c);
            }
            for (char c : s.substr(s_middle_index))
            {
                if (chars_from_first_item.find(c) != chars_from_first_item.end())
                {
                    priority_sum += get_priority(c);
                    break;
                }
            }
        }

        std::cout << "The sum of the priorities is " << std::to_string(priority_sum) << std::endl;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();

        int priority_sum = 0;

        // iterate groups of three elfes
        for (int i = 0; i < input.size(); i += 3)
        {
            std::set<char> chars_from_elf_1;
            std::set<char> chars_from_elf_2;
            for (char c : input[i])
            {
                chars_from_elf_1.insert(c);
            }
            for (char c : input[i + 1])
            {
                chars_from_elf_2.insert(c);
            }
            for (char c : input[i + 2])
            {
                if (chars_from_elf_1.find(c) != chars_from_elf_1.end() && chars_from_elf_2.find(c) != chars_from_elf_2.end())
                {
                    priority_sum += get_priority(c);
                    break;
                }
            }
        }
        std::cout << "The sum of the priorities in groups of three is " << std::to_string(priority_sum) << std::endl;
    }

    int get_priority(const char &c)
    {

        if (c >= 65 && c <= 90)
        {
            // Uppercase item types A through Z have priorities 27 through 52.
            return c - 65 + 27;
        }
        else if (c >= 97 && c <= 122)
        {
            // Lowercase item types a through z have priorities 1 through 26.
            return c - 96;
        }
        else
        {
            return 0;
        }
    }
};

int main()
{
    Day_3 day;
    day.part_one();
    day.part_two();
    return 0;
}