#ifndef Q3_H
#define Q3_H
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <regex>

namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };

    inline auto func = [](const Flight&x) { return x.duration + x.connection_times + 3 * x.price; };

    typedef std::priority_queue<Flight, std::vector<Flight>,
        decltype([](const Flight&a, const Flight&b) { return func(a) > func(b); })
    > flight_queue;

    inline flight_queue gather_flights(const std::string&filename) {
        flight_queue flight;
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            throw std::runtime_error("Unable to read file.");
        }
        auto capture = [](const std::string&str, const int op) {
            // op = 1 : hour   op = 0 : minute
            size_t tot = 0;
            std::regex pat = op ? std::regex(R"((\d+)?h)") : std::regex(R"((\d+)?m)");
            std::smatch match;
            auto pos(str.cbegin());
            while (std::regex_search(pos, str.cend(), match, pat)) {
                tot += std::stoi(match[1].str());
                pos = match.suffix().first;
            }
            return tot;
        };
        std::string line;
        while (getline(ifs, line)) {
            std::regex pattern(
                R"([\d+]- flight_number:(\w+) - duration:(\w+) - connections:(\d+) - connection_times:((?:\w+,?)+) - price:(\w+))");
            std::smatch matches;
            if (!std::regex_match(line, matches, pattern)) {
                continue;
            }
            flight.push({
                matches[1],
                capture(matches[2].str(), 1) * 60 + capture(matches[2].str(), 0),
                std::stoul(matches[3].str()),
                capture(matches[4].str(), 1) * 60 + capture(matches[4].str(), 0),
                std::stoul(matches[5].str())
            });
        }
        return flight;
    }
}

#endif //Q3_H
