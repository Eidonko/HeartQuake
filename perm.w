% Permutations with repetitions, by Eidon (eidon at tutanota.com)

\nocon % omit table of contents
%\datethis % print date on listing
\def\overlinedR{\hbox{$\overline R$}}
\def\cardA{\hbox{card${}_{A}$}}
\def\cardM{\hbox{card${}_{M}$}}
\def\multisetM{\hbox{$M$}}
\def\pl{\hbox{Head${}_{\eightrm left}$}}
\def\pr{\hbox{Head${}_{\eightrm right}$}}
\def\Left{\hbox{the leftmost symbol of permutation $\multisetM$ i.e., $v$}}
\def\pprime{\hbox{$p'$}}

@f overlinedR TeX
@f cardA      TeX	
@f cardM      TeX	
@f multisetM  TeX	
@f pl         TeX
@f pr         TeX
@f Left       TeX
@f pprime     TeX

@* Permutations of a Multiset.
Here it is presented the C language function
for generating the successor of a given permutation according
to the algorithm discussed in \S2.
The multiset to be permuted is |M|. Function |successor()|
gets permutation $p$ and produces $p'$. Alphabet
|A| is normalized into the set of the first $m$ integer numbers.

@c

@<prologo@>@/
@<global variables@>@/
@<successor permutation function@>@/
@<initialization and normalization@>@/



@ Starting section: headers, constants, and global variables.
In particular it is defined constant |EOP| (which stands for 
``\.{End Of Permutations}''), constant |MAX_MULTISET_CARD|,
an upper threshold for $n=\cardM$, and costant 
|MAX_ALPHABET_CARD|, an upper threshold for $m=\cardA$.

@d EOP        NULL
@d MAX_MULTISET_CARD   100
@d MAX_ALPHABET_CARD   10
@<prologo@>=

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

@ A little set of global variables so to minimize the parameter
exchange in function calls.
|M| is the string to be permuted, whose length is |cardM| byte (up to
|MAX_MULTISET_CARD|). |overlinedR| counts the occurences of each digit, so
it disposes of |cardA| cells. The |offset| variable is used to normalize
back and forth the permuted string.

@<global variables@>=
char M[MAX_MULTISET_CARD];	/* multiset $M$ */
int  cardM;			/* $n$ i.e., its cardinality */
unsigned char *overlinedR;	/* multisubset $\overline R$ */
int cardA;	/* $m$, or the number of different symbols in Alphabet $A$ */

int offset;	/* ascii($a_1$), used for normalizing $M$ to $[0,\dots m-1]$ */
char verbose=0;

void printv(char*);
void fprintv(FILE*, char*);
void err(char*);


@* The successor operator.
Some sort of a Turing machine with two contiguous heads,
|pl| and |pr|, initially positioned on the last two characters
on the right end of the permutation.
They move leftward looking for a couple which is {\it not\/}
an inversion i.e. |*pl| is less than |*pr|. As they travel
across the string, |overlinedR| records the occurrences
of encountered characters. 
If a non-inversion is found,
$a_i$ stands below |pl|. It is substituted by the minimum
$a_k$ in |overlinedR| which is greater than $a_i$.
Then |overlinedR| is linearly scanned producing a zero
permutation of $\overline R$.
If all couples are inversions the string is decreasingly ordered
i.e., is a $p_{\infty}$ in which case |successor()| returns |EOP|.

@d Left v

@<successor...@>=
char* successor(char *v, int len)
{
  char *pl, *pr;
  int i, j, k;

  pl = &v[len-2], pr = &v[len-1]; /* move the head on the right end of |v| */
  bzero((char*)overlinedR, cardA); /*  $R\leftarrow\emptyset$ */

  @<inspect the permutation right-to-left looking for a non-inversion in $a_i$@>@;


  if (pr==Left)    /* no inversion means $p=p_{\infty}$, so $p'=\Lambda$ */
	return EOP;


  overlinedR[*pl]++; 		/* $R\cup\{a_i\}$ */

  @<looks for a $k$ which is the minimum $j$ such that $a_j>a_i$@>@;

  overlinedR[k]--;    /* $\{a_i\}\cup {\cal C}_R\{a_k\}$ */
  *pl++    = k;		/* $a_i \leftarrow a_k$ */

  @<builds $p_0^{\overline R}$@>@;

  return v;
}





@ Move the heads up to a couple (|pl|,|pr|) such that |*pl < *pr|
or the left end of the permutation.
Vector |overlinedR[]| counts the occurences of visited symbols.

@<inspect...@>=
while (pr != Left)
  {
    overlinedR[*pr]++;	  /* add the symbol to $\overline R$ */

    /* if (*pl-- < *pr--) break; /* shift to left both |pr| and |pl| */

    if (*pl < *pr) break;
    pr = pl--;
  }



@ if (|*pl|,|*pr|) is {\it not\/} an inversion then we need
to substitute |pl| (i.e., $a_i$) with the minimum of its
majorants.

@<looks for...@>=
for (k = *pl + 1; k<cardM; k++)
   if (overlinedR[k]) break;



@ Closings: we substituted $a_k$ for $a_i$ and now we
build an ordered postfix string i.e., a zero for $\overline R$.
This is made easy because we dispose of |overlinedR| which
orderly counts the occurrence of the symbols in $\overline R$.

@<builds...@>=
for (i=0; i<cardA; i++)
  for (j=0; j<overlinedR[i]; j++)
    *pl++ = i;


@ Prints a permutations and computes $\nu(p)$.
@c
long ptol (char *v, long *ret, long *dis) {
int i;
long l;
static long old_l;
static long ord;

  *dis=0;
  for (l=0L, i=0; i<cardM; i++)
	l = l * cardA + v[i];
  if(old_l)  *dis = l - old_l;
  *ret  = old_l = l;
  return ++ord;
}

void Dump(char* overlinedR) { int i;
printf("overlinedR=");
for (i = 0; i<cardM; i++)
   printf("%1d", overlinedR[i]);
printf("\n");
}

@ Initialization: the permutation is normalized, its length is
computed in |*sl|.

@<initial...@>=
 int initialize(char *s, int *sl, int *cl, int *offset)
{
  int min, max;
  int i;
  char *p=s;
  char c;

  *sl = strlen(s);

  min=255, max=0;	
  while (c = *p++)
    {
      if (c<min) min = c;
      if (c>max) max = c;
    }
  
  *offset = min;	/* offset will be used by |printv()| */

  *cl = max - min + 1;	/* \cardA, or the number of classes */

  overlinedR = (unsigned char *)malloc(*cl);

  /* normalization in 0..max-min */
  for (i=0; i < *sl; i++)
    s[i] -= min;

  return 0;
}

@ error print procedure
@c
void err(char *s) 
{
 fprintf(stderr, "Error condition is \"%s\" - stop.\n", s);
 fprintf(stderr, "Usage: perm perm0 [ perm1 ] [ perm2 ] [...]\n");
 exit(-1);
}


/* END OF FILE PERM.W */
