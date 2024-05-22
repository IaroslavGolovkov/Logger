#ifndef LOGGER_H
#define LOGGER_H

#include <mutex>
#include <string>
#include <fstream>

class Logger{
public:
    static Logger& instance() {
        static Logger ret;
        return ret;
    }
    void write(const std::string& s) {
        std::lock_guard<std::mutex> lock(m_mut);
        m_file.open("log.txt", std::ios_base::app | std::ios_base::out);
        if(m_file.is_open()) {
            m_file << s << std::endl;
            m_file.close();
        }
    }
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator =(const Logger&) = delete;
    Logger& operator =(Logger&&) = delete;
private:
    Logger() {}
    std::mutex m_mut;
    std::ofstream m_file;
};

Logger& logger = Logger::instance();

#endif // LOGGER_H