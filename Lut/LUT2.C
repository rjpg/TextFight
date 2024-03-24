#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>

/*--------------------struct de cor e cractere-------------*/

typedef
 struct
 {
 char pixel;
 int cor;
 }ola;


/*--------------------variaveis globais---------------------*/

FILE *f;
ola monit[40][25];
int x=5,y=10,x2=24,y2=10,side1=1,side2=0,mov2=4,mov1=5,b1=0,b2=0;
int apa1=0,apa2=0,punts1=0,punts2=0;
int corb,xprog=1;

/*------por na matriz do minitor un caractere com uma cor----*/

void monitor (int x,int y,char s,int cor)
{
  monit [x][y].pixel = s;
  monit [x][y].cor =cor;
}

/*-----------retira do ecra um caractere---------------------- 

int echar(int x,int y)
{
return chr(mem[&b800:(y*160)+(x*2)]);
}

  -------------------por a matriz no ecra----------------------*/

void monitp (void)
{
  int x,y;
 for (y=1;y!=21; y++)
 for (x=1;x!= 41 ;x++)
  /*{if (monit[x][y].pixel != ' ')*/
  {textbackground(corb); textcolor(monit [x][y].cor); gotoxy (x,y) ; putch(monit [x][y].pixel);}
  /*}*/
}

/*-----------------limpa a matriz associada ao nomitor---------*/

void monitcl (int t)
{
int x,y;

 if (t==1)
  {
   for (x=0;x!= 40 ;x++)
   for (y=0;y!=25; y++)
   {monit[x][y].cor=corb;monit [x][y].pixel=' ';}
  }
  else
  {
   for (x=0;x!= 40 ;x++)
   for (y=0;y!=21; y++)
   monit [x][y].pixel=' ';
   }
}


/*-----------------limpa apenas um boneco na matriz ---------------*/

void lutlimp(int player)
{
int l,h;

for (l=1 ; l != 12 ; l++)
    for (h=0 ;h!=10;h++)
       if (player==1) monitor(x+h,y+l,' ',0);else  monitor(x2+h,y2+l,' ',0);
}


/*-----------------------procedimento pontape---------------------*/

int  punt (int play,int framec,int cor,int lado)
{
int resu=0;
	char *s;
	int l,h;

	if (lado == 1)
	 { if (!(f=fopen ("lut1p.txt","r")))  printf (" not open ");}
	else
	 {if (!(f=fopen ("lut2p.txt","r")))  printf (" not open ");}




       if (framec == 1 || framec == 5)
	{
	for (l=1 ; l != 12 ; l++)
		{
		fgets (s,13,f);
		for (h=0 ;h!=12;h++)
			{
			if (isspace(*s)) ;else
			if (play==1) monitor(x+h,y+l,*s,cor);
			else monitor(x2+h,y2+l,*s,cor);
			s++;
			}

		}
	}

      else
	{
	for (l=1 ; l != 12 ; l++) fgets (s,13,f);
	for (l=1 ; l != 12 ; l++)
		{
		fgets (s,13,f);
		for (h=0 ;h!=12;h++)
			{
			if (isspace(*s)) ;else  if (play==1) monitor(x+h,y+l,*s,cor);else monitor(x2+h,y2+l,*s,cor);
			s++;
			if (play == 1)
			if (b2>=0 && y2>5)
			if ((x-x2)<=3 && (x-x2)>=-3) {apa2=2;resu=1;} else resu=0;
			if (play ==2)
			if (b1>=0 && y>5)
			if ((x-x2)<=3 && (x-x2)>=-3) {apa1=2;resu=1;} else resu=0;

			}

		}
	}



fclose (f);

return resu;

}

/*-----------------------------faz o chao----------------------------*/

void baixo(void)
{
int xi,yi;
for (xi=1;xi!=41;xi++)
 for (yi=1;yi!=25;yi++)
    {textcolor(6);gotoxy (xi,yi);cprintf ("Û");}
}

/*-------------------------------inverte uma string-----------------*/
char *inverte (char *linha)
{
char *h;
int x,j=0;
for (x=12;x==0;x--)
 { h[j]=linha[x];j++; }
return h;
}

/*-------------------activado quan o boneco perde energia-------------*/


void apa (int x,int y,int lado,int cor)
{
char *s;
int l,h;
 if (lado == 1)
 { if (!(f=fopen ("lut1a.txt","r")))  printf (" not open ");}
 else
  {if (!(f=fopen ("lut2a.txt","r")))  printf (" not open ");}


for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,y+l,*s,cor);
    s++;
    }

  }

fclose (f);
if (punts1>0) {b1=punts1;punts1=0;}
if (punts2>0) {b2=punts2;punts2=0;}

}

/*---------faz o pontape no salto e retorna o valor a retira na energia------*/

int punts (int lado,int framec,int cor,int play)
{
char *s;
int l,h,resu=0;
 if (lado == 1)
 { if (!(f=fopen ("lut1ps.txt","r")))  printf (" not open ");}
 else
  {if (!(f=fopen ("lut2ps.txt","r")))  printf (" not open ");}


if (play == 1)
{
if (framec>10) y--; else y++;
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,(y+l),*s,cor);
    s++;
    }

  }
}
else
{
if (framec>10) y2--; else y2++;
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x2+h,(y2+l),*s,cor);
    s++;
    }

  }

}

fclose (f);
if (play == 1)
if (y-y2<=5 && y-y2>=-5)
if ((x-x2)<=4 && (x-x2)>=-4) {apa2=2;resu=1;} else resu=0;
if (play ==2)
if (y-y2<=5 && y-y2>=-5)
if ((x-x2)<=4 && (x-x2)>=-4) {apa1=2;resu=1;} else resu=0;
return resu;
}



/*---------------------------por lutador no ecra------------------*/

void lutador (int x,int y,int lado,int framec,int cor)
{
char *s;
int l,h;
 if (lado == 1)
 { if (!(f=fopen ("lut1.txt","r")))  printf (" not open ");}
 else
  {if (!(f=fopen ("lut2.txt","r")))  printf (" not open ");}
if (framec < 5)
{
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,y+l,*s,cor);
    s++;
    }

  }
}
else
{
for (l=1 ; l != 12 ; l++) fgets (s,13,f);
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,y+l,*s,cor);
    s++;
    }

  }
}
fclose (f);
}

/*---------------------faz a bara de energia---------------------*/

void vida(int t1,int t2)
{
int i;
if (t1>2 )
for (i=t1/3;  i!=1 ;i--) {monit [i][1].pixel = 'ß';monit [i][1].cor=4;}
if (t2 >2)
for (i=39;  i!=40-(t2/3) ;i--) {monit [i][1].pixel = 'ß';monit [i][1].cor=4;}

monit[19][1].pixel='K';
monit[19][1].cor=15;
monit[20][1].pixel='.';
monit[20][1].cor=15;
monit[21][1].pixel='O';
monit[21][1].cor=15;
monit[2][2].cor=14;
monit[39][2].cor=1;
monit[2][2].pixel='';
monit[39][2].pixel='';
}


/*------------------------faz o lutador saltar--------------*/

void lutadors (int lado,int framec,int cor,int play)
{
char *s;
int l,h;
 if (lado == 1)
 { if (!(f=fopen ("lut1.txt","r")))  printf (" not open ");}
 else
  {if (!(f=fopen ("lut2.txt","r")))  printf (" not open ");}


if (play == 1)
{
if (framec>10) y--; else y++;
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,(y+l),*s,cor);
    s++;
    }

  }
}
else
{
if (framec>10) y2--; else y2++;
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x2+h,(y2+l),*s,cor);
    s++;
    }

  }

}

fclose (f);
}


/*----------------------faz o lutador baixar-------------------*/

void lutadorb (int x,int y,int lado,int framec,int cor)
{
char *s;
int l,h;
 if (lado == 1)
 { if (!(f=fopen ("lut1b.txt","r")))  printf (" not open ");}
 else
  {if (!(f=fopen ("lut2b.txt","r")))  printf (" not open ");}
if (framec < 5)
{
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,y+l,*s,cor);
    s++;
    }

  }
}
else
{
for (l=1 ; l != 12 ; l++) fgets (s,13,f);
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,y+l,*s,cor);
    s++;
    }

  }
}
fclose (f);
}



/*  MAIN */

int main(void)
{

/*   int x=24,y=10,x2=5,y2=10,side1=0,side2=1,mov2=4,mov1=5,b1=0,b2=0;*/
   int vida1=57,vida2=57,punt1=0,punt2=0,soco1=0,soco2=0;
   int ch;
   /*textmode(BW80);*/
   /*graph256 ();*/
   corb=0;
   clrscr();
   monitcl (1);
   baixo();
   lutador (x,y,side1,mov1,14);
   lutador (x2,y2,side2,mov2,1);
   monitp ();
   while (ch != 27)
      {
	while (!kbhit())
	{
	      /*	gotoxy (1,23);
		printf ("%d-\n",x-(x2));
		printf ("%d-",x2-x);  */
		if (mov1<10) mov1++; else mov1=0;
		if (mov2<10) mov2++; else mov2=0;
		monitcl (1);
		vida (vida1,vida2);

   if (apa1>0) {apa(x,y,side1,14);apa1--;}
	 else
	 {
	  if (punts1>0) {vida2=vida2-punts(side1,punts1,14,1);punts1--;}
		else
		{
			if (punt1!=0) { vida2=vida2-punt(1,punt1,14,side1);punt1--; }
			else
			{
			if (b1!=0 )
				if (b1<0)
					{lutadorb (x,y,side1,mov1,14);b1++;}
				else
					{lutadors (side1,b1,14,1);b1--;}
			else
				lutador (x,y,side1,mov1,14);
			}
		}
	 }


   if (apa2>0) {apa(x2,y2,side2,1);apa2--;}
	else
	{
	 if (punts2>0) {vida1=vida1-punts(side2,punts2,1,2);punts2--;}
		else
		{
			if (punt2!=0) { vida1=vida1-punt(2,punt2,1,side2);punt2--; }
			else
			{
			if (b2!=0 )
				if (b2<0)
					{lutadorb (x2,y2,side2,mov2,1);b2++;}
				else
					{lutadors (side2,b2,1,2);b2--;}
			else
				lutador (x2,y2,side2,mov2,1);
			}
		}
	}

  monitp ();   /* repor o ecra */
}/* fim do ciclo while */

	if (x<x2) {side1=1;side2=0;} else {side2=1; side1=0;}
	ch = getch();
	switch (ch)
		{
		case '8': if (b1<=0 && punts1<=0) b1=20; break ;
		case '5': if (b1<=0) b1=-10; break ;
		case '6': if ((x<30) && (x+1!=x2 || b2!=b1)) x++; break ;
		case '4': if ((x>0)  && (x-1!=x2 || b2!=b1)) x--; break ;
		case  0 : if (b1!=0) {punts1=b1;b1=0;} else punt1=5; break;
		case '9': soco1=3; break;
		case 'w': if (b2<=0 && punts2<=0) b2=20; break ;
		case 's': if (b2<=0) b2=-10; break ;
		case 'a': if((x2>0)  && (x!=x2-1 || b2!=b1)) x2--; break ;
		case 'd': if((x2<30) && (x!=x2+1 || b2!=b1)) x2++; break ;
		case 'i': if (b2!=0) {punts2=b2;b2=0;}else punt2=5; break;
		case 'o': soco2=3; break;
		case 'z': textmode(BW80);baixo();break;
		case 'x': textmode(C80);baixo(); break;
		case 'c': textmode(MONO);baixo();break;
		case 'v': textmode(C4350);baixo(); break;
		case 'b': textmode(C80); baixo();break;
		case 'n': textmode(C40); baixo();break;
		case 'm': textmode(BW40);baixo(); break;
		case ',': corb++; break;
		case 'l': if (xprog=1) xprog=0; else xprog=1; break;


                }

     }


 return 0;
}

/* fim */