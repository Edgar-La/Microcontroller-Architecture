# (_EN_) __Turning Machine__
### __RA0 = P1.0__
### __RB0 = P2:0__
* The sequence is started by pressing __"I" (RA0)__ which activates cylinder __"V" (RB0)__.
* This in its advance pushes the piece to be turned and activates the sensor __"b" (RA2)__ activating the motor relay __"M" (RB1).__
* Turning begins.
* During the advance, the sensor __"c" (RA3)__ is reached, which deactivates the cylinder __"V" (RB0)__, starting its retraction.
* When going through __"b" (RA2)__ again, __"M" (RB1) is disconnected.__
* When the limit switch is reached __"a" (RA1)__ an acoustic signal is activated __"A" RB2)__ for the operator to remove the part, place a new one and start a new cycle by pressing __"I" (RA0)._

You can find the code [here](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Turning-machine/main.c).

Also, this is a [video](https://drive.google.com/file/d/1AW2O7KcQvO7X0JAEUhGa8kGq3OfJqP_y/view?usp=sharing) showing the simulation.

# (_ES_) __Máquina de torneado__
### __RA0 = P1.0__
### __RB0 = P2:0__
* La secuencia se inicia al pulsar __"I" (RA0)__ que activa el cilindro __"V" (RB0).__
* Este en su avance empuja la pieza a tornear y acciona el sensor __"b" (RA2)__ activando el relé del motor __"M" (RB1).__
* Comienza el torneado.
* Durante el avance se alcanza el sensor __"c" (RA3)__ que desactiva el cilindro __"V" (RB0)__ iniciándose el retroceso del mismo.
* Al volver a pasar por __"b" (RA2)__, se desconecta __"M" (RB1).__
* Cuando se alcanza el final de carrera __"a" (RA1)__ se activa una señal acústica __"A" RB2)__ para que el operario retire la pieza, coloque otra nueva y, se inicie un nuevo ciclo, al pulsar __"I" (RA0).__

Puedes encontrar el código [aquí](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Turning-machine/main.c).

También hay un [video](https://drive.google.com/file/d/1AW2O7KcQvO7X0JAEUhGa8kGq3OfJqP_y/view?usp=sharing) explicando la simulación.

## (_EN_)Attached / (_ES_)Anexos
![FIG1](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Turning-machine/C_00.PNG)
![FIG2](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Turning-machine/C_01.PNG)
![FIG3](https://github.com/Edgar-La/Microcontroller-Architecture/blob/main/Turning-machine/C_02.PNG)
