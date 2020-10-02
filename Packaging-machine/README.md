# Maquina de envasado
### RA0 = P1.0
### RB0 = P2.0

* Dos relés __"M1" (RB0)__ y __"M2" (RB1)__ gobiernan dos motores que arrastran dos cintas transportadoras.
* __"M1" (RB0)__ transporta piezas y __"M2" (RB1)__ embalajes.
* Un sensor __"DP" (RA1)__ detecta el paso de piezas y, otro __"DE" (RA2)__, detecta el correcto posicionamiento de un envase.
* Al detectarse el paso de 10 piezas, el envase se considera lleno, se activa una señal acústica __"A" (RB2)__ y, la cinta que transporta embalajes, se desplaza hasta situar un nuevo envase vacío.
* En este momento se desactiva la señal acústica __"A"(RB2)__ y nuevamente avanza la cinta de piezas repitiéndose así el ciclo.
* Un interruptor __"I" (RA0)__ activa o no a todo el sistema.
