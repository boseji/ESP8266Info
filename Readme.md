#ESP8266Info
-------------

## ESP8266 Module Info printing Library

<br />
There are 3 main functions that help to display info about the module on which the program is running.
It might be helpful to know what is the internal configuration of the Module like - *Flash Size*,
*Type of Flash Interface*, *MAC ID* etc.
This library is designed to work with the *Serial* library. Hence needs initialization of the *Serial* Library before with `Serial.begin(115200);`. (Note: In general for ESP8266 115200 BAUD a preferred BAUD rate.)


## Example

```arduino
#include <ESP8266Info.h>

void setup() {
  Serial.begin(115200);
  ESP8266info();  
  ESP8266info_Wifi();
}

void loop() {
  // put your main code here, to run repeatedly:

}
```

## License:
Released Under creative commons license 3.0: Attribution-ShareAlike CC BY-SA
