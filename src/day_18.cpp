#include "advent_day.h"
#include <set>
#include <deque>

class Day_18 : public AdventDay
{
public:
    Day_18() : AdventDay(18) {}
    void part_one()
    {
        std::vector<std::string> input = this->get_input();

        // parse each string to tuple and add to set
        std::set<std::tuple<int, int, int>> cubes;
        for (auto cube_coordinate_string : input)
        {
            auto cube_coordinate = parse_coordinate_string(cube_coordinate_string);
            cubes.insert(cube_coordinate);
        }

        // for each cube check each side for another cube, and calculate side_count
        int total_side_count = 0;
        std::vector<std::tuple<int, int, int>> directions_to_check = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};
        for (auto [x_cube, y_cube, z_cube] : cubes)
        {
            int cube_side_count = 6;
            for (auto [x_offset, y_offset, z_offset] : directions_to_check)
            {
                int x = x_cube + x_offset, y = y_cube + y_offset, z = z_cube + z_offset;
                if (cubes.find({x, y, z}) != cubes.end())
                {
                    cube_side_count--;
                }
            }
            total_side_count += cube_side_count;
        }
        std::cout << "The surface area of the scanned lava droplet is " << total_side_count << std::endl;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();

        // parse each string to tuple, add to set and find max coordinates
        std::set<std::tuple<int, int, int>> cubes;
        int x_max = 0, y_max = 0, z_max = 0;
        for (auto cube_coordinate_string : input)
        {
            auto [x, y, z] = parse_coordinate_string(cube_coordinate_string);
            cubes.insert({x, y, z});
            x_max = std::max(x_max, x);
            y_max = std::max(y_max, y);
            z_max = std::max(z_max, z);
        }

        // initialize a 3d vector with padding of 1 on each side containing the lava droplets
        std::vector<std::vector<std::vector<int>>> cubes_3d(x_max + 3, std::vector<std::vector<int>>(y_max + 3, std::vector<int>(z_max + 3, 0)));
        for (auto [x, y, z] : cubes)
        {
            cubes_3d[x + 1][y + 1][z + 1] = 1;
        }

        // bfs search from 0,0,0 to count all the surfaces that are on the outside
        std::deque<std::tuple<int, int, int>> bfs_deque;
        std::vector<std::tuple<int, int, int>> directions_to_check = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};
        bfs_deque.push_back({0, 0, 0});
        int total_surface_count = 0;
        while (!bfs_deque.empty())
        {
            auto [x_current, y_current, z_current] = bfs_deque.front();
            bfs_deque.pop_front();
            int adjacent_surfaces = 0;
            for (auto [x_offset, y_offset, z_offset] : directions_to_check)
            {
                int x = x_current + x_offset, y = y_current + y_offset, z = z_current + z_offset;
                if (x >= 0 && x < cubes_3d.size() && y >= 0 && y < cubes_3d[x].size() && z >= 0 && z < cubes_3d[x][y].size())
                {
                    if (cubes_3d[x][y][z] == 0)
                    {
                        bfs_deque.push_back({x, y, z});
                        cubes_3d[x][y][z] = -1;
                    }
                    if (cubes_3d[x][y][z] == 1)
                    {
                        adjacent_surfaces++;
                    }
                }
            }
            total_surface_count += adjacent_surfaces;
        }
        std::cout << "The surface area of the scanned lava droplet is " << total_surface_count << std::endl;
    }

    std::tuple<int, int, int> parse_coordinate_string(std::string coordinate_string)
    {
        int comma_index = coordinate_string.find(",");
        int x = std::stoi(coordinate_string.substr(0, comma_index));
        coordinate_string = coordinate_string.substr(comma_index + 1);

        comma_index = coordinate_string.find(",");
        int y = std::stoi(coordinate_string.substr(0, comma_index));
        coordinate_string = coordinate_string.substr(comma_index + 1);

        int z = std::stoi(coordinate_string);

        return {x, y, z};
    }
};

int main()
{
    Day_18 day;
    day.part_one();
    day.part_two();
    return 0;
}