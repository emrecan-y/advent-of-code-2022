#include "advent_day.h"
#include <set>
#include <list>

class Day_12 : public AdventDay
{
public:
    Day_12() : AdventDay(12) {}

    struct map_field
    {
        map_field() {}
        map_field(int y, int x, char height) : y(y), x(x), height(height) {}
        char height;
        int x;
        int y;

        int distance_to_begin = INT_MAX;
        map_field *previous_field = nullptr;
    };

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        map_field *start_field;
        map_field *end_field;
        std::vector<std::vector<map_field *>> map(input.size(), std::vector<map_field *>(input[0].size()));
        // parse
        for (int y = 0; y < input.size(); y++)
        {
            for (int x = 0; x < input[y].size(); x++)
            {
                map[y][x] = new map_field(y, x, input[y][x]);
                if (map[y][x]->height == 'S')
                {
                    map[y][x]->height = 'a';
                    map[y][x]->distance_to_begin = 0;
                    start_field = map[y][x];
                }
                if (map[y][x]->height == 'E')
                {
                    map[y][x]->height = 'z';
                    end_field = map[y][x];
                }
            }
        }
        std::cout << "fewest steps required to the location with the best signal is ";
        std::cout << bfs(map, start_field, end_field) << std::endl;
        for (auto arr : map)
        {
            for (auto e : arr)
            {
                delete e;
            }
        }
    }

    int bfs(std::vector<std::vector<map_field *>> &map, map_field *start_field, map_field *end_field)
    {
        std::set<map_field *> visited;
        std::list<map_field *> queue;
        queue.push_back(start_field);
        visited.insert(start_field);

        while (visited.find(end_field) == visited.end())
        {
            map_field *current_field = queue.front();
            queue.pop_front();

            int current_y = current_field->y;
            int current_x = current_field->x;
            int current_dist_to_begin = current_field->distance_to_begin;
            char current_height = current_field->height;

            auto try_add_neighbor = [&](int new_y, int new_x)
            {
                map_field *neighbor = map[new_y][new_x];
                if (visited.find(neighbor) == visited.end() && neighbor->height <= current_height + 1)
                {
                    neighbor->distance_to_begin = current_dist_to_begin + 1;
                    neighbor->previous_field = current_field;
                    queue.push_back(neighbor);
                    visited.insert(neighbor);
                }
            };

            if (current_y > 0)
            {
                try_add_neighbor(current_y - 1, current_x);
            }
            if (current_y < map.size() - 1)
            {
                try_add_neighbor(current_y + 1, current_x);
            }
            if (current_x > 0)
            {
                try_add_neighbor(current_y, current_x - 1);
            }
            if (current_x < map[0].size() - 1)
            {
                try_add_neighbor(current_y, current_x + 1);
            }
        }
        return end_field->distance_to_begin;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();
        map_field *start_field;
        map_field *end_field;
        std::vector<std::vector<map_field *>> map(input.size(), std::vector<map_field *>(input[0].size()));

        // parse
        for (int y = 0; y < input.size(); y++)
        {
            for (int x = 0; x < input[y].size(); x++)
            {
                map[y][x] = new map_field(y, x, input[y][x]);
                if (map[y][x]->height == 'S')
                {
                    map[y][x]->height = 'a';
                    start_field = map[y][x];
                }
                if (map[y][x]->height == 'E')
                {
                    map[y][x]->height = 'z';
                    map[y][x]->distance_to_begin = 0;
                    end_field = map[y][x];
                }
            }
        }
        std::cout << "fewest steps required from the location with the best signal to a location with 'a' is ";
        std::cout << bfs_part_two(map, end_field, 'a') << std::endl;
        for (auto arr : map)
        {
            for (auto e : arr)
            {
                delete e;
            }
        }
    }

    int bfs_part_two(std::vector<std::vector<map_field *>> &map, map_field *start_field, char destination)
    {
        std::set<map_field *> visited;
        std::list<map_field *> queue;
        queue.push_back(start_field);
        visited.insert(start_field);

        while (!queue.empty())
        {
            map_field *current_field = queue.front();
            if (current_field->height == destination)
            {
                break;
            }
            queue.pop_front();

            int current_y = current_field->y;
            int current_x = current_field->x;
            int current_dist_to_begin = current_field->distance_to_begin;
            char current_height = current_field->height;

            auto try_add_neighbor = [&](int new_y, int new_x)
            {
                map_field *neighbor = map[new_y][new_x];
                if (visited.find(neighbor) == visited.end() && (neighbor->height >= current_height - 1))
                {
                    neighbor->distance_to_begin = current_dist_to_begin + 1;
                    neighbor->previous_field = current_field;
                    queue.push_back(neighbor);
                    visited.insert(neighbor);
                }
            };

            if (current_y > 0)
            {
                try_add_neighbor(current_y - 1, current_x);
            }
            if (current_y < map.size() - 1)
            {
                try_add_neighbor(current_y + 1, current_x);
            }
            if (current_x > 0)
            {
                try_add_neighbor(current_y, current_x - 1);
            }
            if (current_x < map[0].size() - 1)
            {
                try_add_neighbor(current_y, current_x + 1);
            }
        }
        return queue.front()->distance_to_begin;
    }
};

int main()
{
    Day_12 day;
    day.part_one();
    day.part_two();
    return 0;
}
