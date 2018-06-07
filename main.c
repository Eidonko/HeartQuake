#define MAIN1 main1
#define MAIN2 main2
#define MAIN3 main \

/*1:*/
#line 8 "main.w"


/*2:*/
#line 22 "main.w"



extern char M[];
extern int cardM;
extern unsigned char*overlinedR;
extern int cardA;
extern int offset;
extern char verbose;

extern void printv();
extern void fprintv();
extern void err();
long ptol(char*,long*,long*);
int save_winner(int);
char*successor(char*,int);
int initialize(char*,int*,int*,int*);
void Dump(char*);
void sc(char[],int);

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 

#include <unistd.h> 
#include "perm.h"
#include "sc.h"
#include "sf.h"



/*:2*/
#line 10 "main.w"

/*3:*/
#line 61 "main.w"



#ifndef LINDA
int MAIN1(int argc,char*argv[])
{
int i;

if(argc!=2)err("arguments");

system("mkdir RESULTS");
strcpy(M,argv[1]);

initialize(M,&cardM,&cardA,&offset);

do{
printv(M);
}while(successor(M,cardM));

return 0;
}
#endif


/*:3*/
#line 11 "main.w"

/*4:*/
#line 92 "main.w"

#ifdef LINDA

struct strobj{char s[30],sprime[30];};
typedef struct strobj obj;

int stcu(obj);

int MAIN2(int argc,char*argv[])
{
int i,status;
obj o;
int compute(obj);

system("mkdir RESULTS");
for(i= 1;i<argc-1;i++){
strcpy(o.s,argv[i]);
strcpy(o.sprime,argv[i+1]);
eval(compute(o));
}

for(i= 1;i<argc-1;i++)
in(?status);

return 0;
}

int compute(obj o)
{
char*p= o.s;
char*pprime= o.sprime;

strcpy(M,p);
initialize(M,&cardM,&cardA,&offset);
do{
;
}while(strcmp(successor(M,cardM),pprime)!=0);
return 0;
}
#endif  



/*:4*/
#line 12 "main.w"

/*5:*/
#line 137 "main.w"


struct strobj{char s[30],sprime[30];};
typedef struct strobj obj;

char*reverse(char*s){
char*q= strdup(s);
char*qq= q;
int l= strlen(s);
int i;
for(i= l-1,qq= q;i>=0;qq++,i--)
*qq= s[i];
return q;
}

int MAIN3(int argc,char*argv[])
{
int i,status,f= 0;
obj o;
int compute(obj);
int stcu(obj);
char*q;

if(argc<2)err("args");

system("mkdir RESULTS");

if(argc==2){
strcpy(o.s,argv[1]);
q= reverse(argv[1]);
strcpy(o.sprime,q);

stcu(o);
free(q);
}else{
for(i= 1;i<argc-1;i++){
f= fork();

switch(f){
case-1:err("fork failed!");
exit(-1);

case 0:
if(verbose){
fprintf(stderr,"fork %d running\n",i);
fflush(stderr);
}
strcpy(o.s,argv[i]);
strcpy(o.sprime,argv[i+1]);

stcu(o);
if(verbose){
fprintf(stderr,"child %d dies\n",i);
fflush(stderr);
}
exit(i);

default:
if(verbose){
printf("process %d (pid=%d) started.\n",i,f);
}
break;
}
}

fflush(stderr);
for(i= 1;i<argc-1;i++){int x;
if(verbose)
printf("waiting process %d...\n",i);
x= wait(&status);

if(verbose)
printf("%d(%d) is done, status = %d.\n",i,x,status);
}
}

return 0;
}

int compute(obj o)
{
char*p= o.s;
char*pprime= o.sprime;
int i;
static FILE*f;

if(f==NULL)f= fopen("output","w");
if(f==NULL)err("can't open file");

strcpy(M,p);
initialize(M,&cardM,&cardA,&offset);
#ifdef PRINT
printf("cardM=%d, cardA=%d, p=%s, pprime=%s\n",cardM,cardA,p,pprime);
#endif

for(i= 0;i<cardM;i++)pprime[i]-= offset;

do{
#ifdef PRINT
fprintv(f,M);
#endif
if(!successor(M,cardM))break;
}while(M&&memcmp(M,pprime,cardM));
#ifdef PRINT
fprintv(f,pprime);
#endif
fclose(f);
exit(1);
}











void fprintv(FILE*file,char*v){
int i;
long l,d,ord;







ord= ptol(v,&l,&d);
#  ifdef QUANTUM
if(ord%QUANTUM==0||ord%QUANTUM==1)
{
#    endif
fprintf(file,"%d\t",ord);
for(l= 0L,i= 0;i<cardM;i++)
putc(v[i]+offset,file);
#       ifdef QUANTUM
if(ord%QUANTUM==0)
#       endif
putc('\n',file);
#       ifdef QUANTUM
else
putc('\t',file);
}
#    endif
}

void printv(char*v){fprintv(stdout,v);}


int stcu(obj o)
{
char*p= o.s;
char*pprime= o.sprime;
int i;
int threshold= THRESHOLD;
#define QUANTUM 1000

strcpy(M,p);
initialize(M,&cardM,&cardA,&offset);

for(i= 0;i<cardM;i++)pprime[i]-= offset;

printf("cardM   =%d, cardA    =%d\n",cardM,cardA);
printf("%20s%10s %s\n","","mosse","permutazione");

for(i= 0;M&&memcmp(M,pprime,cardM);successor(M,cardM),i++)
{
if(i%QUANTUM==0){printf("%30d ",i);printv(M);}
sc(M,threshold);
}
printf("%30d ",i);printv(M);
if(memcmp(M,pprime,cardM)==0)sc(M,threshold);

save_winner(2);
exit(1);
}
/*:5*/
#line 13 "main.w"



/*:1*/
