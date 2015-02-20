#include <math.h> //funcoes matematicas
#include <stdio.h> //entrada e saida
#include <locale.h> //necessária para uso de configurações regionais (uso de acentuação)
#include <time.h> //funcoes temporais

/*
 * Nome: inicializarTabuleiro
 * 
 * Entrada: quantidade de linhas, quantidade de colunas, a matriz tabuleiro e a
 * matriz de deslocamento
 * 
 * Saída: vazio
 */
void incializarTabuleiro( unsigned int tamlinhas, 
                          unsigned int tamcolunas, 
                          char tabuleiro[tamlinhas][tamcolunas], 
                          char deslocamento[tamlinhas][tamcolunas]) { 
    //atribui todas as posições da matriz com um valor padrão
    int linha,
        coluna;
    for(linha=0; linha < tamlinhas; linha++) {
            for(coluna=0; coluna< tamcolunas;coluna++)
            {
                  tabuleiro[linha][coluna] = '*';
                  deslocamento[linha][coluna] = '*';
            }
    }
}

/*
 * Nome: ImprimeTabuleiro
 * 
 * Entrada: o tabuleiro, dimensão da linha, dimensão da coluna, a matriz de deslocamento,
 * numero de deslocamentos feitos
 * 
 * Saída: vazio
 */
void ImprimeTabuleiro( unsigned int tamlinhas, 
                       unsigned int tamcolunas, 
                       char tabuleiro[tamlinhas][tamcolunas], 
                       char deslocamento[tamlinhas][tamcolunas], 
                       unsigned int *movimentos) {
    int linha, coluna;
    for(linha = 0; linha < tamlinhas; linha++) {
        for(coluna = 0; coluna < tamcolunas; coluna++) {
            //impressao de uma unidade do mapa
            printf("[%c]", deslocamento[linha][coluna]);       
        }
        printf("\n");          
    }

    printf("\n");  
    
    /* revelando o tabuleiro: somente para versao de teste */
    /*
    for(linha = 0; linha < tamlinhas; linha++) {
        for(coluna = 0; coluna < tamcolunas; coluna++) {
            printf("[%c]", tabuleiro[linha][coluna]);       
        }
        printf("\n");          
    } 
    */
}

/*
 * Nome: GeraMina
 *
 * Entrada: posição linha da mina(vazia), posição coluna da mina(vazia), dimensão da linha
 * do tabuleiro, dimensão da coluna do tabuleiro
 * 
 * Saída: posição linha da mina, posição coluna da mina
 */
void GeraMina( unsigned int *posicaominaX, 
               unsigned int *posicaominaY, 
               unsigned int tamlinhas, 
               unsigned int tamcolunas) {    
    *posicaominaX = rand( )%tamlinhas; /*será sorteado um número entre 0 e
    dimensao X-1*/
    *posicaominaY = rand( )%tamcolunas; /*será sorteado um número entre 0 e
    dimensao Y-1*/
}

/*
 * Nome: ConstroiTabuleiro
 *
 * Entrada: tabuleiro, dimensão da linha do tabuleiro, dimensão da coluna do tabuleiro,
 * numero de minas
 *
 * Saída: o tabuleiro preenchido com minas geradas e posições livres (a posição inicial do
 * jogador deverá ser uma posição livre).
 */
void ConstroiTabuleiro(int tamlinhas, int tamcolunas, char tabuleiro[tamlinhas][tamcolunas], int minas) {
    unsigned int i,
        posicaominaX = 0,
        posicaominaY = 0;
    
    //para cada mina que deve ser instalada    
    for(i=0; i<minas; i++) {
        //sentinela que indica 1 quando a mina pode ser colocada naquela posicao
        short int mina_instalada = 0;
        do {
            //pede uma posicao aleatoria para a mina
            GeraMina(&posicaominaX, &posicaominaY, tamlinhas, tamcolunas);
          
            //instalando uma mina
            if(tabuleiro[posicaominaX][posicaominaY] == '*')
            {
                //atribui a posicao do tabuleiro a marca de mina
                tabuleiro[posicaominaX][posicaominaY] = '#';
                //sinaliza que a mina pôde ser instalada
                mina_instalada = 1;
            }
        } while(mina_instalada == 0);
    }                
}

/*
 * Nome:VerificaDeslocamento
 *
 * Entrada: posição linha escolhida pelo jogador, posição coluna escolhida pelo jogador,
 * posição linha atual, posição coluna atual
 *
 * Saída: 1, caso o deslocamento seja válido 0, caso o deslocamento seja inválido
 */
unsigned int VerificaDeslocamento( unsigned int mov_linha, 
                                   unsigned int mov_coluna,
                                   unsigned int linha_atual,
                                   unsigned int coluna_atual,
                                   unsigned int tamlinhas,
                                   unsigned int tamcolunas) {
                                            
    if( mov_linha < 0 || mov_linha > tamlinhas-1 || //movimento invalido: fora da faixa de linhas
        mov_coluna < 0 || mov_coluna > tamcolunas-1) //movimento invalido: fora da faixa de colunas
        return 0;
    
    if( mov_linha != linha_atual+1 && mov_linha != linha_atual-1 && mov_linha != linha_atual)
        return 0;
        
    if( mov_coluna != coluna_atual+1 && mov_coluna != coluna_atual-1 && mov_coluna != coluna_atual)
        return 0;
    
    //movimento invalido: sentido noroeste
    if( mov_linha == linha_atual-1 && mov_coluna == coluna_atual-1)
        return 0;
    
    //movimento invalido: sentido nordeste
    if( mov_linha == linha_atual-1 && mov_coluna == coluna_atual+1)
        return 0;
        
    //movimento invalido: sentido sudoeste
    if( mov_linha == linha_atual+1 && mov_coluna == coluna_atual-1)
        return 0;
        
    //movimento invalido: sentido sudeste
    if( mov_linha == linha_atual+1 && mov_coluna == coluna_atual+1)
        return 0;
    
    return 1;         
}

/*
 * Nome: VerificaPosicaoMina
 *
 * Entrada: tabuleiro, posição linha escolhida pelo jogador, posição coluna escolhida pelo
 * jogador
 *
 * Saída: 1, caso a posição escolhida pelo jogador seja uma mina. 0, caso a posição escolhida
 * pelo jogador não seja uma mina.
 */
int VerificaPosicaoMina(char posicao, char mov) {
    //se aquela posicao do tabuleiro é mina e se ele nunca passou por lá
    if(posicao == '#' && mov != '#')
        return 1;
        
    return 0;
}

/* função principal */ 
int main(int argc, char** argv){
    time_t tempoAtual;
    time ( &tempoAtual); /*calcula o tempo atual*/
    /* srand(tempoAtual*(posicaominaX)); /*estabelece uma nova chance de sortear um número
    diferente*/
    srand(tempoAtual); /*estabelece uma nova chance de sortear um número
    diferente*/

    /*lê dados - configuração*/
    //variaveis para armazenar a configuracao
    unsigned int tamlinhas = 0, 
                 tamcolunas = 0, 
                 minas = 0, 
                 vidas = 0;
    
    setlocale(LC_ALL,""); // Função que faz o prompt reconhecer os caracteres especiais, em lugar de caracteres não-usáveis
    
    /* flag_conf: variável sentinela que verifica se a configuração é válida.
     * 1. Numero de linhas do tabuleiro (tamlinhas >= 5)
     * 2. Numero de colunas do tabuleiro (tamcolunas >= 5)
     * 3. Numero de minas a serem inseridas no tabuleiro (minas >= 1 e minas <= tamlinhas*tamcolunas -1)
     * 4. Quantidade de vidas do jogador (vidas > 0 e vidas < 4)
     *
     * flag_conf = 0 //configuração inválida
     * flag_conf = 1 //configuração válida
    */
    short int flag_conf = 0;
    
    do { //enquanto a configuração não for válida
        printf("--------------Deslocamento minado---------------\n");//apresentacao do trabalho
        printf("Insira: linha coluna minas vidas\n"); //pedido de configuração
        
        //recebo a configuração
        scanf("%d %d %d %d", &tamlinhas, &tamcolunas, &minas, &vidas);
        
        //verificando...
        if( tamlinhas >= 5 && //linhas
            tamcolunas >= 5 && //colunas
            minas >= 1 && //minas
            minas <= tamlinhas * tamcolunas - 1 && 
            vidas > 0 && //vidas
            vidas < 4) {
                  
            flag_conf = 1; //configuração aceita
            
        } else {
            printf("CONFIGURAÇÃO INVÁLIDA! PREENCHA OS DADOS NOVAMENTE.\n");
            printf("------------------------------------------------\n");
        }
    } while(flag_conf == 0);
    /*configuração completa*/
       
    //tabuleiro inicializado   
    char tabuleiro[tamlinhas][tamcolunas]; //as dimensoes do tabuleiro sao definidas por tamlinhas e tamcolunas
    char deslocamento[tamlinhas][tamcolunas]; //as dimensoes do tabuleiro sao definidas por tamlinhas e tamcolunas
    
    //defino o valor padrão para o tabuleiro e para o deslocamento = '*'
    incializarTabuleiro(tamlinhas, tamcolunas, tabuleiro, deslocamento);

    /*inicializa posição do jogador como a última (n,m)*/
    tabuleiro[tamlinhas-1][tamcolunas-1] = 'J'; //tabuleiro tem o J para evitar verificacao na hora de colocar minas
    deslocamento[tamlinhas-1][tamcolunas-1] = 'J';

    //constuindo tabuleiro
    ConstroiTabuleiro(tamlinhas, tamcolunas, tabuleiro, minas);
    
    //mostro a quantidade de minas no mapa
    printf("\nMinas iniciais:\n");
    
    int i;
    for(i=0; i<minas; i++) {
        printf("(x x)\n");     
    }
    
    printf("------------------------------------------------\n");
    
    /*
    sentinela que indica o modo que o jogo se encerrou:
    0 = jogo nao encerrado
    1 = ganhou o jogo
    2 = perdeu o jogo
    3 = digitou 0 0 como posicoes
    x = houve problema com o jogo
    */
    short int fim_jogo = 0; 
    unsigned int movimentos = 0,
                 mov_linha = 0,
                 mov_coluna = 0,
                 linha_atual = tamlinhas,
                 coluna_atual = tamcolunas,
                 pisou_mina = 0;
    //enquanto (não é final){
    while(fim_jogo == 0) {
        //imprime deslocamento
        ImprimeTabuleiro(tamlinhas, tamcolunas, tabuleiro, deslocamento, &movimentos);
        
        printf("------------------------------------------------\n");
        
        //se na última jogada ele pisou em uma mina, aviso
        if(pisou_mina == 1) {
            printf("Voce caiu em uma mina! Tem mais %d chance(s).\n", vidas);
        }
        pisou_mina = 0;
        
        //pede movimento
        printf("Escolha uma posição para movimentar:\n");
        scanf("%d %d", &mov_linha, &mov_coluna);
        
        //verifico se o usuario nao quer sair do jogo
        if(mov_linha == 0 && mov_coluna == 0) {
            fim_jogo = 3;             
        } else {
            /*verifica se o deslocamento é válido*/
            //if(VerificaDeslocamento(mov_linha-1, mov_coluna-1, linha_atual-1, coluna_atual-1, tamlinhas, tamcolunas) == 0) {
            //    printf("DESLOCAMENTO INVÁLIDO!\n");
            //    printf("------------------------------------------------\n");
            if(VerificaDeslocamento(mov_linha-1, mov_coluna-1, linha_atual-1, coluna_atual-1, tamlinhas, tamcolunas) != 1) {
                printf("DESLOCAMENTO INVÁLIDO!\n");
                printf("------------------------------------------------\n");
            } else {
                //conta um movimento
                movimentos++;
                
                /*verifica se a posição possui uma mina */
                if(VerificaPosicaoMina(tabuleiro[mov_linha-1][mov_coluna-1], deslocamento[mov_linha-1][mov_coluna-1]) == 1) {                
                    deslocamento[mov_linha-1][mov_coluna-1] = '#';
                    vidas--;
                    pisou_mina = 1;
                }
                
                //se onde pisou nao foi uma mina, marco que ele ja passou por la
                if(deslocamento[linha_atual-1][coluna_atual-1] != '#')  
                    deslocamento[linha_atual-1][coluna_atual-1] = '0';
                
                //atualizo a linha atual como a linha que o usuario pediu    
                linha_atual = mov_linha;
                coluna_atual = mov_coluna;
                    
                //se onde esta nao for uma mina, marco que ele esta num espaco vazio
                if(tabuleiro[linha_atual-1][coluna_atual-1] != '#')
                    deslocamento[linha_atual-1][coluna_atual-1] = 'J';
                //else
                //    deslocamento[linha_atual-1][coluna_atual-1] = '#';
                
                /*verifica se chegou ao final do tabuleiro*/
                if(linha_atual == 1)
                    fim_jogo = 1;               
                
            }
            
        }

        /*verifica se existem “vidas”*/            
        if(vidas <= 0)
            fim_jogo = 2;
            
        
    }/*fim do loop*/
    
    //se ele nao pediu para sair, imprimo pela ultima vez aquele tabuleiro
    if(fim_jogo != 3) {
        //imprimindo o tabuleiro
        ImprimeTabuleiro(tamlinhas, tamcolunas, tabuleiro, deslocamento, &movimentos);
        printf("------------------------------------------------\n");
    }
            
    int linha, coluna; //indices para uso do for
    switch(fim_jogo) {
        case 1: //chegou na primeira linha            
            printf("Você Ganhou! Parabéns!\nMinas finais:\n");
            //apresentar minas
            for(linha = 0; linha < tamlinhas; linha++) {
                for(coluna = 0; coluna < tamcolunas; coluna++) {
                    if(tabuleiro[linha][coluna] == '#') {
                        printf("(%d %d)\n", linha+1, coluna+1);
                    }
                }         
            }
            printf("Foram %d movimentos\n", movimentos);
            break;
        case 2: //perdeu
            printf("Voce caiu em uma mina! Tem mais %d chance(s).\n", vidas);
            printf("Você perdeu o jogo!\nMinas finais:\n");
            //apresentar minas
            for(linha = 0; linha < tamlinhas; linha++) {
                for(coluna = 0; coluna < tamcolunas; coluna++) {
                    if(tabuleiro[linha][coluna] == '#') {
                        printf("(%d %d)\n", linha+1, coluna+1);
                    }
                }         
            }
            printf("Foram %d movimentos\n", movimentos);
            break;
        case 3: //pediu para sair
            printf("JOGO ENCERRADO.\n");
            printf("Foram %d movimentos\n", movimentos);
            break;
        default: //algum possivel bug
            printf("\nERRO INESPERADO. JOGO ENCERRADO.\n");                 
    }
    
    //parada na tela para o usuario ver a mensagem de fim de jogo
    system("pause");
    
    return 0;
}/*fim da main*/
