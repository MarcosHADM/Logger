#include <Arduino.h>
#include <Logger.h>

Logger logger(Debug, "[{time}] {level} [{file}.{function}.{lineno}] {message}"); // Cria uma instância do logger com nível de log Info

void setup()
{
    Serial.begin(115200);

    Serial.println("\n");
    LOG(Debug, "This is a debug message");
    LOG(Info, "This is the number %d: %d", 3, 3);
    LOG(Warning, "Countdown: %d, %d, %d", 3, 2, 1);
    LOG(Error, "Error encountered: %s", "Value invalid");
    LOG(Critical, "This is a critical message");
}

void loop()
{
}