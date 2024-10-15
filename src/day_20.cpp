#include "advent_day.h"
#include <list>
#include <algorithm>

class Day_20 : public AdventDay
{
public:
    Day_20() : AdventDay(20) {}

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        std::vector<long> initial_sequence;
        // pair containing original index and value
        std::list<std::pair<int, long>> new_sequence;

        for (int i = 0; i < input.size(); i++)
        {
            int num_value = std::stoi(input[i]);
            initial_sequence.push_back(num_value);
            new_sequence.push_back({i, num_value});
        }

        mix_list(initial_sequence, new_sequence);

        long sum_groove_coordinates = get_sum_groove_coordinates(new_sequence);
        std::cout << "The sum of the groove coordinates after mixing once is " << sum_groove_coordinates << std::endl;
    }

    void part_two()
    {
        long decryption_key = 811589153;
        std::vector<std::string> input = this->get_input();
        std::vector<long> initial_sequence;
        // pair containing original index and value
        std::list<std::pair<int, long>> new_sequence;

        for (int i = 0; i < input.size(); i++)
        {
            long num_value = std::stoi(input[i]) * decryption_key;
            initial_sequence.push_back(num_value);
            new_sequence.push_back({i, num_value});
        }

        for (int i = 0; i < 10; i++)
        {
            mix_list(initial_sequence, new_sequence);
        }

        long sum_groove_coordinates = get_sum_groove_coordinates(new_sequence);
        std::cout << "The sum of the groove coordinates after mixing ten times is " << sum_groove_coordinates << std::endl;
    }

    long get_sum_groove_coordinates(std::list<std::pair<int, long>> &new_sequence)
    {
        return get_nth_element(new_sequence, 1000) + get_nth_element(new_sequence, 2000) + get_nth_element(new_sequence, 3000);
    }

    void mix_list(std::vector<long> &initial_sequence, std::list<std::pair<int, long>> &new_sequence)
    {
        for (int i = 0; i < initial_sequence.size(); i++)
        {
            long num = initial_sequence[i];
            if (num == 0)
            {
                continue;
            }
            auto it = new_sequence.erase(std::find(new_sequence.begin(), new_sequence.end(), std::pair(i, num)));
            int move_count = abs(num) % (initial_sequence.size() - 1);
            if (num > 0)
            {
                for (; move_count > 0; move_count--)
                {
                    if (it == new_sequence.end())
                    {
                        it = new_sequence.begin();
                    }
                    it++;
                }
            }
            else if (num < 0)
            {
                for (; move_count > 0; move_count--)
                {
                    if (it == new_sequence.begin())
                    {
                        it = new_sequence.end();
                    }
                    it--;
                }
            }
            new_sequence.insert(it, {i, num});
        }
    }

    long get_nth_element(std::list<std::pair<int, long>> &sequence, int count)
    {
        auto it = find_by_value(sequence, 0);
        auto move_count = count % sequence.size();
        for (int i = 0; i < count; i++)
        {
            if (it == sequence.end())
            {
                it = sequence.begin();
            }
            it++;
        }
        return it->second;
    }

    std::list<std::pair<int, long>>::iterator find_by_value(std::list<std::pair<int, long>> &sequence, long value)
    {
        for (auto it = sequence.begin(); it != sequence.end(); it++)
        {
            auto [i, n] = *it;
            if (n == value)
            {
                return it;
            }
        }
        return sequence.end();
    }
};

int main()
{
    Day_20 day;
    day.part_one();
    day.part_two();
    return 0;
}