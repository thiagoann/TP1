/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "jogos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


vetor* jogos_load(const char *nomef){
    /*Variaveis*/
    int t =0;
    jogo j;
    vetor *vec;
    vec  = vetor_novo();
    /* Manipular o nomef como arquivo de texto de leitura */
    FILE *f = fopen(nomef,"r");
    if (f == NULL) 
    {
        return NULL;
    }
    /*Loop while de leitura de arquivo */

    while(fscanf(f,"%s %s %s %d %d %d %d",j.epoca,j.nome_casa,j.nome_fora,&j.golos_casa,&j.golos_fora,&j.vermelhos_casa,&j.vermelhos_fora) != EOF)
    {
        vetor_insere(vec,j,t);
        t++;
        // printf("%s\n",j.nome_casa); // TL----OK
    }
    return vec;
}


int jogos_save(vetor *vec, const char *nomef){
    /* Variaveis */
    int n = 0;
    /* Criaçao de ficheiro em moddo de escrita */

    FILE *f = fopen(nomef,"w");
    if (f == NULL)
    {
        return -1;
    }

    /* Copia dos elementos do vetor vec no novo ficheiro de texto nomef */

    for (n=0;n<vetor_tamanho(vec);n++)
    {
        fprintf(f,"%s %s %s %i %i %i %i\n",vetor_elemento(vec,n)->epoca,vetor_elemento(vec,n)->nome_casa,vetor_elemento(vec,n)->nome_fora,
        vetor_elemento(vec,n)->golos_casa,vetor_elemento(vec,n)->golos_fora,vetor_elemento(vec,n)->vermelhos_casa,vetor_elemento(vec,n)->vermelhos_fora);
    }

    return n;
    fclose(f);
}


vetor_equipas *stats_equipa(vetor *vec){
    
    
    // Criaçao do vetor_equipas 
    vetor_equipas *veceq;
    veceq = vetor_equipas_novo();
    int i=0;
    // Copia do nome da casa para o novo vetor 
    for (i=0;i<vetor_tamanho(vec);i++)
    {
        equipa *casa,*fora;
        casa = NULL;
        fora = NULL;
        for(int j=0;j<vetor_equipas_tamanho(veceq);j++)
        {
            if (strcmp(vetor_elemento(vec,i)->nome_casa,vetor_equipas_elemento(veceq,j)->nome_equipa) == 0 )
            {
                casa = vetor_equipas_elemento(veceq,j);
                
            }
            if (strcmp(vetor_elemento(vec,i)->nome_fora,vetor_equipas_elemento(veceq,j)->nome_equipa) == 0 )
            {

                fora = vetor_equipas_elemento(veceq,j);
            }
        }

        if (casa == NULL)
        {
            equipa nova;
            nova.diff_golos = vetor_elemento(vec,i)->golos_casa - vetor_elemento(vec,i)->golos_fora;
            nova.vermelhos[vetor_elemento(vec, i)->epoca[1] - '5'] = vetor_elemento(vec,i)->vermelhos_casa/38;
            strcpy(nova.nome_equipa, vetor_elemento(vec,i)->nome_casa);
            vetor_equipas_insere(veceq,nova,-1);
        }
        else
        {
            casa->diff_golos += vetor_elemento(vec,i)->golos_casa - vetor_elemento(vec,i)->golos_fora;
            casa->vermelhos[vetor_elemento(vec, i)->epoca[1] - '5'] += vetor_elemento(vec,i)->vermelhos_casa/38;
        }
        
        if (fora== NULL)
        {
            equipa nova;
            nova.diff_golos = vetor_elemento(vec,i)->golos_fora - vetor_elemento(vec,i)->golos_casa;
            nova.vermelhos[vetor_elemento(vec, i)->epoca[1] - '5'] = vetor_elemento(vec,i)->vermelhos_fora/38;
            strcpy(nova.nome_equipa,vetor_elemento(vec,i)->nome_fora);
            vetor_equipas_insere(veceq, nova, -1);
        }
        else
        {
            fora->diff_golos += vetor_elemento(vec,i)->golos_fora - vetor_elemento(vec,i)->golos_casa;
            fora->vermelhos[vetor_elemento(vec, i)->epoca[1] - '5'] += vetor_elemento(vec,i)->vermelhos_casa/38;
        }

    }

    return veceq;
}
//--------------------------------------------------------------ERRO-------------------------------------------
/*
int particao(vetor_equipas *v,int inicio, int final){
    // Variaveis
    int esq,dir;
    equipa *x,*pivo;
    esq = inicio;
    dir = final;
    pivo = vetor_equipas_elemento(v,inicio);
    // Loop de partição
    while (esq<dir)
    {
        while(vetor_equipas_elemento(v,esq)<=pivo)
            esq++; // passa a posiçao seguinte
        while(vetor_equipas_elemento(v,dir)<=pivo)
            dir--; //recua para a posiçao anterior
        if (esq>dir)
        {
            *x = *vetor_equipas_elemento(v,esq);
            *vetor_equipas_elemento(v,esq) = *vetor_equipas_elemento(v,dir); // troca a posiçao do vetor da esquerda com o da direita
            *vetor_equipas_elemento(v,dir) = *x;
        }
    }
   *vetor_equipas_elemento(v,inicio) = *vetor_equipas_elemento(v,dir);
   *vetor_equipas_elemento(v,dir) = *pivo;
    return dir;
}

int quicksort(vetor_equipas *v,int ini,int fim){
    int pivo;
    if (fim>ini){
        pivo = particao(v,ini,fim); // Escolhe o melhor pivo e separa a partiçao em duas metades.
        quicksort(v,ini,pivo+1); // Ordena a primeira metade.
        quicksort(v,pivo+1,fim); // Ordena a segunda metade.
    }
    return 0;
}
int quicksort_str(vetor_equipas *v,int ini,int fim){
    // Variaveis
    int pvt,i,j;
    equipa *pivo,*temp;
    i=ini;
    j=fim;
    pvt = vetor_equipas_tamanho(v)/2;
    pivo = vetor_equipas_elemento(v,pvt);

    
    do{
        
        while(strcmp(vetor_equipas_elemento(v,i)->nome_equipa,pivo->nome_equipa)<0 &&
        (i<fim)){i++;} // movimenta para a direita
        while(strcmp(vetor_equipas_elemento(v,j)->nome_equipa,pivo->nome_equipa)>0 &&
        (j>ini)){j--;} // movimenta para a esquerda

        if (i<=j)
        {
            strcpy(temp,vetor_equipas_elemento(v,i));
            strcpy(vetor_equipas_elemento(v,i),vetor_equipas_elemento(v,j));
            strcpy(vetor_equipas_elemento(v,i),temp);
            i++;
            j--;
        }
    } while(ini<=fim);
    if (ini<j){quicksort_str(v,ini,j);}
    if (i<fim){quicksort_str(v,i,fim);}
    return 0;
}
*/
//--------------------------------- Colocar seu codigo Abaixo -------------------------------------------------



//-------------------------------------------------------------------------------------------------------------

int equipas_ordena(vetor_equipas *v, int criterio){
    
    //Declaracao das variaveis
    int t;
    int fim, ini;
    int i/*inicio*/, j/*final*/;
    equipa *pivot, *aux,*pivot2;

    i = ini;
    j = fim - 1;

        /*Condicoes para erro*/
        if(v == NULL || t >= vetor_equipas_tamanho(v)){return -1;}      
        
        //SENÃO!!!

        //Ler vetor
            for(t = 0; t<vetor_equipas_tamanho(v); t++){
                    
                    //Ordenacao de golos por quicksort

                        if(criterio == 1){
                    //Ciclo infinito
                    while(1){
                       
                       while(i < fim && vetor_equipas_elemento(v, i)->diff_golos <= pivot->diff_golos)
                       i++;//Avança para a próxima posicao

                       while(vetor_equipas_elemento(v, fim)->diff_golos <= pivot->diff_golos)
                           j--;//Recua

                           if(i < j){
                               //faz a troca
                               vetor_equipas_elemento(v, i)->diff_golos = vetor_equipas_elemento(v, j)->diff_golos;
                           }else break;
                        }        
                                //repoe pivot
                                vetor_equipas_elemento(v, i)->diff_golos = vetor_equipas_elemento(v, fim)->diff_golos;
                            

                        }
                            //OK! Agora fazer quicksort para strings
                            /**
                             * Novamente um ciclo while, só que dessa vez devemos usar strings
                             * Esta retorna um inteiro
                             * Devo manipular strings!!!
                             */
                            else if(criterio == 0){
                                 
                                 while(1){
                                
                                    while(i < fim && strcmp(vetor_equipas_elemento(v, i)->nome_equipa, pivot2->nome_equipa) < 0)
                                    i++;//Novamente avança

                                    while(strcmp(vetor_equipas_elemento(v, j)->nome_equipa, pivot2->nome_equipa) > 0)
                                    j--;//Novamente recua

                                    //Agora, se o elemento da esquerda, i, for menor que o da direita, j, fazer um strcpy

                                    if(i < j){
                                    //Neste caso, o strcpy está fazendo a funcao de troca
                                    strcpy(aux->nome_equipa, vetor_equipas_elemento(v, i)->nome_equipa);
                                    strcpy(vetor_equipas_elemento(v, i)->nome_equipa, vetor_equipas_elemento(v, j)->nome_equipa);
                                    strcpy(vetor_equipas_elemento(v, i)->nome_equipa, aux->nome_equipa);
                                    }
                                }
                            }          
                }     
    return 0;
}

int corrige_jogo(vetor *vec, const char *nomef){
    // Variaveis
    int t=0,i=0,j=0;
    vetor *vec_new;
    vec_new = vetor_novo();
    jogo n;
    // Leitura do ficheiro correto
    FILE *f = fopen(nomef,"r");
    if (f==NULL){return -1;}
    while(fscanf(f,"%s %s %s %i %i %i %i",n.epoca,n.nome_casa,n.nome_fora,&n.golos_casa,&n.golos_fora,&n.vermelhos_casa,&n.vermelhos_fora) != EOF)
    {
        //printf("entrei loop while\n!");// TL--OK
        vetor_insere(vec_new,n,t);
        t++;
    // Comparaçao dos elementos do vetor vec com os corretos do vetor vec_new
    for (i=0;i<vetor_tamanho(vec);i++)
    {
        //printf("Entrei Loop for i\n");// TL -- OK
        for(j = 0; j < vetor_tamanho(vec_new); j++)
        {
            // printf("Entrei Loop for j\n");// TL -- OK
            if (strcmp(vetor_elemento(vec,i)->epoca,vetor_elemento(vec_new,j)->epoca)==0
            && strcmp(vetor_elemento(vec,i)->nome_casa,vetor_elemento(vec_new,j)->nome_casa)==0
            && strcmp(vetor_elemento(vec,i)->nome_fora,vetor_elemento(vec_new,j)->nome_fora)==0)
            {
                // printf("Entrei no if!"); //TL -- OK
                vetor_elemento(vec,i)->golos_casa = vetor_elemento(vec_new,j)->golos_casa;
                vetor_elemento(vec,i)->golos_fora = vetor_elemento(vec_new,j)->golos_fora;
                vetor_elemento(vec,i)->vermelhos_casa = vetor_elemento(vec_new,j)->vermelhos_casa;
                vetor_elemento(vec,i)->vermelhos_fora = vetor_elemento(vec_new,j)->vermelhos_fora;
            }
            }
        }
    }
    stats_equipa(vec);
    return 0;
}


int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){
    //Variaveis
    int i=0,pontos=0;

    //Loop de leitura do vetor
    for (i=0;i<vetor_tamanho(vec);i++)
    { 
        if (strcmp(vetor_elemento(vec,i)->epoca,epoca)==0 &&
        strcmp(vetor_elemento(vec,i)->nome_casa,nome_equipa)==0)
        {
            // printf("epoca: %s| equipa: %s | gols casa: %i | gols fora: %i\n ",vetor_elemento(vec,i)->epoca,vetor_elemento(vec,i)->nome_casa,vetor_elemento(vec,i)->golos_casa,vetor_elemento(vec,i)->golos_fora);// TL--OK
            if (vetor_elemento(vec,i)->golos_casa > vetor_elemento(vec,i)->golos_fora){pontos+=3;}//vitoria em casa
            if (vetor_elemento(vec,i)->golos_fora == vetor_elemento(vec,i)->golos_casa){pontos+=1;}//empate
        }
        if (strcmp(vetor_elemento(vec,i)->epoca,epoca)==0 &&
        strcmp(vetor_elemento(vec,i)->nome_fora,nome_equipa)==0)
        {
            //printf(" fora: %s ",vetor_elemento(vec,i)->nome_fora);
            if (vetor_elemento(vec,i)->golos_fora > vetor_elemento(vec,i)->golos_casa){pontos+=3;}//printf("Vitoria fora!\n");}//vitoria fora
            if (vetor_elemento(vec,i)->golos_fora == vetor_elemento(vec,i)->golos_casa){pontos+=1;}//empate
        } 
    }
    return pontos;
    //return-1;
}






