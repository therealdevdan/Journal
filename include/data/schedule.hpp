#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#include <unordered_map>
#include <vector>
#include <string>

using unor_map_vec = std::unordered_map<std::string, 
    std::pair<std::string, 
    std::unordered_map<std::string, std::vector<std::string>>>>;

using unor_map_lst = std::unordered_map<std::string, 
    std::pair<std::string, 
    std::unordered_map<std::string, std::vector<std::string>>>>;

#endif
