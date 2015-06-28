# Rainbowctl
LED strip control as a service (LEDSCAAS)

To control the LED strip, once the firmware has been flashed onto the Arduino, and the NeoPixel strip connected, send a JSON request to the arduino over it's serial interface.

| Mode code | Meaning | Implementation status |
| :-------: | ------- | :-------------------: |
| 0 | Individually set the colour of each pixel | Complete |
| 1 | Set the colour of all pixels to a specific one | Complete |
| 2 | Rainbow mode | Not implemented yet |

The format of the json request can be ascertained from the following examples:

```json
{"mode": 0, "pixel": 28, "r": 0, "g": 255, "b": 128}
```


```json
{"mode": 1, "r": 0, "g": 255, "b": 128}
```
