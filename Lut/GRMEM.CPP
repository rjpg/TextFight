
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <mem.h>
#include <ctype.h>

const float pidiv180=(atan(1)/45);

/*------------------------Fun��es de desenho-------------------------*/
struct RGB
	{
	char R,G,B;
	};

class Dmem
	{
	private :
		float densidade, x_max,x_min,y_max,y_min;
	public:
		int maxx,maxy;
		char **mem;
		float x_center,y_center;
		Dmem (void);			 // chama Hmem(320,200)
		Dmem (int x,int y);	 // construtor aloca matriz
		void point (int x,int y,char valor); //atribui valor � matriz
		void putmem(int x,int y,char *mem,int size); //copia de mem�ria
		int IX (float x); // converte float de X em int ada ado � matriz
		int IY (float y); //    ||  	|| ||  Y  || ||	   ||	 ||	  ||
		void clear(char valor);
		~Dmem();		  // destrutor liberta matriz
	};

Dmem::Dmem(int x,int y)
{
	int i;
	if (!(mem=new char*[y])) /*//(char **) calloc (y,sizeof(char*))))*/
		exit (1);
	for(i=0;i<=y;i++)
		if (!(mem[i]=new char[x])) //(char *) calloc (x+1,sizeof(char))))
		{
			for (;i>=0;i--)
				delete[x] mem[i]; //free(mem[i]);
			delete[y] mem; //free(mem);
			exit (1);
		}
	x_max=10;
	x_min=y_min=y_max=0;

	maxx=x-1;maxy=y-1;
	densidade=maxx/(x_max-x_min);
	y_max=y_min+maxy/densidade;
	
	x_center=0.5*(x_min+x_max);
	y_center=0.5*(y_min+y_max);
	clear(0);
}

Dmem::Dmem(void)
{
	Dmem(320,200);
}

void Dmem::point(int x, int y, char valor)
{
	if (x>=0 && x<=maxx && y>=0 && y<=maxy)
		mem[maxy-y][x]=valor;
}

void Dmem::putmem(int x,int y, char *memtocp,int size)
{
	memcpy(mem+(y*maxx+x),memtocp,sizeof(char)*size);
}

int Dmem::IX (float x)
{
	return (int (densidade*(x-x_min)));
}

int Dmem::IY (float y)
{
	return (int (densidade*(y-y_min)));
}
void Dmem::clear(char valor)
{
/*	int i,j;
	for(i=0;i<=maxx;i++)
		for(j=0;j<=maxy;j++)
		    mem[j][i]=(valor+mem[j][i])/3;*/
	int i;
	for (i=0;i<=maxy;i++)
		setmem(mem[i],maxx+1,valor);   //,maxx+1

	/*setmem(mem,(maxx+1)*(maxy+1),valor);*/
}


Dmem::~Dmem ()
{
	int i;
	for (i=maxy;i>=0;i--)
			delete[maxx+1] mem[i];//free(mem[i]);
	delete [maxy+1]mem;//free(mem);

}

void linemem (int xp,int yp,int xq,int yq,Dmem &ecra,char valor)
{
	int x=xp, y=yp, d=0, dx=xq-xp,dy=yq-yp,c , m,
	xinc=1, yinc=1;
	if(dx<0){xinc=-1;dx=-dx;}
	if(dy<0){yinc=-1;dy=-dy;}
	if(dy<dx)
	{
		c=2*dx;m=2*dy;
		while (x!=xq)
		{
			ecra.point(x,y,valor);
			x+=xinc;d+=m;
			if (d>dx){y+=yinc;d-=c;}
		}
	}
	else
	{
		c=2*dy;m=2*dx;
		while (y!=yq)
		{
			ecra.point(x,y,valor);
			y+=yinc;d+=m;
			if (d>dy){x+=xinc;d-=c;}
		}
	}
}


void circlemem (int xc,int yc,int r,Dmem &ecra, char valor)
{
	int x=0,y=r, u=1, v=2*r-1, E=0;
	ecra.point(xc, yc + r, valor);
	ecra.point(xc, yc - r, valor);
	ecra.point(xc + r, yc, valor);
	ecra.point(xc - r, yc, valor);
	while (x<y)
	{
		x++; E+=u; u+=2;
		if (v<2*E) {y--;E-=v;v-=2;}
		if (x<=y)
		{
			ecra.point(xc+x, yc +y, valor);
			ecra.point(xc-x, yc +y, valor);
			ecra.point(xc+x, yc -y, valor);
			ecra.point(xc-x, yc -y, valor);
			if (x<y)
			{
				ecra.point(xc+y, yc + x, valor);
				ecra.point(xc-y, yc + x, valor);
				ecra.point(xc+y, yc - x, valor);
				ecra.point(xc-y, yc - x, valor);
			}
		}
	}
}


static void checkmem(void *p)
{
	if (p==NULL) {printf ("N�o h� mais mem�ria!!!");exit (1);}
}

void horlinemem (int x1,int x2,int y,Dmem &ecra,char valor)
{
	int i,aux1=x1,aux2=x2;
	int mx=ecra.maxx,my=ecra.maxy;

	if (aux1>aux2) {i=aux1; aux1=aux2;aux2=i;}
        if (aux2>mx) aux2=mx;
	if (aux1<0) aux1=0;
        if (aux1<=mx && y<=my && y>=0)
		setmem(ecra.mem[my-y]+aux1, aux2-aux1+2,valor);
}

void fillpolimem (int *X,int *Y,int n, Dmem &ecra, char valor)
{
	int x,y,i,ymin=1000,ymax=0, j, ny, i1,xp,yp,xq,yq,
		temp, dx,dy,m,dyq,E,xleft,xright;
	typedef struct element
	{
		int xp,yq,dx,dy,E;element *next;
	}*eltpr;
	eltpr *table, p, start, end, p0,q;
	x=X[n-1];y=Y[n-1];
	for(i=0;i<n;i++)
	{
                linemem(x,y,X[i],Y[i],ecra,valor);
		x=X[i];y=Y[i];
		if (y<ymin) ymin=y;
		if (y>ymax) ymax=y;
	}
	ny=ymax-ymin+1;
	table =new eltpr[ny];checkmem(table);
	for(j=0;j<ny;j++) table[j]=NULL;
	for (i=0; i<n ;i++)
	{
		i1=i+1;
		if (i1==n)i1=0;
		xp=X[i];yp=Y[i];
		xq=X[i1];yq=Y[i1];
		if (yp==yq) 
			continue;
		if (yq<yp)
		{
			temp=xp;xp=xq;xq=temp;
			temp=yp;yp=yq;yq=temp;
		}
		p=new element;checkmem(p);
		p->xp=xp;p->dx=xq-xp;
		p->yq=yq;p->dy=yq-yp;//VER SE ESTA CORRECTO yq
		j=yp-ymin;
		p->next = table[j];table[j]=p;
	}
		
	start=end=new element;//sentinela
	checkmem (start);
	for (j=0;j<ny;j++)
	{
		y=ymin+j;
		p=start;
		while (p!=end)
		{
			if(p->yq==y)
			{
				if ((q=p->next)==end) end=p;else *p =*q;
				delete q;
			}
			else
			{
				if ((dx=p->dx)!=0)
				{
					x=p->xp;
					dy=p->dy;
					E=p->E;
					m=dx/dy;
					dyq=2*dy;
					x+=m;E+=2*dx-m*dyq;
					if (E>dy || E< -dy)
					{
						if (dx>0)
						{
							x++;E-=dyq;
						}
						else
						{
							x--;E+=dyq;
						}
					}
					p->xp=x;
					p->E=E;
				}
				p=p->next;
			}
		}
		p=table[j];
		while (p!=NULL)
		{
			x=end->xp=p->xp;yq=p->yq;
			dx=p->dx;dy=p->dy;q=start;
			while (q->xp<x || q->xp==x && 
				q!=end && (long)q->dx*dy<(long)dx*q->dy)
				q=q->next;
			p0=p;p=p->next;
			if (q==end)end=p0;else *p0=*q;
			q->xp=x;q->yq=yq;
			q->dx=dx;q->dy=dy;
			q->E=0;q->next=p0;
		}
		for (p=start;p!=end;p=p->next)
		{
			xleft=p->xp+1;p=p->next;
			xright=p->xp-1;
			if (xleft<=xright)
			{
				horlinemem(xleft,xright,y,ecra,valor);
			}
		}
	}
	p=start;
	while (p!=end)
	{
		p0=p;p=p->next;delete p0;
	}
	delete start;
	delete[ny] table;
}


class memto
{
private:
	int xat ,yat;
	public:
		memto ();
		void moveto (int x,int y);
		void lineto (int x,int y,Dmem &ecra,char valor);
		~memto();
};

memto :: memto ()
{
	xat =0;yat=0;
}
void memto::moveto (int x,int y)
{
	xat=x;yat=y;
}
void memto ::lineto (int x,int y,Dmem &ecra,char valor)
{
	linemem(xat,yat,x,y,ecra,valor);
}

memto::~memto(){}

/*--------------------------------2d functions-------------------------------*/

struct vec
{
	float x,y;
	vec(float xx,float yy) {x=xx;y=yy;}
	vec(){x=0;y=0;}
};

vec operator+(vec &u,vec&v)
{
	return vec(u.x+v.x,u.y+v.y);
}

vec operator-(vec &u, vec &v)
{
	return vec(u.x-v.x,u.y-v.y);
}

vec &operator+=(vec &u,vec&v)
{
	u.x+=v.x;u.y+=v.y;
	return u;
}

vec &operator-=(vec &u,vec&v)
{
	u.x-=v.x;u.y-=v.y;
	return u;
}


void linememfit (vec &pontoa,vec &pontob,Dmem &ecra,char valor)
{
	int xp,yp,xq,yq;
	xp=ecra.IX(pontoa.x);
	yp=ecra.IY(pontoa.y);
	xq=ecra.IX(pontob.x);
	yq=ecra.IY(pontob.y);
	linemem(xp,yp,xq,yq,ecra,valor);
}

void circlememfit(vec &center,int r,Dmem &ecra,char valor)
{
	int x,y;
	x=ecra.IX(center.x);
	y=ecra.IY(center.y);
	circlemem(x,y,r,ecra,valor);
}

void fillpolymemfit (vec *coord,int n,Dmem &ecra,char valor)
{
	int *x,*y,i;
	if (!(x=new int[n])) //(int *) calloc (n,sizeof(int))))
		exit (1);
	if (!(y=new int[n])) //(int *) calloc (n,sizeof(int))))
		exit (1);
	for (i=0;i<n;i++)
	{
		x[i]=ecra.IX(coord[i].x);
		y[i]=ecra.IY(coord[i].y);
	}
	fillpolimem(x,y,n,ecra,valor);
	delete[n] x;//free(x);
	delete[n] y;//free(y);
}

class memtofit
{
private:
	vec at;
	public:
		memtofit ();
		void moveto (vec &a);
		void lineto (vec &b,Dmem &ecra,char valor);
		~memtofit();
};

memtofit :: memtofit ()
{
	at.x =0;at.y=0;
}
void memtofit::moveto (vec &a)
{
	at=a;
}
void memtofit ::lineto (vec &b,Dmem &ecra,char valor)
{
	linememfit(at,b,ecra,valor);
}

memtofit::~memtofit(){}

/*----------------------------------3d functions-------------------------*/
struct vec3
	{
	float x, y, z;
	vec3(double xx, double yy, double zz)
		{
		x=xx;y=yy;z=zz;
		}
	vec3 ()
		{
		x=0;
		y=0;
		z=0;
		}
	};

vec3 operator + (vec3 &u, vec3 &v)
	{
	return vec3 (u.x + v.x, u.y + v.y, u.z + v.z);
	}

vec3 operator - (vec3 &u, vec3 &v)
	{
	return vec3 (u.x - v.x, u.y - v.y, u.z - v.z);
	}

vec3 operator * (double c, vec3 &v)
	{
	return vec3 (c*v.x, c*v.y, c*v.z);
	}

vec3 &operator += (vec3 &u, vec3 &v)
	{
	u.x += v.x; u.y +=v.y; u.z+=v.z;
	return u;
	}

vec3 &operator-=(vec3 &u, vec3 &v)
	{
	u.x -= v.x; u.y -=v.y; u.z-=v.z;
	return u;
	}


vec3 &operator*=(vec3 &v, double c)
	{
	v.x *= c; v.y *= c; v.z*= c;
	return v;
	}

class cam
{
private:
	/*static*/ double v11, v12, v13, v21, v22, v23, v32, v33, v43;
public:
	float rho,theta,phi;
	vec3 target;
	float dist;
	cam();
	void camdef(double rho, double theta, double phi);
	void coeff (double rho, double theta, double phi);
	void eyecoord (vec3 &pw, vec3 &pe);
	void perspective (vec3 &p,vec &pxy);
	vec to2d (vec3 &p,Dmem &ecra);
	~cam();
};

cam::cam()
{
	rho=20;
	theta=45;
	phi=45;

	theta*=pidiv180;
	phi*=pidiv180;

	coeff(rho,theta,phi);
	dist = 8;
	target=vec3(0,0,0);
}

void cam::camdef(double rhod, double thetad, double phid)
{
	rho=rhod;
	theta=thetad;
	phi=phid;

	theta*=pidiv180;
	phi*=pidiv180;

	coeff(rho,theta,phi);

}

void cam::coeff (double rho, double theta, double phi)
	{
	double costh, sinth, cosph, sinph;
	costh = cos(theta); sinth = sin(theta);
	cosph = cos(phi); sinph = sin(phi);
	v11=-sinth; v12= -cosph*costh; v13= -sinph*costh;
	v21= costh; v22= -cosph*sinth; v23= -sinph*sinth;
		    v32= sinph;        v33= -cosph;
				       v43= rho;

	}

void cam::eyecoord (vec3 &pw, vec3 &pe)
	{
	pe.x = v11 * pw.x + v21 * pw.y;
	pe.y = v12 * pw.x + v22 * pw.y + v32 * pw.z;
	pe.z = v13 * pw.x + v23 * pw.y + v33 * pw.z + v43;
	}

void cam::perspective (vec3 &p,vec &pxy)
	{
	vec3 pe;
	eyecoord (p,pe);
	pxy.x = pe.x/pe.z;
	pxy.y = pe.y/pe.z;
	}

vec cam::to2d (vec3 &p,Dmem &ecra)
{
	vec aux,rt;
	perspective (p-target,aux);
	rt.x=dist*aux.x +ecra.x_center;
	rt.y=dist*aux.y +ecra.y_center;
	return rt;
}

cam ::~cam(){}


double dotproduct (vec3 &a, vec3 &b)
	{
	return a.x * b.x + a.y * b.y + a.z * b.z;
	}

double abs (vec3 &v)
	{
	return sqrt (v.x * v.x + v.y * v.y * v.z * v.z);
	}

vec3 crossproduct (vec3 &a, vec3 &b)
	{
	return vec3(a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x);
	}

/*--------------------------------Objectos-3D-----------------------------*/
struct rgb_unit
	{
	float r, g, b;
	rgb_unit(double xx, double yy, double zz)
		{
		r=xx;g=yy;b=zz;
		}
	rgb_unit ()
		{
		r=0;
		g=0;
		b=0;
		}
	};
struct triangle3d
	{
	vec3 a,b,c;
	};

struct triangle2d
	{
	vec ma,mb,mc;
	};

struct smooth_flat_triangle
	{
	triangle3d *vert,*smooth;
	smooth_flat_triangle ()
		{
		vert=NULL;
		smooth=NULL;
		}
	};

struct face_out_obj
	{
	smooth_flat_triangle vert;
	triangle2d map;
	char *material;
	char ab,bc,ca;
	};

struct vert_number
	{
	vec3 vert;
        int number;
	};

struct face_int
	{
	int a,b,c;
	};

struct face_in_obj
	{
	face_int face;
	triangle2d map;
	int smoothgroup;
	char material[10];
	char ab,bc,ca;
	};

struct data_object
	{
	vert_number *vertices;
	face_in_obj *faces;
	int totalF,totalV;
	};

char *give_name_file (char *file)
	{
	return strtok(file,".");
	}
char *give_extension_file (char *file)
	{
	return strrchr (file,'.')+1;
	}

char *skipblank (char *linha)
{
  while (isspace (*linha)) linha++;
  return linha;
}

data_object load_obj_disk(char *file,char *nameobj)
	{
	FILE *in;
	char *str,*aux;
	data_object ob;
	ob.totalF=1;
	ob.totalV=0;
	ob.vertices=NULL;
	ob.faces=NULL;

	if ((in = fopen(file, "r"))== NULL)
		return ob;

	/*aux="X-prog file format DATA-OBJECT";
	fscanf(in,"%s",&str );
	if (strcmp(str,aux)!=0)
		{fclose (in);return ob;}*/

	sprintf(aux,"Name: \"%s\"",nameobj);
	/*fscanf(in,"%s", &str);
	if (strcmp(str,aux)!=0)
		{fclose (in);return ob;}*/

	fscanf(in,"%d",&ob.totalV);
	ob.vertices=new vert_number[ob.totalV];
	checkmem(ob.vertices);

	fscanf(in,"%d",&ob.totalF);
	ob.faces=new face_in_obj[ob.totalF];
	checkmem(ob.faces);

	int i;
	for (i=0;i<ob.totalV;i++)
		{
		fscanf(in,"%f",&ob.vertices[i].vert.x);
		fscanf(in,"%f",&ob.vertices[i].vert.y);
		fscanf(in,"%f",&ob.vertices[i].vert.z);
		ob.vertices[i].number=i;
		}
	for (i=0;i<ob.totalF;i++)
		{
		fscanf(in,"%d",&ob.faces[i].face.a);
		fscanf(in,"%d",&ob.faces[i].face.b);
		fscanf(in,"%d",&ob.faces[i].face.c);
		fscanf(in,"%d",&ob.faces[i].ab);
		fscanf(in,"%d",&ob.faces[i].bc);
		fscanf(in,"%d",&ob.faces[i].ca);
		fscanf(in,"%f",&ob.faces[i].map.ma.x);
		fscanf(in,"%f",&ob.faces[i].map.ma.y);
		fscanf(in,"%f",&ob.faces[i].map.mb.x);
		fscanf(in,"%f",&ob.faces[i].map.mb.y);
		fscanf(in,"%f",&ob.faces[i].map.mc.x);
		fscanf(in,"%f",&ob.faces[i].map.mc.y);
		fscanf(in,"%d",&ob.faces[i].smoothgroup);
		fscanf(in,"%s",&ob.faces[i].material);
		}
	fclose (in);
	return ob;
	}


class object
	{
	public:
		vert_number *vertices;
		face_in_obj *faces;
		char *name;
		int totalF,totalV;
		object (char *file,char *name);
		~object();
	};
object::object (char *file,char *nameobj)
	{
	FILE *in;
	char *str,*aux;
	totalF=1;
	totalV=0;
	vertices=NULL;
	faces=NULL;

	if ((in = fopen(file, "r"))== NULL)
		return ;

	/*aux="X-prog file format DATA-OBJECT";
	fscanf(in,"%s",&str );
	if (strcmp(str,aux)!=0)
		{fclose (in);return;}*/

	/*sprintf(aux,"Name: \"%s\"",nameobj);
	fscanf(in,"%s", &str);
	if (strcmp(str,aux)!=0)
		{fclose (in);return ;}*/

	fscanf(in,"%d",&totalV);
	vertices=new vert_number[totalV];
	checkmem(vertices);

	fscanf(in,"%d",&totalF);
	faces=new face_in_obj[totalF];
	checkmem(faces);

	int i;
	for (i=0;i<totalV;i++)
		{
		fscanf(in,"%f",&vertices[i].vert.x);
		fscanf(in,"%f",&vertices[i].vert.y);
		fscanf(in,"%f",&vertices[i].vert.z);
		vertices[i].number=i;
		}
	for (i=0;i<totalF;i++)
		{
		fscanf(in,"%d",&faces[i].face.a);
		fscanf(in,"%d",&faces[i].face.b);
		fscanf(in,"%d",&faces[i].face.c);
		fscanf(in,"%d",&faces[i].ab);
		fscanf(in,"%d",&faces[i].bc);
		fscanf(in,"%d",&faces[i].ca);
		fscanf(in,"%f",&faces[i].map.ma.x);
		fscanf(in,"%f",&faces[i].map.ma.y);
		fscanf(in,"%f",&faces[i].map.mb.x);
		fscanf(in,"%f",&faces[i].map.mb.y);
		fscanf(in,"%f",&faces[i].map.mc.x);
		fscanf(in,"%f",&faces[i].map.mc.y);
		fscanf(in,"%d",&faces[i].smoothgroup);
		fscanf(in,"%s",&faces[i].material);
		}
	fclose (in);
	name=nameobj;
	}
object::~object()
	{
	delete vertices;
	delete faces;
	}


struct materials
	{
	char *name;
	Dmem *texture;
	rgb_unit color;
	struct materials()
		{
		name="\0";
		texture=NULL;
		}

	};

/*class scene
	{
	private:
		face_out_obj *totalfaces;
		materias *list_mat;
	public:

	};     */
