#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
// função para calcular pontencia e modulo do big number.(a ^ e % n).
long calcular(long long a, long long e, long long n){
    long long A = a, P = 1, E = e;
    while(1){
        if(E == 0)
            return P;
        else if(E%2 != 0){			
            P = (A * P)%n;
            E = 
			(E-1)/2;
        }
        else{
            E = E/2;
        }
        A = (A*A)%n;
    }
}

// Função mdc
int mdc(int num1, int num2) {

    int resto;

    do {
        resto = num1 % num2;

        num1 = num2;
        num2 = resto;

    } while (resto != 0);

    return num1;
}
	
// função para sorteio.
    int sorteioDePrimo(int limite){
        // declaração de variavel com valores primos para sortear.
        int primos[172] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021};
        // processamento do sorteio.
        int auxiliar = (rand() % 172);
        int numeroPrimo = primos[auxiliar];
        
        while(numeroPrimo >= limite) {
            auxiliar = (rand() % 172);
            numeroPrimo = primos[auxiliar];
        }
        return numeroPrimo;
	}
	
void criarChaves(){
    // declaração de variaveis.
    int chavePrivada, chavePublica, tamanhoDoConjunto, euller, contador;
    int numeroPrimoUm, numeroPrimoDois;
    
    
    // processamento de criação das chaves.
 	numeroPrimoUm = sorteioDePrimo(1024);
 	numeroPrimoDois = sorteioDePrimo(1024);
    tamanhoDoConjunto = numeroPrimoUm * numeroPrimoDois;
   	euller=(numeroPrimoUm -1)*(numeroPrimoDois-1);
    chavePublica = sorteioDePrimo(euller);
	chavePrivada=1;
	while(((chavePrivada*chavePublica)%euller)!=1){
		chavePrivada++;
	}
	printf("Tamanho do conjunto: %d.\n", tamanhoDoConjunto);
    printf("Chave Pública: %d.\n", chavePublica);
    printf("Chave Privada: %d.\n", chavePrivada);
}
// função para descriptografar e criptografar
void criptografar(int op) {
    // declaração de variáveis.
    int chave, tamanhoDoConjunto, retornoMensagem[1024];
    int contador;
    char mensagem[1024];

    // processamento da entrada de chaves para opcão escolhida.
    printf("Digite a chave pública: ");
    scanf("%d", &chave);
    printf("Digite o tamanho do conjunto: ");
    scanf("%d", &tamanhoDoConjunto);
    printf("\n");

    // entrada da mensagem.
    printf("Digite a mensagem(max 1024 caracteres): \n\n");
    printf("---> ");
    scanf( "\n");
    fgets(mensagem, 1024, stdin);

    // processamento e saída da encriptação ou decriptação da mensagem.
    printf("\n\n");
    printf("Mensagem com a chave %d e %d!\n", chave, tamanhoDoConjunto);
    printf("---> ");
    for(contador = 0; mensagem[contador] != '\0'; contador++) {
        retornoMensagem[contador] = calcular(mensagem[contador], chave, tamanhoDoConjunto);
        printf("%d&", retornoMensagem[contador]);
    }
}
void decriptar(int op) {
    // declaração de variáveis.
    int chave, tamanhoDoConjunto, retornoMensagem[4096];
    int contador;
    int contadorRetorno = 0;
    char mensagem[4096];

    // processamento da entrada de chaves para opcão escolhida.
    printf("Digite a chave privada: ");
    scanf("%d", &chave);
    printf("Digite o tamanho do conjunto: ");
    scanf("%d", &tamanhoDoConjunto);
    printf("\n");

    // entrada da mensagem.
    printf("Digite a mensagem encripritada(max 4096 caracteres): \n\n");
    printf("---> ");
    scanf( "\n");
    fgets(mensagem, 4096, stdin);
    
    // processamento e saída da encriptação ou decriptação da mensagem.
    printf("\n\n");
    printf("Mensagem com a chave %d e %d!\n", chave, tamanhoDoConjunto);
    printf("---> ");
    int auxiliar = 0;
    for(contador = 0; mensagem[contador] != '\0'; contador++) {
        if(mensagem[contador] == '&') {
            retornoMensagem[contador] = calcular(auxiliar, chave, tamanhoDoConjunto);
            auxiliar = 0;
            printf("%c", retornoMensagem[contador]);
        } else if(auxiliar > 0) {
            auxiliar = (auxiliar * 10) + (mensagem[contador] - 48); // Na tabela ASCII números começam apartir do 48.
        } else {
            auxiliar = (mensagem[contador] - 48); // Na tabela ASCII números começam apartir do 48.
        }
        
    }
}
int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"portuguese");
    srand((unsigned)time(NULL));

    int opcao=5;
    char continuar;
    
    while(opcao != 0){
	    // cabeçalho.
	    printf("***********************************************\n");
	    printf("**                                           **\n");
	    printf("**              CRIPTOGRAFIA RSA             **\n");
	    printf("**                                           **\n");
	    printf("**  número da opcão:                         **\n");
	    printf("**                                           **\n");
	    printf("**  1 - Criar Chaves     2 - Criptografar    **\n");
	    printf("**  3 - Descriptografar  0 - Fechar          **\n");
	    printf("**                                           **\n");
	    printf("***********************************************\n\n");
	    printf("Digite a opcão: ");
	    scanf("%d", &opcao);
	    // valida opcão.
	    while(opcao < 0 || opcao > 3) {
	        printf("Digite uma opcão válida!\n");
	        printf("Digite a opcão: ");
	        scanf("%d", &opcao);
	    }
	    // encaminha entrada de opcão.
	    if(opcao == 1) {
	        criarChaves();
	        scanf("%c", &continuar);
	    }else if(opcao == 2) {
	        criptografar(opcao);
	    }else if(opcao == 3) {
	        decriptar(opcao);
	    }else if(opcao == 0){
	    	break;
		}
	    
	    printf("\n\n\nDeseja Continuar? (s/n): ");
	    scanf("%c",&continuar);
	    if((continuar == 's') || (continuar == 'S')){
	    	system("cls");	
		}else{
			opcao = 0;
	    }
	}
	
    return 0;
}
