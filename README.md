#Libreria per il gioco degli Scacchi

## Problemi da risolvere 

* Gli scacchi(matti) sono verificati controllando tutte le possibilità e tornando indietro -> grande utilizzo di memoria e poca efficienza
* Nullpiece è comodo, ma ha senso?
* Possibile presenza di bug, devo implementare una funzione di debug efficiente su un dataset di partite


## Futuri ampliamenti a breve termine

* Importare una posizione da FEN
* Importare una partita da PGN

## Idee per un'interfaccia grafica

* Conoco processing, ma è in java... non ho tanta voglia di convertire tutto, ci sono alternative?
** QT
** libxd


## Idee per una semplice IA

* Il computer dovrebbe saper valutare una posizione:
** Valore assoluto dei pezzi
** Valore della posizione di un pezzo
* Una IA può andare in profondità simulando tutte le possibilità e scegliendo la migliore
** Quanto a fondo può andare?
** Ha senso implementare questa parte in programmazione dinamica per risparmiare tempo?
