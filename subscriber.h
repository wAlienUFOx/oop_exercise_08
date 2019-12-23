#ifndef SUBSCRIBERS_H
#define SUBSCRIBERS_H
#include <fstream>

class Print {
public:
    void output(std::vector<std::shared_ptr<figures::Figure>> Vec)  {
        for (auto& figure : Vec) {
            figure->print(std::cout);
        }
    }
    ~Print() = default;
};

class Log {
public:
    void output(std::vector<std::shared_ptr<figures::Figure>> Vec)  {
        std::string filename;
        std::cout << "Input filename" << std::endl;
        std::cin >> filename;
        std::ofstream file;
        file.open(filename);
        for (auto &figure : Vec) {
            figure->print(file);
        }
    }
    ~Log() = default;
};

#endif