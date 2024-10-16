#include "advent_day.h"
#include <map>

class Day_22 : public AdventDay
{
public:
    Day_22() : AdventDay(0) {}

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        std::vector<std::vector<char>> monkey_map(input.size() - 2);
        std::vector<std::string> path_commands;
        std::vector<std::pair<char, std::pair<int, int>>> directions = {{'>', {1, 0}}, {'v', {0, 1}}, {'<', {-1, 0}}, {'^', {0, -1}}};

        for (int y = 0; y < input.size(); y++)
        {
            if (input[y] != "")
            {
                monkey_map[y] = std::vector<char>(input[y].size());
                for (int x = 0; x < input[y].size(); x++)
                {
                    monkey_map[y][x] = input[y][x];
                }
            }
            else
            {
                path_commands = parse_commands(input[y + 1]);
                break;
            }
        }

        int current_y = 0;
        int current_x;
        int current_direction = 0;
        // find begin "leftmost open tile of the top row"
        for (int x = 0; x < monkey_map[0].size(); x++)
        {
            if (monkey_map[0][x] == '.')
            {
                current_x = x;
                break;
            }
        }

        for (std::string command : path_commands)
        {
            if (command == "L" || command == "R")
            {
                current_direction = get_direction_after_turn(command[0], current_direction);
            }
            else
            {
                int move_count = std::stoi(command);
                auto [diff_x, diff_y] = directions[current_direction].second;

                for (; move_count > 0; move_count--)
                {
                    monkey_map[current_y][current_x] = directions[current_direction].first;
                    int new_x = current_x + diff_x;

                    int new_y = current_y + diff_y;
                    bool within_bounds_x = new_x >= 0 && new_x < monkey_map[current_y].size();
                    bool within_bounds_y = new_y >= 0 && new_y < monkey_map.size();

                    if ((current_direction % 2 == 0 && within_bounds_x && monkey_map[current_y][new_x] != ' ') ||
                        (current_direction % 2 == 1 && within_bounds_y && monkey_map[new_y][current_x] != ' '))
                    {
                        if (current_direction % 2 == 0 && monkey_map[current_y][new_x] != '#')
                        {
                            current_x = new_x;
                        }
                        else if (current_direction % 2 == 1 && monkey_map[new_y][current_x] != '#')
                        {
                            current_y = new_y;
                        }
                        else
                        {
                            move_count = 0;
                        }
                    }
                    else
                    {
                        if (current_direction % 2 == 0)
                        {
                            new_x = (current_direction == 0) ? find_horizontal_wrap(monkey_map, current_y) : monkey_map[current_y].size() - 1;
                        }
                        else
                        {
                            new_y = find_vertical_wrap(monkey_map, current_x, current_direction);
                        }
                        if (monkey_map[new_y][new_x] == '#')
                        {
                            move_count = 0;
                        }
                        else
                        {
                            current_x = new_x;
                            current_y = new_y;
                        }
                    }
                    monkey_map[current_y][current_x] = directions[current_direction].first;
                }
            }
        }
        print_monkey_map(monkey_map);
        int out = (current_y + 1) * 1000 + (current_x + 1) * 4 + current_direction;
        std::cout << out << monkey_map[current_y][current_x] << std::endl;
    }

    int find_vertical_wrap(std::vector<std::vector<char>> monkey_map, int current_x, int current_direction)
    {
        if (current_direction == 1) // down
        {
            for (int y = 0; y < monkey_map.size(); y++)
            {
                if (current_x < monkey_map[y].size() && monkey_map[y][current_x] != ' ')
                {
                    return y;
                }
            }
        }
        else if (current_direction == 3) // up
        {
            for (int y = monkey_map.size() - 1; y >= 0; y--)
            {
                if (current_x < monkey_map[y].size() && monkey_map[y][current_x] != ' ')
                {
                    return y;
                }
            }
        }
        return -1;
    }

    int find_horizontal_wrap(std::vector<std::vector<char>> monkey_map, int current_y)
    {
        for (int x = 0; x < monkey_map[current_y].size(); x++)
        {
            if (monkey_map[current_y][x] != ' ')
            {
                return x;
            }
        }
        return -1;
    }

    void print_monkey_map(std::vector<std::vector<char>> monkey_map)
    {
        for (auto v : monkey_map)
        {
            for (char c : v)
            {
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> parse_commands(std::string commands)
    {
        std::vector<std::string> commands_vector;
        while (true)
        {
            int l_index, r_index;
            if (commands[0] == 'R' || commands[0] == 'L')
            {
                commands_vector.push_back(commands.substr(0, 1));
                commands = commands.substr(1);
                continue;
            }
            else if ((l_index = commands.find("L")) != -1 | (r_index = commands.find("R")) != -1)
            {
                l_index = l_index == -1 ? INT_MAX : l_index;
                r_index = r_index == -1 ? INT_MAX : r_index;
                int min_index = l_index < r_index ? l_index : r_index;
                commands_vector.push_back(commands.substr(0, min_index));
                commands = commands.substr(min_index);
                continue;
            }
            if (commands != "")
            {
                commands_vector.push_back(commands);
            }

            break;
        }
        return commands_vector;
    }

    int get_direction_after_turn(char turn_command, int current_direction)
    {
        if (turn_command == 'R')
        {
            if (current_direction + 1 <= 3)
            {
                current_direction++;
            }
            else
            {
                current_direction = 0;
            }
        }
        else if (turn_command == 'L')
        {
            if (current_direction - 1 >= 0)
            {
                current_direction--;
            }
            else
            {
                current_direction = 3;
            }
        }
        return current_direction;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();
    }
};

int main()
{
    Day_22 day;
    day.part_one();
    day.part_two();
    return 0;
}