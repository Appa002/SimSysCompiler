//
// Created by a_mod on 19.01.2019.
//

#include "Logger.h"
#include <chrono>
#include <iostream>

const std::string htmlPreamble = R"(<!DOCTYPE html>
<html>
<head>
	<title>Log</title>
	<style type="text/css">
		#running{
			white-space: pre-wrap;
			width: 99vh;
			color: white;
			background-color: black;
			margin: 0 auto;
			font-family: 'Lucida Console', Monaco, monospace;
		}
		#heading{
			white-space: pre-wrap;
			background: #4c4c4c;
			width: 99vh;
			color: #3dff00;
			margin: 0 auto;
			text-align: center;
			font-family: 'Lucida Console', Monaco, monospace;
			font-weight: 800;
		}
	</style>
</head>
<body>
<div id="running">)";

const std::string htmlEnd = R"(</div></body></html>)";

namespace ANSI_CODES{
    const std::string magenta = "\033[34;1m";
    const std::string blue = "\033[35;1m";
    const std::string clear = "\033[0m";
    const std::string heading = "\033[32;1m";
};

ACC::Log::LogStream::LogStream(ACC::Log::Logger &logger, ACC::Log::LogLevel level) :
logger(logger), level(level){

}

ACC::Log::LogStream::~LogStream() {
    logger.log(level, str());
}

ACC::Log::LogStream &ACC::Log::LogStream::operator<<(ACC::Log::Colour colour) {
    this->logger.loadColour(colour);
    return *this;
}

ACC::Log::LogStream ACC::Log::Logger::operator()(ACC::Log::LogLevel level) {
    return LogStream(*this, level);
}

void ACC::Log::Logger::log(ACC::Log::LogLevel level, std::string str) {
    logToConsole(level, str);
    logToFile(level, str);
    colour = Colour::Cleared;
}

ACC::Log::Logger::Logger() {
    auto start = std::chrono::system_clock::now().time_since_epoch().count();
   // path = "./log_"+std::to_string(start)+".html";
    path = "./log.html";
    std::ofstream ofs;
    ofs.open(path, std::ofstream::out | std::ofstream::trunc);
    if(ofs.is_open()){
        ofs << htmlPreamble;
        ofs.close();
    }
    file = std::ofstream(path, std::ios_base::in | std::ios_base::out);
    head = htmlPreamble.size();
}

void ACC::Log::Logger::loadColour(ACC::Log::Colour colour) {
    this->colour = colour;
}

void ACC::Log::Logger::logToConsole(ACC::Log::LogLevel level, std::string str) {
    if(isSilent)
        return;
    switch (colour){
        case Colour::Blue:
            std::cout << ANSI_CODES::blue;
            break;
        case Colour::Magenta:
            std::cout << ANSI_CODES::magenta;
            break;
        case Colour::Cleared:
            std::cout << ANSI_CODES::clear;
            break;
    }
    std::cout << str;
    std::cout << ANSI_CODES::clear;
}

void ACC::Log::Logger::logToFile(ACC::Log::LogLevel level, std::string str) {
    if(!file.is_open())
        return;

    switch (colour){
        case Colour::Blue:
            str = R"(<b style="color: lightblue;">)" + str;
            str += R"(</b>)";
            break;
        case Colour::Magenta:
            str = R"(<b style="color: magenta;">)" + str;
            str += R"(</b>)";
            break;
        case Colour::Cleared:
            break;
    }

    file.seekp(head);
    file << str;
    file << htmlEnd;

    file.flush();

    head += str.size();
}

void ACC::Log::Logger::createHeading(std::string str) {
    if(!isSilent)
        std::cout << ANSI_CODES::heading << str << ANSI_CODES::clear << std::endl;
    str = R"(</div><div id="heading">)" + str + R"(</div><div id="running">)";
    file.seekp(head);
    file << str;
    file << htmlEnd;

    file.flush();

    head += str.size();

}

void ACC::Log::Logger::silence(bool b) {
    isSilent = b;
}

