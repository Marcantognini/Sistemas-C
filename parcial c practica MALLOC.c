/*
Struct donación { 
CHAR ONG [30];
INT MONTO;
CHAR FILANTROPO [30];}

Crear un programa que permita determinar quién es el filántropo que más donaciones hizo y cuáles ong fueron las beneficiadas. No se puede bajar en memoria al FILANTROPO
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char ONG [30];
	int MONTO;
	char FILANTROPO [30];
}DONACION;


int main () {
	
	FILE*FP;
	DONACION *vec=NULL;
	//unsigned int tam=0;
	char maxfil[30];	
	int ong_flag=0;
	int i,j,max=0;
	long int n;
	if (!(FP=fopen("DONACIONES.DAT","rb")) ) {
		printf("ERROR EN APERTURA");
		exit(1);
	} 
	fseek(FP,0,SEEK_END);
	n=ftell(FP)/sizeof(DONACION);
	rewind(FP);
	vec=malloc(n*sizeof(DONACION)); // a MALLOC se le da puntero a sizeof, y en REALLOC, se le da 1 parametron mas, que es el vec al principio
	
	if (vec==NULL) {
        printf("Memoria insuficiente\n");
        fclose(FP);
        return 1;
    }
    
	fread(vec,sizeof(DONACION),n,FP); // LEE TODOS los registros del puntero a estructura de una, SIN WHILE y SIN DIRECCION DE MEMORIA ya que es un puntero
	fclose(FP);
		
for (i=0;i<n;i++) {
	
	int mayor=0;
	for (j=0;j<n;j++) {
		if (strcmp(vec[j].FILANTROPO,vec[i].FILANTROPO)==0) {
			mayor++;
		}	
	}
	if (max<mayor) {
		max=mayor;
		strcpy(maxfil,vec[i].FILANTROPO);
	}
}

for (i=0;i<n;i++) {
		ong_flag=0;
		if (strcmp(vec[i].FILANTROPO,maxfil)==0) {

	for (j=0;j<i;j++) {
		if (strcmp(vec[i].ONG,vec[j].ONG)==0 && strcmp(vec[j].FILANTROPO,maxfil)==0 ) {
			ong_flag=1;
		}
	}
	if (!ong_flag) {
		printf("\n%s",vec[i].ONG);
	}
}
}

free(vec);

return 0;
}

