#include "illini_book.hpp"

#include <fstream>
#include <queue>
#include <utility>
#include <utilities.hpp>
// Your code here!


IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream pplfile(people_fpath);
    std::ifstream rfile(relations_fpath);
    if (!pplfile.is_open() || !rfile.is_open()) {
        throw std::invalid_argument("FAILED TO OPEN THE FILE"); 
    }
    std::string line;
    while (std::getline(pplfile, line)) {
        graph_[std::stoi(line)];
    }
    while (std::getline(rfile, line)) {
        std::vector<std::string> value = utilities::Split(line, ',');
        if (value.size() == 3) {
            signed int one = std::stoi(value[0]); signed int two = std::stoi(value[1]);
            graph_[one].insert({two, value[2]});
            graph_[two].insert({one, value[2]});
            relationships_.insert(value[2]);
        }
    }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    if (!(graph_.contains(uin_1)) || !(graph_.contains(uin_2))) {
        throw std::invalid_argument("NO THIS PERSON");
    }
    if (graph_.at(uin_1).contains(uin_2)) {
        return true;
    }
    std::set<int> visited;
    return BFSnoR(uin_1, visited, uin_2);
}

bool IlliniBook::BFSnoR(const int& start_vertex, std::set<int>& visited, int target) const {  //check when I get back
    std::queue<int> queue;
    queue.push(start_vertex); 
    visited.insert(start_vertex);
    while (!queue.empty()) {
        for (const auto& person : graph_.at(queue.front())) {
            if (!visited.contains(person.first)) {
                queue.push(person.first);
                visited.insert(person.first);
                if (person.first == target) {
                    return true;
                }
            }
        }
        queue.pop();
    }
    return false;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const { 
    if (!(graph_.contains(uin_1)) || !(graph_.contains(uin_2))) {
        throw std::invalid_argument("NO THIS PERSON");
    }
    std::set<int> visited;
    return BFSwR(uin_1, visited, uin_2, relationship);
}


bool IlliniBook::BFSwR(const int& start_vertex, std::set<int>& visited, int target, const std::string &relationship) const {  //check when I get back
    std::queue<int> queue;
    queue.push(start_vertex); 
    if (graph_.at(start_vertex).contains(target) && graph_.at(start_vertex).at(target) == relationship) {
        return true;
    } 
    visited.insert(start_vertex);
    while (!queue.empty()) {
        for (const auto& person : graph_.at(queue.front())) {
            if (person.second != relationship) {
                continue;
            }
            if (!visited.contains(person.first)) {
                queue.push(person.first);
                visited.insert(person.first);
                if (person.first == target && person.second == relationship) {
                    return true;
                }
            }
            
        }
        queue.pop();
    }
    return false;
}


//==================================================================   GetRelated

int IlliniBook::GetRelated(int uin_1, int uin_2) const {    
    std::queue<std::pair<int, int>> queue;
    std::set<int> visited;
    queue.push({uin_1, 0}); 
    visited.insert(uin_1);
    while (!queue.empty()) {
        auto top = queue.front();
        queue.pop();

        if (top.first == uin_2) {
            return top.second;
        }

        for (const auto& person : graph_.at(top.first)) {
            if (visited.find(person.first) == visited.end()) {     
                queue.push(std::make_pair(person.first, top.second + 1));
                visited.insert(person.first);
            }
        }
    }
    return -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::queue<std::pair<int, int>> queue;
    std::set<int> visited;
    queue.push({uin_1, 0}); 
    visited.insert(uin_1);
    while (!queue.empty()) {
        auto top = queue.front();
        queue.pop();

        if (top.first == uin_2) {
            return top.second;
        }

        for (const auto& person : graph_.at(top.first)) {
            if (visited.find(person.first) == visited.end() && person.second == relationship) {     
                queue.push(std::make_pair(person.first, top.second + 1));
                visited.insert(person.first);
            }
        }
    }
    return -1;
}

//===================================================================   GetSteps

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {    
    std::vector<int> shortest;
    std::queue<std::pair<int, int>> queue;
    std::set<int> visited;
    queue.push({uin, 0}); 
    visited.insert(uin);
    while (!queue.empty()) {
        auto top = queue.front();
        queue.pop();

        if (top.second == n) {
            shortest.push_back(top.first);
        }

        for (const auto& person : graph_.at(top.first)) {
            if (visited.find(person.first) == visited.end()) {     // if there is no node in the set, it means it is in the next degree.
                queue.push(std::make_pair(person.first, top.second + 1));
                visited.insert(person.first);
            }
        }
    }
    return shortest;
}


//===================================================================   CountGroups

size_t IlliniBook::CountGroups() const {
    std::set<int> visited;
    size_t num = 0;
    for (const auto& person : graph_) {
        if (!visited.contains(person.first)) {
            Group1(person.first, visited, num);
        }
    }
    return num;
}

void IlliniBook::Group1(const int& start_vertex, std::set<int>& visited, size_t& num) const {
    std::queue<int> queue;
    queue.push(start_vertex);
    visited.insert(start_vertex);
    while (!queue.empty()) {
        auto front = queue.front();
        queue.pop();

        for (const auto& person : graph_.at(front)) {
            if (!visited.contains(person.first)) {
                queue.push(person.first);
                visited.insert(person.first);
            }
        }
    }
    num++;
}


size_t IlliniBook::CountGroups(const std::string &relationship) const {
    if (!(relationships_.contains(relationship))) {
        return graph_.size();
    }
    std::set<int> visited;
    size_t num = 0;
    for (const auto& person : graph_) {
        if (!visited.contains(person.first)) {
            Group23(person.first, visited, num, {relationship});
        }
    }
    if (num != 0) {
        return num;
    }
    return -1;
}

void IlliniBook::Group23(const int& start_vertex, std::set<int>& visited, size_t& num, const std::vector<std::string>& relationships) const {
    std::queue<int> queue;
    queue.push(start_vertex);
    visited.insert(start_vertex);
    while (!queue.empty()) {
        auto front = queue.front();
        queue.pop();


        for (const auto& person : graph_.at(front)) {
            for (const auto& each : relationships) {
                if (each == person.second) {
                    if ((!visited.contains(person.first))) {
                        queue.push(person.first);
                        visited.insert(person.first);
                    }
                }
            }
        }
    }
    num++;
}


size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::set<int> visited;
    size_t num = 0;
    for (const auto& person : graph_) {
        if (!visited.contains(person.first)) {
            Group23(person.first, visited, num, relationships);
        }
    }
    if (num != 0) {
        return num;
    }
    return -1;
}

