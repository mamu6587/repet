##############################################################
Reseplanerare:
        Version 1.0 - 08-01-2015
Av:
        Staffan Edström
        Magnus Muhr

INFORMATION:
--------------------------------------------------------------

Reseplaneraren planerar din bussresa i Uppsala mellan
två busshållplatser efter en busslinje

BUILD:
--------------------------------------------------------------

make:
        -all           skapar körbara filen main
        -clean         städar bort alla tidigare .o-filer
        -net           skapar net.o med reseplanerarfunktioner
        -graphlib      skapar graphlib.o med graffunktioner

INSTRUKTIONER:
--------------------------------------------------------------

#Sök efter möjliga resvägar mellan två busshållplatser:
    * ./main Hållplats1 Hållplats2
    * exempel: ./main Centralstationen Cellovagen

#Planera min resa då jag kan åka tidigast given tid:
    * ./main Hållplats1 Hållplats2 leave 12:34
    * exempel: ./main Lingonvagen "Lundellska skolan" leave 13:37

#Planera min resa då jag vill vara framme innan given tid:
    * ./main 
    * ./main Hållplats1 Hållplats2 arrive 12:34
    * exempel: ./main Polacksbacken Centralstationen arrive 13:37

ÖVRIGT
--------------------------------------------------------------

Om en reseväg inte hittas så skrivs inget ut