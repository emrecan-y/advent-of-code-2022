#include "advent_day.h"

class Day_8 : public AdventDay
{
public:
    Day_8() : AdventDay(8) {}

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        std::vector<std::vector<int>> treemap_2d(input.size(), std::vector<int>(input[0].size()));

        // convert string vector to 2d int vector
        for (int y = 0; y < input.size(); y++)
        {
            for (int x = 0; x < input[y].size(); x++)
            {
                // 48 == '0'
                treemap_2d[y][x] = input[y][x] - 48;
            }
        }

        int visible_tree_count = 0;
        for (int y = 0; y < treemap_2d.size(); y++)
        {
            for (int x = 0; x < treemap_2d[y].size(); x++)
            {
                if (tree_is_visible(treemap_2d, y, x))
                {
                    visible_tree_count++;
                }
            }
        }

        std::cout << "The count of visible trees is " << std::to_string(visible_tree_count) << std::endl;
    }

    bool tree_is_visible(std::vector<std::vector<int>> &treemap_2d, int y, int x)
    {
        // check for tree on border
        if (x == 0 || y == 0 || y == treemap_2d.size() - 1 || x == treemap_2d[0].size() - 1)
        {
            return true;
        }
        bool up, down, left, right;
        up = down = left = right = true;

        // check tree visibility in all directions
        up = visibility_loop(treemap_2d, y, x, -1, 0);
        down = visibility_loop(treemap_2d, y, x, 1, 0);
        left = visibility_loop(treemap_2d, y, x, 0, -1);
        right = visibility_loop(treemap_2d, y, x, 0, 1);

        return up || down || left || right;
    }

    bool visibility_loop(std::vector<std::vector<int>> &treemap_2d, int y, int x, int steps_y, int steps_x)
    {
        int initial_tree = treemap_2d[y][x];
        while (y > 0 && y < treemap_2d.size() - 1 && x > 0 && x < treemap_2d[y].size() - 1)
        {
            y += steps_y;
            x += steps_x;
            if (treemap_2d[y][x] >= initial_tree)
            {
                return false;
            }
        }
        return true;
    }
    void part_two()
    {
        std::vector<std::string> input = this->get_input();
        std::vector<std::vector<int>> treemap_2d(input.size(), std::vector<int>(input[0].size()));

        // convert string vector to 2d int vector
        for (int y = 0; y < input.size(); y++)
        {
            for (int x = 0; x < input[y].size(); x++)
            {
                // 48 == '0'
                treemap_2d[y][x] = input[y][x] - 48;
            }
        }

        int max_scenic_score = 0;
        // iterate over the tress excluding the border trees
        for (int y = 1; y < treemap_2d.size() - 1; y++)
        {
            for (int x = 1; x < treemap_2d[y].size() - 1; x++)
            {
                int scenic_score = calculate_scenic_score(treemap_2d, y, x);
                if (scenic_score > max_scenic_score)
                {
                    max_scenic_score = scenic_score;
                }
            }
        }

        std::cout << "The maximum scenic score is " << std::to_string(max_scenic_score) << std::endl;
    }

    int calculate_scenic_score(std::vector<std::vector<int>> &treemap_2d, int y, int x)
    {
        int up, down, left, right;
        // count visible trees in all directions
        up = visibility_count_loop(treemap_2d, y, x, -1, 0);
        down = visibility_count_loop(treemap_2d, y, x, 1, 0);
        left = visibility_count_loop(treemap_2d, y, x, 0, -1);
        right = visibility_count_loop(treemap_2d, y, x, 0, 1);
        return up * down * left * right;
    }

    int visibility_count_loop(std::vector<std::vector<int>> &treemap_2d, int y, int x, int steps_y, int steps_x)
    {
        int initial_tree = treemap_2d[y][x];
        int count = 0;
        while (y > 0 && y < treemap_2d.size() - 1 && x > 0 && x < treemap_2d[y].size() - 1)
        {
            y += steps_y;
            x += steps_x;
            count++;
            if (treemap_2d[y][x] >= initial_tree)
            {
                break;
            }
        }
        return count;
    }
};

int main()
{
    Day_8 day;
    day.part_one();
    day.part_two();
    return 0;
}