/*  EL ARCHIVO "INGRESO" TIENE LOS DATOS DE LA INSCRIPCION DE ALUMNOS  
  A UNA UNIVERSIDAD. SE COMPONE DE ESTRUCTURAS INGRESO               
  SE COMPONEN DE LEGAJO DEL ALUMNO Y CARRERA EN LA QUE SE INSCRIBIO  

  EL ARCHIVO "EXAMEN" TIENE LOS DATOS DEL EXAMEN DE INGRESO COMUN A  
  TODAS LAS CARRERAS. SE COMPONE DE ESTRUCTURAS EXAMEN               
  ESTAS ESTAN FORMADAS POR EL LEGAJO DEL ALUMNO Y LA NOTA DEL EXAMEN 

  SE PIDE  :                                                           
 1. PERMITIR EL INGRESO DE UN NOMBRE DE CARRERA E INDICAR :           
 	A)  CUANTOS ALUMNOS SE INSCRIBIERON EN ESA CARRERA               
  	B)  CUANTOS ALUMNOS SE PRESENTARON A EXAMEN (DE ESA CARRERA)     
  	C)  CUANTOS ALUMNOS DE ESA CARRERA APROBARON (NOTA >= 6)         


 2. CUAL ES LA CARRERA EN LA QUE HUBO MAYOR INSCRIPCION               

  3. CUAL ES LA CARRERA QUE TUVO MAYOR CANTIDAD DE INGRESANTES         */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXC 50

typedef struct  {
	int LEG ;
	char CARRERA[20] ;
}INGRESO;

typedef struct  {
	int LEG ;
	int NOTA ;
}EXAMEN;

typedef struct {
    char NOM[20];
    int INS;
    int ING; 
} AUX;

int main()
{
		FILE*FPI;
		FILE*FPE;
		INGRESO I;
		EXAMEN E;
		AUX vaux[MAXC];
		
		char carrera[20];
		int cont_a=0, cont_e=0, cont_ap=0;
		int i,cont_ca=0,flag;
		
		if (!(FPI=fopen("INGRESO.DAT","rb"))) {
			printf("ERROR EN APERTURA");
			exit(1);
		}
		
		if (!(FPE=fopen("EXAMEN.DAT","rb"))) {
			printf("ERROR EN APERTURA");
			exit(1);
		}
		
		printf("\nINGRESE NOMBRE DE CARRERA: ");
		scanf("%s",carrera);
		
		while (fread(&I,sizeof(INGRESO),1,FPI)==1) {
			if (strcmp(carrera,I.CARRERA)==0) {
				cont_a++;
				rewind(FPE);
				
			while (fread(&E,sizeof(EXAMEN),1,FPE)==1) {
				if (I.LEG==E.LEG) {
					cont_e++;
				if (E.NOTA>=6) {
					cont_ap++;
				}
			}
		}
	}	
}
		printf("\nRESULTADOS PARA %s:",carrera);
		printf("\nInscritos: %d\nPresentes:%d\nAprobados:%d\n",cont_a,cont_e,cont_ap);
		
		rewind(FPI);
		while (fread(&I,sizeof(INGRESO),1,FPI)==1) {
			flag=0;
			for (i=0;i<cont_ca;i++) {
				if (strcmp(I.CARRERA,vaux[i].NOM)==0)	{
				vaux[i].INS++;
				flag=1;
		
			rewind(FPE);
			while(fread(&E,sizeof(EXAMEN),1,FPE)==1) {
				if (I.LEG==E.LEG && E.NOTA>=6) {
					vaux[i].ING++;
				}
			}
		}
	}
			if(flag==0 && cont_ca <MAXC) {
				strcpy(vaux[cont_ca].NOM,I.CARRERA);
				vaux[cont_ca].INS=1;
				vaux[cont_ca].ING=0;

			rewind(FPE);
			
			while (fread(&E,sizeof(EXAMEN),1,FPE)==1) {
                if (I.LEG == E.LEG && E.NOTA >= 6) {
				vaux[cont_ca].ING++;
				}
            }
            cont_ca++;
        }
    }
    
		int maxins = -1, maxing = -1;
    int posMaxIns = 0, posMaxIng = 0;

    for (i = 0; i < cont_ca; i++) {
        if (vaux[i].INS > maxins) {
            maxins = vaux[i].INS;
            posMaxIns = i;
        }
        if (vaux[i].ING > maxing) {
            maxing = vaux[i].ING;
            posMaxIng = i;
        }
    }	
		getchar();
		
		printf("\n\t\tRESULTADOS:\n");
		if(cont_ca>0) {
		printf("\nCarrera con mayor inscripcion: %s (%d alumnos)", vaux[posMaxIns].NOM, maxins);
    	printf("\nCarrera con mas ingresantes: %s (%d alumnos)", vaux[posMaxIng].NOM, maxing);	
		}
	
		fclose(FPI);
		fclose(FPE);	
		printf ("\n\n\nFIN DEL PROGRAMA");
		
		return 0 ;
}
