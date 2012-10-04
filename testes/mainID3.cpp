#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../id3/dtree.h"
#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"

using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int nExemplos, i, c, nConjExemplos, e, c0, c1, iResposta, nTotalExemplos;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(vector<string>(), ',', true, true);
    objCorpus.carregarArquivo( "../inputs/data.data" );
    iResposta = objCorpus.pegarPosAtributo("Purchase");

    cout << "atributo alvo: " << iResposta << endl;
    cout << (nTotalExemplos = objCorpus.pegarQtdTotalExemplos()) << " exemplos\n";

    //indica classes alvo
    classes.push_back("wontbuy");
    classes.push_back("willbuy");
    c0 = c1 = 0;

    nConjExemplos = objCorpus.pegarQtdConjExemplos();
    for (c=0; c<nConjExemplos; c++){
        nExemplos = objCorpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            if (objCorpus.pegarIndice(classes[0]) == objCorpus.pegarValor(c, e, iResposta))
                c0++;
            else
                c1++;
        }
    }

    cout << c0 << " won't buy / " << c1 << " will buy / " <<endl;

    cout << 100.*c0/nTotalExemplos << " / " << 100.*c1/nTotalExemplos << endl;

    /* Teste generateSubCorpus
    vector < vector <bool> > mask;
    bool sim = true;
    mask.resize(nConjExemplos);
    for (c=0; c<nConjExemplos; c++){
        mask[c].resize(objCorpus.pegarQtdExemplos(c));
        for (e=0; e < nExemplos; e++, sim = !sim)
            mask[c][e] = true;
    }
    Corpus *sub = objCorpus.gerarSubCorpus(mask);
    cout << nTotalExemplos << " - " << sub->pegarQtdTotalExemplos() << endl;
    cout << nConjExemplos << " - " << sub->pegarQtdConjExemplos() << endl;


    for (c=0; c<nConjExemplos; c++){
        nExemplos = objCorpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            for (i = 0; i < 5; i++)
                cout << objCorpus.pegarSimbolo(objCorpus.pegarValor(c, e, i))
                    << "-"<< sub->pegarSimbolo(objCorpus.pegarValor(c, e, i)) << endl;
        }
    }

    */
    //return 0;


    atributos = objCorpus.pegarAtributos();

    for (i=0; i < (int)atributos.size(); i++) {
        cout << "\n Atributo " << i << ":  " << atributos[i];
        // if(atributos[i]!="Purchase")
            atributosTreino.push_back(atributos[i]);
    }

    DecisionTree objTree(atributosTreino, classes);
    DecisionTree objTree2(vector<string>(), classes);
    RandomForest objForest(&objTree2, atributosTreino, 5, 4);
    //Classificador *objClass = objTree.executarTreinamento(objCorpus, iResposta);
    Classificador *objClass = objForest.executarTreinamento(objCorpus, iResposta);
    cout << "OK";
    objCorpus.criarAtributo("algoritmo", "O");
    objClass->executarClassificacao(objCorpus, iResposta+1);

    AvaliadorAcuracia objAvalAcur;
    printf( "\nAcuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpus,
     iResposta, iResposta + 1)[0] );

    //objCorpus.gravarArquivo( "../inputs/data.gravar" );

    delete objClass;

    return 0;
}
