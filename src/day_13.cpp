#include "advent_day.h"
#include <set>
#include <list>

class Day_13 : public AdventDay
{
public:
    Day_13() : AdventDay(13) {}

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        int sum_of_correct_ordered_indices = 0;
        for (int index = 0; index <= input.size() / 3; index++)
        {
            int index_conversion = index * 3;
            std::string packet1 = input[index_conversion];
            std::string packet2 = input[index_conversion + 1];
            int correct;
            if ((correct = packet_compare(packet1, packet2)) == 1)
            {
                sum_of_correct_ordered_indices += index + 1;
            }
        }
        std::cout << "The sum of indices of pairs in the right order is " << sum_of_correct_ordered_indices << std::endl;
    }

    void part_two()
    {
        std::vector<std::string> input = this->get_input();
        std::string divider_1 = "[[2]]";
        std::string divider_2 = "[[6]]";

        auto packet_comparator = [this](const std::string &packet_1, const std::string &packet_2)
        {
            // p1 smaller than p2
            return packet_compare(packet_1, packet_2) == 1;
        };
        std::set<std::string, decltype(packet_comparator)> packets(packet_comparator);
        packets.insert(divider_1);
        packets.insert(divider_2);

        for (int index = 0; index <= input.size() / 3; index++)
        {
            int index_conversion = index * 3;
            packets.insert(input[index_conversion + 0]);
            packets.insert(input[index_conversion + 1]);
        }

        int packet_number = 1;
        int decoder_key = 1;
        for (auto p : packets)
        {
            if (p == divider_1 || p == divider_2)
            {
                decoder_key *= packet_number;
            }
            packet_number++;
        }
        std::cout << "The decoder key for the distress signal is " << decoder_key << std::endl;
    }

    int packet_compare(std::string p1, std::string p2)
    {
        auto p1_list = parse_list(p1);
        auto p2_list = parse_list(p2);

        for (int i = 0; i < p1_list.size() || i < p2_list.size(); i++)
        {
            // right side ran out
            if (i == p2_list.size() && p2_list.size() < p1_list.size())
            {
                return -1;
            }
            // left side ran out
            if (i == p1_list.size() && p1_list.size() < p2_list.size())
            {
                return 1;
            }
            if (is_integer(p1_list[i]) && is_integer(p2_list[i]))
            {
                if (stoi(p1_list[i]) < stoi(p2_list[i]))
                {
                    return 1;
                }
                else if (stoi(p1_list[i]) > stoi(p2_list[i]))
                {
                    return -1;
                }
            }
            else
            {
                int result = packet_compare(p1_list[i], p2_list[i]);
                // not considering neutral return
                if (result != 0)
                {
                    return result;
                }
            }
        }
        // this comparison is not smaller or greater
        return 0;
    }

    std::string vector_to_string(std::vector<std::string> &input)
    {
        std::string out;
        for (auto s : input)
        {
            out += s + ", ";
        }
        return out;
    }

    bool is_integer(std::string s1)
    {
        return s1.find('[') == -1 && s1.find(']') == -1 && s1.find(',') == -1;
    }

    std::string open_packet(std::string p)
    {
        int sq_bracket_b = p.find('[');
        int sq_bracket_e = p.find_last_of(']');
        if (sq_bracket_b != -1 && sq_bracket_e != -1)
        {
            p.erase(sq_bracket_b, 1);
            p.erase(sq_bracket_e - 1, 1);
        }
        return p;
    }

    std::vector<std::string> parse_list(std::string p)
    {
        std::vector<std::string> open_packet_content;
        if (p == "[]")
        {
            return open_packet_content;
        }

        p = open_packet(p);

        int comma_index;
        while ((comma_index = find_comma_index(p)) != -1)
        {
            open_packet_content.push_back(p.substr(0, comma_index));
            p = p.substr(comma_index + 1);
        }
        open_packet_content.push_back(p);
        return open_packet_content;
    }

    int find_comma_index(std::string s)
    {
        int open_brackets = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ',' && open_brackets == 0)
            {
                return i;
            }
            else if (s[i] == '[')
            {
                open_brackets++;
            }
            else if (s[i] == ']')
            {
                open_brackets--;
            }
        }
        return -1;
    }
};

int main()
{
    Day_13 day;
    day.part_one();
    day.part_two();
    return 0;
}
