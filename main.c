#include <stdio.h>
#include <stdlib.h>




        ///Potrebno je napraviti program koji simulira rad programa za radnika u fast food restoranu. Kako bi program uspešno radio potrebno je imati sledeće funkcionalnosti.
        ///Meni –  Na ekran se ispisuje meni koji korisniku prikazuje sve moguće operacije. Korisnik unosom odgovarajućeg broja sa tastature bira željenu funkcionalnost.
        ///Dodavanje novog artikla– Omogućava se kreiranje novog  artikla odnosno proizvoda koji se prodaje. Kako bi se artikl kreirao korisnik mora uneti : Naziv, barkod broj (mora biti jedinstven). Postoje dva tipa artikla, gotov prizvod ( Flasirana voda) i prozvod koji se pravi ( pljeskavica ). Proizvodi koji se prave poseduju i niz sastojaka od kojih se prave.
        ///Prikaz svih -  Ispisuje na ekran sve proizvode  (sa svim relevantnim informacijama) i prikazuje sve njihove sastoje ako ih ima.
        ///Pretraga artikla– Omogućiti pretragu po barkodu ili po nazivu. Prikazati podatke o pronađenom artiklu na ekranu. U slučaju da postoji više proizvoda sa istim nazivom prikazati sve pronađene.
        ///Izmena artikla – Omogućiti izmenu naziva ili sastoja željenog artikla.
        ///Brisanje artikla – Omogućiti brisanje artikla.
        ///Cenovnik  - Omogućiti kreiranje i izmenu cenovnika. Cenovnik poseduje cene za svaki bar kod kao i datum od kada važi.

int meni(){
    int odg=0, err=0;
    printf("1. Dodavanje artikla\n");
    printf("2. Prikaz svih artikla\n");
    printf("3. Pretraga artikla\n");
    printf("4. Izmeni artikal\n");
    printf("5. Obrisi artikal\n");
    printf("6. Cenovnik\n");
    printf("7. Kraj\n");
    do{
    if(err==1)
        printf("Pokusajte ponovo\n");
    else
        err=1;
    scanf("%i", &odg);
    }while(1 > odg || odg > 8);
    return odg;
}

void dodajartikal(){
    char naziv[50];
    char* barkod;
    barkod=(char*)malloc(sizeof(char)*13);
    int gotov=2, err=0;

    printf("naziv: ");
    scanf("%s", naziv);

    printf("barkod od 12 cifara: ");
    do{
    if(err==1)
        printf("Pokusajte ponovo\n");
    else
        err=1;
    scanf("%s", barkod);
    popravibarkod(barkod);
    }while(dalipostojibarkod(barkod)==1);
    printf("gotov proizvod (0 za ne, 1 za da): ");
    scanf("%i", &gotov);
    while(gotov!=0 && gotov!=1){
        printf("neispravan tip\n");
        scanf("%i", &gotov);
    }
    if(gotov==0){
        FILE* a;
        a=fopen(barkod,"w");
        fclose(a);
        sastojci(barkod);
    }

    FILE* upis;
    upis=fopen("artikli.txt","a+");
    fprintf(upis,"%s\n%s\n%i\n\n", naziv, barkod, gotov);
    fclose(upis);
    free(barkod);
}

void sastojci(char* barkod){
    FILE* sastojci;
    FILE* temp;
    char unos[50];
    int odg, err, i;
    while(1){
        odg=0;
        err=0;
        printf("1. Unesi sastojak\n");
        printf("2. Obrisi sastojak\n");
        printf("3. Prikazi sastojke\n");
        printf("4. Kraj promene sastojaka\n");
        do{
            if(err==1)
                printf("Pokusajte ponovo\n");
            else
                err=1;
                scanf("%i", &odg);
            }while(1 > odg || odg > 4);
        switch(odg){
    case 1:
        sastojci=fopen(barkod,"a+");
        scanf("%s", unos);
        fprintf(sastojci,unos);
        fprintf(sastojci,"\n");
        fclose(sastojci);
        break;
    case 2:
        sastojci=fopen(barkod,"r");
        temp=fopen("temp","w");
        char print[50], neprint[50];
        scanf("%s",neprint);
        fscanf(sastojci,"%s",print);
        while(feof(sastojci)==0){
            for(i=0;!(neprint[i]=='\0' && print[i]=='\0');i++){
                if(neprint[i]!=print[i]){
                    fprintf(temp,print);
                    fprintf(temp,"\n");
                    break;
                }
            }
            fscanf(sastojci,"%s",print);
        }
        fclose(temp);
        fclose(sastojci);
        remove(barkod);
        rename("temp",barkod);
        break;
    case 3:
        prikazisastojke(barkod);
        break;
    case 4:
        return;
        break;
        }
    }
}

void prikazi(){
    FILE* fp;
    fp=fopen("artikli.txt", "r");
    char naziv[50], barkod[13];
    int tip;
    fscanf(fp,"%s %s %i", naziv, barkod, &tip);
    while(feof(fp)==0){
    printf("Naziv: %s\n",naziv);
    printf("Barkod: %s\n",barkod);
    printf("Tip: %i\n",tip);
    if(tip==0){
        printf("Sastojci:\n");
        prikazisastojke(barkod);
    }
    printf("\n");
    fscanf(fp,"%s %s %i", naziv, barkod, &tip);
    }
    fclose(fp);
}

void prikazisastojke(char* barkod){
    FILE* ps;
    ps=fopen(barkod,"r");
    char izlaz[50];
    fscanf(ps,"%s",izlaz);
    while(feof(ps)==0){
    printf("%s\n",izlaz);
    fscanf(ps,"%s",izlaz);
    }
    fclose(ps);
}

void obrisiartikal(char* barkod){
    FILE* f1;
    FILE* f2;
    remove(barkod);
    f1=fopen("artikli.txt","r");
    f2=fopen("temp","w");
    int i;
    char dobarkod[13], naziv[50], gotov;
    fscanf(f1,"%s %s %c", naziv, dobarkod, &gotov);
    while(!feof(f1)){
            for(i=0;i<12;i++){
                if(barkod[i]!=dobarkod[i]){
                    fprintf(f2,"%s\n%s\n%c\n\n", naziv, dobarkod, gotov);
                    break;
                }
            }
            fscanf(f1,"%s %s %c",naziv, dobarkod, &gotov);
    }
    fclose(f1);
    fclose(f2);
    remove("artikli.txt");
    rename("temp","artikli.txt");
}

void cenovnik(){
    FILE* cenovnik;
    FILE* temp;
    char* barkod;
    barkod=(char*)malloc(sizeof(char)*13);
    char unos[50], datum[11], bar[13];
    int dan=-1, mesec=-1, godina=-1;
    int i, odg, err;
    while(1){
        odg=0;
        err=0;
        printf("1. Unesi artikal\n");
        printf("2. Obrisi artikal\n");
        printf("3. Prikazi cenovnik\n");
        printf("4. Kraj promene cenovnika\n");
        do{
            if(err==1)
                printf("Pokusajte ponovo\n");
            else
                err=1;
                scanf("%i", &odg);
            }while(1 > odg || odg > 4);
        switch(odg){
    case 1:
        cenovnik=fopen("cenovnik.txt","a+");
        printf("Barkod: ");
        scanf("%s", barkod);
        popravibarkod(barkod);
        if(dalipostojibarkod(barkod)==0){
        printf("Barkod ne postoji\n");
            break;
        }
        fprintf(cenovnik,barkod);
        fprintf(cenovnik,"\n");

        printf("Datum: ");
        scanf("%i/%i/%i", &dan, &mesec, &godina);
        while(dan>31 || mesec>12 || godina<2019){
        printf("Pogresan datum\n");
        scanf("%i/%i/%i", &dan, &mesec, &godina);
        }
        fprintf(cenovnik,"%i/%i/%i\n", dan, mesec, godina);

        printf("Cena: ");
        scanf("%s", unos);
        fprintf(cenovnik,unos);
        fprintf(cenovnik,"\n\n");

        fclose(cenovnik);
        break;
    case 2:
        printf("Barkod: ");
        scanf("%s", barkod);
        popravibarkod(barkod);
        cenovnik=fopen("cenovnik.txt","r");
        temp=fopen("temp","w");
        fscanf(cenovnik,"%s %s %s", bar, datum, unos);
        while(!feof(cenovnik)){
                for(i=0;i<12;i++){
                    if(barkod[i]!=bar[i]){
                        fprintf(temp,"%s\n%s\n%s\n\n", bar, datum, unos);
                        break;
                    }
                }
                fscanf(cenovnik,"%s %s %s", bar, datum, unos);
        }

        fclose(cenovnik);
        fclose(temp);
        remove("cenovnik.txt");
        rename("temp","cenovnik.txt");
        break;
    case 3:
        cenovnik=fopen("cenovnik.txt", "r");
        fscanf(cenovnik,"%s %s %s", barkod, datum, unos);
        while(!feof(cenovnik)){
        printf("Barkod: %s\n",barkod);
        printf("Datum: %s\n",datum);
        printf("Cena: %s\n\n",unos);
        fscanf(cenovnik,"%s %s %s", barkod, datum, unos);
        }
        fclose(cenovnik);
        break;
    case 4:
        free(barkod);
        return;
        break;
        }
    }
}

void popravibarkod(char* barkod){
    int i;
    for(i=0;i<12;i++){
        if(barkod[i]<'0' || barkod[i]>'9')
        barkod[i]='0';
    }
    barkod[12]='\0';

}

void izmeniartikal(char* barkod){
    FILE* f1;
    FILE* f2;
    char bar[13], naziv[50], novinaziv[50], gotov;
    int odg=0, err=0, i, j;
        printf("1. Promeni naziv\n");
        printf("2. Promeni sastojke\n");
        do{
            if(err==1)
                printf("Pokusajte ponovo\n");
            else
                err=1;
                scanf("%i", &odg);
            }while(1 > odg || odg > 2);
        switch(odg){
        case 1:

            printf("Novi naziv: ");
            scanf("%s", novinaziv);
            f1=fopen("artikli.txt","r");
            f2=fopen("temp","w");
            fscanf(f1,"%s %s %c", naziv, bar, &gotov);

            while(!feof(f1)){
            j=0;
            for(i=0;i<12;i++){
                if(barkod[i]==bar[i])
                j++;
            }
                if(j==12)
                    fprintf(f2,"%s\n%s\n%c\n\n", novinaziv, bar, gotov);
                else
                    fprintf(f2,"%s\n%s\n%c\n\n", naziv, bar, gotov);


            fscanf(f1,"%s %s %c", naziv, bar, &gotov);
            }

            fclose(f1);
            fclose(f2);
            remove("artikli.txt");
            rename("temp","artikli.txt");
            break;
        case 2:
            sastojci(barkod);
            break;
        }
}

int dalipostojibarkod(char* barkod){
FILE* b;
int i, j, tip;
char naziv[50], bar[13];
b=fopen("artikli.txt","r");
fscanf(b,"%s %s %i", naziv, bar, &tip);
while(!feof(b)){
        j=0;
    for(i=0;i<12;i++){
        if(barkod[i]==bar[i])
            j++;
    }
    if(j==12){
        fclose(b);
        return 1;
    }
fscanf(b,"%s %s %i", naziv, bar, &tip);
}
fclose(b);
return 0;
}

void nadjiartikal(){
int odg=0, err=0;
        FILE* f1;
        f1=fopen("artikli.txt","r");
        int i, j, gotov, no=1;
        char bar[13], naziv[50], unos[50];
        char* barkod;
        barkod=(char*)malloc(sizeof(char)*13);
        printf("1. Po barkodu\n");
        printf("2. Po nazivu\n");
        do{
            if(err==1)
                printf("Pokusajte ponovo\n");
            else
                err=1;
                scanf("%i", &odg);
            }while(1 > odg || odg > 2);

        switch(odg){
        case 1:
        printf("Barkod: ");
        scanf("%s", barkod);
        popravibarkod(barkod);
        if(dalipostojibarkod(barkod)==0){
            printf("Barkod nije pronadjen\n");
            break;
        }

        fscanf(f1,"%s %s %i", naziv, bar, &gotov);
        while(!feof(f1)){
            j=0;
            for(i=0;i<12;i++){
                if(barkod[i]==bar[i])
                j++;
            }
                if(j==12){
                    printf("Naziv: %s\n",naziv);
                    printf("Tip: %i\n",gotov);
                        if(gotov==0){
                            printf("Sastojci:\n");
                            prikazisastojke(barkod);
                        }
                }
            fscanf(f1,"%s %s %i", naziv, bar, &gotov);
        }
            break;
        case 2:
            printf("Naziv: ");
            scanf("%s", unos);

            fscanf(f1,"%s %s %i", naziv, bar, &gotov);

            while(!feof(f1)){
                for(i=0;!(unos[i]=='\0' && naziv[i]=='\0');i++){
                    if(unos[i]!=naziv[i]){
                        no=0;
                        break;
                    }
                }
                if(no==1){
                        printf("Barkod: %s\n",bar);
                        printf("Tip: %i\n",gotov);
                        if(gotov==0){
                            printf("Sastojci:\n");
                            prikazisastojke(bar);
                    }
                }
                fscanf(f1,"%s %s %i", naziv, bar, &gotov);
                no=1;
            }
            break;
        }
        fclose(f1);
        free(barkod);
}

int main(){
    char* barkod;
    barkod=(char*)malloc(sizeof(char)*13);
    while(1){
        switch(meni()){
            case 1:
                dodajartikal();
                break;
            case 2:
                prikazi();
                break;
            case 3:
                nadjiartikal();
                break;
            case 4:
                printf("Barkod: ");
                scanf("%s", barkod);
                popravibarkod(barkod);
                if(dalipostojibarkod(barkod)==0){
                    printf("Barkod ne postoji\n");
                    break;
                }
                izmeniartikal(barkod);
                break;
            case 5:
                printf("Barkod: ");
                scanf("%s", barkod);
                popravibarkod(barkod);
                if(dalipostojibarkod(barkod)==0){
                    printf("Barkod ne postoji\n");
                    break;
                }
                obrisiartikal(barkod);
                break;
            case 6:
                cenovnik();
                break;
            case 7:
                free(barkod);
                return 0;
                break;
        }
    }
}
