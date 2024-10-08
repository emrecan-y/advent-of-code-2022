#include "advent_day.h"
#include <list>

class Day_14 : public AdventDay
{
public:
    Day_14() : AdventDay(14) {}
    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        std::vector<std::vector<char>> cave(500, std::vector<char>(1000, '.'));
        for (auto s : input)
        {
            std::vector<std::string> coordinates;
            parse_coordinates(coordinates, s);

            for (int i = 0; i < coordinates.size() - 1; i++)
            {
                auto start = parse_single_coordinate(coordinates[i]);
                auto end = parse_single_coordinate(coordinates[i + 1]);
                draw_stone(cave, start, end);
            }
        }
        std::cout << "Until the sand falls in to the abbys, it takes " << sand_simulation(cave) << " sand grains" << std::endl;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();
        std::vector<std::vector<char>> cave(500, std::vector<char>(1000, '.'));
        for (auto s : input)
        {
            std::vector<std::string> coordinates;
            parse_coordinates(coordinates, s);

            for (int i = 0; i < coordinates.size() - 1; i++)
            {
                auto start = parse_single_coordinate(coordinates[i]);
                auto end = parse_single_coordinate(coordinates[i + 1]);
                draw_stone(cave, start, end);
            }
        }
        draw_floor(cave);
        std::cout << "Until the fill the floor and comes to a stop it takes  " << sand_simulation(cave) << " sand grains" << std::endl;
    }

    void print_cave(std::vector<std::vector<char>> &cave)
    {
        for (int y = 0; y < 20; y++)
        {
            for (int x = 460; x < 540; x++)
            {
                std::cout << cave[y][x];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    int sand_simulation(std::vector<std::vector<char>> &cave)
    {
        // for testing purposes i had a while(true) loop after a print_cave, but the compiler optimizations
        // changed the state of the cave, weird behaviour!
        int sand_count = 0;
        while (true)
        {
            std::pair<int, int> sand(500, 0);
            while (sand.second < 499)
            {
                if (cave[sand.second + 1][sand.first] == '.')
                {
                    sand.second++;
                }
                else if (cave[sand.second + 1][sand.first - 1] == '.')
                {
                    sand.second++;
                    sand.first--;
                }
                else if (cave[sand.second + 1][sand.first + 1] == '.')
                {
                    sand.second++;
                    sand.first++;
                }
                else
                {
                    cave[sand.second][sand.first] = 'o';
                    break;
                }
            }
            if (sand.second == 499)
            {
                return sand_count;
            }
            if (sand.first == 500 && sand.second == 0)
            {
                return sand_count + 1;
            }
            sand_count++;
        }
    }

    void draw_stone(std::vector<std::vector<char>> &cave, std::pair<int, int> &start, std::pair<int, int> &end)
    {
        // draw horizontal
        int draw_start = start.first < end.first ? start.first : end.first;
        int draw_end = start.first > end.first ? start.first : end.first;
        for (int x = draw_start; x <= draw_end; x++)
        {
            cave[start.second][x] = '#';
        }

        // draw vertical
        draw_start = start.second < end.second ? start.second : end.second;
        draw_end = start.second > end.second ? start.second : end.second;
        for (int y = draw_start; y <= draw_end; y++)
        {
            cave[y][start.first] = '#';
        }
    }

    std::pair<int, int> parse_single_coordinate(std::string &coordinate)
    {
        int comma_index = coordinate.find(",");
        int x = std::stoi(coordinate.substr(0, comma_index));
        int y = std::stoi(coordinate.substr(comma_index + 1));
        return {x, y};
    }

    void parse_coordinates(std::vector<std::string> &coordinates, std::string &s)
    {
        int arrow_index;
        while ((arrow_index = s.find("->")) != -1)
        {
            coordinates.push_back(s.substr(0, arrow_index));
            s = s.substr(arrow_index + 2);
        }
        coordinates.push_back(s);
    }

    void draw_floor(std::vector<std::vector<char>> &cave)
    {
        int floor_index = -1;
        for (int y = cave.size() - 1; y >= 0 && floor_index == -1; y--)
        {
            for (int x = 0; x < cave[y].size(); x++)
            {
                if (cave[y][x] != '.')
                {
                    floor_index = y + 2;
                    break;
                }
            }
        }

        for (int x = 0; x < cave[floor_index].size(); x++)
        {
            if (cave[floor_index][x])
            {
                cave[floor_index][x] = '#';
            }
        }
    }
};

int main()
{
    Day_14 day;
    day.part_one();
    day.part_two();
    return 0;
}