#include "opengl.hpp"

#ifndef __BASE_LOG_HPP
#define __BASE_LOG_HPP__

class Log
{
public:
    Log(std::string filename);
    Log(std::ostream stream);

    void info(std::string system, std::string message);
    void warning(std::string system, std::string message);
    void error(std::string system, std::string message);

private:
};

#endif
