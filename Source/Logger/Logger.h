//
// Created by a_mod on 19.01.2019.
//

#ifndef SIMSYSCOMPILER_LOGGER_H
#define SIMSYSCOMPILER_LOGGER_H

#include <string>
#include <sstream>
#include <fstream>
#include <Singleton.h>

#define LOG (*ACC::Log::Logger::get())

namespace ACC::Log {
    enum class LogLevel{
        Warning, Error, Alert, Buffer
    };

    enum class Colour{
        Blue, Magenta, Cleared, Red
    };

    class Logger;

    class LogStream : public std::ostringstream{
    private:
        Logger& logger;
        LogLevel level;
    public:
        LogStream (Logger& logger, LogLevel level);
        ~LogStream() override;

        LogStream& operator<<(Colour colour);

    };

    class Logger : public Singleton<Logger>{
    private:
        bool isSilent = false;
        Colour colour = Colour::Cleared;
        std::string path;
        long head;
        std::ofstream file;
        void logToConsole(LogLevel level, std::string str);
        void logToFile(LogLevel level, std::string str);
    public:
        Logger();
        LogStream operator()(LogLevel level = LogLevel::Alert);
        void log(LogLevel level, std::string str);
        void loadColour(Colour colour);
        void createHeading(std::string str);
        void silence(bool b = true);
    };
}

#endif //SIMSYSCOMPILER_LOGGER_H
