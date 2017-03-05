#include <iostream>
#include <string>
using namespace std;

typedef struct nod
{
  int nr;
  struct nod *urm;
  struct nod *prec;
}NOD;
typedef struct lista
{
	NOD *varf,*cursor;
	int n;
}Lista;
Lista l1,l2,l3;

void creeaza(Lista *l)
{
  l->varf=NULL;
  l->cursor=l->varf;
  l->n=0;
}

int nr_elem(Lista l)
{
	return l.n;
}

void succesor(Lista *l)
{
	l->cursor=l->cursor->urm;
}

void predecesor(Lista *l)
{
	l->cursor=l->cursor->prec;
}

void elem_crt(Lista *l,int k)
{
	l->cursor=l->varf;
	for (int i=1;i<=k-1;i++)
		l->cursor=l->cursor->urm;
}

int poz_crt(Lista l)
{
	NOD *p;
	int t=1;
	p=l.varf;
	if (p!=NULL)
		while (p!=l.cursor)
		{
			p=p->urm;
			t++;
		}
	return t;
}
int extrage(Lista l)
{
	return l.cursor->nr;
}

void actualizeaza(Lista *l,int a)
{
	l->cursor->nr=a;
}

void adauga_dupa(Lista *l,int a)
{
  NOD *p=new NOD;
  p->nr=a;
  if (l->varf==NULL) 
  {
	  l->varf=p;
	  p->urm=p;
	  p->prec=p;
  }
  else
  {
   	l->cursor->urm->prec=p;
    	p->urm=l->cursor->urm;
	l->cursor->urm=p;
	p->prec=l->cursor;
  }
  l->cursor=p;
  l->n++;
}

void adauga_inainte(Lista *l,int a)
{
	if (l->varf!=NULL)
		l->cursor=l->cursor->prec;
	adauga_dupa(l,a);
	if (l->cursor->urm==l->varf)
		l->varf=l->cursor;
}


void sterge(Lista *l)
{
	NOD *p;
	p=l->cursor;
	l->cursor->prec->urm=l->cursor->urm;
	l->cursor->urm->prec=l->cursor->prec;
	l->cursor=l->cursor->urm;
	if (l->n==1) l->varf=NULL;
	else if (l->varf==p) l->varf=l->cursor;
	l->n--;
	delete(p);
}

void citeste(Lista *l)
{
	char s[100];
	cout<<"Dati numarul : ";
	cin>>s;
	for(int i=0;i<strlen(s);i++)
			adauga_dupa(l,(int)(s[i]-48));
}

void tipareste(Lista l)
{
	int i,c;
	elem_crt(&l,1);
	for(i=1;i<=nr_elem(l);i++)
	{
		c=extrage(l);
		cout<<c;
		succesor(&l);
	}
}

void aduna(Lista l1,Lista l2,Lista *l3)
{
	int i,r,c1,c2,c3,ind;
	creeaza(l3);
	r=0;
	if(nr_elem(l1)==0) ind=1;
	else if(nr_elem(l2)==0) ind=2;
	else
	{
		elem_crt(&l1,nr_elem(l1));
		elem_crt(&l2,nr_elem(l2));
		ind=0;
		do
		{
			c1=extrage(l1);
			c2=extrage(l2);
			c3=c1+c2+r;
			if (c3<10) r=0;
			else
			{
				c3=c3-10;
				r=1;
			}
			adauga_inainte(l3,c3);
			if (poz_crt(l1)==1) ind=1;
			else if (poz_crt(l2)==1) ind=2;
			else
			{
				predecesor(&l1);
				predecesor(&l2);
			}
		}while (ind==0);
		if (ind==2) 
		{	
			if(poz_crt(l1)!=1) 
			{
			predecesor(&l1);
			do{	
				c1=extrage(l1);
				c3=c1+r;
				if (c3<10) r=0;
				else {
					c3=c3-10;
					r=1;
				}
				adauga_inainte(l3,c3);
				if (poz_crt(l1)==1) ind=1;
				else predecesor(&l1);
			}while(ind==2);
			}
		}
		else if (ind==1)
		{
			if(poz_crt(l2)!=1) 
			{
			predecesor(&l2);
			do{	
				c2=extrage(l2);
				c3=c2+r;
				if (c3<10) r=0;
				else {
					c3=c3-10;
					r=1;
				}
				adauga_inainte(l3,c3);
				if (poz_crt(l2)==1) ind=2;
				else predecesor(&l2);
			}while(ind==1);
			}
		}
		if (r>0) adauga_inainte(l3,r);
	}
}

void main()
{
	creeaza(&l1);
	creeaza(&l2);
	citeste(&l1);
	citeste(&l2);
	aduna(l1,l2,&l3);
	tipareste(l1);
	cout<<" + ";
	tipareste(l2);
	cout<<" = ";
	tipareste(l3);
	cout<<endl;
	system("pause");
}
