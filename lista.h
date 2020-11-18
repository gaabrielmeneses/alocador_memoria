struct Bloco{
	unsigned short int tamanho;
    short livre;
    char* ptr_posicao;
	struct  Bloco * prox;
};

//Lista para os blocos de memorias alocados e livre
class Lista{
private:
	Bloco * inicio;
	int tamanho_memoria;
	char * ptr;
	int flag; // pra iniciar a lista e alocar um bloco do tamanho do vetor  livre = 0

public:

	Lista(int tamanho_memoria, char * ptr){
		this->inserir(tamanho_memoria, ptr);
		this->flag = 0;
		this->tamanho_memoria = tamanho_memoria;
		this->ptr = ptr;
		
	}

	Bloco * novo_bloco(unsigned short int tamanho, char * ptr_posicao, struct Bloco * bloco){
		bloco->tamanho = tamanho;
		if(this->flag == 0){
			bloco->livre = 0;
			this->flag = 1;
		}	
		else bloco->livre = 1;		
		
		bloco->ptr_posicao = ptr_posicao;
		bloco->prox = NULL;
		return bloco;
		

	}

	void inserir(unsigned short int tamanho, char * ptr_posicao){
		Bloco * novo = new Bloco;
		novo = novo_bloco(tamanho, ptr_posicao,novo);	
			
		if(inicio == NULL){
			this->inicio = novo;
		
		}else{
			Bloco * aux = new Bloco;
			aux = inicio;
			while(aux->prox != NULL)aux = aux->prox;
			aux->prox = novo;
			
		}
	}

	void remover(struct blocoMemoria * dado){
	}


	//Ultimo metodo do meualoc
	int imprime(int count){
		//imprime apenas os espaços vazios
		Bloco * novo = inicio;

		for(; novo != NULL; novo = novo->prox){
			if(novo->livre == 0){
				count++;
				std:: cout << novo->tamanho << " ";
				std:: cout << novo->livre << " ptr: ";				
				std:: cout << novo->ptr_posicao << "\n";
			}

		}
		return count;
	}

	int maior_elemento(unsigned short int maior){
		Bloco * novo = inicio;		
		if(novo == NULL){
			return -1;
		}

		while(novo != NULL){
			if(novo->tamanho > maior && novo->livre == 0) maior = novo->tamanho;
			novo = novo->prox;
		}
		return maior;


	}


	unsigned short int media_blocos_vazios(unsigned short int soma_espaco_livre){
		Bloco * novo = inicio;
		
		if(novo == NULL){
			return -1;
		}

		while(novo != NULL){
			
			if(novo->livre == 0)soma_espaco_livre = soma_espaco_livre + novo->tamanho;
			novo = novo->prox;
		}
		return soma_espaco_livre;

	}



	char * verificaLista(char * elemento){
		if(inicio == NULL){
			return 0;
		}

		Bloco * novo =  inicio;
		for(; novo != NULL; novo = novo->prox)
			if(novo->ptr_posicao ==  elemento && novo->livre == 0) return novo->ptr_posicao	;

		

	}

	int _free(char * ponteiro){
		Bloco * novo = inicio;
		if(novo == NULL){
			return -1;
		}
		while(novo != NULL && novo->ptr_posicao != ponteiro)novo = novo->prox;
		novo->livre = 0;
		return 1;
	}

	int coalesce(){
		Bloco * novo = inicio;
		Bloco * aux = new Bloco;

		if(novo == NULL) return -1;
		while(novo != NULL){
			aux = novo->prox;
			if( novo->livre == 0 && aux->livre == 0){
				novo->prox = aux->prox;
				novo->tamanho = novo->tamanho + aux->tamanho;
				delete aux;
			}

			novo = novo->prox;

		}
		return 1;

	}


	~Lista(){
		Bloco * novo = new Bloco;
		novo =  inicio;
		while(novo != NULL){
			Bloco * aux = inicio->prox;
			novo = novo->prox;
			delete aux;

		}
		delete novo;
	}

};








