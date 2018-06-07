/*
	sc.h

	header file di sc.c
 */

#include <stdio.h>
#include <signal.h>

typedef int int4;
typedef int int2;

struct card {
       struct card *next;
       int4         value;
       };

typedef struct card Card;

/* il tipo "Card" serve a costruire LISTE LINKATE DI values[]
   che rappresenteranno (descriveranno) il "gruzzolo" dei due
   contendenti
 */




struct player {
	 Card *top,  *bottom;
	 int   n;
	};

typedef struct player Player;

/* un "Player" e' una lista linkata leggibile in modalita'
   LIFO e FIFO, uno STATO che rappresenta la condizione in
   cui si trova il Player, e l'attuale lunghezza della lista
   linkata
 */





#define NEAL 0
#define JACK 1

/* These are the indexes of the player[] object.
 */



#define CARDNUM  200

/* the number of cards in the pack */





/* the functions in the class: */
#ifdef ANSI
int     Init(int4[]);
/*	I: values[..] O: Initializes the class	   */

int     Turn(int2,int *);
/*	I: {0,1}  O: Turns a card from a player's pack      */

int     Play(int,int4[]);
/*      O: Plays a game      */

void sc(char[],int);
void stampa_pack(char[],int,int4[]);
void push_this_match(int2);
void stop(int2, int, int4[]);
void dump(void);
void saveit(void);
#else
int Init(), Turn(), Play();
void sc(), stampa_pack(), push_this_match(), stop(), dump();
#endif

/* end of pack flag */
#define EOP  NULL
 
#define DEBUG(s)  /* fprintf(stderr, "%s", s); fflush(stderr) */
#define DEBUGFMT1(par,s1)  /* fprintf(stderr, par, s1); fflush(stderr)  */
#define DEBUGFMT2(par,s1,s2) /* fprintf(stderr, par, s1,s2); fflush(stderr) */
#define DEBUGFMT3(par,s1,s2,s3) /* fprintf(stderr, par, s1,s2,s3); fflush(stderr) */
/* EndOfHeader sc.h */

#define MAX_GAMES 100000    
/* The number of winnings for each player 
   is printed every MAX_GAMES matches*/


extern int dimx, dimy;
extern unsigned char *image;
extern unsigned char *imager;
extern unsigned char *imageg;
extern unsigned char *imageb;

extern int max_turns;
extern int min_turns;
extern int graphon, analize;
extern int drawable;
extern FILE *drawfile;

#define IMAGER(x,y)  image[x*dimx*3+y*3]
#define IMAGEG(x,y)  image[x*dimx*3+y*3+1]
#define IMAGEB(x,y)  image[x*dimx*3+y*3+2]

extern int imgidx;
extern int dimxdimy;
#define IMAGE(x,y,z) 		    \
	   { imgidx = x*dimx*3+y*3; \
	     if(imgidx < dimxdimy)    \
	       {		    \
	        image[imgidx++] = z;\
	        image[imgidx++] = z;\
	        image[imgidx] = z;  \
	       }		    \
	   }

#define COULDNT_DUMP -100

extern int threshold;
extern int cardA, cardM;
extern char M[];
/* eof sc.h */
