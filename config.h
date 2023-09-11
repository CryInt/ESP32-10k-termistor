#define ONBOARD_LED 2

#define BUZZER_PIN 32

#define THERMISTOR_PIN 15

double BOARD_VOLTAGE = 3.3; // Voltage from divider
double DIVIDER_RESISTOR_VALUES = 10000; // divider resistor value

double REFERENCE_TEMPERATURE_IN_KELVIN_FOR_25 = 298.15; // Temperature in Kelvin for 25 degree Celsius
double REFERENCE_RESISTANCE_AT_25 = 10000.0; // Resistance of Thermistor at 25 degree Celsius

double MAX_AVAILABLE_ANALOG_VALUE_PIN = 4095.0;

double BETA = 3950.0; // Beta value