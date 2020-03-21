#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#define OLED_RESET 4


class DualPrint : public Print {
  public:
    Adafruit_SSD1306 display = Adafruit_SSD1306(4);
    bool print_to_serial = false;
    bool print_to_display = false;
    long serial_timeout = 10000;

    DualPrint(bool serial, bool display);
    void init();
    void clear_display();
    size_t write(const uint8_t *buffer, size_t size);
    size_t write(uint8_t c);
};
