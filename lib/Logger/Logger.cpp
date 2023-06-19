//Logger.cpp
#include "Logger.h"

Logger::Logger(LogLevel log_level, const char* format) : log_level_(log_level){
    formatter_.setFormat(format);
};

void Logger::setLogLevel(LogLevel log_level) {
    log_level_ = log_level;
}

void Logger::setLogFormat(const String& format) {
    formatter_.setFormat(format);
}

void Logger::_log(LogLevel log_level, const char* file, int line, const char* function, char* buffer) {
    if (log_level_ > log_level) return;
    

    switch (log_level) {
        case Debug:
            log_(file, line, function, COLOR_CYAN, "DEBUG", buffer);
            break;
        case Info:
            log_(file, line, function, COLOR_GREEN, "INFO", buffer);
            break;
        case Warning:
            log_(file, line, function, COLOR_YELLOW, "WARNING", buffer);
            break;
        case Error:
            log_(file, line, function, COLOR_RED, "ERROR", buffer);
            break;
        case Critical:
            char prefix[BUFFER_SIZE];
            strcpy(prefix, COLOR_RED);
            strcat(prefix, TEXT_BOLD);
            log_(file, line, function, prefix, "CRITICAL", buffer);
            break;
    }
    
};

void Logger::log_(const char* file, int line, const char* function, const char* color, const char* prefix, char* buffer) {
    String formatted_message = formatter_.format({
        {"time", getTime()},
        {"level", prefix},
        {"file", file},
        {"function", function},
        {"lineno", String(line)},
        {"message", buffer}
    });

    size_t color_length = strlen(color);
    size_t message_length = formatted_message.length();
    size_t reset_length = strlen(RESET);
    size_t total_length = color_length + message_length + reset_length + 2;
    char output_buffer[total_length];

    memcpy(output_buffer, color, color_length);
    memcpy(output_buffer + color_length, formatted_message.c_str(), message_length);
    memcpy(output_buffer + color_length + message_length, RESET, reset_length);
    memcpy(output_buffer + color_length + message_length + reset_length, "\r\n", 2);
    Serial.write(output_buffer, total_length);
}

String Logger::getTime() {
    //TODO: fazer a função retornar a hora atual
    char buffer[20];
    time_t now = time(nullptr);
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return String(buffer);
    
}

void Logger::Formatter::setFormat(const String& format) {
    format_ = format;
}

String Logger::Formatter::format(const std::initializer_list<std::pair<const char*, String>>& values) {
    String formatted_message = format_;
    for (auto const & value : values) {
        formatted_message.replace("{" + String(value.first) + "}", value.second);
    }
    return formatted_message;
}
