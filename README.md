# UV Sensor Monitor (Arduino Project)

This project uses an UV sensor, an LCD display, and LEDs to monitor and display the UV index, providing real-time data and visual feedback through LEDs.

## Features
- **Real-time UV Index Monitoring**: Reads analog values from the UV sensor.
- **Data Display**: Displays the voltage (mV), UV index (IUV), color indication, and energy received (Joules) on a 16x3 LCD screen.
- **LED Indicators**: Lights up different LEDs based on UV levels.
- **Button Interaction**: Use the button to trigger the UV reading.

## Components Required
- **Hardware**:
  - Arduino (Uno, Mega, or compatible)
  - UV Sensor (Analog or SI1145)
  - 16x3 LCD with I2C
  - 5 LEDs (green, yellow, orange, red, purple)
  - Push button
  - Breadboard and jumper wires

- **Libraries**:
  - `Wire.h`
  - `LiquidCrystal_I2C.h`
  - `Adafruit_SI1145.h`

## Pin Configuration
| Component      | Pin   |
|----------------|-------|
| UV Sensor      | A0    |
| Button         | D2    |
| Green LED      | D3    |
| Yellow LED     | D4    |
| Orange LED     | D5    |
| Red LED        | D6    |
| Purple LED     | D7    |

## How It Works
1. **Button Trigger**: Press the button to initiate a UV reading.
2. **LCD Display**: The screen shows the following data:
   - **Voltage (mV)**: The measured voltage from the sensor.
   - **UV Index (IUV)**: The UV level based on the sensor's reading.
   - **Color**: Color corresponding to the UV index.
   - **Energy (Joules)**: Calculated energy received based on exposure time and skin area.
3. **LED Indicators**: Depending on the UV level, one of the 5 LEDs will light up:
   - **Green** for safe levels (UV index <= 2)
   - **Yellow** for moderate levels (UV index <= 5)
   - **Orange** for high levels (UV index <= 7)
   - **Red** for very high levels (UV index <= 10)
   - **Purple** for extreme levels (UV index > 10)

## Code Explanation

- **Setup**: Initializes the LCD screen and the UV sensor. Configures the button and LEDs as input/output pins.
- **Loop**: Checks if the button is pressed, reads the UV sensor value, processes it to determine the UV index, and updates the LCD and LEDs accordingly.
  
### UV Index Calculation
The sensor's voltage is read, and a UV index is calculated based on the voltage value. Depending on the UV index, the system displays the appropriate color and energy value on the screen.

### LED Color Mapping
- **Green**: Safe levels (UV index 0 - 2)
- **Yellow**: Moderate levels (UV index 3 - 5)
- **Orange**: High levels (UV index 6 - 7)
- **Red**: Very high levels (UV index 8 - 10)
- **Purple**: Extreme levels (UV index > 10)

## How to Run

1. **Install Libraries**:
   - `Adafruit_SI1145`
   - `LiquidCrystal_I2C`

2. **Connect the Components** to your Arduino according to the pin configuration mentioned above.

3. **Upload the Code** to your Arduino board.

4. **Observe the LCD and LEDs**: Press the button to take a UV reading, and view the real-time data on the LCD.

## Example Output on LCD
```
Volt: 1500 mV
IUV: 6
Cor: Vermelho
Rad: 0.105
E: 0.63
```

## Notes
- Make sure the I2C address (`0x3F`) matches your LCD module.
- You may need to adjust the UV index calculations depending on the sensor's model and calibration.
- The energy formula assumes 1 hour of exposure with 0.05 m² of skin exposed to sunlight.

## License
This project is licensed under the MIT License.
