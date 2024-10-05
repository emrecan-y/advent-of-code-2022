#include "advent_day.h"
#include <set>

class Day_9 : public AdventDay
{
public:
    Day_9() : AdventDay(0) {}
    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        std::set<std::tuple<int, int>> tail_visited_coordinates;
        int head_y, head_x, tail_y, tail_x;
        head_y = head_x = tail_y = tail_x = 0;
        tail_visited_coordinates.insert({tail_y, tail_x});

        for (int i = 0; i < input.size(); i++)
        {
            char direction = input[i][0];
            int move_count = std::stoi(input[i].substr(2));
            for (int i = 0; i < move_count; i++)
            {
                int old_head_y = head_y;
                int old_head_x = head_x;
                switch (direction)
                {
                case 'D':
                    head_y--;
                    break;
                case 'U':
                    head_y++;
                    break;
                case 'L':
                    head_x--;
                    break;
                case 'R':
                    head_x++;
                    break;
                }
                if (abs(head_x - tail_x) > 1 || abs(head_y - tail_y) > 1)
                {
                    tail_x = old_head_x;
                    tail_y = old_head_y;
                }
                tail_visited_coordinates.insert({tail_y, tail_x});
            }
        }
        std::cout << "The distinct count of the places the tail has visited is " << tail_visited_coordinates.size() << std::endl;

        std::vector<std::vector<bool>> print(5, std::vector<bool>(6));
        for (auto e : tail_visited_coordinates)
        {
            print[std::get<0>(e)][std::get<1>(e)] = true;
        }

        for (auto e : print)
        {
            for (auto a : e)
            {
                if (a)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
            }
            std::cout << std ::endl;
        }
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();
        std::set<std::tuple<int, int>> tail_visited_coordinates;
        std::vector<std::tuple<int, int>> rope(10, std::tuple<int, int>(0, 0));

        tail_visited_coordinates.insert(rope.front());

        for (int i = 0; i < input.size(); i++)
        {
            char direction = input[i][0];
            int move_count = std::stoi(input[i].substr(2));
            for (int i = 0; i < move_count - 1; i++)
            {
                int old_head_y = std::get<0>(rope.front());
                int old_head_x = std::get<1>(rope.front());
                switch (direction)
                {
                case 'D':
                    std::get<0>(rope.front())--;
                    break;
                case 'U':
                    std::get<0>(rope.front())++;
                    break;
                case 'L':
                    std::get<1>(rope.front())--;
                    break;
                case 'R':
                    std::get<1>(rope.front())++;
                    break;
                }
                for (int r = 0; r < rope.size(); r++)
                {
                    if (r == 0 && (abs(std::get<0>(rope[r]) - std::get<0>(rope[r + 1])) > 1 || abs(std::get<1>(rope[r]) - std::get<1>(rope[r + 1])) > 1))
                    {
                        std::get<0>(rope[r]) = old_head_y;
                        std::get<1>(rope[r]) = old_head_x;
                    }
                    if (abs(std::get<0>(rope[r]) - std::get<0>(rope[r + 1])) > 1 || abs(std::get<1>(rope[r]) - std::get<1>(rope[r + 1])) > 1)
                    {
                        std::get<0>(rope[r + 1]) = std::get<0>(rope[r]);
                        std::get<1>(rope[r + 1]) = std::get<0>(rope[r]);
                    }
                }
                tail_visited_coordinates.insert(rope.front());
            }
        }
        std::cout << "The distinct count of the places the tail has visited is " << tail_visited_coordinates.size() << std::endl;

        std::vector<std::vector<bool>> print(5, std::vector<bool>(6));
        for (auto e : tail_visited_coordinates)
        {
            print[std::get<0>(e)][std::get<1>(e)] = true;
        }

        for (auto e : print)
        {
            for (auto a : e)
            {
                if (a)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
            }
            std::cout << std ::endl;
        }
    }
};

int main()
{
    Day_9 day;
    day.part_one();
    day.part_two();
    return 0;
}