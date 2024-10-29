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

struct person_pos_3d
{
    person_pos_3d(int x, int y, int maze_index)
        : x(x), y(y), maze_index(maze_index) {}
    int x;
    int y;
    int maze_index;

    bool operator<(const person_pos_3d &other) const
    {
        if (x != other.x)
        {
            return x < other.x;
        }
        if (y != other.y)
        {
            return y < other.y;
        }
        return maze_index < other.maze_index;
    }
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
        init_maze();
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

    void init_maze()
    {
        maze = std::vector<std::vector<char>>(y_size, std::vector<char>(x_size, '#'));
        maze[0][1] = '.';
        maze[maze.size() - 1][maze[0].size() - 2] = '.';
        for (int y = 1; y < maze.size() - 1; y++)
        {
            for (int x = 1; x < maze[y].size() - 1; x++)
            {
                maze[y][x] = '.';
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

        person_pos_3d start(1, 0, 0);
        person_pos_3d dest(maze_x_size - 2, maze_y_size - 1, 0);

        std::cout << "The fewest minutesto reach the goal is " << bfs_to_destination(mazes, start, dest).maze_index << std::endl;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();
        this->maze_x_size = input[0].size();
        this->maze_y_size = input.size();

        maze_list mazes(parse_blizzards(input), maze_x_size, maze_y_size);

        person_pos_3d start(1, 0, 0);
        person_pos_3d dest(maze_x_size - 2, maze_y_size - 1, 0);

        dest = bfs_to_destination(mazes, start, dest);
        start = bfs_to_destination(mazes, dest, start);
        dest = bfs_to_destination(mazes, start, dest);

        std::cout << "The fewest minutes to reach the goal, go back to the start, then reach the goal again is "
                  << bfs_to_destination(mazes, start, dest).maze_index
                  << std::endl;
    }

    person_pos_3d bfs_to_destination(maze_list &mazes, person_pos_3d start, person_pos_3d dest)
    {
        // person x,y & maze_index
        std::queue<person_pos_3d> search;
        std::set<person_pos_3d> visited_coordinates;

        search.push(start);
        while (true)
        {
            auto current_pos = search.front();
            search.pop();
            if (current_pos.x == dest.x && current_pos.y == dest.y)
            {
                // print_blizzard_maze(mazes.get_maze(current_pos.maze_index), current_pos.x, current_pos.y);
                return current_pos;
            }
            std::vector<std::pair<int, int>> offset = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto &o : offset)
            {
                int new_x = current_pos.x + o.first;
                int new_y = current_pos.y + o.second;
                if (new_x < 0 || new_x > maze_x_size - 1 || new_y < 0 || new_y > maze_y_size - 1)
                {
                    continue;
                }
                person_pos_3d person_new_pos(new_x, new_y, current_pos.maze_index + 1);
                if (visited_coordinates.find(person_new_pos) == visited_coordinates.end() &&
                    mazes.get_maze(current_pos.maze_index + 1).maze[new_y][new_x] == '.')
                {
                    search.push(person_new_pos);
                    visited_coordinates.insert(person_new_pos);
                }
            }
            // print_blizzard_maze(mazes.get_maze(current_pos.maze_index), current_pos.x, current_pos.y);
        }
    }

    void print_blizzard_maze(blizzard_maze maze, int player_x, int player_y)
    {
        if (player_x >= 0 && player_y >= 0)
            maze.maze[player_y][player_x] = 'E';
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

    std::vector<blizzard> parse_blizzards(std::vector<std::string> &input)
    {
        std::vector<blizzard> blizzards;
        for (int y = 0; y < input.size(); y++)
        {
            for (int x = 0; x < input[y].size(); x++)
            {
                if (input[y][x] != '.' && input[y][x] != '#')
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