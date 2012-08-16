#ifndef CLASSIFICADOR_H
#define CLASSIFICADOR_H

#include "../corpus/corpus.h"

class Classificador
{
    protected:
        string atributoBase;
    public:
        Classificador( string atributoBase );
        virtual ~Classificador();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo ) = 0;
        virtual bool gravarConhecimento( string arquivo ) = 0;
        virtual bool carregarConhecimento( string arquivo ) = 0;
};

#endif // CLASSIFICADOR_H
