'-- 
author: 
  - "Leonardo Scoppitto"
classoption: a4paper
date: "February 2020"
documentclass: report
fontsize: 10pt
geometry: "left=3.5cm,right=3cm,top=3cm,bottom=3cm"
output: pdf_document
title: Laboratorio di Sistemi Operativi
---
\pagebreak
\tableofcontents
\pagebreak

# Ripasso di C

## gcc

Flag di compilazione gcc:

* -o nominare output

* -c produce un file oggetto

* -Wall abilita i warning

* -pedantic conforme a ISO C89

* -Werror tutti i warning diventano error

* -g debug

* -ansi usa lo standard ANSI C(89/90)

* -I per specificare la cartella degli `#include`

* -std=c99 ISO C99 che usiamo noi. Se una funzione di libreria non fa parte di questo standard, devo dichiarare il prototipo.

## Argomenti main

La funzione `main()` ammette argomenti come qualsiasi altra funzione. Le segnature tipiche sono:

* `int main(int argc, char *argv[])`

* `int main(void)`

Le convenzioni sugli argomenti sono:

* argc è il numero di argomenti della funzione main (sempre >=1)
* argv è un array di stringhe che ha come ultima entry NULL (cioè argv[argc] == NULL) e come prima entry il nome del programma (cioè argv[0]==âmyprog")
Inoltre, se il main ritorna 0, sono felice, altrimenti significa che no è terminato con successo.

Gli elementi di argv devono essere convertiti e ci sono simpatiche funzioni come `atoi()`, `atol()` (per i long), `strtol` (consigliato, puoi specificare la base e se trova una cosa che non è un numero, ritorna 0), `sscanf()` (come scanf, ma con una stringa e non su `stdin`)

```c
#include <stdio.h>
#include <stdlib.h>
// Questi sono include file, non librerie!
```

Il comando `seq x y z` su bash crea una sequenza da x a z con passo y. `xargs` gli argomenti di un file:

```bash
seq 1 1 5 | xargs ./prog # | si chiama "pipe"
# Questo è equivalente a scrivere:
./prog 1 2 3 4 5
```

Se il secondo parametro di `strtol` è diverso da `NULL`, ma è un puntatore, salva all'interno di questo l'indirizzo di un array che contiene le entry non valide della conversione. Inoltre, la funzione salva nella variabile globale `errno` (`#include <errno.h>`) il codice di errore che può significare over/underflow o che l'elemento non è un numero.

## Struct e Union

Le strutture sono allienate a multipli della parola di memoria (4 byte per 32 bit, 8 byte per 64 bit).

```c
struct studente {
    char nome[64]; // 64 byte
    char cognome[64]; // 64 byte
    struct altreinfo {
        char *via; 
        int  nc;
        } info; // 8 + 4 (+4) byte (padding per l'allineamento)  
        int matricola; // 4 (+4) byte
}
       -------------------------------------
      |    64    |    64    | 8+4(+4) |4(+4)|
       -------------------------------------
```
## Bit Fields
Ad ogni campo di tipo `[unsigned]int` di una struttura è possibile specificare la sua ampiezza in bits, ma alcuni compilatori come gcc supportano anche `[unsigned]short` ed `[unsigned]long`. Sono usati per la gestione di maschere ed operazioni su bits. **Attenzione** all'endianess della macchina, infatti del codice che utilizza bit-fields non è portabile su differenti architetture.

## Union

Le union, a istanti diversi può avere tipo diverso e viene fatto un cast automatico.

## Allocazione

La `malloc()` non alloca in senso stretto la memoria, ma la riserva e la alloca alla prima richiesta di scrittura. La malloc ritorna `NULL` se non ho più memoria. Questa scrive sullo heap.
La `calloc()` setta tutti i byte di un array a 0, infatti prende come argomenti la dimensione dell'array e la dimensione in byte di ogni elemento.
Se faccio una `free()` su un puntatore non allocato sullo heap, scoppia tutto.
La `realloc()` prende un puntatore (se è `NULL` fa la stessa cosa della malloc) e allarga o restrige l'area di memoria che punta portandola alla dimensione specificata.


## Buone norme

Quando si usano funzioni di libreria per le stringhe, usa sempre la variante in cui si specifica la dimensione di destinazione in modo da non sovrascrivere aree di memoria non riservate a quello che stiamo facendo.

## Funzioni con numero di argomenti variabili

Sono funzioni tipo printf, in cui il numero di argomenti che vengono passati alla funzione è variabile (ma ne deve avere almeno 1) e per dichiararle si deve includere `#include <stdarg.h>`.
Per indicare un numero di argomenti variabile si utilizza `...` (ellipsis) nella definizione della funzione e l'ellipsis deve essere l'ultimo elemento.
Gli elementi fondamentali sono:

* All'interno della funzione bisogna definire una `va_list` che punta agli elementi aggiuntivi e non specificati della funzione (`va_list va;`)

* La macro `va_start` inizializza la variabile `va` per puntare al primo elemento della lista avendo specificato l'ultimo valore noto (`va_start(va, arg);`)
* La macro `va_arg` restituisce il prossimo valore della lista castandolo al tipo specificato (`va_arg(va, int);`)

* La macro `va_end` va chiamata prima dell'uscita della funzione per effettuare il cleanup (`va_end(va);`)

Esempio:
```c
#include <stdarg.h>
#include <stdio.h> // somma di più argomenti
int vasum(int count, ...){
    va_list ap;
    va_start (ap, count); // inizializzo la lista
    int sum = 0;
    for (int i=0; i<count; i++)
        sum += va_arg (ap, int); // il prossimo
    va_end (ap);  // ho finito di usare la lista
    return sum;
}
int main (){
        printf("%d\n", vasum(3, 1,2,3));
        printf("%d\n", vasum(5, 1,2,3,4,5));
        return 0;
}
```

## Core dump

Il core l'immagine della memoria nel momento del seg fault. Di default non viene fatto per motivi di sicurezza, ma è possible forzare il programma a creare un dump dando da bash

```bash
ulimit -a # mostra i limiti di memoria e vediamo core file size = 0
ulimit -c unlimited # sblocca il core dump 
```

Se rieseguo il programma con gdb, gdb mi farà  vedere che succede. Per gdb, se do il comando `up` torno all'ultima chiamata prima che il programma crashasse.

## Puntatori a funzione

```c
int somma (int x, int y){
    return x+y;
}
/* variabile di tipo funzione (int,int)->int */
int (*fun) (int,int);
int a;
fun = somma;
a = fun(3,5);
```

Si può usare per le funzioni di ordine superiore e passare la funzione come argomento di un'altra funzione (vedi il map di OCaml).

Un modo comodo di operare è definire 

```c
typedef int F_t (int);
int piu_uno (int x){
    return x+1;
}
void map (F_t f, int x[], int l){ 
     ...
}
map(piu_uno,a,3);
```

## Puntatore generico

`void*` può contenere indirizzi di variabili di tipi diversi, non si può dereferenizare ed è prima necessario effettuare a un tipo noto. Si usa per gestire il polimorfismo.

Il tipo della `malloc()` ad esempio è `void * malloc (size_t size)` e quando scrivo 

```c
int * a;
a = malloc(10*sizeof(int));
```

effetuo un cast implicito a `int*`.

Il `qsort`, ad esempio può ordinare qualsiasi cosa grazie a `void*`, infatti prende una base che casterà  quando verrà  eseguita e una funzione che comparerà  gli elementi, che a sua volta prenderà  due argomenti `void*` da castare.

```c
void qsort (void* base, size_t nmemb, size_t size, int (*compar) (void*,void*) );
```

Proprio perché il `void*` no ha un tipo, quando nella `compare` faccio `int ai = *(int*)a`, dove `a` è parametro della funzione, `(int*)` serve per castare il `void*` a `int*` e poi dereferenziare con `*`.

## Funzioni rienteranti

Una funzione si dice rientrante (*reentrant function* in Inglese) se la sua esecuzione può essere interrotta in qualsiasi punto ed essere rieseguita da dove era stata interrotta senza che questo produca effetti indesiderati (i.e. risultati scorretti o comportamento diverso rispetto allâoutput ottenuto se la funzione non viene mai interrotta). Se ho una variabile globale o statica all'interno di una funzione, molto probablilmente questa non sarà  rientrante. Avere funzioni rientranti è utile per programmi singlethreaded per fare il content switch (check async functions). Alcune funzioni di libreria non sono rientranti, bensà¬ esiste la versione rientrante segnata con `_r` (`strtok_r`, `rand_r`, ecc.).

## Thread Safe

Nei contesti multithreading, `Lock()` e `Unlock()` servono a bloccare l'esecuzione affinché il codice compreso fra quelle due funzioni venga eseguito da un solo thread e non venga eseguito altro contemporaneamente. Una funzione è thread safe se eseguendo tutti i thread insieme, si separano le variabili in modo che ogni thread dia il risultato giusto.

## Rand

`srand()` genera il seme (*seed*) che si usa per generare la sequenza (se gli passo il tempo in secondi, è casuale, altrimenti se uso unintero ottengo sempre la stessa sequenza). Il processo quindi si appoggia sull'uso di variabili globali e non è reiterante. Se mi salvo lo stato iniziale e lo passo come puntatore a `rand_r`, non uso la variabile globale. I numeri sono pseudocasuali perché a partire dallo stesso *seed* si genera sempre la stessa sequenza.

# Preprocessore

Il preprocessore viene invocato prima della compilazione vera epropria ed esegue delle manipolazioni testuali sul file per sostituire i nomi delle variabili, eliminare i commenti e cose cosà¬. Le cose contrassegnate con `#`, sono le direttive per il preprocessore. Si può vedere il risultato del programma preprocessato con `gcc -E`.
I file di include possono essere di due tipi:

```c
#include <include_file> // include_file viene cercato nelle directory standard, tipicamente /usr/include o /usr/local/include
#include "include_file" // include_file viene cercato prima nella dir locale e se non trovato nelle directory standard. Posso passare anche il PATH
```

Le macro associano un nome a un pezzo di testo, anche parametrico, che verrà  sostituito a tempo di compilazione:

```c
#define nome // Si può non specificare il testo pre if def
#define nome testo
#define nome(parametri) testo
```

Se ho definito una macro senza corpo posso scrivere:

```c
#ifdef nome
// Questa parte di codice viene compilata se nome è definito
#endif
#if bool
// Posso usare anche un booleano
#endif
#ifndef
// Si comporta in modo opposto a ifdef
#endif
``` 

Sono comodi se più file includono gli stessi header, per includerli solo una volta:

```c
#ifndef _STDIO_H
#define _STDIO_H
// Includo stdio.h la prima volta che il processore incontra _STDIO_H, dopodiché ciccia.
#endif
```

Per gli altri due modi di `#define`, nel caso di *nome testo* e *nome testo(param)*, testo verrà  <u>sostituito</u> nel codice al posto di nome, generando errori se ad esempio si invoca una cosa tipo `PRODOTTO(a+1,b)`, perché no sono state specificate le parentesi (`a+1*b`, invece che `(a+1)*b`). Per creare macro su più righe si usa `\`:

```c
#define PRODOTTO(X,Y)\
                    X,Y
```

Vediamo un esempio utile per il debug (da compilare in questo caso con `gcc -DDEBUG=1 nomefile.c`, in generale basta includere l'opzione `-Dmacroval=val` per attivare un flag o definire qualcosa in fase di compilazione):

```c
#include <stdarg.h>
#include <stdio.h>
#if defined(DEBUG) // anche #ifdef
#define dbgprintf(...) \
  dbgprintf_impl(__FILE__, __LINE__, __VA_ARGS__);
// funzione di utilità  per stampe di debugging
int dbgprintf_impl(const char *file, int line, const char* fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  fprintf(stderr, ">>>>> [%s:%d]:\n",file,line);
  vfprintf(stderr, fmt, argp);
  fprintf(stderr, "<<<<<\n");
  va_end(argp);
  return 0;
}
#else
#define dbgprintf(...)
#endif
int main () {
  dbgprintf("ciao mondo\n");
  dbgprintf("questa e' un'altra stampa in un altro punto %s %s %d\n", "ciao1", "ciao2", 3);
  return 0;
}
```


Esistono macro predefinite e macro con argomenti variabili. Cerca stringification.
Posso poi definire durante la compilazione, fare `#undef` e guarda la fine delle slide.

> Guarda stringhe suffisse e strlen di stringhe suffisse 

# Makefile

Il makefile serve a esprimere le dipendenze fra file (`.h`, `.c` e `.o`), dove i file oggetto sono i target, mentre gli altri fanno parte delle dependency list, infatti il file `.o` viene ricompilato solo se una dipendenza è cambiata.
Attento all'indentazione.

```bash
exe: f.o r.o
	gcc f.o r.o -o exe
f.o: f.c t.h r.h
	gcc -Wall -pedantic -c f.c
r.o: r.c r.h
	gcc -Wall -pedantic -c r.c
```

Make crea un albero delle dipendenze