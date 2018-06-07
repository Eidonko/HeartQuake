/* generazione delle permutazioni con ripetizione */
/* header file perm.h */

#include <stdio.h>

typedef double real;

#define MAX_SLEN   200
#define MAX_CLASS   20
#define MAX_THRESHOLD 100000
#define THRESHOLD 30000
#define MAXDIM  1024
#define TRUE 1
#define FALSE 0


#define NORM_1_MAX FALSE
#define COLOR_LEVEL 256


/* simboli possibili */
#define ELEM0  '0'
#define ELEM1  '1'
#define ELEM2  '2'
#define ELEM3  '3'
#define ELEM4  '4'
#define ELEM5  '5'
#define ELEM6  '6'
#define ELEM7  '7'

/* definizioni extern */
extern int num_elem;     /*numero elementi da permutare  */
extern int num_class;    /*numero elementi distinti presenti nella stringa da
                           permutare       */
extern int elem_class[MAX_CLASS];  /*vettore contenente le occorrenze di
                                     ciascuna classe  */
extern real perm_number; /* numero di permutazioni */
extern int max_turns;
extern int min_turns;
extern int graphon;
extern int modulo;
extern int modx, mody;

typedef struct {
	        real block_dim;       /*numero di permutazioni da effettuare*/
	        int   avail[MAX_CLASS];  /*elementi ancora da sistemare per
                                           ciascuna classe  */
	       }status;


/* PROTOTIPI */
/*
   La routine <scan> classifica gli elementi presenti nella combinazione 
   iniziale
*/
#ifdef ANSI
int ord_elem(char);
real fatt(int);
void permuta(status,int,int *,real,int);
real num_perm(int ,int [],int );
void  sf(int []);
#else
void scan();
int ord_elem();
real fatt();
void permuta();
real num_perm();
void  sf();
#endif


extern char perm[];
