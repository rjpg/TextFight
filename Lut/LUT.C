#include <stdio.h>
#include <conio.h>
#include <string.h>


char monit[40][25];

void baixo(void)
{
int xi,yi;
for (xi=1;xi!=41;xi++)
 for (yi=1;yi!=25;yi++)
    {gotoxy (xi,yi);cprintf ("#");}
}

char *inverte (char *linha)
{
char *h;
int x,j=0;
for (x=12;x==0;x--)
 { h[j]=linha[x];j++; }
return h;
}

void monitp (void)
{
  int x,y;
 for (y=1;y!=21; y++)
 for (x=1;x!= 41 ;x++)
  { gotoxy (x,y) ; putch(monit [x][y]);}
}

void monitcl (int t)
{
int x,y;

 if (t==1)
  {
   for (x=0;x!= 40 ;x++)
   for (y=0;y!=25; y++)
   monit [x][y]=' ';
  }
  else
  {
   for (x=0;x!= 40 ;x++)
   for (y=0;y!=21; y++)
   monit [x][y]=' ';
   }

}

void monitor (int x,int y,char s)
{
  monit [x][y] = s;
}


void lutador (int x,int y,int lado,int framec)
{
FILE *f;
char *s;
int l,h;
 if (lado == 1)
 { if (!(f=fopen ("lut1.txt","r")))  printf (" not open ");}
 else
  {if (!(f=fopen ("lut2.txt","r")))  printf (" not open ");}
if (framec < 25)
{
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,y+l,*s);
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
    if (isspace(*s)) ;else monitor(x+h,y+l,*s);
    s++;
    }

  }
}
fclose (f);
}

void vida(int t1,int t2)
{
int i;
for (i=1;i!=t1;i++) monit [i][1] = '�';
for (i=40;i!=40-t2;i--) monit [i][1] = '�';
}

void lutadorb (int x,int y,int lado,int framec)
{
FILE *f;
char *s;
int l,h;
 if (lado == 1)
 { if (!(f=fopen ("lut1b.txt","r")))  printf (" not open ");}
 else
  {if (!(f=fopen ("lut2b.txt","r")))  printf (" not open ");}
if (framec < 25)
{
for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;else monitor(x+h,y+l,*s);
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
    if (isspace(*s)) ;else monitor(x+h,y+l,*s);
    s++;
    }

  }
}
fclose (f);
}


void lutadors (int x,int y,int lado,int framec)
{
FILE *f;
char *s;
int l,h;
 if (lado == 1)
 { if (!(f=fopen ("lut1.txt","r")))  printf (" not open ");}
 else
  {if (!(f=fopen ("lut2.txt","r")))  printf (" not open ");}


for (l=1 ; l != 12 ; l++)
  {
    fgets (s,13,f);
    for (h=0 ;h!=12;h++)
    {
    if (isspace(*s)) ;
    else
    if (framec>=10) monitor(x+h,(y+l)+(framec-20),*s);
    else monitor(x+h,(y+l)-(framec),*s);
    s++;
    }

  }


fclose (f);
}



int main(void)
{

   int x=24,y=10,x2=5,y2=10,side1=0,side2=1,mov2=40,mov1=25,b1=0,b2=0;
   int vida1=18,vida2=18;
   int ch;
   textmode(BW40);
   clrscr();
   monitcl (0);
   baixo();
   lutador (x,y,side1,mov1);
   lutador (x2,y2,side2,mov2);
   monitp ();
   while (ch != 'g')
      {
	while (!kbhit())
	{
		vida (vida1,vida2);
		if (mov1<50) mov1++; else mov1=0;
		if (mov2<50) mov2++; else mov2=0;
		monitcl (0);
		vida (vida1,vida2);


		if (b1!=0 )
			if (b1<0)
			{lutadorb (x,y,side1,mov1);b1++;}
			else
			{lutadors (x,y,side1,b1);b1--;}
		else  lutador (x,y,side1,mov1);

		if (b2!=0 )
			if (b2<0)
			{lutadorb (x2,y2,side2,mov2);b2++;}
			else
			{lutadors (x2,y2,side2,b2);b2--;}
		else  lutador (x2,y2,side2,mov2);

		monitp ();
	}
	if (x<x2) {side1=1;side2=0;} else {side2=1; side1=0;}
	ch = getch();
	switch (ch)
		{
		case '8': if (b1<=0) b1=20; break ;
		case '5': b1=-10; break ;
		case '6': if(x<30  && (x+1!=x2 || b1>0)) x++; break ;
		case '4': if(x>0   && (x-1!=x2 || b1>0)) x--; break ;
		case 'w': if (b2<=0) b2=20; break ;
		case 's': b2=-10; break ;
		case 'a': if(x2>0   && (x!=x2-1 || b2>0)) x2--; break ;
		case 'd': if(x2<30  && (x!=x2+1 || b2>0)) x2++; break ;
		}

     }


 return 0;
}

