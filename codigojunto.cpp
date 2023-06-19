#define BUFFER_SIZE 256             /* Tamanho do buffer de log */

#define TEXT_BOLD "\033[1m"         /* Bold on/off */
#define TEXT_UNDERLINE "\033[4m"    /* Underline on/off */
#define TEXT_BLINK "\033[5m"        /* Blink on/off */
#define TEXT_REVERSE "\033[7m"      /* Reverse on/off */

#define COLOR_BLACK "\033[30m"      /* Preto */
#define COLOR_RED "\033[31m"        /* Vermelho */
#define COLOR_GREEN "\033[32m"      /* Verde */
#define COLOR_YELLOW "\033[33m"     /* Amarelo */
#define COLOR_BLUE "\033[34m"       /* Azul */
#define COLOR_MAGENTA "\033[35m"    /* Magenta */
#define COLOR_CYAN "\033[36m"       /* Ciano */
#define COLOR_WHITE "\033[37m"      /* Branco */

#define RESET "\033[0m"             /* Reset */

#include "RTClib.h"
RTC_DS1307 rtc;

#define log(level, text, ...) \
    do { \
    char buffer[BUFFER_SIZE]; \
    std::sprintf(buffer, text, ##__VA_ARGS__); \
    logger._log(level, __FILE__, __LINE__, __FUNCTION__, buffer); \
    } while(0)

enum LogLevel {
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

class Logger {
    public:
        Logger(LogLevel log_level, const char* format) : log_level_(log_level){
            formatter_.setFormat(format);
        };

        void setLogLevel(LogLevel log_level) {
            log_level_ = log_level;
        };

        void setLogFormat(const String& format) {
            formatter_.setFormat(format);
        };

        void _log(LogLevel log_level, const char* file, int line, const char* function, char* buffer) {
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
            };
        };

    private:
        void log_(const char* file, int line, const char* function, const char* color, const char* prefix, char* buffer) {
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
        };


        String getTime() {
            DateTime now = rtc.now();
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
            return String(buffer);
        }

        unsigned long timestamp_ = 0;
        LogLevel log_level_;

        class Formatter {
            public:
                void setFormat(const String& format) {
                    format_ = format;
                };

                String format(const std::initializer_list<std::pair<const char*, String>>& values) {
                    String formatted_message = format_;
                    for (auto const & value : values) {
                        formatted_message.replace("{" + String(value.first) + "}", value.second);
                    }
                    return formatted_message;
                };
            
            private:
                String format_;

        } formatter_;
};