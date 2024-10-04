#include "advent_day.h"
#include <list>

class Day_5 : public AdventDay
{
public:
    Day_5() : AdventDay(5) {}

    void part_one()
    {
        std::vector<std::string> input = this->get_input();

        int input_border_index = get_input_border_index(input);
        std::vector<std::list<char> *> stack_list;
        parse_stack_list(stack_list, input, input_border_index);

        // iterate over instructions
        for (int i = input_border_index + 1; i < input.size(); i++)
        {
            int count, from, to;
            std::tie(count, from, to) = parse_instruction(input[i]);
            for (int c = 0; c < count; c++)
            {
                stack_list[to]->push_front(stack_list[from]->front());
                stack_list[from]->pop_front();
            }
        }

        std::cout << "The top of each stack using CrateMover9000 results to " << print_result(stack_list) << std::endl;

        for (std::list<char> *p : stack_list)
        {
            delete p;
        }
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();

        int input_border_index = get_input_border_index(input);
        std::vector<std::list<char> *> stack_list;
        parse_stack_list(stack_list, input, input_border_index);

        // iterate over instructions
        // copy entries "at once"
        for (int i = input_border_index + 1; i < input.size(); i++)
        {
            int count, from, to;
            std::tie(count, from, to) = parse_instruction(input[i]);
            std::list<char> move_buffer;
            for (int c = 0; c < count; c++)
            {
                move_buffer.push_back(stack_list[from]->front());
                stack_list[from]->pop_front();
            }
            for (int i = move_buffer.size() - 1; i >= 0; i--)
            {
                stack_list[to]->push_front(move_buffer.back());
                move_buffer.pop_back();
            }
        }

        std::cout << "The top of each stack using CrateMover9001 results to " << print_result(stack_list) << std::endl;

        for (std::list<char> *p : stack_list)
        {
            delete p;
        }
    }

    std::tuple<int, int, int> parse_instruction(std::string s)
    {
        // example "move 3 from 2 to 5"
        s.erase(s.find("move "), 5);
        s.erase(s.find("from "), 5);
        s.erase(s.find("to "), 3);

        int count = stoi(s.substr(0, s.find(" ")));
        int from = stoi(s.substr(s.find(" ") + 1, s.find_last_of(" ")));
        int to = stoi(s.substr(s.find_last_of(" ") + 1));

        // -1 because of 1 based indexing
        return {count, from - 1, to - 1};
    }

    int get_input_border_index(std::vector<std::string> &input)
    {
        // search for empty string
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] == "")
            {
                return i;
            }
        }
        return -1;
    }

    std::string print_result(std::vector<std::list<char> *> &stack_list)
    {
        std::string out = "";
        for (auto a : stack_list)
        {
            out += a->front();
        }
        return out;
    }

    void parse_stack_list(std::vector<std::list<char> *> &stack_list, std::vector<std::string> &input, int input_border_index)
    {
        // iterate over string containing stack numbers for x-coordinates
        std::string stack_numbers = input[input_border_index - 1];
        for (int x = 0; x < stack_numbers.size(); x++)
        {
            if (stack_numbers[x] != ' ')
            {
                std::list<char> *stack = new std::list<char>;
                // iterate over all chars placed on top of the stack numbers
                for (int y = 0; y < input_border_index - 1; y++)
                {
                    if (input[y][x] != ' ')
                    {
                        stack->push_back(input[y][x]);
                    }
                }
                stack_list.push_back(stack);
            }
        }
    }
};

int main()
{
    Day_5 day;
    day.part_one();
    day.part_two();
    return 0;
}