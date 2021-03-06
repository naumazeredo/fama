#ifndef CORPUS_H
#define CORPUS_H

#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <sstream>

using namespace std;

class Corpus
{
    public:
        Corpus( vector<string> atributos = vector<string>() );
        virtual ~Corpus();
        virtual bool carregarArquivo( string arquivo ) = 0;
        virtual bool gravarArquivo( string arquivo ) = 0;
        virtual Corpus* clone() = 0;
        virtual Corpus* construirJanela( void *popUp );
        string pegarSimbolo( int indice );
        int pegarIndice( string simbolo );
        int criarAtributo( string atributo, string valorAtributo = "O");
        bool removerAtributo( string atributo );
        bool removerAtributo( int indice );
        string operator()(int sentenca, int token, int atributo);
        void operator()(int sentenca, int token, int atributo, string valor);
        int pegarValor( int sentenca, int token, int atributo );
        int pegarQtdSentencas();
        int pegarQtdConjExemplos(){return pegarQtdSentencas();}
        int pegarQtdTotalExemplos();
        int pegarQtdAtributos();
        int pegarQtdTokens( int i );
        int pegarQtdExemplos(int i){return pegarQtdTokens(i);}
        int pegarQtdSimbolos();
        bool ajustarValor( int sentenca, int token, int atributo, int valor );
        string pegarAtributo( int indice );
        int pegarPosAtributo( string atributo );
        vector<string> pegarAtributos();
        vector< Corpus* > splitCorpus( vector< bool > vetMascara );
        vector< Corpus* > splitCorpus( vector< int > vetMascara, int nCorpus );
        Corpus* gerarSubCorpus( vector< vector< bool > > vetMascara );
        bool discreto(int, vector<string>& );
        bool discreto(string, vector<string>& );
        virtual Corpus* reamostrar(vector<double>* distribuicao, bool porFrase);
    protected:
        map<string,int> posAtributos;
        vector<string> atributos;
        vector<string> simbolos;
        vector< vector< vector<int> > > frases;
        map<string,int> dicionario;
        int qtd_sentencas;
        int qtd_atributos;
        int qtd_simbolos;
};

#endif // CORPUS_H
