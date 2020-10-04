# (_EN_) __Drill machine__
### __RA0 = P1.0__
### __RB0 = P2:0__
* By pressing the button __"I" (RA0)__ the spindle performs a rapid approach descent, activating the rapid descent motor __"BR" (RB3)__.
* Upon reaching the sensor __"b" (RA2)__, the relay __"M" (RB1)__ is activated, which makes the drill motor rotate and a slow descent is carried out to drill the part __"BL" (RB4)__.
* When sensor __"c" (RA3)__ is activated, the part is considered drilled.
* A rapid ascent of the spindle __"SR" (RB0)__ is started while the __"M" (RB1)__ rotation relay ___is still activated___.
* When the limit switch __"a" (RA1)__ is reached, the rapid rise __"SR" (RB0)__, the rotation relay "__M" (RB1)__ is stopped and an warning acoustic signal __"A"(RA2)__ is activated.
* The cycle begins with a new press of __"I" (RA0)__.

You can find the code [here](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Drill-machine/main.c).

Also, this is a [video](https://drive.google.com/file/d/1AZCyl04CBnwOrDfLP7QQ7QW8FxSePAnS/view?usp=sharing) showing the simulation.

# (_ES_)Máquina de taladrado
### RA0 = P1.0
### RB0 = P2:0
* Al accionar el pulsador __"I" (RA0)__ el cabezal realiza un descenso rápido de aproximación, activando el motor de bajada rápida __"BR"(RB3)__.
* Al llegar al sensor __"b" (RA2)__, se activa el relé __"M" (RB1)__ que hace girar el motor de la broca y se realiza un descenso lento para el taladrado de la pieza __"BL" (RB4)__.
* Cuando se activa el sensor __"c" (RA3)__ se considera que la pieza está taladrada.
* Se inicia una subida rápida del cabezal __"SR" (RB0)__ al tiempo que el relé __"M" (RB1)__ de giro ___sigue activado___.
* Cuando se alcanza el final de carrera __"a" (RA1)__, se detiene la subida rápida __"SR"(RB0)__, el relé de giro "__M" (RB1)__ y se activa una señal acústica __"A" (RA2)__ de aviso.
* El ciclo comienza con una nueva pulsación de __"I" (RA0)__.

Puedes encontrar el código [aquí](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Drill-machine/main.c).

También hay un [video](https://drive.google.com/file/d/1AZCyl04CBnwOrDfLP7QQ7QW8FxSePAnS/view?usp=sharing) explicando la simulación.

## (_EN_)Attached / (_ES_)Anexos
![FIG1](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Drill-machine/T_00.PNG)
![FIG2](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Drill-machine/T_03.PNG)
![FIG3](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Drill-machine/T_08.PNG)
