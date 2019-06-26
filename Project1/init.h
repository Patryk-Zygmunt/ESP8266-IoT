#include <string>

extern const char *CONFIG_PATH;

extern std::string WIFI_SSID;
extern std::string WIFI_PASS;
extern int WIFI_MODE;
extern uint8_t RESET_PIN; //GPIO0, flash button
extern uint8_t LED_PIN; //GPIO16, built-in led

void readStoredConfig();

boolean configPresent();

void handleReset();

void doHardReset();