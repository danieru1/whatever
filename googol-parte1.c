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
int divide(int short a[], int tamA, int short b[], int tamB, int resto);

/*Copia o vetor b para o vetor a*/
int copia(int short a[], int short b[], int tamB);

void inverte(int short a[], int tamA);

int maior(int short a[], int tamA, int short b[],int tamB); 
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
        if(operacao == '/')
            tamR = divide(a,tamA,b,tamB,0);
        if(operacao == '%')
            tamR = divide(a,tamA,b,tamB,1);
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
int divide(int short a[], int tamA, int short b[], int tamB, int resto){
    int tamC=0,i,negativo=0,j=0,k=0,w=0,l=0,tam,tamAux,digito=0,flag,ordem=0,tamO,exato=0,tamExato=0;
    int short cop[MAX_TAM];
    int short res[MAX_TAM];
    int short aux[MAX_TAM];
    int short dividendo[MAX_TAM];
    int short produto[MAX_TAM];
    int short aux2[MAX_TAM];
    zeraVetor(res);
    tamC = copia(cop,a,tamA);
    
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

    if(b[tamB-1]==1 && tamB==1){
        return tamA;
    }
    if(a[tamA-1]==0) /*Casos 0/b*/
        return 1;
    if(maior(b,tamB,a,tamA)==1){ /*Casos b>a (a/b=0)*/
        zeraVetor(a);
        return 1;
    }
    if(maior(b,tamB,a,tamA) == -1){ /*Casos a=b*/
        zeraVetor(a);
        a[0]=1;
        return 1;
    }

    for(j=0;j<tamB;j++){ /*Chuta o primeiro 'pedaço' a ser dividido e coloca no dividendo*/
        dividendo[tamB-1-j]=a[tamA-1-j]; 
    }
    tam=tamB;

    if((maior(b,tamB,dividendo,tam)) ==1){ /*Caso esse pedaço seja menor que o divisor*/
        inverte(dividendo,tam);       /*pega mais um digito*/
        dividendo[j]=a[tamA-1-j];
        tam++;
        inverte(dividendo,tam);
        ordem--;
    }

    for(i=tam;i<=tamA;i++){
        tamAux = copia(aux,b,tamB);
        /*printf("geral=\n");
        imprime(dividendo,tam);
        */
        /*Verifica quantas vezes o divisor 'cabe' dentro do pedaço do dividendo.
          Basicamente acha um digito da divisão.*/
        for(j=1;j<11;j++){  
            if(((flag = (maior(aux,tamAux,dividendo,tam))) !=0)){
                if(flag==1)
                    digito=j-1;
                if (flag==-1)
                    digito=j;
                
                break;
            }
            tamAux =soma(aux,tamAux,b,tamB);
        }
        /*Subtrai o resultado parcial do divendo parcial*/
        tamAux = copia(aux,b,tamB);
        criaNumeroInt(digito,produto);
        tamAux = multiplica(aux,tamAux,produto,1);
        tam = subtrai(dividendo,tam,aux,tamAux);

        /*Coloca o digito resultante no vetor resultado*/
        //printf("digito = %d\n",digito);
        res[k] = digito;
        k++;
        
        /*printf("dividendo=");
        imprime(dividendo,tam);*/
        /*Traz o proximo digito para o dividendo*/
        if(i<tamA){
            for(j=tam-1;j>-1;j--){
            dividendo[j+1] = dividendo[j];
            }
            tam++;
            dividendo[0] = a[tamA-1-i];
            //imprime(dividendo,tam);
        }
        if(tam==2 && dividendo[1]==0)
            tam--;
    }
    inverte(res,k);
    copia(a,res,k);

    if(negativo)
        a[k-1]=-a[k-1];
    if(resto)
        k = copia(a,dividendo,tam);
    return k;
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

/*retorna 1 caso 'a' for maior que 'b' e 0 caso contrário*/
int maior(int short a[], int tamA, int short b[],int tamB) {
    int i;
    if(a[tamA-1] <0 && b[tamB-1] >0)
        return 0;
    if(a[tamA-1] >0 && b[tamB-1] <0)
        return 0;
    if(tamA>tamB)
        return 1;
    if(tamB>tamA)
        return 0;

    for(i=tamA-1;i>-1;i--){
        if(a[i]>b[i])
            return 1;
        if(a[i]<b[i])
            return 0;
    }
return -1;
}

void inverte(int short a[], int tamA){
    int i;
    int short aux[tamA];

    for(i=0;i<tamA;i++)
        aux[i] = a[tamA-i-1];
    copia(a,aux,tamA);
}
