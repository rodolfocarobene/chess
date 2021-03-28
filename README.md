# Libreria per il gioco degli Scacchi

## Problemi da risolvere 

* Il parsing con la promozione (l'uguale) non è implementato
* Non è possibile arrendersi nel proprio turno
* Non è considerato il tempo
* Non è possibile ruotare la scacchiera
* Gli scacchi(matti) sono verificati controllando tutte le possibilità e tornando indietro -> grande utilizzo di memoria e poca efficienza
* Nullpiece è comodo, ma ha senso?
* Errore nel conteggio delle mosse (solved)
* Non è contemplata una mossa come Nhe3 (Il secondo carattere definisce quale pezzo muovere) (solved)
* Non sono contemplate patte né per accordo né per ripetizione o mancanza di materiale (partially solved)
* Possibile presenza di bug, devo implementare una funzione di debug efficiente su un dataset di partite (done, bugs still present)
	* https://www.ficsgames.org/download.html


## Futuri ampliamenti a breve termine

* Importare una posizione da FEN
* Importare una partita da PGN
* Ruota scacchiera

## Idee per un'interfaccia grafica

* Conoco processing, ma è in java... non ho tanta voglia di convertire tutto, ci sono alternative?
	* QT
	* libxd


## Idee per una semplice IA

* Il computer dovrebbe saper valutare una posizione:
	* Valore assoluto dei pezzi
	* Valore della posizione di un pezzo
* Una IA può andare in profondità simulando tutte le possibilità e scegliendo la migliore
	* Quanto a fondo può andare?
	* Ha senso implementare questa parte in programmazione dinamica per risparmiare tempo?
