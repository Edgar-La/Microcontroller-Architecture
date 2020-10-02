# __Máquina de torneado__
### __RA0 = P1.0__
### __RB0 = P2:0__

* La secuencia se inicia al pulsar __"I" (RA0)__ que activa el cilindro __"V" (RB0).__
* Este en su avance empuja la pieza a tornear y acciona el sensor __"b" (RA2)__ activando el relé del motor __"M" (RB1).__
* Comienza el torneado.
* Durante el avance se alcanza el sensor __"c" (RA3)__ que desactiva el cilindro __"V" (RB0)__ iniciándose el retroceso del mismo.
* Al volver a pasar por __"b" (RA2)__, se desconecta __"M" (RB1).__
* Cuando se alcanza el final de carrera __"a" (RA1)__ se activa una señal acústica __"A" RB2)__ para que el operario retire la pieza, coloque otra nueva y, se inicie un nuevo ciclo, al pulsar __"I" (RA0).__
