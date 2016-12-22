#ifndef PATH_HPP_
#define PATH_HPP_

#include <unistd.h>
#include <string>

class Path {
    private:
        Path() {};
    public:
        static std::string Format(const std::string&);
};

#endif