# DualPrint

Small arduino helper library which subclasses the `Print` class to simulatnously print to Serial and OLED using the `Adafruit_GFX` and `Adafruit_SSD1306` library.
Serial and OLED can be turned off/on by passing boolean flags to the constructor.

```
DualPrint printer(bool use_serial, bool use_display);
```

Note: If Serial is turned on, but not connected, the library times out the serial connection after 10 seconds and then only outputs to OLED. A warning is displayed on the OLED, that Serial connection timed out.

Afterwards you can use `printer`, the same way, you use `Serial` (since both subclass `Print`), e.g.:

```
printer.println("Hello World");
```

Furthermore `DualPrint` provides the method `clear_display()`, to clear the display. 
