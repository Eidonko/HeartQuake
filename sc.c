/*
	class_sc.c

	This is the class of object which constitute the play
 */
#define EOG (-1)

#include "sc.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "perm.h"
#include "sf.h"
extern int games;

/* Neal and Jack play the game. In Win we gather the cards
   yet-to-assign to Neal or Jack
 */
Player Neal, Jack;

Card *win[CARDNUM];  /* a stack and its stack-pointer */
int   winp;
#define RESETSTACK winp=0
#define PUSH(c)    win[winp++]=c
#define TOPOFSTACK win[winp-1]
#define POP        --winp
#define EMPTYSTACK (winp==0)




/* We can refer to the players as Neal and Jack, or we can use
   player[0] and player[1], or player[NEAL] and player[JACK];
 */
Player *player[2] = { &Neal, &Jack };




/* the deck */
Card   deck[CARDNUM];


#ifdef ANSI
void sc(char values[],int threshold)
#else
void sc(values, threshold) char values[];int threshold;
#endif
{
	int x;

	games++;
        Init(values);
	x=Play(threshold,M);
        if( x>threshold)
          stampa_pack("RESULTS/not_finished_in_",threshold,values);
}




#ifdef ANSI
int Init(char values[])
#else
int Init(values) char values[];
#endif
{
	int i;
	
	/* Initialization of deck[] */
	for (i=0; i<cardM; i++)
	    {
		deck[i].value = M[i];
		deck[i].next  = deck + i + 1;
	    }

	deck[cardM/2-1].next = deck[cardM-1].next = NULL;

	/* now, (say cardM is 40),
		deck[0]  -> deck[1]  -> ... deck[19] -> NULL
	   and
		deck[20] -> deck[21] -> ... deck[39] -> NULL
	 */



	/* Initializes both Players */
	Neal.top    = deck;
	Neal.bottom = deck + cardM/2 -1;
	Neal.n      = cardM/2;

	Jack.top    = deck + cardM/2;
	Jack.bottom = deck + cardM -1;
	Jack.n      = cardM/2;

	RESETSTACK;
}



#ifdef ANSI
int Play(int threshold, char values[])
#else
int Play(threshold, values) int threshold; char values[];
#endif
{
	int2 who_turns; 
	int  turns;
	int  c=-1;
	extern int z;
    int stop_the_game(int);

/* INITFLIP initializes flipping, FLIP performs it */
#define INITFLIP who_turns = JACK, turns = -1
#define OTHER    1-who_turns
#define FLIP	 who_turns = OTHER


	turns=0;
	/* a 2-state automata! */
	INITFLIP;
F_state:
	if(turns>threshold) return turns;

	FLIP;
	if ( ! (c=Turn(who_turns,&turns)) ) goto F_state;
S_state:
	if(turns>threshold) return turns;

	FLIP;
	switch (c)
	  {
	     case EOG: 
			stop_the_game(who_turns); 
		        DEBUG("out of Play -- EOG condition found");
		        return turns;
	     case 5: 
		if (c=Turn(who_turns,&turns)) 
		      goto S_state;
	     case 4: 
		if (c=Turn(who_turns,&turns)) 
		      goto S_state;
	     case 3: 
		if (c=Turn(who_turns,&turns)) 
		      goto S_state;
	     case 2: 
		if (c=Turn(who_turns,&turns)) 
		      goto S_state;
	     case 1: 
		if (c=Turn(who_turns,&turns)) 
		      goto S_state;
	        break;
	     default:
	      printf("strange condition!default case in switch!\n");
	      printf("c=%d\n", c);
	      fflush(stdout);exit(-1);
	  }

	push_this_match(OTHER);
	goto F_state;
}




/* Turn() re-Turns ( :-) ) EOG if the current player's deck is over,
   or the card on top of the current player's deck. This results in
   a shortening of the current user's deck and in a growing for
   None's deck
 */
#ifdef ANSI
int Turn(int2 index,int *t)
#else
int Turn(index, t) int2 index; int *t;
#endif
{
	Card *c = player[index]->top;

	(*t)++;

	if (c == NULL)
		return EOG;

	if (player[index]->top == NULL)
		return EOG;

	if (player[index]->top == player[index]->bottom)
		return EOG;

	player[index]->top = player[index]->top->next;

	PUSH(c);
/*
DEBUGFMT1("out of Turn() (return=%d)\n", c->value);
*/
	dump();
	return (int) c->value;
}





/* pushes all Cards in the win stack on bottom of the winner,
   re-initializes the stack pointer
 */
#ifdef ANSI
void push_this_match(int2 winner)
#else
void push_this_match(winner) int2 winner;
#endif
{
	int i;
	Player *p = player[winner];
	int thedeck[100];

/*DEBUGFMT2("within push_this_match():%s wins %d cards\n",
		(winner?"Jack":"Neal"), winp);*/


	for (i=0; i<winp; i++)
	      {
		p->bottom->next = win[i];
		p->bottom       = win[i];
	      }
	p->bottom->next = NULL;

	RESETSTACK;
/*
DEBUG("out of push_this_match()");
*/
	dump();
}

int save_winner(int winner)
{
   FILE *f;
   static int J,N;

     if(winner!=2)
        winner?J++:N++;

  if (games % 20000 == 0 || winner==2)
   {
     f=fopen("RESULTS/winnings","w");
     if(f==NULL) { perror("can't open RESULTS/winnings"); exit(-6); }
     fprintf(f,"Jack's winnings = %d\nNeal's winnings = %d\n",J,N);
     fclose(f);
   }
}

#ifdef ANSI
int stop_the_game(int winner)
#else
int stop_the_game(winner) int winner;
#endif
{ 
   save_winner(winner);
}

#ifdef STRINGCMP
void dump()
{
	int i;
	sf_t njm[3];
	int thedeck[100];
	Card *t;
	static FILE *f;
	static int sizenjm=3*sizeof(sf_t);
#ifdef ANSI
   sf_t goedelize(int,int,int4*);
#else
   sf_t goedelize();
#endif

	if (analize)
	{
	if (f==NULL)
	    if ( (f=fopen("dump", "w")) == NULL )
		exit(COULDNT_DUMP);


	/*
	for (i=0, t=Neal.top; t!=NULL; t=t->next, i++)
	    thedeck[i] = t->value;
	njm[0] = goedelize (cardA, i, thedeck);
	for (i=0, t=Jack.top; t!=NULL; t=t->next, i++)
	    thedeck[i] = t->value;
	njm[1] = goedelize (cardA, i, thedeck);
	for (i=0; i<winp; i++)
	    thedeck[i]=win[i]->value;
	njm[2] = goedelize (cardA, i, thedeck);
 
	fwrite(njm, sizenjm, 1, f);
	*/
	for (t=Neal.top; t!=NULL; t=t->next)
	    fprintf(f, "%d", t->value);
	fprintf(f, "  ");
	for (t=Jack.top; t!=NULL; t=t->next)
	    fprintf(f, "%d", t->value);
	fprintf(f, "  ");
	for (i=0; i<winp; i++)
	    fprintf(f, "%d", win[i]->value);
	if (winp == 0)
	fprintf(f, "-");
	fprintf(f, "\n");
	}
}
#else /* NON STRINGCMP */
void dump()
{
        int i;
        sf_t njm[3];
        int thedeck[100];
        Card *t;
        static FILE *f;
        static int sizenjm=3*sizeof(sf_t);
#ifdef ANSI
   sf_t goedelize(int,int,int4*);
#else
   sf_t goedelize();
#endif

        if (analize)
        {
        if (f==NULL)
            if ( (f=fopen("dump", "w")) == NULL )
                exit(COULDNT_DUMP);
#ifndef ASCIICONF
        for (i=0, t=Neal.top; t!=NULL; t=t->next, i++)
            thedeck[i] = t->value;
        njm[0] = goedelize (cardA, i, thedeck);
        for (i=0, t=Jack.top; t!=NULL; t=t->next, i++)
            thedeck[i] = t->value;
        njm[1] = goedelize (cardA, i, thedeck);
        for (i=0; i<winp; i++)
            thedeck[i]=win[i]->value;
        njm[2] = goedelize (cardA, i, thedeck);

        fwrite(njm, sizenjm, 1, f);
#else
        for (t=Neal.top; t!=NULL; t=t->next)
            fprintf(f, "%d", t->value);
        fprintf(f, "  ");
        for (t=Jack.top; t!=NULL; t=t->next)
            fprintf(f, "%d", t->value);
        fprintf(f, "  ");
        for (i=0; i<winp; i++)
            fprintf(f, "%d", win[i]->value);
        if (winp == 0)
        fprintf(f, "-");
        fprintf(f, "\n");
#endif
        }
}
#endif /* STRINGCMP */

/********************************************************************/
#ifdef ANSI
void stampa_pack(char nome[],int sec,int4 deck[])
#else
void stampa_pack(nome, sec, deck) char nome[]; int sec; int4 deck[];
#endif
/********************************************************************/
{
  int i;
  FILE *file_ris;
  char nome_file[100];
  char char_sec[50];
  extern int offset;

  strcpy(nome_file,nome);
  sprintf(char_sec,"%d",sec);
  strcat(nome_file,char_sec);
  file_ris=fopen(nome_file,"a");
  if(file_ris==NULL) {
	perror("stampa_pack");
	exit(-6);
  }
   for (i=0;i<cardM;i++)
     fprintf(file_ris,"%c",M[i]+offset);
  fprintf(file_ris,"\n");
  fclose(file_ris);
}


/*
	interpretes a deck as a base-cardA number and converts it
	into decimal
*/
#ifdef ANSI
int base10(int cardA, int cardM, int values[])
#else
int base10(cardA, cardM, values) int cardA; int cardM; int values[];
#endif
{
  int i, res, mul;

  res=0;
  mul=1;
  for (i=cardM-1; i>=0; i--, mul *= cardA)
      {
	res += mul*values[i];
      }
  return res;
}



#ifdef ANSI
sf_t goedelize(int cardA, int cardM, int values[])
#else
sf_t goedelize(cardA, cardM, values) int cardA; int cardM; int values[];
#endif
{
  int i;
  sf_t res, mul;

  res=0.0;
  mul=1.0;
  for (i=cardM-1; i>=0; i--, mul *= (sf_t)cardA)
      {
	res += (sf_t) mul*(values[i]+1.0);
      }
  return res;
}


/* eof class_sc.c */
