/*Programa que simula um jogo de criação de cabras
    Intruções:

    (~) = Lama;
    (t) = Trigo broto;
    (T) = Trigo Crescido;
    (u) = Cabrito;
    (U) = Cabra sem chifres;
    (Ü) = Cabra com chifres (na tabela ASCII, o U com trema = -102);
    (R) = Raposa;

    Fertilizar: Fertiliza um trigo broto em trigo crescido;
    Colher: Colhe um Trigo crescido, gera saldo de trigo;
    Ordenhar: Ordenha uma cabra sem chifres, gera saldo de leite e cabra fica com chifre;
    Alimentar: - Alimenta um bizerro para gerar uma cabra com chifres
               - Alimenta uma cabra com outra do lado para gerar um cabrito
    Mover: Caso cabra com chifre se mova para onde há raposa: raposa morre, gera saldo de osso, cabra perde chifre;
    Noite: Raposas se movem podendo matar cabras ou cabritos;

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int leite=1;
int osso=0;
int trigo=0;
int jogadas=1;
char campo[25][50];
//impressão
void imprime(){
    int i, j;
    printf("\n    00000000001111111111222222222233333333334444444444\n");
    printf("    01234567890123456789012345678901234567890123456789\n");
    for(i=0;i<25;i++){
        printf("[%2d]", i);
        for(j=0;j<50;j++){
            printf("%c", campo[i][j]);
        }
        printf("\n");
    }

}
//inicialização
void inicializa(){
    int i, j, l, c;
    //vazio
    for(i=0;i<50;i++){
        for(j=0;j<50;j++){
            campo[i][j]=' ';
        }
    }
    //3 lama 3-3
    for(i=0;i<3;i++){
        l=rand()%24;
        c=rand()%48;
        if((campo[l][c]==' ')&&(campo[l][c+1]==' ')&&(campo[l][c+2]==' ')&&(campo[l+1][c]==' ')&&(campo[l+1][c+1]==' ')&&(campo[l+1][c+2]==' ')){
        campo[l][c]='~';
        campo[l][c+1]='~';
        campo[l][c+2]='~';
        campo[l+1][c]='~';
        campo[l+1][c+1]='~';
        campo[l+1][c+2]='~';
        }else{i--;}
    }
    //3 lama 2-2-2
    for(i=0;i<3;i++){
        l=rand()%23;
        c=rand()%49;
        if((campo[l][c]==' ')&&(campo[l][c+1]==' ')&&(campo[l+1][c]==' ')&&(campo[l+1][c+1]==' ')&&(campo[l+2][c]==' ')&&(campo[l+2][c+1]==' ')){
            campo[l][c]='~';
            campo[l][c+1]='~';
            campo[l+1][c]='~';
            campo[l+1][c+1]='~';
            campo[l+2][c]='~';
            campo[l+2][c+1]='~';
        }else{i--;}
    }
    //5 trigo / 11 raposa / 5 cabra
    for(i=0;i<21;i++){
        l=rand()%25;
        c=rand()%50;
        if(campo[l][c]==' '){
            if(i<5){
                campo[l][c]='t';
            }
            if((i>=5)&&(i<16)){
                campo[l][c]='R';
            }
            if(i>=16){
                campo[l][c]=-102;
            }
        }else{i--;}
    }
}
//fertilizar trigo(t)
void fertilizar(){
    int l, c;
    if(osso>0){
        printf("Fertilizar trigo(t) [linha coluna]: ");
        scanf("%d %d", &l, &c);
        getchar();
         if((l>=0)&&(l<25)&&(c>=0)&&(c<50)){
            if(campo[l][c]=='t'){
                campo[l][c]='T';
                osso--;
                jogadas++;
            }else{
                printf("[Nao ha trigo(t) nessa coordenada!]\n");
            }
         }else{
             printf("[Coordenadas invalidas!]\n");
         }
    }else{
        printf("[Nao ha saldo de farinha de osso!]\n");
    }
}
//colher trigo(T)
void colher(){
    int l, c;
    printf("Colher trigo(T) [linha coluna]: ");
    scanf("%d %d", &l, &c);
    getchar();
        if((l>=0)&&(l<25)&&(c>=0)&&(c<50)){
            if(campo[l][c]=='T'){
                campo[l][c]=' ';
                trigo++;
                jogadas++;
            }else{
                printf("[Nao ha trigo(T) nessa coordenada!]\n");
            }
        }else{
            printf("[Coordenadas invalidas!]\n");
        }
}
//ordenhar cabra(U)
void ordenhar(){
    int l, c;
    printf("Ordenhar cabra sem chifre(U) [linha coluna]: ");
    scanf("%d %d", &l, &c);
    getchar();
        if((l>=0)&&(l<25)&&(c>=0)&&(c<50)){
            if(campo[l][c]=='U'){
                campo[l][c]=-102;
                leite++;
                jogadas++;
            }else{
                printf("[Nao ha cabra sem chifre(U) nessa coordenada!]\n");
            }
        }else{
            printf("[Coordenadas invalidas!]\n");
        }
}
//alimentar cabrita(u) ou cabra com chifre
void alimentar(){
    int l, c;
    printf("Alimentar cabrita(u) ou cabra com chifre(%c) [linha coluna]: ", -102);
    scanf("%d %d", &l, &c);
    getchar();
        if((l>=0)&&(l<25)&&(c>=0)&&(c<50)){
            if(campo[l][c]== -102){
                if(trigo>0){
                    if((campo[l][c+1]==-102)&&(campo[l][c+2]==' ')){
                        campo[l][c+2]='u';
                        trigo--;
                        jogadas++;
                    }else{
                        printf("[Nao ha cabra na direita ou lugar para gerar uma cabrita!]\n");
                    }
                }else{
                    printf("[Nao ha saldo de trigo!]\n");
                }
            }else{
                if(campo[l][c]!='u'){
                printf("[Nao ha cabra com chifre(%c) nessa coordenada!]\n", -102);
                }
            }
            if((campo[l][c]=='u')&&(campo[l][c]!=-102)){
                if(leite>0){
                    campo[l][c]=-102;
                    leite--;
                    jogadas++;
                }else{
                    printf("[Nao ha saldo de leite!]\n");
                }
            }else{
                if(campo[l][c]!=-102){
                printf("[Nao ha cabrita(u) nessa coordenada!]\n");
                }
            }
        }else{
            printf("[Coordenadas invalidas!]\n");
        }
}
//mover
void mover(){
    int l1, c1, l2, c2;
    printf("Mover cabra(U/%c) ou cabrito(u)\n", -102);
    printf("Origem [linha coluna]:");
    scanf("%d %d", &l1, &c1);
    getchar();
    if((l1>=0)&&(l1<25)&&(c1>=0)&&(c1<50)&&((campo[l1][c1]=='U')||(campo[l1][c1]==-102)||(campo[l1][c1]=='u'))){
        printf("Destino [linha coluna]:");
        scanf("%d %d", &l2, &c2);
        getchar();
        if((l2>=0)&&(l2<25)&&(c2>=0)&&(c2<50)&&((campo[l2][c2]=='R')||(campo[l2][c2]==' '))&&((l1!=l2)||(c1!=c2))&&(
           (abs(l1-l2)==1)||
           (abs(c1-c2)==1)
            )){
            if((campo[l1][c1]==-102)&&(campo[l2][c2]=='R')){
                campo[l2][c2]= 'U';
                campo[l1][c1]= ' ';
                osso++;
                jogadas++;
            }else{
                if(campo[l2][c2]==' '){
                    campo[l2][c2]= campo[l1][c1];
                    campo[l1][c1]=' ';
                    jogadas++;
                }
            }
        }else{
            printf("[Coordenadas ivalidas!]\n");
    }
    }else{
        printf("[Coordenadas ivalidas!]\n");
    }
}
void noite(){
    int i, j, l, c;
    jogadas=1;
    for(i=0;i<25;i++){
        for(j=0;j<50;j++){
            if(campo[i][j]=='R'){
                campo[i][j]=' ';
            }
        }
    }
    for(i=0;i<=11;i++){
        l=rand()%25;
        c=rand()%50;
        if((campo[l][c]==' ')||(campo[l][c]=='u')||(campo[l][c]=='U')||(campo[l][c]==-102)){
            campo[l][c]='R';
        }else{i--;}
    }
    for(i=0;i<25;i++){
        for(j=0;j<50;j++){
            if((campo[i][j]==' ')&&(rand()%1250==1)){
                campo[i][j]='t';
            }
            if((campo[i][j]=='U')&&(rand()%100>30)){
                campo[i][j]= -102;
            }
        }
    }
}
int main(int argc, char *argv){
    char op=' ';
    srand(time(NULL));

    inicializa();

    while(op!='s'){
        //funcao imprime
        imprime();
        printf("leite=%d farinha de osso=%d trigo=%d\n", leite, osso, trigo);
        printf("(f)ertilizar / (c)olher / (o)rdenhar / (a)limentar / (m)over / (n)oite / (s)air");
        printf("\n[Jogada %d] opcao:", jogadas);
        scanf("%c", &op);
        getchar();
        switch(op){
            case 'f' : //fertilizar trigo
                fertilizar();
                break;
            case 'c' : //colher trigo
                colher();
                break;
            case 'o' : //ordenhar cabra
                ordenhar();
                break;
            case 'a' : //alimentar cabrita ou cabra
                alimentar();
                break;
            case 'm' : //mover
                mover();
                break;
            case 'n' : //noite
                noite();
            case 's' :
                break;
            default:
                printf("\n[opcao invalida] \n");
        }
        if(jogadas>7){
            imprime();
            noite();
        }
    }
    return 0;
}
