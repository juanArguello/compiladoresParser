
// Librerias utilizadas 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "analizadorLexico.c"


// variable global
int indice = -1;
int estadoError = 0;


// Prototipos de los procedimientos propias
void errorSintactico();
void match(char *  expectedToken);
void getToken();
void json();
void element();
void object();
void array();
void o();
void a();
void atributte_list();
void element_list();
void atributte();
void al();
void el();
void atributte_name();
void atributte_value();


// funcion principal
int main(int argc,char* args[]){
	analizadorLexico(argc,args);
	getToken();
	json();
	if(estadoError < 0)
		return 0;
	else
		printf("El fuente es sintacticamente correcto");
	return 0;
}



// Implementacion de los procedimientos propios
void  getToken(){
	indice++;
	tokenActual[indice];
}

void errorSintactico(const char * mensaje){
	printf("Error Sintactico: %s\n",mensaje);
}
	
void match(char * expectedToken ){
	if(strcmp(tokenActual[indice].pe->lexema, expectedToken)){
		getToken();
	}else{
		errorSintactico("Errores encontrados en el fuente. Token no esperado");
		estadoError--;
	}	
}


	

void json(){
	switch(tokenActual[indice].pe->componenteLexico){
		case L_LLAVE:
			element();
			match("EOF");
			break;
		case L_CORCHETE:
			element();
			match("EOF");
			break;
		default:
			errorSintactico("Se esperaba una llave izquierda \242 corchete izquierdo");
	}
		
}

void element(){
	switch(tokenActual[indice].pe->componenteLexico){
		case L_LLAVE:
			object();
			break;
		case L_CORCHETE:
			array();
			break;
		default:
			errorSintactico("Se esperaba una llave izquierda \242 corchete izquierdo");
	}
}

void object(){
	switch(tokenActual[indice].pe->componenteLexico){
		case L_LLAVE:
			match("{");
			o();
			break;
		default:
			errorSintactico("Se esperaba una llave izquierda");
	}	
}

void array(){
	switch(tokenActual[indice].pe->componenteLexico){
		case L_CORCHETE:
			match("[");
			a();
			break;
		default:
			errorSintactico("Se esperaba un corchete izquierdo");
	}
}

void o(){
	switch(tokenActual[indice].pe->componenteLexico){
		case STRING:
			atributte_list();
			match("}");
			break;
		case R_LLAVE:
			match("}");
			break;
		default:
			errorSintactico("Se esperaba un string \242 llave derecho");
	}
}

void a(){
	switch(tokenActual[indice].pe->componenteLexico){
		case R_CORCHETE:
			match("]");
			break;
		case L_LLAVE:
			element_list();
			match("]");
			break;
		case L_CORCHETE:
			element_list();
			match("]");
			break;
		default:
			errorSintactico("Se esperaba un corchete derecho, llave izquierda \242 corchete izquierdo");
	}
}


void atributte_list(){
	switch(tokenActual[indice].pe->componenteLexico){
		case STRING:
			atributte();
			al();
			break;
		default:
			errorSintactico("Se esperaba un string ");
	}
}


void element_list(){
	switch(tokenActual[indice].pe->componenteLexico){
		case L_LLAVE:
			element();
			el();
			break;
		case L_CORCHETE:
			element();
			el();
			break;
		default:
			errorSintactico("Se esperaba una llave izquierda \242 corchete izquierdo");
	}
}


void atributte(){
	switch(tokenActual[indice].pe->componenteLexico){
		case STRING:
			atributte_name();
			match(":");
			atributte_value();
			break;
		default:
			errorSintactico("Se esperaba un string ");
	}
}

void al(){
	switch(tokenActual[indice].pe->componenteLexico){
		case COMA:
			match(",");
			atributte();
			al();
			break;
		default:
			break;
	}
}


void el(){
	switch(tokenActual[indice].pe->componenteLexico){
		case COMA:
			match(",");
			element();
			el();
			break;
		default:
			break;
	}
}


void atributte_name(){
	switch(tokenActual[indice].pe->componenteLexico){
		case STRING:
			match(tokenActual[indice].pe->lexema);
			break;
		default:
			errorSintactico("Se esperaba un string ");
	}
}


void atributte_value(){
	switch(tokenActual[indice].pe->componenteLexico){
		case L_LLAVE :
			element();
			break;
		case L_CORCHETE :
			element();
			break;
		case STRING :
			match(tokenActual[indice].pe->lexema);
			break;
		case NUMBER :
			match(tokenActual[indice].pe->lexema);
			break;
		case PR_TRUE :
			match(tokenActual[indice].pe->lexema);
			break;
		case PR_FALSE :
			match(tokenActual[indice].pe->lexema);
			break;
		case PR_NULL :
			match(tokenActual[indice].pe->lexema);
			break;
		default:
			errorSintactico("Se esperaba una llave izquierda, un corchete izquierdo, string, number, true, false \242 null ");
	}
}





