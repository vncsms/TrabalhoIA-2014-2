#include <string.h>
#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <stack>

using namespace std;


typedef struct no
{
    string estado;
    no *pai;
    string acao;
    string pais;
    int custo;
} nodo;

typedef struct par
{
    string acao;
    string estado;
    int valido;
} par;

typedef struct fronteira
{
    int tam;
    stack<nodo> pilha;
} fronteira;

int calculacusto(nodo a)
{
    int custo=0;
    for(int i = 1 ; i < 10 ; i++)
    {
        if(a.estado[i-1]-48!=i&&a.estado[i-1]!='_')
        {
            custo++;
        }
    }
    return custo;
}

// 0 -> esquerda // 1 -> diretia // 2 -> cima // 3 -> baixo
map<int, par> sucessor(string nome)
{
    int pos ;
    par aux;
    map<int, par> pares;
    for(int i = 0 ; i < (int) nome.size() ; i++)
    {
        if(nome[i] == '_') pos = i;
    }

    aux.valido = 0;
    for(int i = 0 ; i < 4 ; i ++)
    {
        pares[i] = aux;
    }

    if(pos < 6)
    {
        pares[3].acao = "abaixo";
        pares[3].valido =1;
        pares[3].estado = nome;
        pares[3].estado[pos] = nome[pos+3];
        pares[3].estado[pos+3] = '_';

    }
    if(pos>2)
    {
        pares[2].acao = "acima";
        pares[2].valido =1;
        pares[2].estado = nome;
        pares[2].estado[pos] = nome[pos-3];
        pares[2].estado[pos-3] = '_';
    }
    if(pos!=2 and pos!= 5 and pos!= 8)
    {
        pares[1].acao = "direita";
        pares[1].valido =1;
        pares[1].estado = nome;
        pares[1].estado[pos] = nome[pos+1];
        pares[1].estado[pos+1] = '_';
    }
    if(pos!= 0 and pos != 3 and pos!= 6)
    {
        pares[0].acao = "esquerda";
        pares[0].valido =1;
        pares[0].estado = nome;
        pares[0].estado[pos] = nome[pos-1];
        pares[0].estado[pos-1] = '_';
    }
    return pares;
}

nodo crianodo(string estado , nodo pai , string acao , int custo)
{
    nodo aux;
    aux.pais = pai.estado;
    aux.estado  = estado;
    aux.pai = &pai;
    aux.acao = acao;
    aux.custo = custo ;
    return aux;
}

map<int , nodo> expande(nodo a)
{
    map<int, par> pares = sucessor(a.estado);
    map<int, nodo> nodos;
    nodo aux;
    for(int i = 0 ; i < 4 ; i ++)
    {
        if(pares[i].valido==1)
        {
            aux = crianodo(pares[i].estado , a , pares[i].acao , a.custo+1);
            nodos[i] =  aux;
        }
    }
    return nodos;
}

bool operator <(nodo a , nodo b)
{
    return a.custo < b.custo;
}
bool operator >(nodo a , nodo b)
{
    return a.custo > b.custo;
}
bool operator ==(nodo a , nodo b)
{
    return (a.custo == b.custo);
}
bool operator !=(nodo a , nodo b)
{
    return (a.custo!=b.custo);
}
void adiciona(fronteira *p , nodo a)
{
    p->pilha.push(a);
}
void imprimeresultado(nodo *a , nodo inicial, vector<nodo> myvector)
{
    stack<string> direcoes;
    //cout << a->acao << " ";
	if(a->estado == inicial.estado) return;
    int num = 0;
    direcoes.push(a->acao);
    string p = a->pais;
    while(p!=inicial.estado)
    {
        for (vector<nodo>::iterator itt = myvector.begin() ; itt != myvector.end(); ++itt)
        {
            if(itt->estado == p)
            {
                direcoes.push(itt->acao);
                p = itt->pais ;
                break;
            }
        }
    }
    while (!direcoes.empty())
    {
     cout << direcoes.top() <<" ";
     direcoes.pop();
     num++;
    }
}
void buscaresultado(fronteira a , nodo inicial)
{
    std::set<nodo>::iterator it;
    int cont= 0;
    int flag;
    map<int , nodo> nodos;
    map<int , string> fechado;
    vector<nodo> myvector;
    nodo aux;
    int tamfechado =0;
    a.pilha.push(inicial);
    a.tam=0;
    a.tam++;
    while(a.tam!=0)
    {
        cont++;
        flag = 0;
        aux = a.pilha.top();
        a.pilha.pop();
        a.tam--;
        if(aux.estado=="12345678_")
        {
            imprimeresultado(&aux,inicial , myvector);
            return;
        }

        for (vector<nodo>::iterator itt = myvector.begin() ; itt != myvector.end(); ++itt)
        {
            if(itt->estado == aux.estado) {flag = 1 ; break;}
        }

        if(!flag)
        {
            tamfechado++;
            myvector.push_back(aux);
            nodos = expande(aux);

            for(map<int,nodo>::iterator ii=nodos.begin(); ii!=nodos.end(); ++ii)
            {
                aux = (*ii).second;
                a.pilha.push((*ii).second);
                a.tam++;
            }
            nodos.clear();
        }
    }
}



int main(int argc, char *argv[])
{

    nodo a;
    map<int , nodo> nodos;
    fronteira b;

    a.estado=argv[1];
    a.pai=NULL;
    a.acao="";
    a.custo=0;

    buscaresultado(b,a);

    return 0;
}
