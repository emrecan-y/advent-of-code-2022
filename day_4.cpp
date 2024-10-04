#include "advent_day.h"

class Day_4 : public AdventDay
{
public:
    Day_4() : AdventDay(4) {}

    void part_one()
    {
        std::vector<std::string> input = this->get_input();

        int count_fully_containing_pairs = 0;
        for (std::string s : input)
        {
            int comma_index = s.find(",");
            std::string first_elf_s = s.substr(0, comma_index);
            std::string second_elf_s = s.substr(comma_index + 1);

            std::tuple<int, int> first_elf_r = parse_range(first_elf_s);
            std::tuple<int, int> second_elf_r = parse_range(second_elf_s);

            if (std::get<0>(first_elf_r) <= std::get<0>(second_elf_r) && std::get<1>(first_elf_r) >= std::get<1>(second_elf_r) ||
                std::get<0>(first_elf_r) >= std::get<0>(second_elf_r) && std::get<1>(first_elf_r) <= std::get<1>(second_elf_r))
            {
                count_fully_containing_pairs++;
            }
        }
        std::cout << "The sum of fully containing pairs is " << std::to_string(count_fully_containing_pairs) << std::endl;
    }

    std::tuple<int, int> parse_range(std::string s)
    {
        int dash_index = s.find("-");
        return {std::stoi(s.substr(0, dash_index)), std::stoi(s.substr(dash_index + 1))};
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();

        int count_overlapping_pairs = 0;
        for (std::string s : input)
        {
            int comma_index = s.find(",");
            std::string first_elf_s = s.substr(0, comma_index);
            std::string second_elf_s = s.substr(comma_index + 1);

            std::tuple<int, int> first_elf_r = parse_range(first_elf_s);
            std::tuple<int, int> second_elf_r = parse_range(second_elf_s);

            // 1_start <= 2_end && 2_start <= 1_end
            // 1    |----|
            // 2  |----|
            if (std::get<0>(first_elf_r) <= std::get<1>(second_elf_r) && std::get<0>(second_elf_r) <= std::get<1>(first_elf_r))
            {
                count_overlapping_pairs++;
            }
        }
        std::cout << "The sum of range overlapping pairs is " << std::to_string(count_overlapping_pairs) << std::endl;
    }
};

int main()
{
    Day_4 day;
    day.part_one();
    day.part_two();
    return 0;
}