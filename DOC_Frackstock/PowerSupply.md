# Power Supply	

ToDo:

* Alle Bauteile auf 0603





## Charging Management

Bisher:



![image-20231120153111704](C:\Users\nicol\Documents\GitHub\ET20_Frackstock\DOC_Frackstock\assets\image-20231120153111704.png)

Da der TP4056 nur ein chinesisches Datenblatt zur Verfügung stellt, wird auf eine alternative von Microchip zurückgegriffen. Ausserdem wird dann keine Battery Protection schaltung benötigt.





**Alternative **

Als Alternative könnte der MCP73871 eingesetzt werden. Dieser kann mit 500mA laden und sorgt auch nach dem Laden für ein Battery Management. (Keine Zusätzliche Power Sharing / Switch Schaltung nötig.).

![image-20231120155026589](C:\Users\nicol\Documents\GitHub\ET20_Frackstock\DOC_Frackstock\assets\image-20231120155026589.png)

**Version**

Es wird der Typ 2CC verwendet.



![image-20231120160749514](C:\Users\nicol\Documents\GitHub\ET20_Frackstock\DOC_Frackstock\assets\image-20231120160749514.png)
