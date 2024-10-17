#include "advent_day.h"
#include <map>
#include <set>
#include <deque>

struct Direction
{
    Direction(std::string move_direction, std::vector<std::string> adjacency_check)
    {
        this->move_direction = move_direction;
        this->adjacency_check = adjacency_check;
    }
    std::string move_direction;
    std::vector<std::string> adjacency_check;
};

class Day_23 : public AdventDay
{
public:
    Day_23() : AdventDay(23) {};

    void part_one()
    {

        init_elf_coordinates();
        init_directions();

        for (int roundCount = 10; roundCount > 0; roundCount--)
        {
            std::map<std::pair<int, int>, int> possible_moves;
            // first half
            for (auto [elf_pos, elf_id] : elf_coordinates)
            {
                // consider the eight adjacent positions, if no other Elves are in one of those eight positions, the Elf does not do anything
                if (!has_adjacent_elves(elf_pos))
                {
                    continue;
                }

                // check direction proposes
                for (Direction current_direction : directions)
                {
                    // second half
                    if (!direction_has_adjacent_elves(current_direction, elf_pos))
                    {
                        auto [dx, dy] = string_to_dir[current_direction.move_direction];
                        std::pair<int, int> coordinates_after_move = {elf_pos.first + dx, elf_pos.second + dy};
                        if (possible_moves.find(coordinates_after_move) == possible_moves.end())
                        {
                            possible_moves[coordinates_after_move] = elf_id;
                        }
                        else
                        {
                            possible_moves[coordinates_after_move] = -1;
                        }
                        break;
                    }
                }
            }
            // make possible moves
            for (auto move : possible_moves)
            {
                if (move.second != -1)
                {
                    move_elf_by_id(move);
                }
            }
            directions.push_back(directions.front());
            directions.pop_front();
        }
        std::cout << "The smallest rectangle after 10 rounds has an empty tile count of " << calculate_empty_ground_tiles() << std::endl;
    }

    void part_two()
    {
        init_elf_coordinates();
        init_directions();
        int round_count = 1;
        while (true)
        {
            std::map<std::pair<int, int>, int> possible_moves;
            // first half
            for (auto [elf_pos, elf_id] : elf_coordinates)
            {
                // consider the eight adjacent positions, if no other Elves are in one of those eight positions, the Elf does not do anything
                if (!has_adjacent_elves(elf_pos))
                {
                    continue;
                }

                // check direction proposes
                for (Direction current_direction : directions)
                {
                    // second half
                    if (!direction_has_adjacent_elves(current_direction, elf_pos))
                    {
                        auto [dx, dy] = string_to_dir[current_direction.move_direction];
                        std::pair<int, int> coordinates_after_move = {elf_pos.first + dx, elf_pos.second + dy};
                        if (possible_moves.find(coordinates_after_move) == possible_moves.end())
                        {
                            possible_moves[coordinates_after_move] = elf_id;
                        }
                        else
                        {
                            possible_moves[coordinates_after_move] = -1;
                        }
                        break;
                    }
                }
            }
            if (possible_moves.empty())
            {
                break;
            }
            // make possible moves
            for (auto move : possible_moves)
            {
                if (move.second != -1)
                {
                    move_elf_by_id(move);
                }
            }
            round_count++;
            directions.push_back(directions.front());
            directions.pop_front();
        }

        std::cout << "The number of the first round where no Elf moves is " << round_count << std::endl;
    }

private:
    std::map<std::pair<int, int>, int> elf_coordinates;
    std::deque<Direction> directions;
    std::map<std::string, std::pair<int, int>> string_to_dir =
        {{"N", {0, -1}}, {"NE", {1, -1}}, {"E", {1, 0}}, {"SE", {1, 1}}, {"S", {0, 1}}, {"SW", {-1, 1}}, {"W", {-1, 0}}, {"NW", {-1, -1}}};

    void init_directions()
    {
        directions.clear();
        // If there is no Elf in the N, NE, or NW adjacent positions, the Elf proposes moving north one step.
        // If there is no Elf in the S, SE, or SW adjacent positions, the Elf proposes moving south one step.
        // If there is no Elf in the W, NW, or SW adjacent positions, the Elf proposes moving west one step.
        // If there is no Elf in the E, NE, or SE adjacent positions, the Elf proposes moving east one step.
        directions.push_back(Direction("N", {"N", "NE", "NW"}));
        directions.push_back(Direction("S", {"S", "SE", "SW"}));
        directions.push_back(Direction("W", {"W", "NW", "SW"}));
        directions.push_back(Direction("E", {"E", "NE", "SE"}));
    };

    void init_elf_coordinates()
    {
        elf_coordinates.clear();
        std::vector<std::string> input = this->get_input();
        int elf_id = 0;
        for (int y = 0; y < input.size(); y++)
        {
            for (int x = 0; x < input[y].size(); x++)
            {
                if (input[y][x] == '#')
                {
                    elf_coordinates[{x, y}] = elf_id;
                    elf_id++;
                }
            }
        }
    }

    int calculate_empty_ground_tiles()
    {
        std::pair<int, int> min_coordinates = {INT_MAX, INT_MAX};
        std::pair<int, int> max_coordinates = {INT_MIN, INT_MIN};
        for (auto [elf_pos, elf_id] : elf_coordinates)
        {
            auto [elf_x, elf_y] = elf_pos;
            min_coordinates.first = elf_x < min_coordinates.first ? elf_x : min_coordinates.first;
            min_coordinates.second = elf_y < min_coordinates.second ? elf_y : min_coordinates.second;
            max_coordinates.first = elf_x > max_coordinates.first ? elf_x : max_coordinates.first;
            max_coordinates.second = elf_y > max_coordinates.second ? elf_y : max_coordinates.second;
        }
        int x_size = max_coordinates.first - min_coordinates.first + 1;
        int y_size = max_coordinates.second - min_coordinates.second + 1;
        return x_size * y_size - elf_coordinates.size();
    }

    bool direction_has_adjacent_elves(Direction &current_direction, const std::pair<int, int> elf_pos)
    {
        for (auto direction_string : current_direction.adjacency_check)
        {
            auto [dx, dy] = string_to_dir[direction_string];
            if (elf_coordinates.find({elf_pos.first + dx, elf_pos.second + dy}) != elf_coordinates.end())
            {
                return true;
            }
        }
        return false;
    }

    bool has_adjacent_elves(const std::pair<int, int> elf_pos)
    {
        std::vector<std::pair<int, int>> adjacent_blocks = {{1, 1}, {0, 1}, {-1, 1}, {1, 0}, {-1, 0}, {1, -1}, {0, -1}, {-1, -1}};
        for (auto [dx, dy] : adjacent_blocks)
        {
            if (elf_coordinates.find({elf_pos.first + dx, elf_pos.second + dy}) != elf_coordinates.end())
            {
                return true;
            }
        }
        return false;
    }

    void move_elf_by_id(std::pair<std::pair<int, int>, int> move)
    {
        auto elf_id = move.second;
        auto elf_pos = find_elf_pos_by_if(elf_id);
        elf_coordinates.erase(elf_pos);
        elf_coordinates[move.first] = elf_id;
    }

    std::pair<int, int> find_elf_pos_by_if(int id)
    {
        for (auto elf : elf_coordinates)
        {
            if (elf.second == id)
            {
                return elf.first;
            }
        }
        return {};
    }

    void print()
    {
        std::vector<std::vector<bool>> print_out(30, std::vector<bool>(30, false));
        for (auto [elf_pos, elf_id] : elf_coordinates)
        {
            print_out[elf_pos.second + 15][elf_pos.first + 15] = true;
        }

        for (int y = 0; y < print_out.size(); y++)
        {
            for (int x = 0; x < print_out[y].size(); x++)
            {
                if (print_out[y][x])
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main()
{
    Day_23 day;
    day.part_one();
    day.part_two();
    return 0;
}