#include <Arduino.h>
#include <Logger.h>

Logger logger(Debug, "[{time}] {level} [{file}.{function}.{lineno}] {message}"); // Cria uma instância do logger com nível de log Info

void setup() {
    Serial.begin(115200);

    Serial.println("\nIniciando o logger...");
}

void loop() {
    log(Debug, "This is a debug message");
    log(Info, "Esse e o numero %d: %d", 3, 3);
    log(Warning, "Contagem regressiva: %d, %d, %d", 3, 2, 1);
    log(Error, "Erro encontrado: %s", "Valor invalido");
    log(Critical, "This is a critical message");

    delay(5000);
    Serial.println("\n\n");
}
