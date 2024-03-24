# Power Supply	

ToDo:

* Alle Bauteile auf 0603





## Charging Management

Bisher:

Da der TP4056 nur ein chinesisches Datenblatt zur Verfügung stellt, wird auf eine alternative von Microchip zurückgegriffen. Ausserdem wird dann keine Battery Protection schaltung benötigt.

![image-20231120153111704](assets/image-20231120153111704-0744366.png)



**Alternative **

Als Alternative könnte der MCP73871 eingesetzt werden. Dieser kann mit 500mA laden und sorgt auch nach dem Laden für ein Battery Management. (Keine Zusätzliche Power Sharing / Switch Schaltung nötig.).

![image-20231120155026589](assets/image-20231120155026589-0744350.png)

**Version**

Es wird der Typ 2CC verwendet. Diese Version Ladet mit einer Spannung von 4.2V

![image-20231120160749514](assets/image-20231120160749514-0744330.png)

**VPCC**

Wird nicht benötigt, Pin wird daher auf VCC gehängt.



**SEL**

Auch wenn die Schaltung mit einem USB geladen wird, wird nicht das USB-Feature genutzt. SEL somit auf High gehängt.



**Prog1**

Fast charge current set: Damit wird der maximale Ladestrom festgelegt. 
$$
I_{charge} = 1A, \qquad R_{PROG1} = \frac{1000V}{1A} = 1k \Omega
$$

**Prog2**

Wird auf High gehängt (500mA Charge)



**Prog3**

Lade-Schlussstrom: Sobald Ladestrom unter diesen festgelegten Wert fällt, wird der Ladevorgang abgeschlossen.

$I_{termination}$ aus Datenblatt der 18650 Zelle
$$
I_{termination} = 125mA, \qquad R_{PROG3} = \frac{1000V}{125mA} = 8k\Omega
$$


**THERM**

Die Batterietemperatur wird nicht aufgezeichnet, die Zelle besitzt bereits eine Temperaturschutzschaltung. Daher wird ein "normaler" 10kOhm Widerstand verwendet.



**Li-Ion Zelle**

https://www.conrad.ch/de/p/samsung-nr18650-25r-spezial-akku-18650-hochstromfaehig-hochtemperaturfaehig-flat-top-li-ion-3-6-v-2500-mah-1431335.html



* Schutz vor Temperatur, Überspannung und Kurzschluss enthalten
* 4.2 V Ladespannung
* 3.6 V Nominal
* 2500 mAh
* Charge: 1.25A, 4.20V, 125mA cut-off
* Discharge: 2.5V cut-off



*aktuelle Zelle ist von EVE, jedoch ohne Schutzschaltung*



