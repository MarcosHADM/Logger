#include <Arduino.h>
#include <Logger.h>

Logger logger(Debug, "[{time}] {level} [{file}.{function}.{lineno}] {message}"); // Cria uma instância do logger com nível de log Info

/*void setup() {
    Serial.begin(115200);

    Serial.println("\n");
    LOG(Debug, "This is a debug message");
    LOG(Info, "Esse e o numero %d: %d", 3, 3);
    LOG(Warning, "Contagem regressiva: %d, %d, %d", 3, 2, 1);
    LOG(Error, "Erro encontrado: %s", "Valor invalido");
    LOG(Critical, "This is a critical message");
}

void loop() {
    

    delay(5000);
    //Serial.println("\n\n");
}
*/

double currentTemperature = 20.0; // Temperatura inicial
const double targetTemperature = 25.0;
const double heatingRate = 0.1; // Taxa de aquecimento por segundo
const double coolingRate = 0.05; // Taxa de resfriamento por segundo

void setup() {
    Serial.begin(115200);
    delay(1000);
    LOG(Info, "Sistema de controle de temperatura iniciado");
}

void loop() {
    double temperatureDifference = targetTemperature - currentTemperature;

    if (temperatureDifference > 0.0) {
        // Aquecer
        currentTemperature += heatingRate;
        LOG(Info, "Aquecedor ligado - Temperatura atual: %.1f", currentTemperature);
    } else {
        // Resfriar
        currentTemperature -= coolingRate;
        LOG(Info, "Aquecedor desligado - Temperatura atual: %.1f", currentTemperature);
    }

    delay(1000);
}