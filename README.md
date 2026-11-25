# Enable-Project-Infact_CPR

## ESP32-C6 component tests

Open this folder in VS Code with PlatformIO. Close any open Serial Monitor with **Ctrl+C**, then use **Upload**. After Upload reports success, open **Serial Monitor** with **Ctrl+Alt+S**. The project uses **COM6** and **115200 baud**. Type these single letters directly in the monitor.

| Key | Test |
| --- | --- |
| `f` | Show live force-sensor readings. This starts automatically at boot. |
| `d` | Check for a VL53L0X and print up to 20 distance readings in millimetres. |
| `b` | Pulse the active buzzer driver for 250 ms. |
| `?` | Pause the force readings and show the command list. |

Unplug USB before changing connections. Test one component at a time.

### Force sensor

Jumper ESP32 `GPIO1` to `GPIO2`. Connect the two force-sensor contacts between that shared node and `GND`. Either contact can go to ground. With the sensor on a flat surface, press and release the centre. The raw reading should fall when pressed and rise when released.

### Time-of-flight sensor

The distance code supports **VL53L0X**. Check the markings on the purple module before wiring. For a VL53L0X breakout with a `VIN` input rated for 3.3 V and I2C pins, use the mapping below. Connect each wire by the printed label on the breakout.

| Breakout pin | ESP32 pin |
| --- | --- |
| VIN | 3V3 |
| GND | GND |
| SDA | GPIO18 |
| SCL | GPIO19 |

Leave the breakout's shutdown and interrupt pins open for this test. The header should be soldered or otherwise make a secure electrical connection. Reconnect USB, press `d`, and move a flat object closer and farther at roughly 10 to 30 cm. The distances should move in the same direction as the object. If the board markings differ or the program cannot identify it, check the exact sensor model before continuing.

### Active buzzer

The SFM-27-I sounds when supplied with DC. For a basic sound test with jumpers, connect red to the ESP32's **3V3 power pin** and black to **GND** with USB unplugged. Reconnect USB briefly to test and unplug to stop. Keep the buzzer away from your ears.

For the software-controlled test, use a **3.3 V-compatible low-side transistor driver**. Connect GPIO6 to the driver's control input, share ground with the ESP32, and connect the buzzer between 3V3 and the driver's switched output. For a bare logic-level N-channel MOSFET, use a gate-to-ground pull-down, source to ground, and drain to the buzzer's black wire. Connect the buzzer's red wire to 3V3. Press `b` in Serial Monitor to trigger a short beep.
