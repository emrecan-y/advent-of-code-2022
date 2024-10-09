#include "advent_day.h"
#include <list>
#include <set>

class Day_17 : AdventDay
{
public:
    Day_17() : AdventDay(17) {}
    std::vector<std::vector<bool>> vectical_chamber;

    void part_one()
    {
        std::string input_commands = this->get_input()[0];

        vectical_chamber = std::vector<std::vector<bool>>(0, std::vector<bool>(7, false));

        std::vector<std::vector<std::vector<bool>>> rocks = get_rocks();
        int current_rock_index = 0;
        int current_input_command_index = 0;
        for (int rock_count = 2022; rock_count > 0; rock_count--)
        {
            auto current_rock = rocks[current_rock_index];
            int current_rock_x = 2;
            int current_rock_y = calc_new_rock_y(current_rock);
            while (true)
            {
                auto current_input = input_commands[current_input_command_index];

                if (current_input == '>' && move_possible(current_rock, current_rock_x, current_rock_y, 1))
                {
                    current_rock_x++;
                }
                else if (current_input == '<' && move_possible(current_rock, current_rock_x, current_rock_y, -1))
                {
                    current_rock_x--;
                }

                current_input_command_index = current_input_command_index + 1 == input_commands.size() ? 0 : current_input_command_index + 1;

                if (check_colision(current_rock, current_rock_x, current_rock_y))
                {
                    break;
                }
                current_rock_y--;
            }
            persist_rock_on_vertival_chamber(current_rock, current_rock_x, current_rock_y);
            current_rock_index = current_rock_index + 1 == rocks.size() ? 0 : current_rock_index + 1;
        }
        std::cout << "The rocks reach " << get_highest_point_from_chamber(vectical_chamber) << std::endl;
    }

    void part_two()
    {
        std::string input_commands = this->get_input()[0];

        vectical_chamber = std::vector<std::vector<bool>>(0, std::vector<bool>(7, false));

        std::vector<std::vector<std::vector<bool>>> rocks = get_rocks();
        int current_rock_index = 0;
        int current_input_command_index = 0;
        for (std::int64_t rock_count = 1000000000000; rock_count > 0; rock_count--)
        {
            auto current_rock = rocks[current_rock_index];
            int current_rock_x = 2;
            int current_rock_y = calc_new_rock_y(current_rock);
            while (true)
            {
                auto current_input = input_commands[current_input_command_index];

                if (current_input == '>' && move_possible(current_rock, current_rock_x, current_rock_y, 1))
                {
                    current_rock_x++;
                }
                else if (current_input == '<' && move_possible(current_rock, current_rock_x, current_rock_y, -1))
                {
                    current_rock_x--;
                }

                current_input_command_index = current_input_command_index + 1 == input_commands.size() ? 0 : current_input_command_index + 1;

                if (check_colision(current_rock, current_rock_x, current_rock_y))
                {
                    break;
                }
                current_rock_y--;
            }
            persist_rock_on_vertival_chamber(current_rock, current_rock_x, current_rock_y);
            current_rock_index = current_rock_index + 1 == rocks.size() ? 0 : current_rock_index + 1;
        }
        std::cout << "The rocks reach " << get_highest_point_from_chamber(vectical_chamber) << std::endl;
    }

    void persist_rock_on_vertival_chamber(std::vector<std::vector<bool>> &current_rock, int &current_rock_x, int &current_rock_y)
    {
        for (int y = 0; y < current_rock.size(); y++)
        {
            for (int x = 0; x < current_rock[y].size(); x++)
            {
                if (current_rock[y][x])
                {
                    vectical_chamber[current_rock_y + y][current_rock_x + x] = true;
                }
            }
        }
    }

    int calc_new_rock_y(std::vector<std::vector<bool>> &current_rock)
    {
        int highest_point = get_highest_point_from_chamber(vectical_chamber);
        int rock_free_levels = vectical_chamber.size() - highest_point;
        int levels_to_add = 3 - rock_free_levels + current_rock.size();
        for (; levels_to_add > 0; levels_to_add--)
        {
            vectical_chamber.push_back(std::vector<bool>(7, false));
        }
        return highest_point + 3;
    }

    bool check_colision(std::vector<std::vector<bool>> &current_rock, int &current_rock_x, int &current_rock_y)
    {
        int y_after_fall = current_rock_y - 1;
        if (y_after_fall < 0)
        {
            return true;
        }
        for (int y = 0; y < current_rock.size(); y++)
        {
            for (int x = 0; x < current_rock[y].size(); x++)
            {
                if (current_rock[y][x] && vectical_chamber[y_after_fall + y][current_rock_x + x])
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool move_possible(std::vector<std::vector<bool>> &current_rock, int current_rock_x, int current_rock_y, int move)
    {
        int x_after_move = current_rock_x + move;
        if (x_after_move < 0 || x_after_move + current_rock[0].size() > vectical_chamber[0].size())
        {
            return false;
        }
        for (int y = 0; y < current_rock.size(); y++)
        {
            for (int x = 0; x < current_rock[y].size(); x++)
            {
                if (current_rock[y][x] && vectical_chamber[current_rock_y + y][x_after_move + x])
                {
                    return false;
                }
            }
        }
        return true;
    }

    std::int64_t get_highest_point_from_chamber(std::vector<std::vector<bool>> &vectical_chamber)
    {
        int highest_point = 0;
        for (int y = vectical_chamber.size() - 1; y >= 0; y--)
        {
            for (int x = 0; x < vectical_chamber[y].size(); x++)
            {
                if (vectical_chamber[y][x])
                {
                    return y + 1;
                }
            }
        }
        return 0;
    }

    std::vector<std::vector<std::vector<bool>>> get_rocks()
    {
        std::vector<std::vector<std::vector<bool>>> rocks(5);
        // -
        rocks[0] = {{true, true, true, true}};
        // +
        rocks[1] = {{false, true, false}, {true, true, true}, {false, true, false}};
        // L
        rocks[2] = {{true, true, true}, {false, false, true}, {false, false, true}};
        // I
        rocks[3] = {{true}, {true}, {true}, {true}};
        // square
        rocks[4] = {{true, true}, {true, true}};
        return rocks;
    }
};

int main()
{
    Day_17 day;
    day.part_one();
    // day.part_two();
    return 0;
}