#include "advent_day.h"
#include <map>
#include <set>

struct valve
{
    std::string name;
    int flow_rate;
    bool is_open;
    std::map<std::string, int> valves_to_cost;
};

class Day_16 : public AdventDay
{
public:
    Day_16() : AdventDay(0) {}

    void part_one()
    {
        std::vector<std::string> valve_names;
        std::map<std::string, valve> valves_map;
        parse_input(valve_names, valves_map);

        for (auto &v : valves_map)
        {
            // add missing valve names in each valve_to_cost map
            auto &v_map = v.second.valves_to_cost;
            for (auto v_name : valve_names)
            {
                if (v_map.find(v_name) == v_map.end())
                {
                    // "infinity"
                    v_map[v_name] = 99999;
                }
            }
        }

        // "floyd warshall"
        for (int i = 0; i < valve_names.size(); i++)
        {
            for (int j = 0; j < valve_names.size(); j++)
            {
                for (int k = 0; k < valve_names.size(); k++)
                {
                    std::string i_vn = valve_names[i];
                    std::string j_vn = valve_names[j];
                    std::string k_vn = valve_names[k];
                    if (valves_map[j_vn].valves_to_cost[k_vn] > valves_map[j_vn].valves_to_cost[i_vn] + valves_map[i_vn].valves_to_cost[k_vn])
                    {
                        valves_map[j_vn].valves_to_cost[k_vn] = valves_map[j_vn].valves_to_cost[i_vn] + valves_map[i_vn].valves_to_cost[k_vn];
                    }
                }
            }
        }
        // print_cost_table(valve_names, valves_map);

        std::string current_valve = "AA";
        int total_flow = 0;
        // get_max_flow(valves_map, non_broken_valves, current_valve, total_flow, 0, 30);
        total_flow = get_max_flow_recursive(valves_map, current_valve, 0, 0, 30);
        std::cout << total_flow;
    }

    void print_cost_table(std::vector<std::string> &valve_names, std::map<std::string, valve> &valves_map)
    {
        for (auto v : valves_map)
        {
            std::cout << v.first << " -> ";
            for (auto a : v.second.valves_to_cost)
            {
                std::cout << a.first << ":" << a.second << ", ";
            }
            std::cout << std::endl;
        }
    }
    void parse_input(std::vector<std::string> &valve_names, std::map<std::string, valve> &valves)
    {
        std::vector<std::string> input = this->get_input();
        for (auto s : input)
        {
            // remove "Valve "
            s = s.substr(6);
            std::string valve_name = s.substr(0, 2);
            valves[valve_name].name = valve_name;
            valves[valve_name].valves_to_cost[valve_name] = 0;
            valve_names.push_back(valve_name);

            // remove "...flow rate="
            s = s.substr(s.find("rate=") + 5);
            int semicolon_index = s.find(";");
            int flow_rate = std::stoi(s.substr(0, semicolon_index));
            valves[valve_name].flow_rate = flow_rate;

            int valve_index = s.find("valve ");
            if (valve_index != -1)
            {
                std::string other_valve_name = s.substr(valve_index + 6);
                valves[valve_name].valves_to_cost[other_valve_name] = 1;
            }
            else
            {
                int valves_index = s.find("valves ");
                s = s.substr(valves_index + 6);

                int comma_index;
                while ((comma_index = s.find(",")) != -1)
                {
                    std::string other_valve_name = s.substr(1, comma_index - 1);
                    valves[valve_name].valves_to_cost[other_valve_name] = 1;
                    s = s.substr(comma_index + 1);
                }
                valves[valve_name].valves_to_cost[s.substr(1)] = 1;
            }
        }
    }

    void get_max_flow(std::map<std::string, valve> &valves_map, std::set<std::string> &non_broken_valves, std::string valve_from, int &totalflow, int flowrate, int minutes)
    {
        std::cout << valve_from << "->";
        if (minutes == 0)
        {
            return;
        }
        else if (non_broken_valves.size() == 0)
        {
            totalflow += (flowrate * minutes);
            return;
        }
        totalflow += flowrate;
        double max_flow_per_minute_of_distance = -INFINITY;
        std::string max_flow_per_minute_of_distance_valve = "";
        int distance_in_minutes = 0;
        for (auto v : valves_map[valve_from].valves_to_cost)
        {
            if (non_broken_valves.find(v.first) != non_broken_valves.end())
            {
                double flow_per_minute_of_distance = valves_map[v.first].flow_rate / v.second;
                if (flow_per_minute_of_distance > max_flow_per_minute_of_distance)
                {
                    max_flow_per_minute_of_distance = flow_per_minute_of_distance;
                    max_flow_per_minute_of_distance_valve = v.first;
                    distance_in_minutes = v.second;
                }
            }
        }

        // open valve
        non_broken_valves.erase(max_flow_per_minute_of_distance_valve);
        minutes--;
        totalflow += flowrate;

        flowrate += valves_map[max_flow_per_minute_of_distance_valve].flow_rate;
        totalflow += (flowrate * (distance_in_minutes - 1));
        get_max_flow(valves_map, non_broken_valves, max_flow_per_minute_of_distance_valve, totalflow, flowrate, minutes - distance_in_minutes);
        non_broken_valves.insert(max_flow_per_minute_of_distance_valve);
    }

    int get_max_flow_recursive(std::map<std::string, valve> &valves_map, std::string current_valve, int total_flow, int flowrate, int minutes)
    {
        if (minutes == 0)
        {
            return 0;
        }
        int max_flow = INT_MIN;
        bool all_valves_open = true;
        for (auto &map_entry : valves_map[current_valve].valves_to_cost)
        {
            auto valve_name = map_entry.first;
            auto path_cost = map_entry.second;
            auto &valve_object = valves_map[valve_name];
            if (valve_object.flow_rate > 0 && !valve_object.is_open && path_cost < minutes)
            {
                all_valves_open = false;
                // calculate the totalflow until the valve opens
                int new_totalflow = total_flow + ((path_cost + 1) * flowrate);

                // calculate the totalflow after valve has opened
                int new_flowrate = flowrate + valve_object.flow_rate;
                valve_object.is_open = true;
                int flow = get_max_flow_recursive(valves_map, valve_name, new_totalflow, new_flowrate, minutes - (path_cost + 1));
                valve_object.is_open = false;
                if (flow > max_flow)
                {
                    max_flow = flow;
                }
            }
        }
        if (all_valves_open)
        {
            return total_flow + (flowrate * minutes);
        }
        else
        {
            return max_flow;
        }
    }

    void part_two()
    {
    }
};

int main()
{
    Day_16 day;
    day.part_one();
    day.part_two();
    return 0;
}