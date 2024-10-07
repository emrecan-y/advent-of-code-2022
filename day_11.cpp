#include "advent_day.h"
#include <list>
#include <set>
class Monkey
{
public:
    Monkey() {}
    virtual ~Monkey() {}
    std::list<int> items;

    char operation_type;
    char operation_value;

    int divisible_test_val;
    int divisible_test_true_destination;
    int divisible_test_false_destination;

    int total_inspection_count = 0;
};

class Day_11 : AdventDay
{
public:
    Day_11() : AdventDay(11) {}
    void part_one()
    {
        std::vector<Monkey *> monkeys;
        parse_monkeys(monkeys);
        for (int round = 0; round < 20; round++)
        {
            play_round(monkeys, true, 0);
        }
        std::set<int> inspection_counts;
        for (Monkey *m : monkeys)
        {
            inspection_counts.insert(m->total_inspection_count);
            delete m;
        }
        int first_max = *--inspection_counts.end();
        int second_max = *-- --inspection_counts.end();
        std::cout << "The level of monkey business after 20 rounds of stuff-slinging simian shenanigans is " << first_max * second_max << std::endl;
    }

    void part_two()
    {
        std::vector<Monkey *> monkeys;
        parse_monkeys(monkeys);

        // instead of /3 use this common_multiple to modulo the worry leves before throwing
        int common_multiple = 1;
        for (Monkey *m : monkeys)
        {
            common_multiple *= m->divisible_test_val;
        }

        for (int round = 0; round < 10000; round++)
        {
            play_round(monkeys, false, common_multiple);
        }

        std::set<int> inspection_counts;
        for (Monkey *m : monkeys)
        {
            inspection_counts.insert(m->total_inspection_count);
            delete m;
        }

        int first_max = *--inspection_counts.end();
        int second_max = *-- --inspection_counts.end();
        long result = long(first_max) * long(second_max);
        std::cout
            << "The level of monkey business after 10000 rounds of stuff-slinging simian shenanigans is " << result << std::endl;
    }

    void play_round(std::vector<Monkey *> &monkeys, bool divide_by_three, int common_multiple)
    {
        for (Monkey *m : monkeys)
        {
            std::list<int> items_copy = m->items;
            for (int worry_level : items_copy)
            {
                m->total_inspection_count++;
                make_operation(m, worry_level);

                if (divide_by_three)
                {
                    worry_level /= 3;
                }
                else
                {
                    worry_level %= common_multiple;
                }

                monkey_throw(monkeys, m, worry_level);
                m->items.pop_front();
            }
        }
    }

    void monkey_throw(std::vector<Monkey *> &monkeys, Monkey *m, int &worry_level)
    {
        if (worry_level % m->divisible_test_val == 0)
        {
            monkeys[m->divisible_test_true_destination]->items.push_back(worry_level);
        }
        else
        {
            monkeys[m->divisible_test_false_destination]->items.push_back(worry_level);
        }
    }

    void make_operation(Monkey *m, int &worry_level)
    {
        if (m->operation_type == '+')
        {
            worry_level += m->operation_value;
        }
        else if (m->operation_type == '*')
        { // multiply self
            if (m->operation_value == -1)
            {
                worry_level *= worry_level;
            }
            else
            {
                worry_level *= m->operation_value;
            }
        }
    }

    void parse_monkeys(std::vector<Monkey *> &monkeys)
    {
        std::vector<std::string> input = this->get_input();
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i].find("Monkey ") != -1)
            {
                Monkey *new_monkey = new Monkey();
                // starting items
                input[i + 1] = input[i + 1].substr(input[i + 1].find(":") + 2);
                int comma_index;
                while ((comma_index = input[i + 1].find(",")) != -1)
                {
                    int item = std::stoi(input[i + 1].substr(0, comma_index));
                    input[i + 1] = input[i + 1].substr(comma_index + 1);
                    new_monkey->items.push_back(item);
                }
                new_monkey->items.push_back(std::stoi(input[i + 1]));
                // operation
                new_monkey->operation_type = input[i + 2][23];
                if (input[i + 2].substr(25) == "old")
                {
                    new_monkey->operation_value = -1;
                }
                else
                {
                    new_monkey->operation_value = std::stoi(input[i + 2].substr(24));
                }

                // divisible test
                new_monkey->divisible_test_val = std::stoi(input[i + 3].substr(input[i + 3].find("by") + 2));
                new_monkey->divisible_test_true_destination = std::stoi(input[i + 4].substr(input[i + 4].find("monkey") + 6));
                new_monkey->divisible_test_false_destination = std::stoi(input[i + 5].substr(input[i + 5].find("monkey") + 6));
                monkeys.push_back(new_monkey);
            }
        }
    }
};

int main()
{
    Day_11 day;
    day.part_one();
    day.part_two();
    return 0;
}