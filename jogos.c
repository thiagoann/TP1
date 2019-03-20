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
    
    //declarando variáveis
    vetor*vec = vetor_novo();
    FILE *f;
    int i, l = 0;
    jogo j;

    //vetor inicia-se a 0
    vec = NULL;
        

    //abrir ficheiro em modo de leitura
    f = fopen(f, "r");

    //Condicões par erro 
    if(f == NULL || vec == NULL){
        printf("Erro! ");
    return NULL;
    }   
        while(f != NULL && fscanf(f, "%s %s %s %d %d %d %d", j.epoca, j.nome_casa, j.nome_fora, 
        &j.golos_casa, &j.golos_fora, &j.vermelhos_casa, &j.vermelhos_fora)!=EOF){

                vetor_insere(vec, j, l);
        l++;
        }
    
    //Caso contrário...

return vec;
fclose(f);
}


int jogos_save(vetor *vec, const char *nomef){

        FILE *f1;
        int j;
        int pos;

        f1 = fopen(nomef, "w");
        if(f1 == NULL || pos < 0 || pos >=vec->tamanho)
        return -1;

        for(j = 0; j < vetor_tamanho(vec); j++){
            fprintf(f1, "%s %s %s %d %d %d %d\n ", vetor_elemento(vec, j)->epoca, vetor_elemento(vec, j)->nome_casa,
             vetor_elemento(vec, j)->nome_fora, 
            vetor_elemento(vec, j)->golos_casa, vetor_elemento(vec, j)->golos_fora, 
            vetor_elemento(vec, j)->vermelhos_casa, vetor_elemento(vec, j)->vermelhos_fora);
             return j;
        }

fclose(f1);
}


vetor_equipas *stats_equipa(vetor *vec){

    int totalJogos = 38;
    int m;
    vetor_equipas *vec2 = vetor_equipas_novo();
    equipa *casa, *fora;

    casa = NULL;
    fora = NULL;
        
        if(vec == NULL && vec2 == NULL){
            return NULL;
        }

        //Caso contrário
        for(m = 0; m < vetor_tamanho(vec); m++){
            for(m = 0; m < vetor_equipas_tamanho(vec2); m++){

                if(strcmp(vetor_elemento(vec, m)->nome_casa, vetor_equipas_elemento(vec2, m)->nome_equipa) ==0){
                
                casa = vetor_equipas_elemento(vec2, m);
                }

                if(strcmp(vetor_elemento(vec, m)->nome_fora, vetor_equipas_elemento(vec2, m)->nome_equipa) ==0)
                fora = vetor_equipas_elemento(vec2, m);
             
                    if(casa == NULL){
                    //A equipa ainda nao exite
                        
                        equipa nova;
                        nova.diff_golos = vetor_elemento(vec, m)->golos_casa - vetor_elemento(vec, m)->golos_fora;
                        nova->vermelhos[vetor_elementos(vec, m)->epoca[1] - '5'] = vetor_elemento(vec, m)->vermelhos_casa + 
                        vetor_elemento(vec, m)->vermelhos_fora;
                        nova->nome_equipa = vetor_elemento(vec, m)->nome_casa;
                            vetor_equipas_insere(vec2, nova, m);
                    }
                        else{
                        casa ->diff_golos += vetor_elemento(vec, m)->golos_casa - vetor_elemento(vec, m)->golos_fora;
                        casa->vermelhos[vetor_elementos(vec, m)->epoca[1] - '5'] += vetor_elemento(vec, m)->vermelhos_casa - 
                        vetor_elemento(vec, m)->vermelhos_fora;
                        }
                
                    if(fora == NULL){
                    equipa nova;
                        nova.diff_golos = vetor_elemento(vec, m)->golos_casa - vetor_elemento(vec, m)->golos_fora;
                        nova->vermelhos[vetor_elementos(vec, m)->epoca[1] - '5'] = vetor_elemento(vec, m)->vermelhos_casa + 
                        vetor_elemento(vec, m)->vermelhos_fora/38;
                        nova->nome_equipa = vetor_elemento(vec, m)->nome_casa;
                        strcpy(nova.nome_equipa, vetor_elemento(vec, m)->nome_fora);
                            vetor_equipas_insere(vec2, nova, -1);
                    }
                    
                    else{
                        fora ->diff_golos += vetor_elemento(vec, m)->golos_fora - vetor_elemento(vec, m)->golos_casa;
                        fora->vermelhos[vetor_elementos(vec, m)->epoca[1] - '5'] += vetor_elemento(vec, m)->vermelhos_fora/38;
                    }
                }//end 2º for
        }//end 1º for


    return vec2;

}
    

int equipas_ordena(vetor_equipas *v, int criterio){


    
    return -1;
     
}

int corrige_jogo(vetor *vec, const char *nomef){

    int o;
    FILE *f5;
    equipa *dados;

    f5 = fopen(nomef, "r");

    /*Em caso de erro*/
    if (f5 == NULL || vec == NULL ) {
    return -1;
    }
        //Caso contrário...

        while(f5!=NULL){
            for(o = 0; o < vetor_tamanho(vec); o++){
                
            }
        }

}


int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){

    int pontos = 0;
    int k;
    equipa *eq2//equipa casa
    equipa *eq3//equipa fora

        if(vec == NULL || k>=vetor_tamanho(vec)){
        return -1;
        }
        
        /*CASO CONTRÁRIO*/
        //ler vetor
        for(k = 0; k < vetor_tamanho(vec); k++){
                for(k = 0; k < vetor_equipas_tamanho(vec); k++){

                //Guarda equipa da casa em vetor_equipas.
                    if(strcmp(vetor_elemento(vec, k)->nome_casa, vetor_elemento(vec, k)->nome_equipa) == 0){
                    eq2 = vetor_equipas_elemento(vec, k);
                }
                    //Guarda equipa de fora em vetor_equipas
                        if(strcmp(vetor_elemento(vec, k)->nome_fora, vetor_elemento(vec, k)->nome_equipa) == 0){
                        eq3 = vetor_equipas_elemento(vec, k);
                    }
                    /**
                     * OK! Guardei os equipas da casa e de fora no vetor_equipas.
                     * Agora, devo trabalhar com os dados fornecidos pelo ficheiro
                     */
                    while(epoca != 0){
                       
                       /*Compara os golos*/
                            if(eq2->golos_casa > eq3->golos_fora){
                            //A equipa da casa ganhou
                            pontos+=3;
                        }
                                else if(eq2->golos_casa == eq3->golos_fora){
                                pontos++;
                            }
                                else{
                                pontos = 0;
                        }
                    }
            }   
        }
    return 0;
}



