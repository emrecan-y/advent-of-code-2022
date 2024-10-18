
#include "advent_day.h"
#include <map>

class Day_25 : public AdventDay
{
public:
    Day_25() : AdventDay(25) {};

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        long sum = 0;
        for (auto snafu_string : input)
        {
            sum += snafu_to_long(snafu_string);
        }
        std::cout << sum << std::endl;
        std::cout << long_to_snafu(sum) << std::endl;
    }

    void part_two()
    {
    }

    long snafu_to_long(std::string snafu_string)
    {
        std::map<char, int> snafu_dictionary =
            {{'=', -2}, {'-', -1}, {'0', 0}, {'1', 1}, {'2', 2}};
        long power_value = 0;
        long decimal_value = 0;
        for (int i = snafu_string.size() - 1; i >= 0; i--, power_value++)
        {
            long current_base = pow(5, power_value);
            decimal_value += (current_base * snafu_dictionary[snafu_string[i]]);
        }
        return decimal_value;
    }

    std::string long_to_snafu(long target_value)
    {

        std::string snafu_string = "";
        std::map<long, char> snafu_dictionary =
            {{-2, '='}, {-1, '-'}, {0, '0'}, {1, '1'}, {2, '2'}};
        long current_value = 0;
        // start at the highest exponent and decrease, each iteration try to find the minumun difference to 0
        for (int current_exponent = round(log(target_value) / log(5)); current_exponent >= 0; current_exponent--)
        {
            long min_difference = LONG_MAX;
            int min_difference_val = 0;
            long current_power_of_five = pow(5, current_exponent);
            for (auto snafu : snafu_dictionary)
            {
                long result = current_power_of_five * snafu.first;
                long difference = abs((current_value - target_value) + result);
                if (difference < min_difference)
                {
                    min_difference = difference;
                    min_difference_val = snafu.first;
                }
            }
            snafu_string += snafu_dictionary[min_difference_val];
            current_value += current_power_of_five * min_difference_val;
        }
        return snafu_string;
    }
};

int main()
{
    Day_25 day;
    day.part_one();
    day.part_two();
    return 0;
}