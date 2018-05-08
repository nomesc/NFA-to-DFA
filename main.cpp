#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class Stare
{
    int *noduri;
    int k;
public:
    Stare();
    Stare(Stare const &);
    int existaNod(int const &,int ,int )const;
    Stare&operator=(Stare const &);
    void adaugareNod(int);
    Stare&operator+(Stare const &);
    bool operator==(Stare const &);
    friend ostream& operator<<(ostream&,Stare const &);
    friend istream& operator>>(istream&,Stare &);
    bool inlcusa(Stare const &);
    bool elementcomun(Stare const &);
};

////////////////////////////////////////////

bool Stare::elementcomun(Stare const &obj) {
    if(k==0||obj.k==0)
        return false;
    int i;
    if(k<=obj.k)
    {
        for(i=0;i<k;i++)
            if(obj.existaNod(noduri[i],0,obj.k-i)>=0)
                return true;
    }
    else
    {
        for(i=0;i<obj.k;i++)
            if(existaNod(obj.noduri[i],0,k-1)>=0)
                return true;
    }
    return false;
}

bool Stare::inlcusa(Stare const &obj) {
    if(obj.k>=k)
        return false;
    for(int i=0;i<obj.k;i++)
    {
        if(existaNod(obj.noduri[i],0,k-1)==-1)
            return false;
    }
    return true;
}

int compare(const void *x,const void * y)
{
    if(*(int*)x<*(int*)y)
        return -1;
    if(*(int*)x==*(int*)y)
        return 0;
    return 1;
}

istream& operator>>(istream&in,Stare & obj){
    in>>obj.k;
    delete[] obj.noduri;
    obj.noduri=new int[obj.k];
    //fout<<"xxxxxxxxxxxxxxxxxxxxxxxxxx";
    for(int i=0;i<obj.k;i++)
        in>>obj.noduri[i];
    qsort(obj.noduri,obj.k, sizeof(int),compare);
    return in;
}

ostream& operator<<(ostream&out,Stare const & obj){
    out<<"{";
    for(int i=0;i<obj.k;i++)
    {
        out<<obj.noduri[i]<<" ";
    }
    out<<"}";
    return out;
}

bool Stare::operator==(Stare const &obj) {
    if(k!=obj.k)
        return false;
    for(int i=0;i<k;i++)
        if(noduri[i]!=obj.noduri[i])
            return false;
    return true;
}

Stare& Stare::operator+(Stare const &obj) {
    Stare *aux=new Stare;
    int i;
    for(i=0;i<k;i++)
        aux->adaugareNod(noduri[i]);
    for(i=0;i<obj.k;i++)
        aux->adaugareNod(obj.noduri[i]);
    return *aux;
}

void Stare::adaugareNod(int x) {
    if(existaNod(x,0,k-1)!=-1)
        return;
    k++;
    int *aux=new int[k];
    for(int i=0;i<k-1;i++)
        aux[i]=noduri[i];
    aux[k-1]=x;
    qsort(aux,k, sizeof(int),compare);
    delete[]noduri;
    noduri=aux;
}

Stare & Stare::operator =(Stare const & obj){
    if(this==&obj)
        return *this;
    k=obj.k;
    delete noduri;
    noduri=new int[k];
    for(int i=0;i<k;i++)
        noduri[i]=obj.noduri[i];
    return *this;
}

int Stare::existaNod(int const &x,int l=0,int r=-1337)const {
    if(r==-1337)
        r=k-1;
    if(r<l)
        return -1;
    int mid=l+(r-l)/2;
    if(noduri[mid]==x)
        return mid;
    if(noduri[mid]>x)
        return existaNod(x,l,mid-1);
    return existaNod(x,mid+1,r);
}

Stare::Stare(Stare const &obj) {
    k=obj.k;
    noduri=new int[k];
    for(int i=0;i<k;i++)
        noduri[i]=obj.noduri[i];
}

Stare::Stare() {
    k=0;
    noduri= nullptr;
}

struct Linie
{
    Stare x,*starile;
    Linie*next;
};

void meritaafisate(Linie* start,Stare * vector,int &elemente,int nrliterealfa)
{
    if(start==nullptr)
        return;
    int i;
    for(i=0;i<elemente;i++)
        if(start->x==vector[i])
            return;
    vector[elemente]=start->x;
    elemente++;
    for(i=0;i<nrliterealfa;i++)
    {
        Stare decautat=start->starile[i];
        Linie *Parcurgere=start;
        while(Parcurgere!=nullptr)
        {
            if(Parcurgere->x==decautat)
            {
                meritaafisate(Parcurgere,vector,elemente,nrliterealfa);
                break;
            }
            Parcurgere=Parcurgere->next;
        }
    }
}

int main() {
    ifstream fin("date.in");
    ofstream fout("date.out");
    int nrliterealf,nrstari,i,j;
    char *alfabet,c;
    fin>>nrliterealf;
    alfabet=new char[nrliterealf+1];
    fin>>alfabet>>nrstari;
    //fout<<nrstari<<endl<<nrliterealf<<endl;
    Stare finale;
    //fout<<"dddddddddddddddddddddddddddd";
    fin>>finale;
    //fout<<"aaaaaaaaaaaaaaaaaaaaa";
    Linie *start,*final;
    //fout<<nrstari<<endl;
    start=final=nullptr;
    for(i=0;i<nrstari;i++)
    {
        //fout<<i<<i<<i;
        Linie *aux=new Linie;
        aux->next=nullptr;
        aux->starile=new Stare[nrliterealf];
        fin>>aux->x;
        for(j=0;j<nrliterealf;j++)
        {
            fin>>c;
            fin>>aux->starile[j];
        }
        if(start== nullptr)
        {
            start=final=aux;
        }
        else
        {
            final->next=aux;
            final=aux;
        }
    }
    fin.close();
    Linie *Parcurgere=start,*auxx;
    int catelinii=0;
    while(Parcurgere!=nullptr)
    {
        catelinii++;
        for(i=0;i<nrliterealf;i++)
        {
            Stare y=Parcurgere->starile[i];
            auxx=start;
            int ok=0;
            while(auxx!=nullptr)
            {
                if(auxx->x==y)
                {
                    ok=1;
                    break;
                }
                auxx=auxx->next;
            }
            if(ok)
                continue;
            Linie *aux=new Linie;
            aux->x=y;
            aux->starile=new Stare[nrliterealf];
            for(j=0;j<nrliterealf;j++)
            {
                auxx=start;
                while(auxx!=nullptr)
                {
                    if(aux->x.inlcusa(auxx->x))
                    {
                        aux->starile[j]=aux->starile[j]+auxx->starile[j];
                    }
                    auxx=auxx->next;
                }
            }
            aux->next=Parcurgere->next;
            Parcurgere->next=aux;
        }
        Parcurgere=Parcurgere->next;
    }
    Stare *vector=new Stare[catelinii];
    int catemerita=0;
    meritaafisate(start,vector,catemerita,nrliterealf);
    Parcurgere=start;
    //fout<<"\ncitire reusita probabil\n";
    //int debug=0;
    while(Parcurgere!= nullptr)
    {
        Stare y=Parcurgere->x;
        Linie * cautare=start;
        int ok=0;
        //fout<<debug<<endl;
        //debug++;
        while(cautare!=Parcurgere)
        {
            if(y==cautare->x)
            {
                ok=1;
                Parcurgere=Parcurgere->next;
                break;
            }
            cautare=cautare->next;
        }
        //fout<<"OOOO"<<ok;
        if(ok)
            continue;
        Stare vida;
        if(Parcurgere->x==vida)
        {
            Parcurgere=Parcurgere->next;
            continue;
        }
        int merita=0;
        for(int yyy=0;yyy<catemerita;yyy++)
        {
            if(Parcurgere->x==vector[yyy])
            {
                merita=1;
                break;
            }
        }
        if(merita==0)
        {
            Parcurgere=Parcurgere->next;
            continue;
        }
        fout<<"//////////////////\n"<<"Stare: "<<Parcurgere->x;
        if(Parcurgere->x.elementcomun(finale))
            fout<<" FINALA"<<endl;
        else fout<<endl;
        for(i=0;i<nrliterealf;i++)
        {
            fout<<alfabet[i]<<":"<<Parcurgere->starile[i]<<endl;
        }
        Parcurgere=Parcurgere->next;
    }
    return 0;
}
