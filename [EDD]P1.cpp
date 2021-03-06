#include<iostream>
#include<conio.h>
#include<cstring>
#include<string>
#include<bits/stdc++.h>
#include<sstream> 
#include<fstream> 

//para graphviz
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

using namespace::std;

struct nodo{
	char dato;
	int x,y,contador;
	string palabra;
	nodo* siguiente;
	nodo* atras;
}*primero, *ultimo;

struct pila1{
	string dato;
	string buscado;
	string reemplazado;
	string estado;
	string palabra;
	string posicion;
	int x;
	int y;
	pila1* siguiente;
}*primeroP1;

struct pila2{
	string dato;
	string buscado;
	string reemplazado;
	string estado;
	string palabra;
	string posicion;
	int x;
	int y;
	pila2* siguiente;
}*primeroP2;


struct listaSimple{
	string buscadas;
	string reemplazadas;
	listaSimple* siguiente;
}*primeroLS, *ultimoLS;


struct listaCircular{
	string nombre;
	string direccion;
	int contador;
	listaCircular* siguiente;
}*primeroLC, *ultimoLC;


void Menu();
void AgregarNodo(char,int,int,int);
void AgregarNodoInicio(char,int,int,int,string);
void AgregarNodoFinal(char,int,int,int,string);
void AgregarNodoPosicion(char,int,int,int,int,string);
void EliminarNodo(int,int);
void BuscarNodo(string,string);
void ModificarPalabra(int,int,string);
void EliminarBuscarReemplazar(int Ex,int Ey);
void MostrarLista1();
void MostrarLista2();
void AgregarTexto();
void EnviarDatos();
void Buscar();
void Tecla();
bool Vacia();
void TeclaDelete();
void EnviarPalabraReemplazar();
void MandaraEliminarBuscar(int,int,int,int,string);
void ModificarPosiciones(int,int,int);
void CambiarEditorTexto();

//archivos
void AbrirArchivo();
void GuardarArchivo();
void GuardarTextoArchivoLista();
void vaciarListaDoble();


int TamanioListaDoble();
string texto;
string agregarPalabra;
int posx = 0;
int posy = 2;
int contadorNodos = 1;
int contPalabrasModificadas=0;
int contArchivosRecientes;
//pilas
string retornarCadena(int);
bool RetornarUltima();
bool RetornarUltima2();
string BanderaRevertir;
string RevertirBuscar;
string RevertirReemplazar;
string RevertirCaracter;

string BanderaRevertir2;

//Pra Pila 1
void InsertarPila1(string,string,string,string,int,int);
void MostrarPila1();
void BuscarPila1();
void ModificarPila1();
void EliminarPila1(string,string,int,int);
void EliminarPila1Otro();

//Pra Pila 2
void InsertarPila2(string,string,string,string,int,int);
void MostrarPila2();
void EliminarPila2();


//paralistasimple
void insertarListaSimple(string,string);
void MostrarListaSimple();


//paralistacircular
void InsertarListaCircular(string,string,int);	
void MostrarListaCircular();
int contListaCircular;


//Reportes
void PedirOpcionReporte();
void GenerarGraficaListaDoble();
void GenerarGraficaListaSimple();
void GenerarGraficaPila1();
void GenerarGraficaArchivos();

int main(){
	Menu();
//	Tecla();
	getch();
	return 0;
}

void Menu(){
	int opcion = 0;
	do{
		cout << "\n------Menu------\n" ;
		cout << "1)Crear Archivo \n" ;
		cout << "2)Abrir Archivo \n" ;
		cout << "3)Archivos Recientes \n";
		cout << "4)MostrarListas \n";
		cout << "5)salir \n";
		cout << "Opcion :";
		cin >> opcion;
		switch(opcion){
			case 1:
				EnviarDatos();
				cout << "\n";
				system("pause");			
				break;
			case 2:
				AbrirArchivo();				
				system("pause");
				EnviarDatos();
				break;
			case 3:		
				MostrarListaCircular();								    
				system("pause");
				break;
			case 4:
				MostrarLista1();
				MostrarPila1();
				MostrarPila2();
				MostrarListaSimple();
				system("pause");
				break;			
			}
		system("cls");
	}while(opcion!=5);
	cout << "**fin programa**";
}

void AgregarTexto(){
	char texto[100];
	int longitud;
	cout << "Ingrese Texto : ";
	cin.getline(texto,100,'\n');
	
	longitud = strlen(texto);
	int cont = 0, i =0;
	
	
	while(i<longitud){
		cout << "-"<< texto[i] <<endl;
		i++;
		/*
		while(i<longitud && texto[i]==' '){
			i++;
		}
		
		if(cont<longitud){
			cont++;
		}
		
		while(i<longitud && texto[i]!=' '){
			i++;
		} */
	}
	
	cout << "\n la cantida es : " << i;
}

void EnviarDatos(){	// ME Muestra el (Editor de texto) con opciones
	system("cls");
	cout << " ^w(Buscar y Reemplazar)     ^c(Reportes)     s^(Guardar)     x^(Escape) \n" ;
	cout << "D-----------------------------------------------------------------------D\n" ;
	cout << texto;
	char key;
	int ascii;		
	while(1){
		key = getch();
		ascii = key;
	//	if(ascii > 0){
			if(ascii == 24){ //tecla ctrl+x
				system("cls");
				Menu();		
			}else if(ascii == 13){   //tecla enter
				cout << "\n";
				AgregarNodo('\n',posx,posy,contadorNodos);				
				contadorNodos++;							
				texto += "\n";								
				
				int cp = posx;
				cp = cp - agregarPalabra.size();
				for (int i = cp; i < posx; i++) {
					ModificarPalabra(i,posy,agregarPalabra);
				} 
				posy++;
				posx=0;	
				agregarPalabra= "";
				
			}else if(ascii == 8){ // tecla delete
				TeclaDelete();
				posx--;
				contadorNodos--;
				EnviarDatos();
			}else if(ascii == 23){ // tecla ctrl+w
			    BanderaRevertir = "falso";
				contPalabrasModificadas = 0;
				EnviarPalabraReemplazar();
				EnviarDatos();
			}else if(ascii == 32){ // tecla espacio
				cout << key;
				AgregarNodo(key,posx,posy,contadorNodos);
				posx++;
				contadorNodos++;
				texto += key;
				
				int cp = posx;
				cp = cp - agregarPalabra.size() -1;
				for (int i = cp; i < posx-1; i++) {
					ModificarPalabra(i,posy,agregarPalabra);
				}
				agregarPalabra= "";
			}else if(ascii == 26){ // tecla ctrl+z
				if(primeroP1!=NULL){					
					bool m = RetornarUltima();
					if(m==true){
						BanderaRevertir = "verdadero";
						BuscarNodo(RevertirBuscar,RevertirReemplazar);
						CambiarEditorTexto();
						BanderaRevertir = "falso";										
					}else{
						char temp[1];
						strcpy(temp,RevertirCaracter.c_str());
						AgregarNodo(temp[0],posx,posy,contadorNodos);
					
						EliminarPila1Otro();
						string n = retornarCadena(posx);
						string m = retornarCadena(posy);
						InsertarPila2("Null","Null",RevertirCaracter,n+","+m,posx,posy);
						agregarPalabra+=RevertirCaracter;
						BanderaRevertir = "falso";					
						texto+=RevertirCaracter;
						contadorNodos++;
						posx++;					
					}					
				}else{
					cout << "\n\n\n ** Pila vacia ** \n";
					system("pause");
				}
				EnviarDatos();
				
			}else if(ascii == 25){ // tecla ctrl+y
				if(primeroP2!=NULL){				
					bool m = RetornarUltima2();
					if(m==true){
						BanderaRevertir2 = "verdadero";
						BuscarNodo(RevertirReemplazar,RevertirBuscar);
						CambiarEditorTexto();
						BanderaRevertir2 = "falso";										
					}else{
						TeclaDelete();
						posx--;
						contadorNodos--;
						EliminarPila2();
						EnviarDatos();	
					}					
				}else{
					cout << "\n\n\n ** Pila 2 vacia ** \n";
					system("pause");
				}
				EnviarDatos();
				
			}else if(ascii == 3){ // tecla ctrl+c				
				PedirOpcionReporte();
				EnviarDatos();
				
			}else if(ascii == 19){ // tecla ctrl+s				
				GuardarArchivo();				
				EnviarDatos();				
			}else{
				cout << key;
				AgregarNodo(key,posx,posy,contadorNodos);
				posx++;
				contadorNodos++;
				texto += key;
				agregarPalabra+=key;
			}	
		//}		
											
	}	
	cout << "\n\n";
}

void EnviarPalabraReemplazar(){
	string pBuscar;
	string pReemplazar;
	string pRecibir;
	string tArreglo[4];
	cout << "\n\n\nBuscar Y Reemplazar: ";
	cin >> pRecibir;	
	string tpalabra;		
	int n = 0;			
	int tcont = pRecibir.size();
	char str[tcont];     
	char*coma;
	strcpy(str, pRecibir.c_str());	 
	coma = strtok(str,";");
	while(coma!=NULL){
		tArreglo[n] = coma;
		n++;
		coma = strtok(NULL,";");
	}
	pBuscar = tArreglo[0];
	pReemplazar = tArreglo[1];
	
	BuscarNodo(pBuscar,pReemplazar);
	CambiarEditorTexto();
	cout<<"\n** "<<contPalabrasModificadas<<" Palabras Afectadas"<<" **"<<"\n\n\n";
	system("pause");
}

void MandaraEliminarBuscar(int mx,int my,int tamanio, int cont,string pSustituir){
	contPalabrasModificadas++;
	int cSus = pSustituir.size();
//	cout << "\n palabra sust :"<<pSustituir<<endl;
	for (int i = mx; i <= mx+tamanio; i++) {
 	 	EliminarBuscarReemplazar(i,my);
	}
	
	int Desplegarx = mx;
	char temp[cSus];		
	strcpy(temp,pSustituir.c_str());
	int susti=0;
	int agregarC = cont;
	for (int i = cont; i < cont+cSus; i++) {		
		AgregarNodoPosicion(temp[susti],i,mx,my,agregarC,pSustituir);	
		mx++;
		susti++;
		agregarC++;	
	//	tamanioDes++;	
	}		
	ModificarPosiciones(Desplegarx,my,cont);	
}

void TeclaDelete(){
	nodo* actual = new nodo();
	actual = ultimo;
	char bus = actual -> dato;
	int a = actual -> x;
	int b = actual -> y;
	if(bus=='\n'){
		posy--;
		posx = a+1;
	} 	
	EliminarNodo(a,b);
		
 	string s = retornarCadena(a);   
 	string g = retornarCadena(b);  
	string ma = s+","+g;
	string zdato(1,bus);	
	InsertarPila1("Null","Null",zdato,ma,a,b);
		
	CambiarEditorTexto();

	int asd = 0;
	asd = agregarPalabra.size();
	char temp[asd];
	
	if(asd!=0){
		strcpy(temp,agregarPalabra.c_str());
		agregarPalabra = "";
		for (int i = 0; i < asd-1; i++) {
 	 	agregarPalabra+= temp[i];
		}
	}
		
}

void AgregarNodo(char n,int nx,int ny,int cont){
	nodo* nuevo = new nodo();
	nuevo -> dato = n;
	nuevo -> x = nx;
	nuevo -> y = ny;
	nuevo -> contador = cont;
	
	if(primero == NULL){
		primero = nuevo;
		primero -> siguiente = NULL;
		primero -> atras = NULL;
		ultimo = primero;
	}else{
		ultimo -> siguiente = nuevo;
		nuevo -> siguiente = NULL;
		nuevo -> atras = ultimo;
		ultimo = nuevo;
	}
	
//	cout << "Nodo Ingresado \n";	
}

void AgregarNodoInicio(char n,int nx,int ny,int cont,string pagregar){
	nodo* nuevo = new nodo();
	nuevo -> dato = n;
	nuevo -> x = nx;
	nuevo -> y = ny;
	nuevo -> contador = cont;
	nuevo -> palabra = pagregar;
	nuevo -> siguiente = NULL;
	nuevo -> atras = NULL;
	
	if(Vacia()){
		primero  = nuevo;
		ultimo = nuevo;
	}else {
		nuevo -> siguiente = primero;
		primero -> atras = nuevo;
		primero = nuevo;
	}
}

void AgregarNodoFinal(char n,int nx,int ny,int cont,string pagregar){
	nodo* nuevo = new nodo();
	nuevo -> dato = n;
	nuevo -> x = nx;
	nuevo -> y = ny;
	nuevo -> contador = cont;
	nuevo -> palabra = pagregar;
	nuevo -> siguiente = NULL;
	nuevo -> atras = NULL;
	
	if(Vacia()){
		primero  = nuevo;
		ultimo = nuevo;
	}else {
		ultimo -> siguiente = nuevo;
		nuevo -> atras = ultimo;
		ultimo = nuevo;
	}
}

void AgregarNodoPosicion(char n,int npos,int nx,int ny,int cont,string pSustituir){
	nodo* nuevo = new nodo();
	nuevo -> dato = n;
	nuevo -> x = nx;
	nuevo -> y = ny;
	nuevo -> contador = cont;
	nuevo -> palabra = pSustituir;
	nuevo -> siguiente = NULL;
	nuevo -> atras = NULL;
	
	if(Vacia()){
		primero = nuevo;
		ultimo = nuevo;
	}else{
		if(npos == 1){
			AgregarNodoInicio(n,nx,ny,cont,pSustituir);
			
		}else if(npos== (TamanioListaDoble()+1)){
			AgregarNodoFinal(n,nx,ny,cont,pSustituir);
			
		}else if(npos> 1 && npos < (TamanioListaDoble()+1)){
			nodo* aux;
			aux = primero;
			for(int i=1 ; i<npos ; i++){
				aux = aux -> siguiente;
			}
			aux -> atras -> siguiente = nuevo;
			nuevo -> siguiente = aux;
			nuevo -> atras = aux -> atras;
			aux -> atras = nuevo;
		}else{
			cout << "Error, la posicion es invalida";
		}
	}
	
//	cout << "Nodo Ingresado \n";	
}

void EliminarNodo(int Ex, int Ey){
	nodo* actual = new nodo();
	actual = primero;
	nodo* anterior = new nodo();
	anterior = NULL;
	bool encontrado = false;
	
	if(primero != NULL){
		while(actual!=NULL && encontrado!=true){
			if(actual->x == Ex && actual->y == Ey){
				if(actual==primero){
					primero = primero->siguiente;
					primero->atras = NULL;
				}else if(actual==ultimo){
					anterior->siguiente = NULL;
					ultimo = anterior;					
				}else{
					anterior->siguiente = actual->siguiente;
					actual->siguiente->atras = anterior;
				}
			//	cout << "\n Nodo Eliminado";
				encontrado = true;
			}
			anterior = actual;
			actual = actual->siguiente;
		}		
		if(!encontrado){
			cout << "\n No encontrado";
		}
	}else{
		cout << "\n Lista Vacia";
	}
}

void BuscarNodo(string nodoBuscado, string nodoSustituir){
	nodo* actual = new nodo();
	actual = primero;
	bool encontrado = false;
	int contBus = 0;
	int tamanio = nodoBuscado.size();
	if(primero != NULL){
		while(actual!=NULL){ //&& encontrado!=true){
			if(actual->palabra == nodoBuscado){
				contBus++;
				if(BanderaRevertir=="verdadero"){   //si existe dato de buscar y reemplazar pila1
					if(contBus==1){
					MandaraEliminarBuscar(actual->x,actual->y,tamanio-1,actual->contador,nodoSustituir);
					EliminarPila1Otro();
					InsertarPila2(nodoSustituir,nodoBuscado,"Null","Null",0,0);																							
					}
				}else{
					if(BanderaRevertir2 =="verdadero"){//si existe dato buscar y reemplzar pila2
						if(contBus==1){
						MandaraEliminarBuscar(actual->x,actual->y,tamanio-1,actual->contador,nodoSustituir);
						InsertarPila1(nodoBuscado,nodoSustituir,"Null","Null",0,0);
						EliminarPila2();																								
						}
					}else{
						if(contBus==1){
						MandaraEliminarBuscar(actual->x,actual->y,tamanio-1,actual->contador,nodoSustituir);
						insertarListaSimple(nodoBuscado,nodoSustituir);
						InsertarPila1(nodoBuscado,nodoSustituir,"Null","Null",0,0);																								
						}
					}
					
				}								
				
				if (contBus==tamanio){
					contBus = 0;
				}					
				//encontrado = true;
			}
			actual = actual->siguiente;
		}		
	/*	if(!encontrado){
			cout << "\n No encontrado boolll";
		} */
	}else{
		cout << "\n Lista Vacia";
	}	
}

void EliminarBuscarReemplazar(int Ex,int Ey){
	nodo* actual = new nodo();
	actual = primero;
	nodo* anterior = new nodo();
	anterior = NULL;
	bool encontrado = false;
	
	if(primero != NULL){
		while(actual!=NULL && encontrado!=true){
			if(actual->x == Ex && actual->y == Ey){
				if(actual==primero){
					primero = primero->siguiente;
					primero->atras = NULL;
				}else if(actual==ultimo){
					anterior->siguiente = NULL;
					ultimo = anterior;					
				}else{
					anterior->siguiente = actual->siguiente;
					actual->siguiente->atras = anterior;
				}
			//	cout << "\n Nodo Eliminado";
				encontrado = true;
			}
			anterior = actual;
			actual = actual->siguiente;
		}		
		if(!encontrado){
			cout << "\n No encontrado";
		}
	}else{
		cout << "\n Lista Vacia";
	}
}

void ModificarPalabra(int Modix, int Modiy,string nodoModificar){
	nodo* actual = new nodo();
	actual = primero;
	bool encontrado = false;
	if(primero != NULL){
		while(actual!=NULL && encontrado!=true){
			if(actual->x == Modix && actual->y == Modiy){
		//		cout << "\n dato: -" << actual->dato << " - encontrado \n";
				actual -> palabra = nodoModificar;
		//		cout << "\n modificado--";
				encontrado = true;
			}
			actual = actual->siguiente;
		}		
		if(!encontrado){
			cout << "\n No encontrado";
		}
	}else{
		cout << "\n Lista Vacia";
	} 
}

void ModificarPosiciones(int Modix, int Modiy,int Modic){
	nodo* actual = new nodo();
	actual = primero;
	bool encontrado = false;	
	int xSus = Modix;
	int cSus = Modic;
	if(primero != NULL){
		while(actual!=NULL){
			if(actual->y == Modiy && actual->x >= Modix){
				actual -> x = xSus;
				xSus++;							
			}
			if(actual->contador>=Modic){
				actual -> contador = cSus;
				cSus++;
			}
			actual = actual->siguiente;
		}		
	}else{
		cout << "\n Lista Vacia";
	} 
}

int TamanioListaDoble(){
	int cont = 0;
	nodo *actual;
	actual = primero;
	while(actual!=NULL){
		cont++;
		actual = actual -> siguiente;
	}
	return cont;
}

bool Vacia(){
	if(primero == NULL && ultimo == NULL){
		return true;		
	}else{
		return false;
	}
}

void Buscar(){
	char i;
	char j;
	cout << "\n\n buscar dato: " ;
	cin >> i ;
	cout << "\n\n Modificar dato: " ;
	cin >> j ;
//	ModificarNodo(i,j);
	cout << "\n\n fin buscar  ";  
}

void CambiarEditorTexto(){
	texto = "";
	nodo* actual = new nodo();
	actual = primero;
	if(primero!=NULL){
		while(actual!=NULL){
			texto +=actual -> dato;
			actual = actual -> siguiente;
		}
	}else{
		cout << "\n lista vacia \n";
	}
	cout << "\n";
}

void MostrarLista1(){
	cout << "\n Lista = \n";
	nodo* actual = new nodo();
	actual = primero;
	if(primero!=NULL){
		while(actual!=NULL){
			
			if(actual->dato == '\n'){
				cout <<actual->contador <<"-" << ' ' << "-(" << actual -> x<<","<<actual -> y<<")"<<"->"<<actual -> palabra<<"\n";
			}else{
				cout <<actual->contador <<"-" << actual -> dato << "-(" << actual -> x<<","<<actual -> y<<")"<<"->"<<actual -> palabra<<"\n";				
			}
			actual = actual -> siguiente;
		}
	}else{
		cout << "\n lista vacia \n";
	}
	cout << "\n";
}

void MostrarLista2(){
	nodo* actual = new nodo();
	actual = ultimo;
	if(primero!=NULL){
		while(actual!=NULL){
			cout << "\n" << actual -> dato;
			actual = actual -> atras;
		}
	}else{
		cout << "\n lista vacia \n";
	}
}

void Tecla(){
	char key;
	int ascii;
		
	cout << "presione una tecla:"<< endl ;
	
	while(1){
		key = getch();
		ascii = key;
		
		if(ascii > 0){
			if(ascii == 27){
			break;		
			}else if(ascii == 13){
			cout << "presiono la tecla -> " << "enter" << " codigo ascci es :" << ascii << endl;
			}else if(ascii == 72){
			cout << " arriba\n";
			}else if(ascii == 80){
			cout << "abajo\n";
			}else if(ascii == 75){
			cout << " izquierda\n";;
			}else if(ascii == 77){
			cout << " derecha\n";
			}
			else{
			cout << "presiono la tecla -> " << key << " codigo ascci es :" << ascii << endl;
			}
		}
											
	}
	
	cout << "Finalizo"<< endl ;
}

string retornarCadena(int entero){
	stringstream ss; 
	ss<<entero;  
 	string s;  
    ss>>s;    
	return s;
}

void vaciarListaDoble(){
	nodo* actual = new nodo();
	actual = primero;
	nodo* anterior = new nodo();
	anterior = NULL;
	if(primero != NULL){
		while(actual!=NULL){		
				if(actual==primero){
					primero = primero->siguiente;
					primero->atras = NULL;
				}else if(actual==ultimo){
					anterior->siguiente = NULL;
					ultimo = anterior;					
				}else{
					anterior->siguiente = actual->siguiente;
					actual->siguiente->atras = anterior;
				}			
			anterior = actual;
			actual = actual->siguiente;
		}		
	}else{
	
	}
}

//Para las Pilas

void InsertarPila1(string pbuscado,string preemplazado,string ppalabra,string pposicion,int px,int py){
	pila1* nuevo = new pila1();
	nuevo -> buscado = pbuscado;
	nuevo -> reemplazado = preemplazado;
	nuevo -> estado = "No Revertido";
	nuevo -> palabra = ppalabra;
	nuevo -> posicion = pposicion;
	nuevo -> x = px;
	nuevo -> y = py;
	
	
	nuevo->siguiente = primeroP1;
	primeroP1 = nuevo;
		
}

void MostrarPila1(){
	cout<<endl<<"--Pila1---";
	pila1* actual = new pila1();
	actual = primeroP1;
	
	if(primeroP1!=NULL){
		while(actual!=NULL){
			cout<<endl<<"buscado : "<<actual->buscado;
			cout<<endl<<"reemplazado : "<<actual->reemplazado;
			cout<<endl<<"estado : "<<actual->estado;
			cout<<endl<<"palabra : "<<actual->palabra;
			cout<<endl<<"posicion : "<<actual->posicion;
			cout<<endl<<"        |";
			actual = actual->siguiente;
		}
	}else{
		cout<<endl<<"la Pila esta vacia"<<endl;
	}
		
}

void BuscarPila1(){
	pila1* actual = new pila1();
	actual = primeroP1;
	string nodoBuscado = "";
	bool encontrado = false;
	cout<<"\nnodo buscar :";
	cin>> nodoBuscado;
	
	if(primeroP1!=NULL){
		while(actual!=NULL && encontrado != true){
			if(actual->dato==nodoBuscado){
				cout<<endl<<"dato :"<<nodoBuscado<<endl;
				encontrado=true;
			}
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout<<endl<<"pila no encontrada"<<endl;
		}
	}else{
		cout<<endl<<"la Pila esta vacia"<<endl;
	}		
} 

void ModificarPila1(){
	pila1* actual = new pila1();
	actual = primeroP1;
	string nodoBuscado = "";
	bool encontrado = false;
	cout<<"\nnodo modificar :";
	cin>> nodoBuscado;
	
	if(primeroP1!=NULL){
		while(actual!=NULL && encontrado != true){
			if(actual->dato==nodoBuscado){
				cout<<endl<<"dato modificar : ";
				cin>> actual->dato;
				cout<<endl<<"modificado ";
				encontrado=true;
			}
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout<<endl<<"pila no encontrada"<<endl;
		}
	}else{
		cout<<endl<<"la Pila esta vacia"<<endl;
	}
}

void EliminarPila1(string nodoBuscado,string nodoreemplazado,int ex,int ey){
	pila1* actual = new pila1();
	actual = primeroP1;
	pila1* anterior = new pila1();
	anterior = NULL;
    bool encontrado = false;
	if(primeroP1!=NULL){
		while(actual!=NULL && encontrado != true){
		//	if((actual->buscado==nodoBuscado && actual->reemplazado==nodoreemplazado)
		//		||(actual->x==ex && actual->y==ey)){
				if(actual==primeroP1){
					primeroP1 = primeroP1->siguiente;
				}else{
					anterior->siguiente = actual->siguiente;
				}
				cout<<endl<<"eliminado";
				encontrado=true;
			//}
			anterior = actual;
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout<<endl<<"pila no encontrada"<<endl;
		}
	}else{
		cout<<endl<<"la Pila esta vacia"<<endl;
	}
}

void EliminarPila1Otro(){
	if(primeroP1==NULL){
		cout<<endl<<"la Pila esta vacia"<<endl;
		return;
	}
	pila1* actual = new pila1();
	actual = primeroP1;
	cout<<endl<<"Eliminado ->"<<actual->palabra<<endl;
	primeroP1 = actual->siguiente;
	delete(actual);
}

bool RetornarUltima(){
	bool mandar;
	pila1* actual = new pila1();
	actual = primeroP1;
	if(actual->buscado == "Null"){
		mandar = false;
		RevertirCaracter = actual->palabra;
	}else{
		mandar = true;
		RevertirBuscar = actual->reemplazado;
		RevertirReemplazar = actual->buscado;
	}
	return mandar; 
}


//Para la Pila 2
void InsertarPila2(string pbuscado,string preemplazado,string ppalabra,string pposicion,int px,int py){
	pila2* nuevo = new pila2();
	nuevo -> buscado = pbuscado;
	nuevo -> reemplazado = preemplazado;
	nuevo -> estado = "Revertido";
	nuevo -> palabra = ppalabra;
	nuevo -> posicion = pposicion;
	nuevo -> x = px;
	nuevo -> y = py;
	
	nuevo->siguiente = primeroP2;
	primeroP2 = nuevo;		
}

void MostrarPila2(){
	cout<<endl<<"--Pila2---";
	pila2* actual = new pila2();
	actual = primeroP2;
	
	if(primeroP2!=NULL){
		while(actual!=NULL){
			cout<<endl<<"buscado : "<<actual->buscado;
			cout<<endl<<"reemplazado : "<<actual->reemplazado;
			cout<<endl<<"estado : "<<actual->estado;
			cout<<endl<<"palabra : "<<actual->palabra;
			cout<<endl<<"posicion : "<<actual->posicion;
			cout<<endl<<"        |";
			actual = actual->siguiente;
		}
	}else{
		cout<<endl<<"la Pila 2 esta vacia"<<endl;
	}
		
}

void EliminarPila2(){
	if(primeroP2==NULL){
		cout<<endl<<"la Pila esta vacia"<<endl;
		return;
	}
	pila2* actual = new pila2();
	actual = primeroP2;
	cout<<endl<<"Eliminado ->"<<actual->palabra<<endl;
	primeroP2 = actual->siguiente;
	delete(actual);
}

bool RetornarUltima2(){
	bool mandar;
	pila2* actual = new pila2();
	actual = primeroP2;
	if(actual->buscado == "Null"){
		mandar = false;
		RevertirCaracter = actual->palabra;
	}else{
		mandar = true;
		RevertirBuscar = actual->reemplazado;
		RevertirReemplazar = actual->buscado;
	}
	return mandar; 
}


//Para Listas Simples
void insertarListaSimple(string buscado,string reemplazado){
	listaSimple*nuevo = new listaSimple();

	nuevo->buscadas = buscado;
	nuevo->reemplazadas = reemplazado;
	
	if(primeroLS==NULL){
		primeroLS = nuevo;
		primeroLS->siguiente = NULL;
		ultimoLS = nuevo;
	}else{
		ultimoLS->siguiente = nuevo;
		nuevo->siguiente = NULL;
		ultimoLS =nuevo;
	}
	
}

void MostrarListaSimple(){
	listaSimple*actual = new listaSimple();
	actual = primeroLS;
	if(primeroLS!=NULL){
		while(actual!=NULL){
			cout<<"--"<<actual->buscadas<<actual->reemplazadas<<"--"<<endl;
			actual = actual->siguiente;
		}
	}else{
		cout<<"\n\n lista simple vacia\n\n";
	}
}


//Para Lista Circular

void InsertarListaCircular(string Cnombre,string Cdireccion,int CcontadorCircular){
	listaCircular*nuevo = new listaCircular();

	nuevo->nombre = Cnombre;
	nuevo->direccion = Cdireccion;
	nuevo->contador = CcontadorCircular;
	if(primeroLC==NULL){
		primeroLC = nuevo;
		primeroLC->siguiente = primeroLC;
		ultimoLC = primeroLC;
	}else{
		ultimoLC->siguiente = nuevo;
		nuevo->siguiente = primeroLC;
		ultimoLC =nuevo;
	}	
}

void MostrarListaCircular(){
	system("cls");
	cout << "        ^c(GenerarReporte de Archivos)            x^(Escape) \n" ;
	cout << "D-----------------------------------------------------------------------D\n" ;
	cout<<"\n\n        Archivos Recientes\n\n\n";
	listaCircular*actual = new listaCircular();
	actual = primeroLC;
	
	if(primeroLC!=NULL){
		do{
			cout<<"        "<<actual->contador<<") "<<actual->nombre<<"        "<<actual->direccion<<"--"<<"\n";
			actual = actual->siguiente;
		}while(actual!=primeroLC);
	}else{
		cout<<"\n\n lista circular vacia\n\n";
	}
	
	char key;
	int ascii;
	while(1){
		key = getch();
		ascii = key;
		if(ascii == 24){ //tecla ctrl+x
				system("cls");
				Menu();	
		}else if(ascii == 3){ // tecla ctrl+c				
				GenerarGraficaArchivos();
				MostrarListaCircular();								
		}else if(ascii>=49 && ascii<=57)
		{
			
		}else{
			
		}
	}
	cout<<"\n\n\n";
}

//Archivos
void AbrirArchivo(){
	ifstream arch;
    string direccionAbrir = "C:\\Users\\HP\\Desktop\\Archivo";
	string nombreAbrir;
	cout<<"\n\n\n Nombre de Archivo: ";
	cin>>nombreAbrir;
	direccionAbrir+= "\\"+nombreAbrir+".txt";
	
	arch.open(direccionAbrir.c_str(),ios::in);
	
	if(arch.fail()){
		cout<<"\n\nno se encontro archivo"<<endl;
		Menu();
	}
	
	InsertarListaCircular(nombreAbrir,direccionAbrir,contArchivosRecientes+1);
	contArchivosRecientes++;
	texto="";
	while(!arch.eof()){
		getline(arch,texto);		
	}
	arch.close();
	GuardarTextoArchivoLista();
	
	cout<<"\n\n**texto de archivo agregado a editor**\n"<<endl;
	system("pause");
}

void GuardarArchivo(){
	ofstream arch;
	string direccionAbrir = "C:\\Users\\HP\\Desktop\\Archivo";
	string nombreAbrir;
	cout<<"\n\n\n Nombre de Archivo: ";
	cin>>nombreAbrir;
	direccionAbrir+= "\\"+nombreAbrir+".txt";

	arch.open(direccionAbrir.c_str(),ios::out);
	
	if(arch.fail()){
		cout<<"\n\nno se abrio archivo"<<endl;
		exit(1);
	}else{
		cout<<"\n\n** Archivo Creado **\n\n"<<endl;
	}

	arch<<texto;	
	arch.close();
	
	system("pause");
}

void GuardarTextoArchivoLista(){
	//vaciarListaDoble();
	posx = 0;
	posy = 2;
	contadorNodos = 1;
	contPalabrasModificadas=0;
	int asd = 0;
	asd = texto.size();
	char temp[asd];
	
	if(asd!=0){
		strcpy(temp,texto.c_str());
		for (int i = 0; i < asd; i++) {			
 	 		if(temp[i]==' '){ 	 			
				AgregarNodo(' ',posx,posy,contadorNodos);
				posx++;
				contadorNodos++;
				
				int cp = posx;
				cp = cp - agregarPalabra.size() -1;
				for (int i = cp; i < posx-1; i++) {
					ModificarPalabra(i,posy,agregarPalabra);
				}
				agregarPalabra="";
			}else{
				AgregarNodo(temp[i],posx,posy,contadorNodos);
				posx++;
				contadorNodos++;
				agregarPalabra+=temp[i];
			}				
		}
	}
}



//para Reportes

void PedirOpcionReporte(){
	int opcion=0;
	cout << "\n\n\nReportes:  1)Lista     2) Palabras Buscadas     3)Palabras Ordenadas \n\n" ;
	cout << "Eliga Opcion: ";
	cin >> opcion;
	if(opcion==1){				
		GenerarGraficaListaDoble();	
		system("pause");	
	}else if(opcion==2){
		GenerarGraficaPila1();
		system("pause");		
	}else if(opcion==3){
		GenerarGraficaListaSimple()	;
		system("pause");	
	}else{
		cout << "\n\n **Opcion Incorrecta**";
	}	
}

void GenerarGraficaListaDoble(){
	int cont = 0;
	string concatenar = "";
	
	nodo*actual = new nodo();
	actual=primero;
	ofstream arch;
	arch.open("listadoble.dot",ios::out);
	arch<<"digraph G{\n";
	arch<<"rankdir = LR;\n";
	arch<<"null1 [label=\"NULL\"];\n";
	arch<<"null2 [label=\"NULL\"];\n";		
	
	while (actual!=NULL) {	
		concatenar+="char"+retornarCadena(cont)+"[label=\""+actual->dato+"\"];\n";
      	actual=actual->siguiente;
      	cont++;		
    }
    
    for(int i=0;i<cont-1;i++){
    	concatenar+="char"+retornarCadena(i)+"->char"+retornarCadena(i+1)+";\n";
    	concatenar+="char"+retornarCadena(i+1)+"->char"+retornarCadena(i)+";\n";   	
	}
		
	arch<<concatenar;
	arch<<"null1->char0;\n";
	arch<<"char0->null1;\n";
	arch<<"char"+retornarCadena(cont-1)+"->null2;\n";
	arch<<"null2->char"+retornarCadena(cont-1)+";\n";
  	
	arch<<"}\n";
	arch.close();	
	
	system("dot -Tpng listadoble.dot -o listadoble.png");
	cout << "\n\n*** Reporte Lista generada\n\n\n";
	system("pause");
}

void GenerarGraficaPila1(){
	int cont = 0;
	int cont2 = 0;
	string concatenar = "";
	string p1 = "Palabra Buscada : ";
	string p2 = "Reemplazada por : ";
	string p3 = "Estado : ";
	string p4 = "Palabra : ";
	string p5 = "Posicion : ";
	
	pila1*actual = new pila1();
	actual=primeroP1;
	
	pila2*actual2 = new pila2();
	actual2=primeroP2;
	
	ofstream arch;
	arch.open("listapila11.dot",ios::out);
	arch<<"digraph G{\n";
	arch<<"rankdir = LR;\n";
			
	while (actual!=NULL) {	
		concatenar+="char"+retornarCadena(cont)+"[shape=box label=\""
		+p1+actual->buscado+"\n"
		+p2+actual->reemplazado+"\n"
		+p3+actual->estado+"\n"
		+p4+actual->palabra+"\n"
		+p5+actual->posicion+"\n"
		+"\"style=filled fillcolor=green];\n";
      	actual=actual->siguiente;
      	cont++;		
    }
    for(int i=0;i<cont-1;i++){
    	concatenar+="char"+retornarCadena(i)+"->char"+retornarCadena(i+1)+";\n"; 	
	}		
	arch<<concatenar;
	
	
	concatenar = "";
	while (actual2!=NULL) {	
		concatenar+="p"+retornarCadena(cont2)+"[shape=box label=\""
		+p1+actual2->buscado+"\n"
		+p2+actual2->reemplazado+"\n"
		+p3+actual2->estado+"\n"
		+p4+actual2->palabra+"\n"
		+p5+actual2->posicion+"\n"
		+"\"style=filled fillcolor=red];\n";
      	actual2=actual2->siguiente;
      	cont2++;		
    }

    for(int i=0;i<cont2-1;i++){
    	concatenar+="p"+retornarCadena(i)+"->p"+retornarCadena(i+1)+";\n"; 	
	}		
	arch<<concatenar;
	
	arch<<"}\n";
	arch.close();	
	
	system("dot -Tpng listapila11.dot -o listapila11.png");
	cout << "\n\n** Reporte Palabras Buscadas generada\n\n\n";
	system("pause");
}

void GenerarGraficaListaSimple(){
	int cont = 0;
	int cont2 = 0;
	string concatenar = "";
	string p1 = "Reemplazada por : ";
	string p2 = "Reemplazo a : ";
	
	listaSimple*actual = new listaSimple();
	actual=primeroLS;
	
	listaSimple*actual2 = new listaSimple();
	actual2=primeroLS;
	
	ofstream arch;
	arch.open("listaSimple.dot",ios::out);
	arch<<"digraph G{\n";
	arch<<"rankdir = LR;\n";

	while (actual!=NULL) {	
		concatenar+="char"+retornarCadena(cont)+"[shape=box label=\""
		+actual->buscadas+"\n"
		+p1+actual->reemplazadas+"\n"
		+"\"style=filled fillcolor=green];\n";
      	actual=actual->siguiente;
      	cont++;		
    }
	
    for(int i=0;i<cont-1;i++){
    	concatenar+="char"+retornarCadena(i)+"->char"+retornarCadena(i+1)+";\n";	
	}		
	arch<<concatenar;
	
	concatenar="";

	while (actual2!=NULL) {	
		concatenar+="p"+retornarCadena(cont2)+"[shape=box label=\""
		+actual2->reemplazadas+"\n"
		+p2+actual2->buscadas+"\n"
		+"\"style=filled fillcolor=yellow];\n";
      	actual2=actual2->siguiente;
      	cont2++;		
    }
	
    for(int i=0;i<cont2-1;i++){
    	concatenar+="p"+retornarCadena(i)+"->p"+retornarCadena(i+1)+";\n";	
	}		
	arch<<concatenar;


	arch<<"}\n";
	arch.close();	
	
	system("dot -Tpng listaSimple.dot -o listaSimple.png");
	cout << "\n\n** Reporte Palabras Ordenadas generada\n\n\n";
	system("pause");
}

void GenerarGraficaArchivos(){
	int cont = 0;
	string concatenar = "";

	listaCircular*actual = new listaCircular();
	actual = primeroLC;
	
	ofstream arch;
	arch.open("listaCircular.dot",ios::out);
	arch<<"digraph G{\n";
	arch<<"rankdir = LR;\n";

	do{
		concatenar+="char"+retornarCadena(cont)+"[shape=box label=\""
		+actual->nombre+"\n"
		+actual->direccion+"\n"
		+"\"style=filled fillcolor=green];\n";
      	actual=actual->siguiente;
      	cont++;		
    }while(actual!=primeroLC);
	
    for(int i=0;i<cont-1;i++){
    	concatenar+="char"+retornarCadena(i)+"->char"+retornarCadena(i+1)+";\n";	
	}		
	arch<<concatenar;	
	arch<<"char"+retornarCadena(cont-1)+"->char0;\n";
	
	
	arch<<"}\n";
	arch.close();	
	
	system("dot -Tpng listaCircular.dot -o listaCircular.png");
	cout<<"\n\n\n\n***grafica realizada**\n\n\n\n";
	system("pause");
}

