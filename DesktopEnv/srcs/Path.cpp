#include "Path.hpp"

std::string Path::Format(const std::string& p_Path)
{
    if (p_Path.at(0) == '/')
        return std::string(p_Path);
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    return std::string(cwd) + "/" + p_Path;
}