#include <stdio.h>
#include <stdlib.h>

struct Paran{
    int *niz;
    int duzina;
};

struct Neparan{
    int *niz;
    int duzina;
};

int main()
{
    int i, temp=-1;
    char string[50];
    scanf("%s", string);
    struct Paran *p = malloc(sizeof(struct Paran));
    struct Neparan *n = malloc(sizeof(struct Neparan));
    p[0].duzina=0;
    n[0].duzina=0;
    ///prvi for za brojanje memorije
    for(i=0;;i++){
        if((string[i]>='0')&&(string[i]<='9')){
            if(temp==-1){
                temp=0;
            }
            temp*=10;
            temp+=string[i]-'0';
        }
        else if(temp!=-1){
            if(temp%2==0){
                p[0].duzina+=1;
            }
            else{
                n[0].duzina+=1;
            }
            temp=-1;
        }
        if(string[i]=='\0'){
            break;
        }
    }
    p[0].niz = malloc(sizeof(int) * p[0].duzina);
    n[0].niz = malloc(sizeof(int) * n[0].duzina);
    p[0].duzina=0;
    n[0].duzina=0;
    ///drugi for za popunjavanje niza
    for(i=0;;i++){
        if((string[i]>='0')&&(string[i]<='9')){
            if(temp==-1){
                temp=0;
            }
            temp*=10;
            temp+=string[i]-'0';
        }
        else if(temp!=-1){
            if(temp%2==0){
                p[0].niz[p[0].duzina]=temp;
                p[0].duzina+=1;
            }
            else{
                n[0].niz[n[0].duzina]=temp;
                n[0].duzina+=1;
            }
            temp=-1;
        }
        if(string[i]=='\0'){
            break;
        }
    }
    printf("\nParni brojevi: ");
    for(i=0;i<p[0].duzina;i++){
        printf("%i ",p[0].niz[i]);
    }
    printf("(%i)", p[0].duzina);
    printf("\nNeparni brojevi: ");
    for(i=0;i<n[0].duzina;i++){
        printf("%i ",n[0].niz[i]);
    }
    printf("(%i)", n[0].duzina);
    free(p);
    free(n);
    return 0;
}
