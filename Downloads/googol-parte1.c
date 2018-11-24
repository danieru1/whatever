/*Autor: Daniel Espindola da Silva
  RA: 11201720556 (Único integrante)
  Projeto Googol. */

#include <stdio.h>
#define MAX_TAM 2000

/*Recebe um vetor de inteiros de tamanho 2000
e preenche ele com zeros*/
void zeraVetor(int short num[]);

/*Recebe um inteiro e escreve os dígitos de trás pra frente em um vetor*/
int criaNumeroInt(int n, int short num[]);

/*Recebe uma sequência de números numa string
e escreve os dígitos de trás pra frente em um vetor*/
int criaNumeroStr(char str[], int short num[]);

/*imprime o vetor de números de trás pra frente*/
void imprime(int short num[], int tam);

/*recebe 2 vetores de inteiros e seus respectivos tamanhos
  soma o numero representado por eles colocando o resultado
  no vetor a e devolve o tamanho do vetor resultante.*/
int soma(int short a[], int tamA, int short b[], int tamB);

/*Mesma coisa que o 'int soma' só que para subtração*/
int subtrai(int short a[], int tamA, int short b[], int tamB);

/*Multiplica 'a' por 'b' e guarda o resultado (a*b) em'a'
  'b' não é modificado.
  Devolve o número de dígitos do resultado. */
int multiplica(int short a[], int tamA, int short b[], int tamB);

/*Divide 'a' por 'b' e guarda o resultado (a/b) em 'a'
  'b' não é modificado
  Devolve o número de dígitos como resultado.*/
int divide(int short a[], int tamA, int short b[], int tamB);

/*Copia o vetor b para o vetor a*/
int copia(int short a[], int short b[], int tamB);

int main() {
    char str [MAX_TAM];
    int short a [MAX_TAM];
    int short b [MAX_TAM];
    int tamA,tamB,tamR;
    char operacao;
    
    zeraVetor(a);
    zeraVetor(b);

    scanf("%s",str);
    tamA = criaNumeroStr(str, a);

    while(str[0] != 'F'){
        scanf("%s",str);
        tamB = criaNumeroStr(str,b);
        
        getchar(); /*Pega o \n*/
        operacao = getchar(); /*Pega o operador*/
        
        if(operacao == '+')
            tamR = soma(a,tamA,b,tamB);
        if(operacao == '-')
            tamR = subtrai(a,tamA,b,tamB);
        if(operacao == '*')
            tamR = multiplica(a,tamA,b,tamB);
        
        imprime(a,tamR);
        
        zeraVetor(a);
        zeraVetor(b);

        scanf("%s",str);
        tamA = criaNumeroStr(str,a);
    }

return 0;
}


int criaNumeroStr(char str[], int short num[]){
    int i=0,j=0,k=0,tam=0,tamFinal,negativo=0;
    /*Pega o tamanho da string*/
    while(str[k]!='\0'){
        k++;
    }
    tam=k;

    /*Resolve os casos de numero negativo*/
    if(str[0] == '-'){
        negativo = 1;
        tam--;        
        num[tam-1] = -(str[1]-'0');
        j=2;
        i=1;
    }
    while(str[j] != '\0') {
        num[tam-1-i] = str[j]-'0'; 
        i++;
        j++;
    }
    tamFinal = i;

    /*Ajusta o tamanho caso o input tenha zeros à esquerda (ex: 0000050 em vez de 50)*/
    for(j=0;num[i-1-j]==0 && tamFinal>1;j++)
        tamFinal--;
    /*Ajusta o sinal caso o número negativo tenha sido passado com zeros à esquerda*/
    if(negativo && num[tamFinal-1]>0)
        num[tamFinal-1]= -num[tamFinal-1];

    return tamFinal;
}

void imprime(int short num[], int tam){
    int i=0;
    for(i=0;i<tam;i++)
        printf("%d",num[tam-i-1]);
    printf("\n");
}

int criaNumeroInt(int n, int short num[]){
    int i,j=0,digitos=1,negativo=0;
    /*Resolve os casos negativos*/
    if(n<0){
        n=-n;
        negativo=1;
    }
    /*Conta os digitos do n*/
    for(i=10;(n/i)!=0;i*=10) 
        digitos++;
    while(digitos) {
        num[j] = n%10;
        n=n/10;
        digitos--;
        j++;
    }
    if(negativo)
        num[j-1] = -num[j-1];
    return j;
}

int soma(int short a[], int tamA, int short b[], int tamB){
    int i,tam,aux,tamFinal=0;
    tam = (tamA>tamB)?tamA:tamB;
    
    if(a[tamA-1]<0 && b[tamB-1]>=0){         
        a[tamA-1] = -a[tamA-1];              /*Casos em que foi chamada uma soma com um dos*/
        tamFinal = subtrai(b,tamB,a,tamA);   /*operandos negativo. Nesse caso a soma*/
        copia(a,b,tamB);                     /*é convertida em uma subtração*/
        return tamFinal;                     /*Ex: (-2)+10 -> 10-2*/
    }
    if (b[tamB-1]<0 && a[tamA-1]>=0){
        b[tamB-1] = -b[tamB-1];
        tamFinal = subtrai(a,tamA,b,tamB);
        return tamFinal;
    }

    if(a[tamA-1]<0 && b[tamB-1]<0){
        a[tamA-1] = -a[tamA-1];             /*Casos de soma de 2 números negativos.*/
        b[tamB-1] = -b[tamB-1];             /*É feita a soma sem sinal e adicionado*/
        tamFinal = soma(a,tamA,b,tamB);     /*o sinal negativo ao resultado*/
        a[tamFinal-1] = -a[tamFinal-1];
        return tamFinal;
    }

    for(i=0;i<tam;i++) {
        aux = a[i] + b[i];
        
        if(aux>9){        /*Casos que a soma de 2 digitos gera um número com mais de 1 digito*/
            if(i==(tam-1))/*Portanto aumenta em uma casa o tamanho do resultado*/
                tamFinal++;
            a[i+1]++;
            aux=aux%10;       
        }

        a[i] = aux;
    }
    tamFinal+=i;

    return tamFinal;
}

int subtrai(int short a[], int tamA, int short b[], int tamB){
    int i,j,k, tam=tamA, aux, tamVa, tamFinal=0,negativo=0;
    int short vAux[MAX_TAM];
    char maior;
    
    if(a[tamA-1]<0 && b[tamB-1]>=0){ /*Casos (-a) - b transformados em -(a+b)*/
        a[tamA-1] = -a[tamA-1];      /*Remove o sinal de A*/
        tamA = soma(a,tamA,b,tamB);  /*Soma a e b*/
        a[tamA-1] = -a[tamA-1];      /*Coloca o sinal negativo no resultado.*/
        return tamA;
    }
    if(a[tamA-1]>=0 && b[tamB-1]<0){ /*Casos a - (-b) transformados em a+b*/
        b[tamB-1] = -b[tamB-1];      
        tamA = soma(a,tamA,b,tamB);
        return tamA;
    } 
    if(a[tamA-1]<0 && b[tamB-1]<0){  /*Casos (-a)-(-b) transformados em b-a*/
        b[tamB-1] = -b[tamB-1];
        a[tamA-1] = -a[tamA-1];
        tamB = subtrai(b,tamB,a,tamA);
        tamA = copia(a,b,tamB);
        return tamA;
    }
    /*Os ifs a seguir tem o intuito de resolver os casos a<b*/ 
    /*Caso b>a troca 'b' por 'a' e indica que o resultado será negativo*/
    if(tamB>tamA) {
        tam=tamB;
        zeraVetor(vAux);

        tamVa = copia(vAux,a,tamA);
        tamA = copia(a,b,tamB);
        tamB = copia(b, vAux, tamVa);
        negativo=1;
    }

    else if(tamB==tamA) {
        for(k=tamA-1;k>=0;k--){
            if(a[k] > b[k]){
                maior = 'a';
                break;
            }
            if(a[k] < b[k]){
                maior = 'b';
                break;
            }
        }
        
        if(maior=='b'){
            zeraVetor(vAux);

            tamVa = copia(vAux,a,tamA);
            tamA = copia(a,b,tamB);
            tamB = copia(b, vAux, tamVa);

            negativo=1;
        }  
    }

    for(i=0;i<tam;i++) {
        if(a[i] < b[i]) {
            a[i+1]--;
            a[i]+=10;
        }
        aux = a[i] - b[i];
        a[i] = aux;
    }

    tamFinal = i; 
    
    /*Resolve os casos que a subtração gerou um resultado 
    com menos digitos que o numero 'a'.
    (Evita por exemplo: 800-750 = 050 em vez de 50)*/
    for(j=0;(a[i-1-j]==0) && tamFinal>1;j++)
        tamFinal--;
    if(negativo)
        a[tamFinal-1] = -a[tamFinal-1];

    return tamFinal;
}

int multiplica(int short a[], int tamA, int short b[], int tamB){
    int i,j=0,k=0,negativo=0;
    short int vAux[MAX_TAM];
    short int n[MAX_TAM];
    int tamVa,tamN=0,res=0,resto=0;
    zeraVetor(n);
    
    if(a[tamA-1]<0 && b[tamB-1]<0){ /*os if's encadeados a seguir resolve os casos*/
        a[tamA-1]=-a[tamA-1];       /*nos quais pelo menos um dos operandos é negativo*/
        b[tamB-1]=-b[tamB-1];
    }
    else if(a[tamA-1]<0){
        a[tamA-1]=-a[tamA-1];
        negativo=1;
    }
    else if(b[tamB-1]<0){
        b[tamB-1]=-b[tamB-1];
        negativo=1;
    }

    if((a[0]==0 && tamA==1) || (b[0]==0 && tamB==1)){
        zeraVetor(a);   /*Casos a*0 ou 0*b*/
        return 1;
    }

    if(tamB>tamA) { /*Troca os vetores quando é uma ordem de grandeza maior que 'a'*/
        zeraVetor(vAux);
        tamVa = copia(vAux,a,tamA);
        tamA = copia(a,b,tamB);
        tamB = copia(b, vAux, tamVa);
    }
    zeraVetor(vAux);
    tamVa=1;
    
    for(j=0;j<tamB;j++){
        tamN=0;
        for(i=0;i<tamA;i++){
            res = b[j]*a[i]; /*Encontra o resultado da multiplicação dos digitos*/
            n[i+k] = (res+resto)%10;
            resto = (res+resto)/10;
            tamN++;
        }
        if(resto!=0){
            n[i+k] = resto;
            tamN++;
            resto=0;
        }
        tamVa = soma(vAux,tamVa,n,tamN+k);
        zeraVetor(n);
        k++;
    }
    if(negativo)
        vAux[tamVa-1] = -vAux[tamVa-1];

    copia(a,vAux,tamVa);
    return tamVa;
}

int copia(int short a[], int short b[], int tamB){
    int i;
    for(i=0;i<MAX_TAM;i++)
        a[i] = b[i];
    return tamB;
}

void zeraVetor(int short num[]){
    int i;
    for(i=0;i<(MAX_TAM);i++)
        num[i] = 0;
}
















































