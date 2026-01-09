/*
EL ARCHIVO DONACIONES ESTA COMPUESTO POR REGISTROS DE LA SIGUIENTE FORMA:
STRUCT DONACION {
CHAR ONG [20];
INT MONTO;
CHAR FILANTROPO[20];
};
DONDE LA ONG ES LA INSTITUCION QUE RECIVE LA DONACION, MOTNO ES LA CANTIDAD DE U$S QUE RECIBE 
Y FILANTRIPO ES LA PERSONA O EMPRESA QUE RELIZA LA DONACION.REALIZAR UN PROGRAMA QUE PERMITA 
DETERMINAR CUAL ES LA ONF QUE RECIVIO MAYOR DINERO EN DONACIONES Y QUIENES FUERON SUS DONANTES.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char ONG[20];
	int MONTO;
	char FILANTROPO[20];
}DONACION;


int main () {
	FILE*FP;
	DONACION *vec=NULL; // vector estructuras dinamico
	long n;
	char max_ong[20];	// variable donde voy a copiar la ond beneficiada
	int i,j,max_monto=0,cont_fil=0;

	
	if (!(FP=fopen("DONACIONES.DAT","rb")) ) { //abro archivo
		printf("ERROR EN APERTURA");
		exit(1);
	}  
	
	fseek(FP,0,SEEK_END);
	n=ftell(FP)/sizeof(DONACION);
	rewind(FP); //saco tamaño para darle al vector
	
	vec=malloc(n*sizeof(DONACION)); //Vector dinamico
	char max_fil[n][20]; //vector de strings de mismo tamaño que vector
	
	fread(vec,sizeof(DONACION),n,FP); // leo todo el resto (SIN while)
	fclose(FP); // una vez que lee todos los registros, cierro archivo
	
	for (i=0;i<n;i++) { // ONG MAS BENEFICIADA
		int acum_monto=0;
		for (j=0;j<n;j++) {
			
			if (strcmp(vec[i].ONG,vec[j].ONG)==0) {
				
			acum_monto+=vec[j].MONTO; // ACUMULO MONTO
		} }
		if (acum_monto>max_monto) { // ASIGNO MONTO MAXIMO Y SU ONG BENEFICIADA
			max_monto=acum_monto;
			strcpy(max_ong,vec[i].ONG);
		}
	}
	
	for (i=0;i<n;i++) { // GUARDO FILANTROPOS QUE DONARON A ONG MAS BENEFICIADA
			int flag=0; 
		if (strcmp(max_ong,vec[i].ONG)==0) { // CUANDO SE BARRA LA ONG MAS BENEFICIADA
		
		for (j=0;j<cont_fil;j++) {
			if (strcmp(max_fil[j],vec[i].FILANTROPO)==0) { // REPETIDO, FLAG LEVANTADA
			flag=1;
		} }
		if (!flag) {
			strcpy(max_fil[cont_fil],vec[i].FILANTROPO); // GUARDA A LOS FILANTROPOS EN UN ARRAY DE STRINGS
			cont_fil++; // AUMENTA CONTADOR DE FILANTROPOS
		}
	}
}
	
	printf("\nONG MAS BENEFICIADA: %s",max_ong);
	printf("\nCUYOS DONANTES FUERON:");
	
	for (i=0;i<cont_fil;i++) { // IMPRIMO FILANTROPOS GUARDADOS
			printf("\n%s\n",max_fil[i]);
		}
	free(vec); //LIBERO MEMORIA
return 0;
}
