#include <stdio.h>
#include <stdlib.h>

struct artikal{
    int sifra;
    char naziv[20];
    double cena;
};
typedef struct artikal Artikal;

struct prodavnica{
    char naziv[20];
    Artikal *artikli;
    int brojArtikala;
};
typedef struct prodavnica Prodavnica;

Prodavnica *p;

int meni(){
    int odg=0, nepostoji=-1;
    printf("1. Postavi naziv prodavnice\n");
    printf("2. Dodaj artikal\n");
    printf("3. Obrisi artikal za sifru\n");
    printf("4. Obrisi sve artikle\n");
    printf("5. Pronadji artikal preko sifre\n");
    printf("6. Prikazi artikle\n");
    printf("7. Kraj rada\n");
    do{
    if(nepostoji==0)
        printf("Izabrali ste operaciju koja ne postoji.\n");
    else
        nepostoji=0;
    scanf("%d", &odg);
    }while( odg < 1 || odg > 7);
    return odg;
}
void postaviNaziv(){
    char novinaziv[20];
    int i;
    printf("Upisite novi naziv prodavnice\n");
    scanf("%s", novinaziv);
    for(i=0;i<20;i++)
    {
        p->naziv[i] = novinaziv[i];
    }
}
void dodajArtikal(){
    p->artikli=(Artikal*)realloc(p->artikli,sizeof(Artikal)*(p->brojArtikala+1));
    printf("Sifra: ");
    scanf("%d", &p->artikli[p->brojArtikala].sifra);
    printf("Naziv: ");
    scanf("%s", p->artikli[p->brojArtikala].naziv);
    printf("Cena: ");
    scanf("%lf", &p->artikli[p->brojArtikala].cena);
    p->brojArtikala++;
}
void obrisiZasifru(int x){
    int j, i;
    for(i=0;i<p->brojArtikala;i++){
        if(x==p->artikli[i].sifra){
        j=i;
        }
    }
    for(j;j<p->brojArtikala;j++){
        p->artikli[j].sifra=p->artikli[j+1].sifra;
        for(i=0;p->artikli[x+1].naziv[i]!='\0';i++){
            p->artikli[j].naziv[i]=p->artikli[j+1].naziv[i];
        }
        p->artikli[j].cena=p->artikli[j+1].cena;
    }
    p->artikli=(Artikal*)realloc(p->artikli,sizeof(Artikal)*(p->brojArtikala-1));
    p->brojArtikala--;
}
void obrisi(){
    free(p->artikli);
    p->artikli=malloc(sizeof(Artikal));
    p->brojArtikala=0;
}
Artikal pronadji(int x){
    int i, a=0;
    for(i=0;i<p->brojArtikala;i++)
    {
        if(x==p->artikli[i].sifra)
        {
            a=1;
            printf("Sifra: %i\nNaziv: %s\nCena: %.2lf\n", p->artikli[i].sifra, p->artikli[i].naziv, p->artikli[i].cena);
        }
    }
    if(a==0){
        printf("Sifra ne postoji.\n");
    }
}
void stampaj(){
    int i;
    printf("Prodavnica: %s\n",p->naziv);
    printf("Broj artikala: %i\n",p->brojArtikala);
    for(i=0;i<p->brojArtikala;++i)
    {
        printf("Sifra: %i\nNaziv: %s\nCena: %.2lf\n", p->artikli[i].sifra, p->artikli[i].naziv, p->artikli[i].cena);
    }
}


int main()
{
    int odg, sifra;
    p=(Prodavnica*)malloc(sizeof(Prodavnica));
    p->artikli=malloc(sizeof(Artikal));
    p->brojArtikala=0;
    while(1){
    odg = meni();
        switch(odg){
            case 1:
                fflush(stdin);
                postaviNaziv();
                break;
            case 2:
                fflush(stdin);
                dodajArtikal();
                break;
            case 3:
                fflush(stdin);
                printf("Sifra: ");
                scanf("%i", &sifra);
                obrisiZasifru(sifra);
                break;
            case 4:
                obrisi();
                break;
            case 5:
                fflush(stdin);
                printf("Sifra: ");
                scanf("%i", &sifra);
                pronadji(sifra);
                break;
            case 6:
                stampaj();
                break;
            case 7:
                free(p->artikli);
                free(p);
                return 0;
                break;

        }
    }
}
