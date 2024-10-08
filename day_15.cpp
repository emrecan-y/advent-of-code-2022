#include "advent_day.h"
#include <set>

class Day_15 : public AdventDay
{
    struct signal_pair
    {
        signal_pair(std::pair<int, int> sensor, std::pair<int, int> beacon) : sensor(sensor), beacon(beacon) {}
        std::pair<int, int> sensor;
        std::pair<int, int> beacon;
    };

    struct range
    {
        range(int start, int end) : start(start), end(end) {}
        int start;
        int end;

        bool operator<(const range &other) const
        {
            return end < other.start;
        }
    };

public:
    Day_15() : AdventDay(15)
    {
    }

    void part_one()
    {
        std::vector<std::string> input = this->get_input();
        std::vector<signal_pair> signal_pairs;
        for (auto s : input)
        {
            int colon_index = s.find(":");
            auto sensor = parse_coordinate(s.substr(0, colon_index));
            auto beacon = parse_coordinate(s.substr(colon_index + 1));
            signal_pairs.emplace_back(sensor, beacon);
        }

        std::set<range> no_beacon_x_coord;
        std::set<int> beacon_x_coord;

        int row_to_check = 2000000;

        for (auto sp : signal_pairs)
        {
            int dist_sensor_to_beacon = calculate_manhattan_distance(sp);

            if (sp.sensor.second - dist_sensor_to_beacon <= row_to_check || sp.sensor.second + dist_sensor_to_beacon >= row_to_check)
            {
                int x_range = dist_sensor_to_beacon - abs(sp.sensor.second - row_to_check);
                if (x_range > 0)
                {
                    range range_on_x(sp.sensor.first - x_range, sp.sensor.first + x_range);
                    add_range_to_set(no_beacon_x_coord, range_on_x);

                    // check beacon on x axis
                    if (sp.beacon.second == row_to_check)
                    {

                        beacon_x_coord.insert(sp.beacon.first);
                    }
                }
            }
        }
        // print_x_axis(no_beacon_x_coord, beacon_x_coord);
        int no_beacon_x_coord_total_count = 0;
        for (auto range : no_beacon_x_coord)
        {
            no_beacon_x_coord_total_count += (range.end - range.start + 1);
        }
        no_beacon_x_coord_total_count -= beacon_x_coord.size();
        std::cout << "In the row where y=" << row_to_check << ", " << no_beacon_x_coord_total_count << " positions cannot contain a beacon" << std::endl;
    }

    void print_x_axis(std::set<range> &no_beacon_x_coord, std::set<int> &beacon_x_coord)
    {
        for (int x = -5; x < 30; x++)
        {
            if (beacon_x_coord.find(x) != beacon_x_coord.end())
            {
                std::cout << "B";
            }
            else if (no_beacon_x_coord.find({x, x}) != no_beacon_x_coord.end())
            {
                std::cout << "#";
            }
            else
            {
                std::cout << ".";
            }
        }
    }

    void add_range_to_set(std::set<range> &ranges, range range_to_add)
    {
        std::set<range>::iterator overlapping_range;
        while ((overlapping_range = ranges.find(range_to_add)) != ranges.end())
        {
            int new_start = overlapping_range->start < range_to_add.start ? overlapping_range->start : range_to_add.start;
            int new_end = overlapping_range->end > range_to_add.end ? overlapping_range->end : range_to_add.end;
            ranges.erase(overlapping_range);
            range_to_add = range(new_start, new_end);
        }
        ranges.insert(range_to_add);
    }

    int calculate_manhattan_distance(signal_pair &sp)
    {
        return abs(sp.beacon.first - sp.sensor.first) + abs(sp.beacon.second - sp.sensor.second);
    }

    int calculate_manhattan_distance(std::pair<int, int> pos1, std::pair<int, int> pos2)
    {
        return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
    }

    std::pair<int, int> parse_coordinate(std::string coordinate)
    {
        int comma_index = coordinate.find(",");
        int y_index = coordinate.find("y=");
        int x_index = coordinate.find("x=");
        int x = std::stoi(coordinate.substr(x_index + 2, comma_index));
        int y = std::stoi(coordinate.substr(y_index + 2));
        // std::cout << "x: " << x << " y: " << y << std::endl;
        return {x, y};
    }

    void part_two()
    {
    }
};

int main()
{

    Day_15 day;
    day.part_one();
    day.part_two();
    return 0;
}