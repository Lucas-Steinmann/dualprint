#include "dualprint.h"
#include <SenseBoxMCU.h>

DualPrint::DualPrint(bool serial, bool display)
{
  this->print_to_serial = serial;
  this->print_to_display = display;
}

void DualPrint::init()
{
  if (this->print_to_serial) {
    // First begin Serial
    Serial.begin(9600);
  }

  if (this->print_to_display) {
    senseBoxIO.powerI2C(true);
    delay(2000);
    this->display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
    this->display.display();
    delay(1000);
    this->display.clearDisplay();
    this->display.setTextSize(1);
    this->display.setTextColor(WHITE,BLACK);
  }
  
  if (this->print_to_serial) {
    // Wait till serial is finished or timed out.
    long delays = 0;
    while (!Serial)
    {
      delay(100);
      delays++;
      if (this->print_to_display && delays*100 >= this->serial_timeout)
      {
        // If timed out, break but display warning on OLED
        this->println("WARNING: Serial timed out. You can disable serial and thereby skip the delay.");
        delay(2000);
        this->clear_display();
        break;
      }
    }
  }
}

void DualPrint::clear_display()
{
  if (this->print_to_display) {
    this->display.clearDisplay();
    this->display.setCursor(0,0);
    delay(1000);
  }
}
size_t DualPrint::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  while (size--) {
    if (write(*buffer++)) n++;
    else break;
  }
  if (this->print_to_display) {
    this->display.display();
  }
  return n;
}

size_t DualPrint::write(uint8_t c) 
{
  size_t ret1, ret2;
  if (this->print_to_serial) {
    ret1 = Serial.write(c);
  }
  if (this->print_to_display) {
    ret2 = this->display.write(c);
  }
  return ret1 > ret2 ? ret1 : ret2;
}
