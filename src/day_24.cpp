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
    blizzard_maze(std::vector<blizzard> blizzards, int x_size, int y_size) : blizzards(blizzards)
    {
        create_maze(x_size, y_size);
    }
    std::vector<blizzard> blizzards;
    std::vector<std::vector<char>> maze;

    void create_maze(int x_size, int y_size)
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
};

class Day_24 : public AdventDay
{
public:
    Day_24() : AdventDay(0) {};

    int maze_x_size;
    int maze_y_size;

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        this->maze_x_size = input[0].size() - 2;
        this->maze_y_size = input.size() - 2;

        std::vector<blizzard> blizzards = parse_blizzards(input);
        std::vector<blizzard_maze> maze;
        maze.push_back(blizzard_maze(blizzards, maze_x_size, maze_y_size));

        for (int i = 0; i < 10000; i++)
        {
            blizzards = get_next_blizzard_state(maze.back().blizzards);
            maze.push_back(blizzard_maze(blizzards, maze_x_size, maze_y_size));
            // print_blizzard_maze(maze.back());
        }
        std::cout << "bfs" << std::endl;
        std::cout << bfs_maze_count(maze);
    }

    int bfs_maze_count(std::vector<blizzard_maze> &maze)
    {
        // person x,y & maze_index
        std::queue<std::pair<std::pair<int, int>, int>> search;
        search.push({{0, 0}, 0});
        while (true)
        {
            auto current_pos = search.front();
            search.pop();

            if (current_pos.first.first == maze_x_size - 1 && current_pos.first.second == maze_y_size - 1)
            {
                print_blizzard_maze(maze[current_pos.second], current_pos.first.first, current_pos.first.second);

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
                if (maze[current_pos.second + 1].maze[new_y][new_x] == '.')
                {
                    search.push({{new_x, new_y}, current_pos.second + 1});
                }
            }
            // print_blizzard_maze(maze[current_pos.second], current_pos.first.first, current_pos.first.second);
        }
    }

    void print_blizzard_maze(blizzard_maze maze, int x, int y)
    {
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

    std::vector<blizzard> get_next_blizzard_state(std::vector<blizzard> current_state)
    {
        for (auto &b : current_state)
        {
            switch (b.dir)
            {
            case '^':
                b.y = b.y > 0 ? b.y - 1 : maze_y_size - 1;
                break;
            case '>':
                b.x = b.x < maze_x_size - 1 ? b.x + 1 : 0;
                break;
            case '<':
                b.x = b.x > 0 ? b.x - 1 : maze_x_size - 1;
                break;
            case 'v':
                b.y = b.y < maze_y_size - 1 ? b.y + 1 : 0;
                break;
            }
        }
        return current_state;
    }

    std::vector<blizzard> parse_blizzards(std::vector<std::string> &input)
    {
        std::vector<blizzard> blizzards;
        for (int y = 1; y < input.size() - 1; y++)
        {
            for (int x = 1; x < input[y].size() - 1; x++)
            {
                if (input[y][x] != '.')
                {
                    blizzards.push_back(blizzard(input[y][x], x - 1, y - 1));
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