#include "advent_day.h"
#include <map>

struct humn_found_exception : std::runtime_error
{
    using std::runtime_error::runtime_error;
};
class Day_21 : public AdventDay
{
public:
    Day_21() : AdventDay(21) {}

    void part_one()
    {
        std::map<std::string, std::string> monkey_name_to_job;
        for (auto s : this->get_input())
        {
            int colon_index = s.find(":");
            auto monkey_name = s.substr(0, colon_index);
            auto monkey_job = s.substr(colon_index + 2);
            monkey_name_to_job[monkey_name] = monkey_job;
        }
        long result = get_monkey_numeric_value(monkey_name_to_job, "root", false);
        std::cout << "The monkey named root will yell the number " << result << std::endl;
    }

    void part_two()
    {
        std::map<std::string, std::string> monkey_name_to_job;
        for (auto s : this->get_input())
        {
            int colon_index = s.find(":");
            auto monkey_name = s.substr(0, colon_index);
            auto monkey_job = s.substr(colon_index + 2);
            monkey_name_to_job[monkey_name] = monkey_job;
        }
        auto root_job = monkey_name_to_job["root"];

        long value;
        try
        {
            value = get_monkey_numeric_value(monkey_name_to_job, root_job.substr(0, 4), true);
            value = get_human_numeric_value(monkey_name_to_job, root_job.substr(7), value);
        }
        catch (const humn_found_exception &e)
        {
            value = get_monkey_numeric_value(monkey_name_to_job, root_job.substr(7), false);
            value = get_human_numeric_value(monkey_name_to_job, root_job.substr(0, 4), value);
        }
        std::cout << "To pass the root's equality test I yell " << value << std::endl;
    }

    long get_monkey_numeric_value(std::map<std::string, std::string> &monkey_name_to_job, std::string monkey_name, bool check_for_humn)
    {
        if (check_for_humn && monkey_name == "humn")
        {
            throw humn_found_exception("A human was detected, please be cautious next time!");
        }
        auto monkey_job = monkey_name_to_job[monkey_name];
        try
        {
            return std::stoi(monkey_job);
        }
        catch (const std::invalid_argument &e)
        {
            char operation_type = monkey_job[5];
            long value_1 = get_monkey_numeric_value(monkey_name_to_job, monkey_job.substr(0, 4), check_for_humn);
            long value_2 = get_monkey_numeric_value(monkey_name_to_job, monkey_job.substr(7), check_for_humn);
            switch (operation_type)
            {
            case '*':
                return value_1 * value_2;
            case '/':
                return value_1 / value_2;
            case '-':
                return value_1 - value_2;
            case '+':
                return value_1 + value_2;
            }
        }
        return 0;
    }

    long get_human_numeric_value(std::map<std::string, std::string> &monkey_name_to_job, std::string monkey_name, long value_to_be_equal)
    {
        auto monkey_job = monkey_name_to_job[monkey_name];

        char operation_type = monkey_job[5];
        long value;
        auto monkey1 = monkey_job.substr(0, 4);
        auto monkey2 = monkey_job.substr(7);
        try
        {
            value = get_monkey_numeric_value(monkey_name_to_job, monkey1, true);
            long new_value_to_be_equal;
            switch (operation_type)
            {
            case '*':
                new_value_to_be_equal = value_to_be_equal / value;
                break;
            case '/':
                new_value_to_be_equal = value / value_to_be_equal;
                break;
            case '-':
                new_value_to_be_equal = value - value_to_be_equal;
                break;
            case '+':
                new_value_to_be_equal = value_to_be_equal - value;
                break;
            }
            // std::cout << value_to_be_equal << " = " << value << " " << operation_type << " " << new_value_to_be_equal << std::endl;
            if (monkey2 == "humn")
            {
                return new_value_to_be_equal;
            }
            else
            {
                return get_human_numeric_value(monkey_name_to_job, monkey2, new_value_to_be_equal);
            }
        }
        catch (const humn_found_exception &e)
        {
            value = get_monkey_numeric_value(monkey_name_to_job, monkey2, true);
            long new_value_to_be_equal;
            switch (operation_type)
            {
            case '*':
                new_value_to_be_equal = value_to_be_equal / value;
                break;
            case '/':
                new_value_to_be_equal = value * value_to_be_equal;
                break;
            case '-':
                new_value_to_be_equal = value + value_to_be_equal;
                break;
            case '+':
                new_value_to_be_equal = value_to_be_equal - value;
                break;
            }
            // std::cout << value_to_be_equal << " = " << new_value_to_be_equal << " " << operation_type << " " << value << std::endl;
            if (monkey1 == "humn")
            {
                return new_value_to_be_equal;
            }
            else
            {
                return get_human_numeric_value(monkey_name_to_job, monkey1, new_value_to_be_equal);
            }
        }
    }
};

int main()
{
    Day_21 day;
    day.part_one();
    day.part_two();
    return 0;
}