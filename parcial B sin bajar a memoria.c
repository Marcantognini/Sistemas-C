/*
EL ARCHIVO DONACIONES ESTA COMPUESTO POR REGISTROS DE LA SIGUIENTE FORMA:
STRUCT DONACION {
CHAR ONG [20];
INT MONTO;
CHAR FILANTROPO[20];
};
DONDE LA ONG ES LA INSTITUCION QUE RECIVE LA DONACION, MOTNO ES LA CANTIDAD DE U$S QUE RECIBE 
Y FILANTRIPO ES LA PERSONA O EMPRESA QUE RELIZA LA DONACION.REALIZAR UN PROGRAMA QUE PERMITA 
DETERMINAR CUAL ES LA ONG QUE RECIBIO MAYOR DINERO EN DONACIONES Y QUIENES FUERON SUS DONANTES.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct DONACION{
	char ONG[20];
	int MONTO;
	char FILANTROPO[20];
};

// ong_max acum_monto while max_fil(VARIOS)
int main() {
	FILE *F;
	FILE *aux;
	struct DONACION DON;
	struct DONACION A;
	int max_monto=0,acum_monto;
	char max_ong[20],max_fil[20];

	if (!(F=fopen("DONACIONES.DAT","rb")) ) {
		printf("ERROR EN LECTURA");
		exit(1);
	}
	
		if (!(aux=fopen("DONACIONES.DAT","rb")) ) {
		printf("ERROR EN LECTURA");
		exit(1);
	}
	
	while (fread(&DON,sizeof(DON),1,F)==1) {
		acum_monto=0;
		
		rewind(aux);
		while (fread(&A,sizeof(A),1,aux)==1) {
		if (strcmp(DON.ONG,A.ONG)==0) {
		acum_monto+=A.MONTO;	
	}
	}
	if (acum_monto > max_monto) {
        max_monto = acum_monto; 
        strcpy(max_ong, DON.ONG);
	} 
}
	fclose(aux);
	
	printf("ONG mas beneficiada: %s\n", max_ong); 
    printf("Monto total recibido: %d\n", max_monto);
    printf("Listado de Donantes:\n");
	
	rewind(F);
	
	while(fread(&DON,sizeof(DON),1,F)==1) {
		if (strcmp(DON.ONG,max_ong)==0) {	
			printf("%s\n",DON.FILANTROPO);
		}
	}
	
	fclose(F);
	
	return 0;
}
