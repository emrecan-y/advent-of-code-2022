#include "advent_day.h"

class Day_10 : public AdventDay
{
public:
    Day_10() : AdventDay(10) {}

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        int register_x = 1;
        int sum_signal_strength = 0;
        int total_cycle_count = 0;

        for (int i = 0; i < input.size(); i++)
        {
            int cycle = 0;
            int value_to_be_added_after_cycle = 0;

            // parse input line
            if (input[i] == "noop")
            {
                cycle = 1;
                value_to_be_added_after_cycle = 0;
            }
            else
            {
                // addx num_x
                int num_x = std::stoi(input[i].substr(input[i].find(" ") + 1));
                cycle = 2;
                value_to_be_added_after_cycle = num_x;
            }

            // "CPU" loop
            for (; cycle > 0; cycle--)
            {
                total_cycle_count++;
                if (total_cycle_count == 20 || total_cycle_count <= 220 && (total_cycle_count - 20) % 40 == 0)
                {
                    int signal_strength = register_x * total_cycle_count;
                    sum_signal_strength += signal_strength;
                }
            }
            register_x += value_to_be_added_after_cycle;
        }
        std::cout << "The sum of these six signal strengths is " << sum_signal_strength << std::endl;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();
        int register_x = 1;
        int total_cycle_count = 0;

        std::vector<std::vector<char>> display(6, std::vector<char>(40, '.'));
        for (int i = 0; i < input.size(); i++)
        {
            int cycle = 0;
            int value_to_be_added_after_cycle = 0;

            // parse input line
            if (input[i] == "noop")
            {
                cycle = 1;
                value_to_be_added_after_cycle = 0;
            }
            else
            {
                // addx num_x
                int num_x = std::stoi(input[i].substr(input[i].find(" ") + 1));
                cycle = 2;
                value_to_be_added_after_cycle = num_x;
            }

            // "CPU" and display loop
            for (; cycle > 0; cycle--)
            {
                int y = total_cycle_count / 40;
                int x = total_cycle_count % 40;
                if (x >= register_x - 1 && x <= register_x + 1)
                {
                    display[y][x] = '#';
                }
                total_cycle_count++;
            }
            register_x += value_to_be_added_after_cycle;
        }
        std::cout << "The resulting image;" << std::endl;
        for (auto array : display)
        {
            for (char c : array)
            {
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    Day_10 day;
    day.part_one();
    day.part_two();
    return 0;
}