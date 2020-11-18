#define BESTFIT 0
#define FIRSTFIT 1
#define NEXTFIT 2
#include "lista.h"

//TAMANHO MÁXIMO DE ALOCACAO: 65535 (maior unsigned short)

class meualoc{
    private:
	    char * memoria; //char* pois eh byte a byte
        Lista * lista;          //Alterações marcadas com (*)
        Bloco * bloco;
        int tam, politica; //
        int numero_alocacoes;

	public:
		//tamanhoMemoria vai definir o tamanho da memória que o alocador vai utilizar
		//politicaMem define como escolher o bloco de onde saira a memória
		meualoc(int tamanhoMemoria,int politicaMem);

		//Pega um pedaco da variavel memoria e aloca, retornando o ponteiro para o comeco dessa regiao e atualizando a lista de livres.
		char *aloca(unsigned short int tamanho);

		//Verifica se a posicao dada pelo ponteiro esta alocada
		char *  verifica(char* ponteiro,int posicao);
		
		//Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
		int libera(char* ponteiro);

		//Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
		void imprimeDados();



		~meualoc();


};


meualoc::meualoc(int tamanhoMemoria, int politicaMem){
    this->tam = tamanhoMemoria;
    this->politica = politicaMem;
    this->memoria = new char[this->tam];
    lista = new Lista(tamanhoMemoria, this->memoria);   
    this->numero_alocacoes = 0;

}
char* meualoc::aloca(unsigned short int tamanho){
    char * novo = NULL;
    
    lista->inserir(tamanho, novo);
    this->numero_alocacoes++;
    return novo;
    
}


char * meualoc::verifica(char* ponteiro, int posicao){
    lista->verificaLista(&ponteiro[posicao]);
}


void meualoc::imprimeDados(){
    int count = 0;
    count = lista->imprime(count);
    std::cout << count << "\n";
    
    unsigned short int maior = 0;
    maior = lista->maior_elemento(maior);
    std::cout << maior << "\n"; 
    
    
    unsigned short int soma_espacos_livres = 0;
    soma_espacos_livres =  lista->media_blocos_vazios(soma_espacos_livres);
    
    float a = (float)count;
    soma_espacos_livres = soma_espacos_livres/a;
    std::cout << "media: "<< soma_espacos_livres <<"\n";

}

int meualoc::libera(char * ponteiro){
    int liberou = lista->_free(ponteiro);
    if(this->numero_alocacoes == 5){
        while(lista->coalesce() == 1);

    }
    return liberou;
}


meualoc::~meualoc(){
    delete memoria;
    delete lista;
  
}





