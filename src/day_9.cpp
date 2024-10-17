#include "advent_day.h"
#include <set>

class Day_9 : public AdventDay
{
public:
    Day_9() : AdventDay(9) {}
    void part_one()
    {
        int rope_length = 2;
        int distinct_rope_visits = simulate_rope_and_count_tail(rope_length);
        std::cout << "The tail of a rope with length " << rope_length << " has visited " << distinct_rope_visits << " distinct places" << std::endl;
    }

    void part_two()
    {
        int rope_length = 10;
        int distinct_rope_visits = simulate_rope_and_count_tail(rope_length);
        std::cout << "The tail of a rope with length " << rope_length << " has visited " << distinct_rope_visits << " distinct places" << std::endl;
    }

    int simulate_rope_and_count_tail(int rope_length)
    {
        std::vector<std::string> input = this->get_input();
        std::set<std::pair<int, int>> tail_visited_coordinates;
        std::vector<std::pair<int, int>> rope(rope_length, std::pair<int, int>(0, 0));
        tail_visited_coordinates.insert(rope.back());
        for (int i = 0; i < input.size(); i++)
        {
            char direction = input[i][0];
            int move_count = std::stoi(input[i].substr(2));
            for (int i = 0; i < move_count; i++)
            {
                move_head(direction, rope.front());
                move_rope(rope);
                tail_visited_coordinates.insert(rope.back());
            }
        }
        // print_debug(tail_visited_coordinates);
        return tail_visited_coordinates.size();
    }

    void move_rope(std::vector<std::pair<int, int>> &rope)
    {
        for (int r = 1; r < rope.size(); r++)
        {
            int abs_diff_x = abs(rope[r].first - rope[r - 1].first);
            int abs_diff_y = abs(rope[r].second - rope[r - 1].second);
            if (abs_diff_x == 2 && abs_diff_y == 0)
            {
                rope[r].first = rope[r].first > rope[r - 1].first ? rope[r].first - 1 : rope[r].first + 1;
            }
            else if (abs_diff_y == 2 && abs_diff_x == 0)
            {
                rope[r].second = rope[r].second > rope[r - 1].second ? rope[r].second - 1 : rope[r].second + 1;
            }
            else if (abs_diff_x > 1 || abs_diff_y > 1)
            {
                std::pair<int, int> diagonals[] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
                for (auto diag : diagonals)
                {
                    if (abs(rope[r].first + diag.first - rope[r - 1].first) < 2 && abs(rope[r].second + diag.second - rope[r - 1].second) < 2)
                    {
                        rope[r].first += diag.first;
                        rope[r].second += diag.second;
                        break;
                    }
                }
            }
        }
    }

    void move_head(char direction, std::pair<int, int> &head)
    {
        switch (direction)
        {
        case 'D':
            head.second--;
            break;
        case 'U':
            head.second++;
            break;
        case 'L':
            head.first--;
            break;
        case 'R':
            head.first++;
            break;
        }
    }

    void print_debug(std::set<std::pair<int, int>> tail_visited_coordinates)
    {
        std::vector<std::vector<bool>> print(5, std::vector<bool>(6));
        for (auto e : tail_visited_coordinates)
        {
            print[e.second][e.first] = true;
        }
        for (int y = print.size() - 1; y >= 0; y--)
        {
            for (int x = 0; x < print[y].size(); x++)
            {
                if (print[y][x])
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