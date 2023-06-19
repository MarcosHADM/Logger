//Logger.h
#ifndef Logger_h
#define Logger_h

#include <Arduino.h>

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

#define LOG(level, text, ...) \
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
        Logger(LogLevel log_level = Debug, const char* format = "{level} - {message}");

        void setLogLevel(LogLevel log_level);
        void setLogFormat(const String& format);
        void _log(LogLevel log_level, const char* file, int line, const char* function, char* buffer);

    private:

        void log_(const char* file, int line, const char* function, const char* color, const char* prefix, char* buffer);

        String getTime();
        unsigned long timestamp_ = 0;
        LogLevel log_level_;

        class Formatter {
            public:
                void setFormat(const String& format);
                String format(const std::initializer_list<std::pair<const char*, String>>& values);
            
            private:
                String format_;

        } formatter_;
};

#endif
