#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//função para alocar o tabuleiro
void mtabuleiro(char ***mat) {
  
  int i;
  
  *mat = (char **)malloc(3*sizeof(char*));
  
  for (i = 0; i < 3; i++) {
    (*mat)[i] = (char*)malloc(3*sizeof(char));
  }
  
  return;
}


//função para imprimir o tabuleiro
void imprime(char **a) {
  
  printf(" %c|%c|%c\n--+-+--\n %c|%c|%c\n--+-+--\n %c|%c|%c\n", a[0][0], a[0][1], a[0][2], a[1][0], a[1][1], a[1][2], a[2][0], a[2][1], a[2][2]);
  
  return;
}


//função pro jogador escolher a jogada na versão 1, verificar se a jogada é válida ou se a casa está ocupada e retornar a escolha pra main
int casa1() {
  
  int escolha;
  
  printf("Escolha a casa em que quer jogar.\n");
  //verifica se a jogada escolhida é válida
  do {
    scanf("%d", &escolha);
    __fpurge(stdin);
    if (escolha < 1 || escolha > 9) {
      printf("Digite um número de 1 a 9 correspondente a casa que quer jogar.\n");
    }
  } while (escolha < 1 || escolha > 9);
  
  return(escolha);
}

//função pro jogador escolher a jogada na versão bônus, verificar se a jogada é válida ou se a casa está ocupada e retornar a escolha pra main
int casa2(char **tabuleiro) {
  
  int escolha, i, j;
  
  printf("\nEscolha a casa em que quer jogar.\n");
  //verifica se a jogada escolhida é válida
  do {
    scanf("%d", &escolha);
    __fpurge(stdin);
    if(escolha < 1 || escolha > 9){
      printf("Digite o número de 1 a 9 correspondente a casa que quer jogar.\n");
    }
  } while (escolha < 1 || escolha > 9);
  
  //como o tabuleiro vai de 1 até 9, devemos converter esse número para a linguagem matricial fazendo as operações abaixo
  i = (escolha - 1)/3;
  j = (escolha - 1)%3;
  
  //verifica se a casa está vazia, se estiver, coloca 'O' no lugar, caso contrário, chama a função novamente até o jogador fazer uma jogada válida
  if (tabuleiro[i][j] == ' ') {
    tabuleiro[i][j] = 'O';
  } else {
    printf("A casa já está ocupada.");
    escolha = casa2(tabuleiro);
  }

  return(escolha);
}


//função pro computador realizar a jogada na versão bônus baseando-se na escolha do oponente
void ia(char **tabuleiro, int escolha) {
  
  int i, j;
  
  //a estratégia é basicamente pegar a escolha do oponente e jogar sempre no lado oposto
  escolha = 10 - escolha;
  i = (escolha - 1)/3;
  j = (escolha - 1)%3;
  tabuleiro[i][j] = 'X';
  
  return;
}


//função pra verificar se o jogo bônus acabou
int perdeu(char **a) {
  
  int i, j, n[3][3], somal = 0, somac = 0, somadp = 0, somads = 0;
  
  //laço pra verificar como está o tabuleiro de char e criar um novo tabuleiro de int atribuindo os respectivos valores em suas casas, onde 'X' vale 1, 'O' vale 4 e vazio vale 0
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (a[i][j] == 'X') {
	n[i][j] = 1;
      }
      if (a[i][j] == 'O') {
	n[i][j] = 4;
      }
      if (a[i][j] == ' ') {
	n[i][j] = 0;
      }
    }
  }
  
  //depois de atribuido todos os valores jogados no tabuleiro, faz os laços pra verificar a soma das diagonais e das linhas e colunas
  for (i = 0; i < 3; i++) {
    somadp = somadp + n[i][i];
    somads = somads + n[i][2-i];
  }
  
  for (i = 0; i < 3; i++) {
    somal = 0;
    somac = 0;
    for (j = 0; j < 3; j++) {
      somal = somal + n[i][j];
      somac = somac + n[j][i];
    }
    if ((somal == 12) || (somal == 3) || (somac == 12) || (somac == 3)) {
      break;
    }
  }
  //verifica as somas em que o jogo acabou, se alguma delas estiver satisfazendo, retorna 1 pra main pra dizer que o jogo acabou, caso contrário, retorna 0
  if ((somal == 12) || (somal == 3) || (somac == 12) || (somac == 3) || (somadp == 12) || (somadp == 3) || (somads == 12) || (somads == 3)) {
    return(1);
  }
  
  return(0);
}


//função pra verificar se o jogo da versão 1 acabou e pra retornar a escolha que o computador deve fazer pra caso não tenha acabado
int checa_e_ganha(char **tabuleiro) {
  
  int i, j, somal, somac, somads = 0, somadp = 0, n[3][3], escolha = 0;
  
  //laço pra verificar como está o tabuleiro de char e criar um novo tabuleiro de int atribuindo os respectivos valores em suas casas, onde 'X' vale 1, 'O' vale 4 e vazio vale 0
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (tabuleiro[i][j] == 'X') {
	n[i][j] = 1;
      }
      if (tabuleiro[i][j] == 'O') {
	n[i][j] = 4;
      }
      if (tabuleiro[i][j] == ' ') {
	n[i][j] = 0;
      }
    }
  }
  
  //depois de atribuido todos os valores jogados no tabuleiro, faz os laços pra verificar a soma das diagonais e das linhas e colunas
  for (i = 0; i < 3; i++) {
    somadp = somadp + n[i][i];
    somads = somads + n[i][2-i];
  }
  
  //se a soma da diagonal principal for 2 é porque tem dois 'X' nessa diagonal, logo, deve procurar pela casa vazia na diagonal e retornar a posição dela pro computador jogar
  if (somadp == 2) {
    for (i = 0; i < 3; i++) {
      if (n[i][i] == 0) {
	break;
      }
    }
    j = i;
    //retorna o número da casa que o computador deve jogar positivo pro computador saber que deve jogar 'X'
    escolha = (3*i + 1 + j);
    return(escolha);
  }

  //se a soma da diagonal principal for 8 é porque tem dois 'O' nessa diagonal, logo, deve procurar pela casa vazia na diagonal e retornar a posição dela pro computador jogar
  if (somadp == 8) {
    for (i = 0; i < 3; i++) {
      if (n[i][i] == 0) {
	break;
      }
    }
    j = i;
    //retorna o número da casa que o computador deve jogar negativo pro computador saber que deve jogar 'O'
    escolha = -(3*i + 1 + j);
    return(escolha);
  }

  //se a soma da diagonal secundária for 2 é porque tem dois 'X' nessa diagonal, logo, deve procurar pela casa vazia na diagonal e retornar a posição dela pro computador jogar
  if (somads == 2) {
    for (i = 0; i < 3; i++) {
      if (n[i][2-i] == 0) {
	break;
      }
    }
    j = 2 - i;
    //retorna o número da casa que o computador deve jogar positivo pro computador saber que deve jogar 'X'
    escolha = (3*i + 1 + j);
    return(escolha);
  }

  //se a soma da diagonal secundária for 8 é porque tem dois 'O' nessa diagonal, logo, deve procurar pela casa vazia na diagonal e retornar a posição dela pro computador jogar
  if (somads == 8) {
    for (i = 0; i < 3; i++) {
      if (n[i][2-i]==0) {
	break;
      }
    }
    j = 2 - i;
    //retorna o número da casa que o computador deve jogar negativo pro computador saber que deve jogar 'O'
    escolha = -(3*i + 1 + j);
    return(escolha);
  }
  
  //se nenhuma das diagonais tiver uma jogada vencedora, procuraa nas linhas e colunas
  for (i = 0; i < 3; i++) {
    somal = 0;
    somac = 0;
    for (j = 0; j < 3; j++) {
      somal = somal + n[i][j];
      somac = somac + n[j][i];
    }
    if ((somal == 2) || (somal == 8) || (somac == 8) || (somac==2)) {
      break;
    }
  }

  //se a soma de alguma das linhas for 2 é porque tem dois 'X' nessa linha, logo, deve procurar pela casa vazia na linha e retornar a posição dela pro computador jogar
  if (somal == 2) {
    for (j = 0; j < 3; j++) {
      if (n[i][j] == 0) {
	break;
      }
    }
    //retorna o número da casa que o computador deve jogar positivo pro computador saber que deve jogar 'X'
    escolha = (3*i + 1 + j);
    return(escolha);
  }

  //se a soma de alguma das linhas for 8 é porque tem dois 'O' nessa linha, logo, deve procurar pela casa vazia na linha e retornar a posição dela pro computador jogar
  if (somal == 8) {
    for (j = 0; j < 3; j++) {
      if (n[i][j] == 0) {
	break;
      }
    }
    //retorna o número da casa que o computador deve jogar negativo pro computador saber que deve jogar 'O'
    escolha = -(3*i + 1 + j);
    return(escolha);
  }

  //se a soma de alguma das colunas for 2 é porque tem dois 'X' nessa coluna, logo, deve procurar pela casa vazia na coluna e retornar a posição dela pro computador jogar
  if (somac == 2) {
    for (j = 0; j < 3; j++) {
      if (n[j][i] == 0) {
	break;
      }
    }
    //retorna o número da casa que o computador deve jogar positivo pro computador saber que deve jogar 'X'
    escolha = (3*j + 1 + i);
    return(escolha);
  }

  //se a soma de alguma das colunas for 8 é porque tem dois 'O' nessa coluna, logo, deve procurar pela casa vazia na coluna e retornar a posição dela pro computador jogar
  if (somac == 8) {
    for (j = 0; j < 3; j++) {
      if (n[j][i] == 0) {
	break;
      }
    }
    //retorna o número da casa que o computador deve jogar negativo pro computador saber que deve jogar 'O'
    escolha = -(3*j + 1 + i);
    return(escolha);
  }

  return(escolha);
}


//função pra saber se o jogador quer jogar 'X' ou 'O' no jogo 1
char lance() {
  
  int escolha;
  char jogada;

  printf("Agora é sua vez!\n");
  printf("Deseja utilizar 'X' (digite 1) ou 'O' (digite 2)?\n");
  
  do {
    scanf("%d", &escolha);
    __fpurge(stdin);
    
    if ((escolha != 1) && (escolha != 2)) {
      printf("Tente de novo. Escolha 1 ou 2.\n");
    }
  } while ((escolha != 1) && (escolha != 2));
  if (escolha == 1) {
    jogada = 'X';
  } else {
    jogada = 'O';
  }
  
  return(jogada);
}


int main() {
  
  char **tabuleiro, z = NULL, auxjogada, jogada;
  int i, j, espera = clock(), escolha, aux, fim, menu = 0, ran;
  
  //aloca o tabuleiro
  mtabuleiro(&tabuleiro);
  srand(time(NULL));
  system("clear");
  
  
  //laço pra sair do programa só quando a pessoa digitar pra sair
  do {
    //laço pra ficar no menu até a pessoa digitar algo correto
    do {
      //limpa o buffer porque no menu de ajuda você tem a opção de digitar qualquer tecla pra voltar pro menu inicial, mas a variável só recebe int, então pra não entrar em loop infinito caso a pessoa digite um char o buffer está sendo limpado
      __fpurge(stdin);
      printf("+--------------------------------------+\n| Opcao:                     | Digite: |\n+--------------------------------------+\n| Jogar 1a versao            |    1    |\n| Jogar versao bonus         |    2    |\n| Menu de ajuda              |    3    |\n| Sair                       |    4    |\n+--------------------------------------+\n");
      scanf("%d", &menu);
    } while (menu < 1 || menu > 4);
    
    //laço pra verificar se a pessoa decidiu ir do menu de ajuda pra algum jogo direto, se ela quis sair ou ir pro menu principal
    do {
      
      //se ela digitou 1 no menu principal ou na opção do menu de ajuda, entra no primeiro jogo
      if (menu == 1) {
	
	//limpa o tabuleiro
	escolha = 0;
	ran = rand() % 2;
	fim = 0;
	for (i = 0; i < 3; i++) {
	  for (j = 0; j < 3; j++) {
	    tabuleiro[i][j] = ' ';
	  }
	}
	
	//mostra o tabuleiro e printa que o computador vai jogar
	system("clear");
	imprime(tabuleiro);
	printf("\nO computador vai jogar.\n");
	
	//laço pra esperar um tempo pra printar a jogada do computador
	while ((clock() - espera) < 350000) {
	printf("%c", z);
	}

	system("clear");
	espera = clock();
	
	//como a jogada do computador é aleatória, pega a escolha do srand e joga de acordo com o que retornar
	if (ran == 1) {
	  tabuleiro[1][1] = 'X';
	} else {
	  tabuleiro[1][1] = 'O';
	}
	imprime(tabuleiro);
	fim = 0;
	
	while (fim != 1) {
	  //Vez da pessoa
	  jogada = lance(); //verifica se a pessoa quer jogar 'X' ou 'O'
	  auxjogada = jogada; //armazena essa escolha pro computador saber o que jogar futuramente
	  do {
	    //verifica a casa em que a pessoa quer jogar (1 até 9) e transforma pra linguagem matricial
	    escolha = casa1();
	    i = (escolha - 1)/3;
	    j = (escolha - 1)%3;
	    if (tabuleiro[i][j] == ' ') {
	      tabuleiro[i][j] = jogada;
	      jogada = ' ';
	    } else {
	      printf("A casa já está ocupada.\n");
	    }
	  } while (jogada != ' ');
	  imprime(tabuleiro);
	  //Vez do PC
	  aux = escolha; //armazena a escolha da casa do jogador pra realizar a jogada de acordo
	  escolha = checa_e_ganha(tabuleiro); //chama a função que verifica qual a melhor jogada pro computador pra caso tenha chances de vitória
	  //se retornar um número maior do que zero é porque o computador de jogar X, caso contrário é porque ele deve jogar O
	  if (escolha > 0) {
	    jogada = 'X';
	  }
	  if (escolha < 0) {
	    jogada = 'O';
	    escolha = -escolha;
	  } 
	  //se a escolha for zero é porque ainda não tem jogada vencedora, então o computador deve jogar do lado oposto do escolhido pelo jogador com a mesma opção de escolha de 'X' ou 'O' do jogador. Por exemplo: se o jogador jogou 'X' na casa 1, o computador vai jogar 'X' na casa 9
	  if (escolha == 0) {
	    escolha = aux + 2*(5-aux);
	    jogada = auxjogada;
	  }
	  
	  //transforma a jogada pra linguagem matricial e realiza a jogada esperando um tempo
	  i = (escolha - 1)/3;
	  j = (escolha - 1)%3;
	  system("clear");
	  imprime(tabuleiro);
	  tabuleiro[i][j] = jogada;
	  printf("\nO computador vai jogar.\n");	
	  
	  while ((clock() - espera) < 350000) {
	    printf("%c", z);
	  }
	  
	  system("clear");
	  espera = clock();
	  imprime(tabuleiro);
	  fim = perdeu(tabuleiro);
	  
	  //como a estratégia é vencedora, verifica quando o jogador perdeu pra printar pra ele e voltar pro menu inicial
	  if (fim == 1) {
	    printf("\nVoce perdeu.\n");
	    
	    while ((clock() - espera) < 350000) {
	      printf("%c", z);
	    }
	    
	    system("clear");
	    espera = clock();
	    menu = 0;
	  }
	}
      }
      
      //se a pessoa digitou 2 no menu principal ou na opção do menu de ajuda, entra na versão bônus do jogo
      if (menu == 2) {
	
	//limpa o tabuleiro
	fim = 0;
	escolha = 0;
	for (i = 0; i < 3; i++) {
	  for (j = 0; j < 3; j++) {
	    tabuleiro[i][j] = ' ';
	  }
	}
	
	//mostra o tabuleiro e printa que o computador vai jogar
	system("clear");
	imprime(tabuleiro);
	printf("\nO computador vai jogar.\n");
	
	//espera um tempo pra realizar a jogada do computador
	while ((clock() - espera) < 350000) {
	  printf("%c", z);
	}
	
	//joga X no meio do tabuleiro sempre
	system("clear");
	tabuleiro[1][1] = 'X';
	imprime(tabuleiro);
	espera = clock();
	aux = 1;
	
	//laço de condição pra ver se o jogo acabou
	while (fim != 1 && aux != 9) {
	  //Vez do Usuario
	  escolha = casa2(tabuleiro); //pega a escolha da casa (1 até 9) em que o jogador quer jogar
	  system("clear");
	  imprime(tabuleiro);
	  fim = perdeu(tabuleiro); //verifica se o jogo acabou e o jogador perdeu
	  aux++;
	  //se acabou, dá um break
	  if (fim == 1) {
	    break;
	  }
	  //Vez do PC
	  ia(tabuleiro, escolha); //chama a função pro computador jogar e passa a escolha do jogador pro computador jogar de acordo
	  printf("\nO computador vai jogar.\n");
	  
	  while ((clock() - espera) < 350000) {
	    printf("%c", z);
	  }
	  
	  system("clear");
	  espera = clock();
	  imprime(tabuleiro);
	  aux++;
	  fim = perdeu(tabuleiro); //verifica se o jogo acabou e o jogador perdeu
	}
	//se fim for 1 é porque o jogador perdeu, logo, mostra que ele perdeu, espera um tempo e volta pro menu principal
	if (fim == 1) {
	  printf("\nVoce perdeu.\n");
	  
	  while ((clock() - espera) < 350000) {
	    printf("%c", z);
	}
	  
	  system("clear");
	  espera = clock();
	  menu = 0;
	  //senão o jogo empatou, logo, mostra que empatou e espera um tempo pra voltar pro menu principal
	} else {
	  printf("\nEmpatou.\n");
	  
	  while ((clock() - espera) < 350000) {
	    printf("%c", z);
	  }
	  
	system("clear");
	espera = clock();
	menu = 0;
	}
      }
      
      
      //se a pessoa digitou 3 no menu principal, entra no menu de ajuda
      if (menu == 3) {
	system("clear");
	//mostra o guia básico de ambos os jogos e pede pra pessoa escolhar qual das regras principais de cada uma das versões ela quer ler
	printf("Bem vindo a ajuda.\n\n Vamos ensinar como jogar.\n Em ambas as variacoes, o computador sempre comecara a jogar. Para executar\numa jogada, digite o numero da casa, como na ilustracao a seguir:\n\n 1|2|3\n--+-+--\n 4|5|6\n--+-+--\n 7|8|9\n\n Assim, para ocupar a casa 8, basta digitar '8', para ocupar a casa 7, basta\ndigitar '7' etc.\n Se o numero digitado nao estiver entre 1 e 9, voce terá de jogar de novo.\n Caso a casa escolhida já esteja ocupada, voce devera jogar novamente tambem.\nAgora, voce deve conhecer as regras de cada uma das variacoes, que diferem\ndas do jogo tradicional. Aperte 1 para ler as regras da variacao 1 e 2\npara as regras da variacao 2\n");
	//laço pra verificar se a pessoa digitou corretamente 1 ou 2
	do {
	  //limpa o buffer pra caso a pessoa digite uma letra no lugar do número e não entrar em um loop infinito
	  __fpurge(stdin);
	  scanf("%d", &i);
	  if ((i != 1) && (i != 2)) {
	    printf("Digite 1 ou 2.\n");
	  }
	} while ((i != 1) && (i != 2));
	
	//se a pessoa digitou 1 entrará nas regras do primeiro jogo
	if (i == 1) {
	  menu = 0;
	  //printa as regras específicas do jogo 1
	  system("clear");
	  printf("Na primeira versao do Jogo da Velha, sempre que se inicia uma nova\nrodada, voce devera escolher que marcador quer usar. No momento da jogada,\nse voce preenche uma linha, coluna ou diagonal do tabuleiro com o marcador que\nusou, GANHA o jogo.\n Assim, o jogo deve funcionar da seguinte maneira: voce ira digitar que\nmarcador deseja usar ('X' ou 'O'). Depois, voce ira digitar a posicao na qual\n quer que seu marcador seja inserido no tabuleiro. Depois, o computador faz\no mesmo. O jogo termina quando uma linha, coluna ou diagonal eh completada so com 'X' ou 'O' ou o tabuleiro todo eh preenchido sem haver vitoria de ninguem, resultando em empate.\n Alguns exemplos:\n\n1.\n O|X| \n--+-+--\n  |X|O\n--+-+--\n  | |O\nNeste caso, o jogador com a vez pode ganhar escolhendo 'O' e jogando em 3\nou escolhendo 'X' e jogando em 8.\n\n2.\n O|X|O\n--+-+--\n X|O|X\n--+-+--\n X| |X\nNeste caso, se o jogador com a vez escolher 'X' e jogar em 8 ele ganha,\nenquanto se ele escolher 'O' e jogar em 8 o jogo empata.\n\n");
	  //printa as opções pra pessoa ver o que ela quer fazer a partir daqui
	  printf("Digite um 1 para jogar a versao 1, 2 para jogar a versao 2, 4 para sair ou qualquer outra tecla para voltar ao menu inicial\n");
	  scanf("%d", &menu);
	  //verifica o que ela digitou, se não foi nenhuma das opções dadas, volta pro menu principal
	  if ((menu != 1) && (menu != 2) && (menu != 4)) {
	    menu = 0;
	  }
	  system("clear");
	}
	
	//se a pessoa digitou 2 lá em cima entrará nas regras do jogo bônus
	if (i == 2) {
	  menu = 0;
	  //printa as regras específicas do jogo bônus
	  system("clear");
	  printf("Na versao bonus do Jogo da Velha, o computador comeca e ira usar o marcador X enquanto voce ira usar o marcador O.\nQuando um jogador coloca 3 de seus marcadores em uma mesma linha, coluna ou diagonal do tabuleiro, ele PERDE o jogo. Caso o tabuleiro seja preenchido totalmente sem que ninguem tenha perdido, o jogo empata.\n Exemplos:\n1.\n X|X|X\n--+-+--\n O|O|X\n--+-+--\n O|O|X\nO jogador 1 perdeu\n\n2.\n O|X|O\n--+-+--\n X|O|X\n--+-+--\n X| |O\nO jogador 2 perdeu\n\n3.\n X|O|X\n--+-+--\n O|X|O\n--+-+--\n O|X|O\nO jogo empatou\n\n");
	  //printa as opções pra pessoa ver o que ela quer fazer a partir daqui
	  printf("Digite um 1 para jogar a versao 1, 2 para jogar a versao 2, 4 para sair ou qualquer outra tecla para voltar ao menu inicial\n");      
	  scanf("%d", &menu);
	  //verifica o que ela digitou, se não foi nenhuma das opções dadas, volta pro menu principal
	  if ((menu != 1) && (menu != 2) && (menu != 4)) {
	    menu = 0;
	  }
	  system("clear");
	}
      }
      
      //se a pessoa digitou 4 é pra sair do programa
      if (menu == 4) {
	return 0;
      }
    } while (menu > 0 && menu < 5); //condição dada pelas escolhas do menu de ajuda
  } while (menu == 0); //condição pra permanecer no programa
  
  return 0;
}
