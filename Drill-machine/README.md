# Máquina de taladrado
### RA0 = P1.0
### RB0 = P2:0
* Al accionar el pulsador __"I" (RA0)__ el cabezal realiza un descenso rápido de aproximación, activando el motor de bajada rápida __"BR"(RB3)__.
* Al llegar al sensor __"b" (RA2)__, se activa el relé __"M" (RB1)__ que hace girar el motor de la broca y se realiza un descenso lento para el taladrado de la pieza __"BL" (RB4)__.
* Cuando se activa el sensor __"c" (RA3)__ se considera que la pieza está taladrada.
* Se inicia una subida rápida del cabezal __"SR" (RB0)__ al tiempo que el relé __"M" (RB1)__ de giro ___sigue activado___.
* Cuando se alcanza el final de carrera __"a" (RA1)__, se detiene la subida rápida __"SR"(RB0)__, el relé de giro "__M" (RB1)__ y se activa una señal acústica __"A" (RA2)__ de aviso.
* El ciclo comienza con una nueva pulsación de __"I" (RA0)__.
