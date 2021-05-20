/*

Esse checker lê as intruções do robo no mesmo formato esperado da saída descrita no enunciado:

K
Comando 1
Comando 2
...
Comando K

Ou seja, para usá-lo, use exatamente a saída do seu código como entrada desse programa (sem informar o N ou outros limites)

O código vai simular e imprimir, passo e passo, os movimentos do robô, e informar pela função WA se algum erro ecorrer


PARA A SUBTASK 2, DESCOMENTAR A LINHA 53

*/


#include <cstdio>
#include <cstdlib>
#include <string>
#define ll long long
#define debug
#define MAX_STEPS 10000000
using namespace std;

int v[20200];

int dir[1010][1010];
int new_state[1010][1010];
int new_lamp[1010][1010];

void WA(string s=""){
	printf("%s\n",s.c_str());
	exit(0);
}

void AC(int posi,int k,int s){
	printf("robo finalizou na posicao %d com %d instrucoes em %d passos\n",posi,k,s);
	exit(0);
}

int main(int argc,char**argv){

	auto vet = v + 10100;

	int k;
	scanf("%d",&k);

	// adicionar manualmente condição da Subtask 2
	 // vet[250] = 1;

	for(int i=0;i<k;i++){
		int si = 0,li = 0,mv = 0,sf = 0,lf = 0;
		// si = estado inicial
		// li = numero escrito na lampada inicial
		// sf = estado novo
		// lf = numero novo da lampada
		scanf("%d%d%d",&si,&li,&mv);
		// mv = +- 1 -> andar
		// mv = 0 -> acendar a lampada, podem ter varios comandos desse tipo, desde que os (si,li) não repitam
		if(mv != 0) {
			scanf("%d%d",&sf,&lf);
		}
		// os estados nas instruções devem estar entre 0 e 1.000

		if(si > 1000 || sf > 1000 || si < 0 || sf < 0) WA("estado do robo invalido");
		if(li > 1000 || lf > 1000 || li < 0 || lf < 0) WA("estado da lampada invalido");

		if(dir[li][si]) WA("instrucao repetida\n");
		if(abs(mv) > 1) WA("valor de 'move' invalido");

		if(mv == 0)
			mv = 2;

		dir[li][si] = mv; // 1 = andar pra direira, -1 = andar pra esquerda, 2 = finalizar

		
		debug("dir %d %d = %d\n",li,si,mv);
		new_state[li][si] = sf;
		new_lamp[li][si] = lf;
		
		
	}


	int steps = 0;
	int posi = 0;
	int state = 0;
	
	while(steps < MAX_STEPS){

		steps++;
		printf("Passo %d: posicao = %d, estado = %d, numero escrito = %d\n",steps,posi,state,vet[posi]);


		if(dir[vet[posi]][state] == 0) WA("robo nao achou comando para fazer");
		if(dir[vet[posi]][state] == 2) AC(posi,k,steps);

		int mv = dir[vet[posi]][state];
		int sf = new_state[vet[posi]][state];
		int lf = new_lamp[vet[posi]][state];

		vet[posi] = lf;
		posi += mv;
		state = sf;

		if(abs(posi) > 10000) WA("o robo nunca pode se distanciar mais que 10.000 casas da origem");

	}

	WA("excedeu limite de passos");
	
	
	
}
