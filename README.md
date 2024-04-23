# Yet another split keyboard with low profile Gateron switches

Basically a replica of any other split keyboard project you can find on github
* Pro micro controller
* Gateron low profile KS-33 switches with hot-swap sockets
* No OLED screen, LEDs or other shiny stuff

The main difference in the layout is that the positions of the thumb-keys is moved to the center with respect to more famous keyboards like the Lily58, more like the Voyager.
Vertical stagging of about 1/4 of a key size is applied in the vertical direction, between columns.
The distance between switches is 19mm and not 19.05mm like many other, I don't care it's not 3/4 of an inch.

The PCB is designed using KiCad. It is the same for both right and left side, depending on where components are soldered.
There's no 3D printed case or key support mask, but I'd like to implement it.

For the time being I'm not planning to implement QMK or similar things, key map is hardcoded in the code.
The code is based on the Arduino library because I'm lazy. For the same reason I'm using PlatformIO.

For the used switches and controller lib/footprint, credit to [foostan/kdb](https://github.com/foostan/kbd/tree/main).

Pictures to come.
