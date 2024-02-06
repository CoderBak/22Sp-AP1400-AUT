#ifndef Q2_H
#define Q2_H
#include <vector>
#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>

namespace q2 {
    struct Patient {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    inline std::vector<Patient> read_file(const std::string&filename) {
        std::vector<Patient> patient;
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            throw std::runtime_error("Unable to read file.");
        }
        std::string line;
        getline(ifs, line);
        getline(ifs, line);
        while (getline(ifs, line)) {
            std::vector<std::string> lst;
            boost::char_delimiters_separator<char> sep(",");
            for (const auto&token: boost::tokenizer(line, sep)) {
                if (token != ",") { lst.push_back(token); }
            }
            patient.push_back({
                lst[0] + " " + lst[1],
                std::stoul(lst[2]), std::stoul(lst[3]),
                std::stoul(lst[4]), std::stoul(lst[5])
            });
        }
        return patient;
    }

    inline void sort(std::vector<Patient>&target) {
        auto func = [](const Patient&x) { return 3 * x.age + 5 * x.smokes + 2 * x.area_q + 4 * x.alkhol; };
        std::sort(target.begin(), target.end(),
                  [func](const Patient&x, const Patient&y) { return func(x) > func(y); });
    }
}

#endif //Q2_H
