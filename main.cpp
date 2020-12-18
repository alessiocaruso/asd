#include<iostream>
#include<cstdlib>
using namespace std;
#define MAX_SIZE 30
/*definisce NODO come nuovo tipo struct nodo */
typedef struct incroci_labirinto {
    char info; //informazione del vertice
    int nro_vertici_adiacenti; //numero dei vertici adiacenti
    int peso;
    struct incroci_labirinto *vertice_adiacente[5]; //array puntatori ai vertici adiacenti max5
    int num_ind;
    int visitato; //1 - nodo visitato; 0 - nodo non visitato
} grafo;
void depth_first_search_iterativo(grafo [], grafo);
void pop(int *, grafo [], int *);
void push(grafo *, grafo [], int *);
int main()
{

    grafo labirinto[MAX_SIZE];

    labirinto[0].info='A';
    labirinto[0].nro_vertici_adiacenti=2;
    labirinto[0].vertice_adiacente[0] = &labirinto[1]; //Il vertice A Ã¨ collegato al vertice #
    labirinto[0].vertice_adiacente[1] = &labirinto[3]; //Il vertice A Ã¨ collegato al vertice B
    labirinto[0].num_ind = 0;
    labirinto[0].visitato = 0; //1 - nodo visitato; 0 - nodo non visitato

    labirinto[1].info='B';
    labirinto[1].nro_vertici_adiacenti=4
    labirinto[1].vertice_adiacente[0] = &labirinto[0]; //Il vertice B Ã¨ collegato al vertice A
    labirinto[1].vertice_adiacente[1] = &labirinto[2]; //Il vertice B Ã¨ collegato al vertice C
    labirinto[1].vertice_adiacente[2] = &labirinto[4]; //Il vertice B Ã¨ collegato al vertice D
    labirinto[1].num_ind = 1;
    labirinto[1].visitato = 0; //1 - nodo visitato; 0 - nodo non visitato

    labirinto[2].info='C';
    labirinto[2].nro_vertici_adiacenti=1;
    labirinto[2].vertice_adiacente[0] = &labirinto[1]; //Il vertice C Ã¨ collegato al vertice B
    labirinto[2].num_ind = 2;
    labirinto[2].visitato = 0; //1 - nodo visitato; 0 - nodo non visitato

    labirinto[3].info='D';
    labirinto[3].nro_vertici_adiacenti=1;
    labirinto[3].vertice_adiacente[0] = &labirinto[0]; //Il vertice D Ã¨ collegato al vertice #
    labirinto[3].num_ind = 3;
    labirinto[3].visitato = 0; //1 - nodo visitato; 0 - nodo non visitato

    labirinto[4].info='E';
    labirinto[4].nro_vertici_adiacenti=1;
    labirinto[4].vertice_adiacente[0] = &labirinto[1]; //Il vertice E Ã¨ collegato al vertice C
    labirinto[4].num_ind = 4;
    labirinto[4].visitato = 0; //1 - nodo visitato; 0 - nodo non visitato


    cout<<"Cammino che parte dall'ingresso A e termina nell'uscita Q del Labirinto"<<endl;
    //Chiamata alla function, si passa come vertice di partenza il vertice A come da esercizio
    depth_first_search_iterativo(labirinto, labirinto[0]);

}

void depth_first_search_iterativo(grafo labirinto[], grafo vertice)
{
    int head=-1, num_ind, k;

    grafo stack[MAX_SIZE]; //dichiarazione della pila come array di MAX_SIZE struct (vertici)
    /*controlla se lo stack e' pieno*/
    if (head>MAX_SIZE-1)
    {
        printf("***IMPOSSIBILE AGGIUNGERE - PILA PIENA***");
        exit(1);
    }
    /*VISITA IL NODO DI PARTENZA E INSERISCI NELLO STACK I NODI ADIACENTI AD ESSO*/
    printf("%c ",vertice.info);
    vertice.visitato = 1; //setta il flag del vertice = 1 perche' visitato
//si itera per quanti sono i nodi adiacenti, e si inserisce ciascun nodo adiacente nella pila
    for (k=0; k<vertice.nro_vertici_adiacenti; k++)
        push(vertice.vertice_adiacente[k], stack, &head);
    while (head!=-1) /*FINTANTOCHE' LA PILA NON E' VUOTA*/


    {

        pop(&num_ind, stack, &head);
        /*SE NON E' GIA' STATO VISITATO LO SI VISITA*/
        if (labirinto[num_ind].visitato == 0)
        {
            printf("%c ",labirinto[num_ind].info); //VISITA IL VERTICE ESTRATTO
            labirinto[num_ind].visitato = 1;
/*setta il flag del vertice estratto (di indice num_ind nell'array di struct) e
visitato = 1 perchè visitato appunto */
/*CONTROLLO PER VEDERE SE SI E’ ARRIVATI ALL'USCITA*/
            if (labirinto[num_ind].info == 'E')
//se il vertice estratto e' il vertice di uscita del labirinto
            {

                head=-1; //setta la condizione di uscita dal ciclo
                labirinto[num_ind].nro_vertici_adiacenti=0;

            }
/*E SI INSERISCONO NELLO STACK I VERTICI ADIACENTI A QUELLO ESTRATTO*/
            for (k=0; k<labirinto[num_ind].nro_vertici_adiacenti; k++)

            {

                if (head>MAX_SIZE-1)
                {
                    cout<<"ARRAY PIENO: IMPOSSIBILE AGGIUNGERE"<<endl;
                    exit(1);
                }

                push(labirinto[num_ind].vertice_adiacente[k], stack, &head);
            }
        }
    }
}

void pop(int *num_ind, grafo stack[], int *head)
{
    /*prima di eliminare (non in senso vero e proprio ma mediante il decremento di head)
    l'elemento dallo stack, estraggo le informazioni o meglio l'indice che individua la
    struttura nell'array*/
    *num_ind = stack[*head].num_ind;
    /*per simulare l'eliminazione viene semplicemente decrementato head che quindi sara'
    l'indice che individuerÃ l'elemento precedente nello stack*/
    (*head)--;
}

void push(grafo *vertice, grafo stack[], int *head)
{

    (*head)++; //incrementa l'indice che identifica l'elemento in testa allo stack
    stack[*head].info = vertice->info; //inserisce la struct corrispondente al nodo nello stack
    stack[*head].nro_vertici_adiacenti = vertice->nro_vertici_adiacenti;
    stack[*head].num_ind = vertice->num_ind;
    stack[*head].visitato = vertice->visitato;
}
