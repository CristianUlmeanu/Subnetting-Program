#include <iostream>
#include <stdlib.h>
#include <bitset>
#include <cmath>

using namespace std;

class Retea
{
private:
    int nr_host;
    int ip[4];
    int masca;
    int bin_masca[4];
    string nume;

    int NA[4];
    int BA[4];
    int RA_min[4];
    int RA_max[4];
public:
    int get_nr_host(){return nr_host;}
    void initializare(int*, int);
    void calcule_initial();
    void calcule_secundar_1(Retea);
    void calcule_secundar_restul_1(Retea);
    void calcule_secundar_restul_2(Retea);
    void scot();

    friend int operator-(Retea&, Retea&);
    void citire(istream&);
    friend istream& operator>>(istream&, Retea&);
    void afisare(ostream&);
    friend ostream& operator<<(ostream&, Retea&);
};

void Retea::initializare(int *v,int masca)
{
    for(int i=0;i<4;i++)
        this->ip[i]=v[i];
    this->masca=masca;
}

void Retea::calcule_initial()
{
    int loc_masca=this->masca,cont=0;
    while(cont<4)
    {
        if(loc_masca>=8)
        {
            bin_masca[cont]=255;
            loc_masca-=8;
        }
        else
        if(loc_masca==7)
        {
            bin_masca[cont]=254;
            loc_masca-=7;
        }
        else
        if(loc_masca==6)
        {
            bin_masca[cont]=252;
            loc_masca-=6;
        }
        else
        if(loc_masca==5)
        {
            bin_masca[cont]=248;
            loc_masca-=5;
        }
        else
        if(loc_masca==4)
        {
            bin_masca[cont]=240;
            loc_masca-=4;
        }
        else
        if(loc_masca==3)
        {
            bin_masca[cont]=224;
            loc_masca-=3;
        }
        else
        if(loc_masca==2)
        {
            bin_masca[cont]=192;
            loc_masca-=2;
        }
        else
        if(loc_masca==1)
        {
            bin_masca[cont]=128;
            loc_masca-=1;
        }
        else
        if(loc_masca==0)
            bin_masca[cont]=0;

        cont++;
    }

    //CALCUL NA
    bitset<8> val[4];
    for(int i=0;i<3;i++)
    {
        bitset<8> foo(this->ip[i]);
        bitset<8> bar(bin_masca[i]);
        val[i]=foo&bar;
        NA[i]=(int)(val[i].to_ulong());
    }
    bitset<8> foo(this->ip[3]);
    bitset<8> bar(bin_masca[3]);
    val[3]=foo&bar;
    NA[3]=(int)(val[3].to_ulong());

    //CALCUL BA
    int octet_necomplet=this->masca/8;
    int poz_stop=this->masca%8;
    for(int i=0;i<octet_necomplet;i++)
        BA[i]=NA[i];
    BA[octet_necomplet]=NA[octet_necomplet];
    for(int i=0;i<8-poz_stop;i++)
        BA[octet_necomplet]+=pow(2,i);
    int i=octet_necomplet+1;
    while(i<4)
    {
        BA[i]=255;
        i++;
    }

    //CALCUL RA
    for(int i=0;i<3;i++)
        RA_min[i]=NA[i];
    RA_min[3]=NA[3]+1;

    for(int i=0;i<3;i++)
        RA_max[i]=BA[i];
    RA_max[3]=BA[3]-1;
}

void Retea::calcule_secundar_1(Retea v)
{
    cout<<"\n\tReteaua cu numele "<<nume<<" si "<<this->nr_host<<" hosturi are:\n\n";
    int gasit=0;
    int putere=-1;
    while(gasit==0)
    {
        if(pow(2,putere)-2<this->nr_host&&this->nr_host<=pow(2,putere+1)-2)
        {
            putere++;
            gasit++;
        }
        else
            putere++;
    }
    this->masca=32-putere;
    int loc_masca=this->masca,cont=0;
    while(cont<4)
    {
        if(loc_masca>=8)
        {
            bin_masca[cont]=255;
            loc_masca-=8;
        }
        else
        if(loc_masca==7)
        {
            bin_masca[cont]=254;
            loc_masca-=7;
        }
        else
        if(loc_masca==6)
        {
            bin_masca[cont]=252;
            loc_masca-=6;
        }
        else
        if(loc_masca==5)
        {
            bin_masca[cont]=248;
            loc_masca-=5;
        }
        else
        if(loc_masca==4)
        {
            bin_masca[cont]=240;
            loc_masca-=4;
        }
        else
        if(loc_masca==3)
        {
            bin_masca[cont]=224;
            loc_masca-=3;
        }
        else
        if(loc_masca==2)
        {
            bin_masca[cont]=192;
            loc_masca-=2;
        }
        else
        if(loc_masca==1)
        {
            bin_masca[cont]=128;
            loc_masca-=1;
        }
        else
        if(loc_masca==0)
            bin_masca[cont]=0;

        cont++;
    }
    cout<<"Puterea lui 2 este: "<<putere<<"\n";
    cout<<"Masca: "<<masca<<"\n";
    cout<<"Masca in decimal: ";
    for(int i=0;i<3;i++)
        cout<<bin_masca[i]<<".";
    cout<<bin_masca[3]<<"\n\n";

    //CALCUL NA
    for(int i=0;i<4;i++)
        this->NA[i]=v.NA[i];
    cout<<"NA: ";
    for(int i=0;i<3;i++)
        cout<<NA[i]<<".";
    cout<<NA[3]<<"/"<<this->masca<<endl;

     //CALCUL BA
    int octet_necomplet=this->masca/8;
    int poz_stop=this->masca%8;
    for(int i=0;i<octet_necomplet;i++)
        BA[i]=NA[i];
    BA[octet_necomplet]=NA[octet_necomplet];
    for(int i=0;i<8-poz_stop;i++)
        BA[octet_necomplet]+=pow(2,i);
    int i=octet_necomplet+1;
    while(i<4)
    {
        BA[i]=255;
        i++;
    }
    cout<<"BA: ";
    for(int i=0;i<3;i++)
        cout<<BA[i]<<".";
    cout<<BA[3]<<"/"<<this->masca<<endl;

    //CALCUL RA
    for(int i=0;i<3;i++)
        RA_min[i]=NA[i];
    RA_min[3]=NA[3]+1;

    for(int i=0;i<3;i++)
        RA_max[i]=BA[i];
    RA_max[3]=BA[3]-1;

    cout<<"RA: ";
    for(int i=0;i<3;i++)
        cout<<RA_min[i]<<".";
    cout<<RA_min[3]<<"-";
    for(int i=0;i<3;i++)
        cout<<RA_max[i]<<".";
    cout<<RA_max[3]<<"/"<<this->masca<<"\n\n";

    int dif_ra=0;
    for(int i=0;i<4;i++)
        if(i==2)
        {
            dif_ra+=(RA_max[i]-RA_min[i])*256;
        }
        else
        if(i==3)
        {
            if(RA_min[2]==RA_max[2])
            {
                if(RA_min[i]==0)
                    dif_ra+=RA_max[i]+1;
                else
                    dif_ra+=RA_max[i]-RA_min[i];
            }
            else
            {
                dif_ra-=256;
                dif_ra+=256-RA_min[i];
                dif_ra+=RA_max[i]+1;
            }
        }
    if(dif_ra==1)
    {
        cout<<"\tESTE INTRE ROUTERE/WIFI-ROUTER SI AI DOAR 2 IP-URI\n";
        cout<<"Host 1: ";
            for(int i=0;i<3;i++)
        cout<<RA_min[i]<<".";
        cout<<RA_min[3]<<"/"<<this->masca<<endl;
        cout<<"Host 2: ";
            for(int i=0;i<3;i++)
        cout<<RA_max[i]<<".";
        cout<<RA_max[3]<<"/"<<this->masca<<endl;
    }
    else
    {
        //CALCULE IP-URI
        cout<<"Default gateway: ";
            for(int i=0;i<3;i++)
            cout<<RA_min[i]<<".";
        cout<<RA_min[3]<<"/"<<this->masca<<endl;

        cout<<"Server: ";
        for(int i=0;i<3;i++)
            cout<<RA_max[i]<<".";
        cout<<RA_max[3]<<"/"<<this->masca<<endl;

        cout<<"Switch: ";
        int nr_switch=ceil((float)nr_host/26);
        if(nr_switch==0)
            nr_switch++;
        int switch_min=RA_min[3]+1;
        int contor=0, switch_max;
        if(nr_switch+switch_min>=256)
        {
            contor++;
            switch_max=nr_switch+switch_min-(256-RA_min[3])-2;
        }
        else
            switch_max=switch_min+nr_switch;
        if(switch_min!=switch_max)
        {
            for(int i=0;i<3;i++)
                cout<<RA_min[i]<<".";
            cout<<switch_min<<"-";


            for(int i=0;i<3;i++)
                if(i==2&&contor==1)
                {
                    RA_min[i]++;
                    cout<<RA_min[i]<<".";
                }
                else
                    cout<<RA_min[i]<<".";
            cout<<switch_max<<"/"<<this->masca<<endl;
        }
        else
        {
            for(int i=0;i<3;i++)
                cout<<RA_min[i]<<".";
            cout<<switch_max<<"/"<<this->masca<<endl;
        }


        int nr_switch1=ceil((float)pow(2,putere)/26);
        cout<<"\nNr ipuri pentru range maxim (2 la putere): "<<pow(2,putere)<<endl;
        cout<<"Nr switch pentru range maxim: "<<nr_switch1<<endl;
        cout<<"IP_DCHP_SRV: ";
        if(nr_switch1==0)
            nr_switch1++;
        int switch_min1=RA_min[3]+1;
        int contor1=0, switch_max1;
        if(nr_switch1+switch_min1>=256)
        {
            contor1++;
            switch_max1=nr_switch1+switch_min1-(256-RA_min[3])-2;
        }
        else
            switch_max1=switch_min1+nr_switch1;
        if(switch_min1!=switch_max1)
        {
            for(int i=0;i<3;i++)
                if(i==2&&contor1==1)
                {
                    RA_min[i]++;
                    cout<<RA_min[i]<<".";
                }
                else
                    cout<<RA_min[i]<<".";
            cout<<switch_max1<<"/"<<this->masca<<endl;
        }
        cout<<"Max number of users (DHCP): "<<pow(2,putere)-2-nr_switch1<<endl;

        cout<<"\nHost: ";
        for(int i=0;i<3;i++)
            cout<<RA_min[i]<<".";
        cout<<switch_max+1<<"-";
        for(int i=0;i<3;i++)
            cout<<RA_max[i]<<".";
        cout<<RA_max[3]-1<<"/"<<this->masca<<endl;
    }
}

void Retea::calcule_secundar_restul_1(Retea v)
{
    cout<<"\n\tReteaua cu numele "<<nume<<" si cu "<<this->nr_host<<" hosturi are:\n\n";
    int gasit=0;
    int putere=-1;
    while(gasit==0)
    {
        if(pow(2,putere)-2<this->nr_host&&this->nr_host<=pow(2,putere+1)-2)
        {
            putere++;
            gasit++;
        }
        else
            putere++;
    }
    this->masca=32-putere;
    int loc_masca=this->masca,cont=0;
    while(cont<4)
    {
        if(loc_masca>=8)
        {
            bin_masca[cont]=255;
            loc_masca-=8;
        }
        else
        if(loc_masca==7)
        {
            bin_masca[cont]=254;
            loc_masca-=7;
        }
        else
        if(loc_masca==6)
        {
            bin_masca[cont]=252;
            loc_masca-=6;
        }
        else
        if(loc_masca==5)
        {
            bin_masca[cont]=248;
            loc_masca-=5;
        }
        else
        if(loc_masca==4)
        {
            bin_masca[cont]=240;
            loc_masca-=4;
        }
        else
        if(loc_masca==3)
        {
            bin_masca[cont]=224;
            loc_masca-=3;
        }
        else
        if(loc_masca==2)
        {
            bin_masca[cont]=192;
            loc_masca-=2;
        }
        else
        if(loc_masca==1)
        {
            bin_masca[cont]=128;
            loc_masca-=1;
        }
        else
        if(loc_masca==0)
            bin_masca[cont]=0;

        cont++;
    }
    cout<<"Puterea lui 2 este: "<<putere<<"\n";
    cout<<"Masca: "<<masca<<"\n";
    cout<<"Masca in decimal: ";
    for(int i=0;i<3;i++)
        cout<<bin_masca[i]<<".";
    cout<<bin_masca[3]<<"\n\n";

    //CALCUL NA
    if(v.BA[3]==255)
    {
        for(int i=0;i<2;i++)
            this->NA[i]=v.BA[i];
        this->NA[2]=v.BA[2]+1;
        this->NA[3]=0;
    }
    else
    {
        for(int i=0;i<3;i++)
                this->NA[i]=v.BA[i];
        this->NA[3]=v.BA[3]+1;
    }
    cout<<"NA: ";
    for(int i=0;i<3;i++)
        cout<<NA[i]<<".";
    cout<<NA[3]<<"/"<<this->masca<<endl;

    //CALCUL BA
    int octet_necomplet=this->masca/8;
    int poz_stop=this->masca%8;
    for(int i=0;i<octet_necomplet;i++)
        BA[i]=NA[i];
    BA[octet_necomplet]=NA[octet_necomplet];
    for(int i=0;i<8-poz_stop;i++)
        BA[octet_necomplet]+=pow(2,i);
    int i=octet_necomplet+1;
    while(i<4)
    {
        BA[i]=255;
        i++;
    }
    cout<<"BA: ";
    for(int i=0;i<3;i++)
        cout<<BA[i]<<".";
    cout<<BA[3]<<"/"<<this->masca<<endl;

    //CALCUL RA
    for(int i=0;i<3;i++)
        RA_min[i]=NA[i];
    RA_min[3]=NA[3]+1;

    for(int i=0;i<3;i++)
        RA_max[i]=BA[i];
    RA_max[3]=BA[3]-1;

    cout<<"RA: ";
    for(int i=0;i<3;i++)
        cout<<RA_min[i]<<".";
    cout<<RA_min[3]<<"-";
    for(int i=0;i<3;i++)
        cout<<RA_max[i]<<".";
    cout<<RA_max[3]<<"/"<<this->masca<<"\n\n";

    int dif_ra=0;
    for(int i=0;i<4;i++)
        if(i==2)
        {
            dif_ra+=(RA_max[i]-RA_min[i])*256;
        }
        else
        if(i==3)
        {
            if(RA_min[2]==RA_max[2])
            {
                if(RA_min[i]==0)
                    dif_ra+=RA_max[i]+1;
                else
                    dif_ra+=RA_max[i]-RA_min[i]+1;
            }
            else
            {
                dif_ra-=256;
                dif_ra+=256-RA_min[i];
                dif_ra+=RA_max[i]+1;
            }
        }
    if(dif_ra==1)
    {
        cout<<"\tESTE INTRE ROUTERE/WIFI-ROUTER SI AI DOAR 2 IP-URI\n";
        cout<<"Host 1: ";
            for(int i=0;i<3;i++)
        cout<<RA_min[i]<<".";
        cout<<RA_min[3]<<"/"<<this->masca<<endl;
        cout<<"Host 2: ";
            for(int i=0;i<3;i++)
        cout<<RA_max[i]<<".";
        cout<<RA_max[3]<<"/"<<this->masca<<endl;
    }
    else
    {
        //CALCULE IP-URI
        cout<<"Default gateway: ";
            for(int i=0;i<3;i++)
            cout<<RA_min[i]<<".";
        cout<<RA_min[3]<<"/"<<this->masca<<endl;

        cout<<"Server: ";
        for(int i=0;i<3;i++)
            cout<<RA_max[i]<<".";
        cout<<RA_max[3]<<"/"<<this->masca<<endl;

        cout<<"Switch: ";
        int nr_switch=ceil(nr_host/26);
        if(nr_switch==0)
            nr_switch++;
        int switch_min=RA_min[3]+1;
        int contor=0, switch_max;
        if(nr_switch+switch_min>=256)
        {
            contor++;
            switch_max=nr_switch+switch_min-(256-RA_min[3])-2;
        }
        else
            switch_max=switch_min+nr_switch;

        if(switch_min!=switch_max)
        {
            for(int i=0;i<3;i++)
                cout<<RA_min[i]<<".";
            cout<<switch_min<<"-";


            for(int i=0;i<3;i++)
                if(i==2&&contor==1)
                {
                    RA_min[i]++;
                    cout<<RA_min[i]<<".";
                }
                else
                    cout<<RA_min[i]<<".";
            cout<<switch_max<<"/"<<this->masca<<endl;
        }
        else
        {
            for(int i=0;i<3;i++)
                cout<<RA_min[i]<<".";
            cout<<switch_max<<"/"<<this->masca<<endl;
        }

        int nr_switch1=ceil((float)pow(2,putere)/26);
        cout<<"\nNr ipuri pentru range maxim (2 la putere): "<<dif_ra<<endl;
        cout<<"Nr switch pentru range maxim: "<<nr_switch1<<endl;
        cout<<"IP_DCHP_SRV: ";
        if(nr_switch1==0)
            nr_switch1++;
        int switch_min1=RA_min[3]+1;
        int contor1=0, switch_max1;
        if(nr_switch1+switch_min1>=256)
        {
            contor1++;
            switch_max1=nr_switch1+switch_min1-(256-RA_min[3])-2;
        }
        else
            switch_max1=switch_min1+nr_switch1;
        if(switch_min1!=switch_max1)
        {
            for(int i=0;i<3;i++)
                if(i==2&&contor1==1)
                {
                    RA_min[i]++;
                    cout<<RA_min[i]<<".";
                }
                else
                    cout<<RA_min[i]<<".";
            cout<<switch_max1<<"/"<<this->masca<<endl;
        }
        cout<<"Max number of users (DHCP): "<<pow(2,putere)-2-nr_switch1<<endl;

        cout<<"\nHost: ";
        for(int i=0;i<3;i++)
            cout<<RA_min[i]<<".";
        cout<<switch_max+1<<"-";
        for(int i=0;i<3;i++)
            cout<<RA_max[i]<<".";
        cout<<RA_max[3]-1<<"/"<<this->masca<<endl;
    }
}

void Retea::calcule_secundar_restul_2(Retea v)
{
    this->masca=30;
    int loc_masca=this->masca,cont=0;
    while(cont<4)
    {
        if(loc_masca>=8)
        {
            bin_masca[cont]=255;
            loc_masca-=8;
        }
        else
        if(loc_masca==7)
        {
            bin_masca[cont]=254;
            loc_masca-=7;
        }
        else
        if(loc_masca==6)
        {
            bin_masca[cont]=252;
            loc_masca-=6;
        }
        else
        if(loc_masca==5)
        {
            bin_masca[cont]=248;
            loc_masca-=5;
        }
        else
        if(loc_masca==4)
        {
            bin_masca[cont]=240;
            loc_masca-=4;
        }
        else
        if(loc_masca==3)
        {
            bin_masca[cont]=224;
            loc_masca-=3;
        }
        else
        if(loc_masca==2)
        {
            bin_masca[cont]=192;
            loc_masca-=2;
        }
        else
        if(loc_masca==1)
        {
            bin_masca[cont]=128;
            loc_masca-=1;
        }
        else
        if(loc_masca==0)
            bin_masca[cont]=0;

        cont++;
    }
    cout<<"Masca: "<<masca<<"\n";
    cout<<"Masca in decimal: ";
    for(int i=0;i<3;i++)
        cout<<bin_masca[i]<<".";
    cout<<bin_masca[3]<<"\n\n";

    //CALCUL NA
    if(v.BA[3]==255)
    {
        for(int i=0;i<2;i++)
            this->NA[i]=v.BA[i];
        this->NA[2]=v.BA[2]+1;
        this->NA[3]=0;
    }
    else
    {
        for(int i=0;i<3;i++)
                this->NA[i]=v.BA[i];
        this->NA[3]=v.BA[3]+1;
    }
    cout<<"NA: ";
    for(int i=0;i<3;i++)
        cout<<NA[i]<<".";
    cout<<NA[3]<<"/"<<this->masca<<endl;

    //CALCUL BA
    int octet_necomplet=this->masca/8;
    int poz_stop=this->masca%8;
    for(int i=0;i<octet_necomplet;i++)
        BA[i]=NA[i];
    BA[octet_necomplet]=NA[octet_necomplet];
    for(int i=0;i<8-poz_stop;i++)
        BA[octet_necomplet]+=pow(2,i);
    int i=octet_necomplet+1;
    while(i<4)
    {
        BA[i]=255;
        i++;
    }
    cout<<"BA: ";
    for(int i=0;i<3;i++)
        cout<<BA[i]<<".";
    cout<<BA[3]<<"/"<<this->masca<<endl;

    //CALCUL RA
    for(int i=0;i<3;i++)
        RA_min[i]=NA[i];
    RA_min[3]=NA[3]+1;

    for(int i=0;i<3;i++)
        RA_max[i]=BA[i];
    RA_max[3]=BA[3]-1;

    cout<<"RA: ";
    for(int i=0;i<3;i++)
        cout<<RA_min[i]<<".";
    cout<<RA_min[3]<<"-";
    for(int i=0;i<3;i++)
        cout<<RA_max[i]<<".";
    cout<<RA_max[3]<<"/"<<this->masca<<"\n\n";

    int dif_ra=0;
    for(int i=0;i<4;i++)
        if(RA_min[i]<RA_max[i]&&i<3)
            dif_ra+=(RA_max[i]-RA_min[i])*256;
        else
            dif_ra+=RA_max[i]-RA_min[i];
    if(dif_ra==1)
    {
        cout<<"\tHost 1: ";
            for(int i=0;i<3;i++)
        cout<<RA_min[i]<<".";
        cout<<RA_min[3]<<"/"<<this->masca<<endl;
        cout<<"\tHost 2: ";
            for(int i=0;i<3;i++)
        cout<<RA_max[i]<<".";
        cout<<RA_max[3]<<"/"<<this->masca<<endl;
    }
}

int operator-(Retea& a, Retea& b)
{
    return a.nr_host-b.nr_host;
}

void Retea::citire(istream& in)
{
    cout<<"Nr hosturi: ";
    in>>this->nr_host;
    cout<<"Numele LANului este: ";
    in>>this->nume;
    cout<<endl;
}

istream& operator>>(istream& in, Retea& z)
{
    z.citire(in);
    return in;
}

void Retea::afisare(ostream& out)
{
    out<<"\n\tReteaua INITIALA are urmatoarele date:\n\n";
    out<<"IP address: ";
    for(int i=0;i<3;i++)
        out<<ip[i]<<".";
    out<<ip[3]<<"/"<<this->masca<<endl;
    out<<"Mask: ";
    for(int i=0;i<3;i++)
        out<<bin_masca[i]<<".";
    out<<bin_masca[3]<<"\n\n";

    out<<"NA: ";
    for(int i=0;i<3;i++)
        out<<NA[i]<<".";
    out<<NA[3]<<"/"<<this->masca<<endl;

    out<<"BA: ";
    for(int i=0;i<3;i++)
        out<<BA[i]<<".";
    out<<BA[3]<<"/"<<this->masca<<endl;

    out<<"RA: ";
    for(int i=0;i<3;i++)
        out<<RA_min[i]<<".";
    out<<RA_min[3]<<"-";
    for(int i=0;i<3;i++)
        out<<RA_max[i]<<".";
    out<<RA_max[3]<<"/"<<this->masca<<"\n\n";
}

ostream& operator<<(ostream& out, Retea&z)
{
    z.afisare(out);
    return out;
}

int compare (const void * a, const void * b)
{
  return -(*(Retea*)a - *(Retea*)b);
}

int main()
{
    int n,m,i,j=0,k=0;
    int ip[4];
    int masca;
    cout<<"Introduceti ip retea (fara puncte): ";
    for(int i=0;i<4;i++)
        cin>>ip[i];
    cout<<"Masca retea: ";
    cin>>masca;
    cout<<"\nIntroduceti numarul de LAN-uri: ";
    cin>>n;
    cout<<"\nIntroduceti numarul de WIFI-uri: ";
    cin>>m;
    cout<<endl;
    Retea v[n+1];
    v[0].initializare(ip,masca);
    for(int i=1;i<=n;i++)
        cin>>v[i];
    system("pause");
    system("cls");

    v[0].calcule_initial();
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            if(v[i].get_nr_host()<v[j].get_nr_host())
            swap(v[i],v[j]);
        }
    }
    cout<<v[0];
    cout<<"\n---------------------------------------------------------------------\n";
    v[1].calcule_secundar_1(v[0]);
    for(i=2;i<=n;i++)
        v[i].calcule_secundar_restul_1(v[i-1]);

    cout<<"\n---------------------------------------------------------------------\n";
    if(m>0){
    cout<<"\n\n\tPrima retea WIFI este:\n\n";
    v[j].calcule_secundar_restul_2(v[n]);
    for(j=1;j<m;j++)
    {
        cout<<"\n\n\tReteaua WIFI cu numarul "<<j+1<<" este:\n\n";
        v[j].calcule_secundar_restul_2(v[j-1]);
    }
    cout<<"\n\n\tPrima retea dintre routere este:\n\n";
    v[k].calcule_secundar_restul_2(v[j-1]);
    for(k=1;k<n-1;k++)
    {
        cout<<"\n\n\tReteaua dintre routere cu numarul "<<k+1<<" este:\n\n";
        v[k].calcule_secundar_restul_2(v[k-1]);
    }
    }
    else
    {
    cout<<"\n\n\tPrima retea dintre routere este:\n\n";
    v[k].calcule_secundar_restul_2(v[n]);
    for(k=1;k<n-1;k++)
    {
        cout<<"\n\n\tReteaua dintre routere cu numarul "<<k+1<<" este:\n\n";
        v[k].calcule_secundar_restul_2(v[k-1]);
    }
    }
    cout<<endl;
}
