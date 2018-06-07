#define EOP NULL
#define MAX_MULTISET_CARD 100
#define MAX_ALPHABET_CARD 10
#define Left v \

/*1:*/
#line 31 "perm.w"


/*2:*/
#line 49 "perm.w"


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/*:2*/
#line 33 "perm.w"

/*3:*/
#line 62 "perm.w"

char M[MAX_MULTISET_CARD];
int cardM;
unsigned char*overlinedR;
int cardA;

int offset;
char verbose= 0;

void printv(char*);
void fprintv(FILE*,char*);
void err(char*);


/*:3*/
#line 34 "perm.w"

/*4:*/
#line 94 "perm.w"

char*successor(char*v,int len)
{
char*pl,*pr;
int i,j,k;

pl= &v[len-2],pr= &v[len-1];
bzero((char*)overlinedR,cardA);

/*5:*/
#line 130 "perm.w"

while(pr!=Left)
{
overlinedR[*pr]++;



if(*pl<*pr)break;
pr= pl--;
}



/*:5*/
#line 103 "perm.w"



if(pr==Left)
return EOP;


overlinedR[*pl]++;

/*6:*/
#line 147 "perm.w"

for(k= *pl+1;k<cardM;k++)
if(overlinedR[k])break;



/*:6*/
#line 112 "perm.w"


overlinedR[k]--;
*pl++= k;

/*7:*/
#line 158 "perm.w"

for(i= 0;i<cardA;i++)
for(j= 0;j<overlinedR[i];j++)
*pl++= i;


/*:7*/
#line 117 "perm.w"


return v;
}





/*:4*/
#line 35 "perm.w"

/*9:*/
#line 190 "perm.w"

int initialize(char*s,int*sl,int*cl,int*offset)
{
int min,max;
int i;
char*p= s;
char c;

*sl= strlen(s);

min= 255,max= 0;
while(c= *p++)
{
if(c<min)min= c;
if(c> max)max= c;
}

*offset= min;

*cl= max-min+1;

overlinedR= (unsigned char*)malloc(*cl);


for(i= 0;i<*sl;i++)
s[i]-= min;

return 0;
}

/*:9*/
#line 36 "perm.w"




/*:1*//*8:*/
#line 165 "perm.w"

long ptol(char*v,long*ret,long*dis){
int i;
long l;
static long old_l;
static long ord;

*dis= 0;
for(l= 0L,i= 0;i<cardM;i++)
l= l*cardA+v[i];
if(old_l)*dis= l-old_l;
*ret= old_l= l;
return++ord;
}

void Dump(char*overlinedR){int i;
printf("overlinedR=");
for(i= 0;i<cardM;i++)
printf("%1d",overlinedR[i]);
printf("\n");
}

/*:8*//*10:*/
#line 221 "perm.w"

void err(char*s)
{
fprintf(stderr,"Error condition is \"%s\" - stop.\n",s);
fprintf(stderr,"Usage: perm perm0 [ perm1 ] [ perm2 ] [...]\n");
exit(-1);
}


/*:10*/
