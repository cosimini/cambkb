# Yet another split keyboard with low profile Gateron switches

**Important note: tested, it works**
Now the hard part, try getting used to it.

Basically a replica of any other split keyboard project you can find on github
* Pro micro controller
* Gateron low profile KS-33 switches with hot-swap sockets
* No OLED screen, LEDs or other shiny stuff

The main difference in the layout is that the positions of the thumb-keys is moved to the center with respect to more famous keyboards like the Lily58, more like the Voyager.
Vertical stagging of about 1/4 of a key size is applied in the vertical direction, between columns.
The distance between switches is 19mm and not 19.05mm like many other, I don't care it's not 3/4 of an inch.

The PCB is designed using KiCad. It is the same for both right and left side, depending on where components are soldered.
There's no 3D printed case or key support mask, but I'd like to implement it.

The reason for the double socket for the controller is that I was usure on which side I'd like to put the controller.

For the time being I'm not planning to implement QMK or similar things, key map is hardcoded in the code.
The code is based on the Arduino library because I'm lazy. For the same reason I'm using PlatformIO.

For the used switches and controller lib/footprint, credit to [foostan/kdb](https://github.com/foostan/kbd/tree/main).

# Pictures of the result
![2024-06-16-17-23-48-641_1](https://github.com/cosimini/cambkb/assets/62906444/ec2ab020-c1a1-40b0-9ac5-2ad97fab3e9b)
![2024-06-16-17-22-16-511_1](https://github.com/cosimini/cambkb/assets/62906444/fa82e1bc-4dc1-4705-ae86-45e039a12837)
![2024-06-16-17-20-41-814_1](https://github.com/cosimini/cambkb/assets/62906444/ce6cdbbb-3ab2-4c71-b18e-c91bc6841e46)
![2024-06-16-17-21-01-321_1](https://github.com/cosimini/cambkb/assets/62906444/29d4baf3-8957-483d-917b-7c76c966f15b)
