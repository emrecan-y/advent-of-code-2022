#include "advent_day.h"
#include <set>
#include <queue>

struct blizzard
{
    blizzard(char dir, int x, int y) : dir(dir), x(x), y(y) {}
    char dir;
    int x;
    int y;
};

struct blizzard_maze
{
    std::vector<blizzard> blizzards;
    std::vector<std::vector<char>> maze;
    int x_size;
    int y_size;

    blizzard_maze(std::vector<blizzard> blizzards, int x_size, int y_size)
        : blizzards(blizzards), x_size(x_size), y_size(y_size)
    {
        create_maze();
    }

    void create_maze()
    {
        maze = std::vector<std::vector<char>>(y_size, std::vector<char>(x_size, '.'));
        for (auto b : blizzards)
        {
            if (maze[b.y][b.x] == '.')
            {
                maze[b.y][b.x] = b.dir;
            }
            else if (maze[b.y][b.x] == '2')
            {
                maze[b.y][b.x]++;
            }
            else
            {
                maze[b.y][b.x] = '2';
            }
        }
    }

    std::vector<blizzard> get_next_blizzards_state()
    {
        std::vector<blizzard> next_state(blizzards);
        for (auto &b : next_state)
        {
            switch (b.dir)
            {
            case '^':
                b.y = b.y > 1 ? b.y - 1 : y_size - 2;
                break;
            case '>':
                b.x = b.x < x_size - 2 ? b.x + 1 : 1;
                break;
            case '<':
                b.x = b.x > 1 ? b.x - 1 : x_size - 2;
                break;
            case 'v':
                b.y = b.y < y_size - 2 ? b.y + 1 : 1;
                break;
            }
        }
        return next_state;
    }
};

struct maze_list
{
    std::vector<blizzard_maze> mazes;
    int x_size;
    int y_size;

    maze_list(std::vector<blizzard> initial_state, int x_size, int y_size)
    {
        this->x_size = x_size;
        this->y_size = y_size;
        mazes.push_back(blizzard_maze(initial_state, x_size, y_size));
    }

    blizzard_maze &get_maze(int index)
    {
        if (index >= mazes.size())
        {
            generate_mazes(index);
        }
        return mazes[index];
    }

    void generate_mazes(int end_index)
    {
        while (end_index >= mazes.size())
        {
            auto next_blizzards_state = mazes.back().get_next_blizzards_state();
            mazes.push_back(blizzard_maze(next_blizzards_state, x_size, y_size));
        }
    }
};

class Day_24 : public AdventDay
{
public:
    Day_24() : AdventDay(24) {};

    int maze_x_size;
    int maze_y_size;

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        this->maze_x_size = input[0].size();
        this->maze_y_size = input.size();

        maze_list mazes(parse_blizzards(input), maze_x_size, maze_y_size);

        std::cout << "bfs" << std::endl;
        std::cout << bfs_maze_count(mazes);
    }

    int bfs_maze_count(maze_list &mazes)
    {
        // person x,y & maze_index
        std::queue<std::pair<std::pair<int, int>, int>> search;
        std::set<std::pair<std::pair<int, int>, int>> visited_coordinates;

        search.push({{1, 0}, 0});
        while (true)
        {
            auto current_pos = search.front();
            search.pop();
            if (current_pos.first.first == maze_x_size - 2 && current_pos.first.second == maze_y_size - 1)
            {
                print_blizzard_maze(mazes.get_maze(current_pos.second), current_pos.first.first, current_pos.first.second);
                return current_pos.second;
            }
            std::vector<std::pair<int, int>> offset = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto &o : offset)
            {
                int new_x = current_pos.first.first + o.first;
                int new_y = current_pos.first.second + o.second;
                if (new_x < 0 || new_x > maze_x_size - 1 || new_y < 0 || new_y > maze_y_size - 1)
                {
                    continue;
                }
                if (mazes.get_maze(current_pos.second + 1).maze[new_y][new_x] == '.' &&
                    visited_coordinates.find({{new_x, new_y}, current_pos.second + 1}) == visited_coordinates.end())
                {
                    search.push({{new_x, new_y}, current_pos.second + 1});
                    visited_coordinates.insert({{new_x, new_y}, current_pos.second + 1});
                }
            }
            if (current_pos.first == std::pair(0, -1))
            {
                current_pos.second++;
                search.push(current_pos);
            }
            // print_blizzard_maze(mazes.get_maze(current_pos.second), current_pos.first.first, current_pos.first.second);
        }
    }

    void print_blizzard_maze(blizzard_maze maze, int x, int y)
    {
        if (x >= 0 && y >= 0)
            maze.maze[y][x] = 'E';
        auto m = maze.maze;
        for (int y = 0; y < m.size(); y++)
        {
            for (int x = 0; x < m[y].size(); x++)
            {
                std::cout << m[y][x];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void part_two()
    {
    }

    std::vector<blizzard> parse_blizzards(std::vector<std::string> &input)
    {
        std::vector<blizzard> blizzards;
        for (int y = 0; y < input.size(); y++)
        {
            for (int x = 0; x < input[y].size(); x++)
            {
                if (input[y][x] != '.')
                {
                    blizzards.push_back(blizzard(input[y][x], x, y));
                }
            }
        }
        return blizzards;
    }
};

int main()
{
    Day_24 day;
    day.part_one();
    day.part_two();
    return 0;
}