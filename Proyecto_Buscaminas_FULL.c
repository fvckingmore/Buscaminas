/*-----------------------------------------------------------------------------------*/
/*PROYECTO BUSCAMINAS*/
/*-----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FM 20
#define CM 20
#define bar "------------------------"

/*PROTOTIPOS DE FUNCIONES*/

void f_muestra (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_max, int colum_max);
void f_inicializacion (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_max, int colum_max, int num_minas);
int f_recorrido (int matriz_int[FM][CM],int fila,int colum, int fila_max, int colum_max);
void f_usr (int matriz_ext[FM][CM], int fila_max, int colum_max, int *fila_usr, int *colum_usr);
int f_abrir_casilla (int matriz_ext[FM][CM], int fila_usr, int colum_usr);
void f_casillas_cercanas (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_usr, int colum_usr, int fila_max, int colum_max);
void f_primeras_casillas (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_usr, int colum_usr, int fila_max, int colum_max);
void buf();
int f_menu();
void f_dificultad(int *fila_max, int *colum_max, int *num_minas);
int f_verificar (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_max, int colum_max, int fila_usr, int colum_usr, int num_minas);
void f_explotar (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_max, int colum_max);
int f_volver_jugar();
void f_dificultad_usr (int *fila_max, int *colum_max, int *num_minas);

/*-----------------------------------------------------------------------------------*/

/*FUNCION PRINCIPAL*/

int main(){
	
	int matriz_int[FM][CM],matriz_ext[FM][CM];
	int fila_max, colum_max, num_minas, fila_usr, colum_usr;
	
	srand(time(0));
	
	if(f_menu()==1){
		
		do{
		
			f_dificultad(&fila_max, &colum_max, &num_minas);	
			f_inicializacion(matriz_int, matriz_ext, fila_max, colum_max, num_minas);
			
			do{
			
				f_muestra (matriz_int, matriz_ext, fila_max, colum_max);
				f_usr (matriz_ext, fila_max, colum_max, &fila_usr, &colum_usr);
				f_primeras_casillas (matriz_int, matriz_ext, fila_usr, colum_usr, fila_max, colum_max);
				
				if( f_verificar(matriz_int, matriz_ext, fila_max, colum_max, fila_usr, colum_usr, num_minas)==0 ){
					
					f_casillas_cercanas (matriz_int, matriz_ext, fila_usr, colum_usr, fila_max, colum_max);
				}
				
				system("clear");
				
			}while( f_verificar (matriz_int, matriz_ext, fila_max, colum_max, fila_usr, colum_usr, num_minas)==0 );
			
			if( f_verificar (matriz_int, matriz_ext, fila_max, colum_max, fila_usr, colum_usr, num_minas)==-1 ){
				
				f_explotar(matriz_int, matriz_ext, fila_max, colum_max);
				f_muestra (matriz_int, matriz_ext, fila_max, colum_max);
				printf("\n\n"); printf(bar); printf("\n\n");
				printf("MMl   .Occlc  :dccc. ,xclo. :dcco'  :cOlc  .occc  ;cokcc. xlcc:    cMM\n");
				printf("MMl   .M   K: od     ck  0c dd   X,   N.   Od       ;K    N'       cMM\n");
				printf("MMl   .Mlcll  o0ccc  cKc0o  dd   kl   N.    'ldd.   ;K    Ndcc,    cMM\n");
				printf("MMl   .M      ox...  ck  0: dx.'oO  ..W;.  ....ko   ;K    N:...    cMM\n");
				printf("MMl    ,      .,,,,  ..   , .,,'    ',,,,  ';;,.    .'    ',,,'    cMM\n");
			}
			else{
				
				if( f_verificar (matriz_int, matriz_ext, fila_max, colum_max, fila_usr, colum_usr, num_minas)==1 ){
					
					f_muestra (matriz_int, matriz_ext, fila_max, colum_max);
					printf("\n\n"); printf(bar); printf("\n\n"); 
					printf("MM;     .:lc,    c,   .:.  .,   .c'    .:cc;  cccccc' .::::;    ;MM\n");
					printf("MM;   .Ko.  .   OdN'  lXX. ck   XlN.  cX.  .    ;N    ,W        ;MM\n");
					printf("MM;   dO  llc  c0 ;X  lx,K.ck  xo oO  .dxo;.    ,N    ,Wlll;    ;MM\n");
					printf("MM;   lK   'W .WxllNx lx ,Kok ;WoloWc     ,N;   ,N    ,W        ;MM\n");
					printf("MM;    ckolx0 O:   .X,cd  ,Nx K.   .X.;lllox.   'K    ,Nlll:    ;MM\n");;
				}
			}
			
		}while( f_volver_jugar()==1 );

	}
	else{
		
		printf("Usted ha salido del juego");
	}
	
//getch();
return 0;
}

/*-----------------------------------------------------------------------------------*/

/*LIMPIEZA DE BUFFER*/

void buf(){ //BUFFER

	int c;
	
	while((c=fgetc(stdin))!=EOF && c!='\n'){}
}

/*-----------------------------------------------------------------------------------*/

/*FUNCION INICIALIZACION DE LA MATRIZ INTERNA, EXTERNA, MINAS Y NUMERO DE MINAS ALREDEDOR DE UNA CASILLA*/

void f_inicializacion (int matriz_int[FM][CM], int matrix_ext[FM][CM], int fila_max, int colum_max, int num_minas){ 

	/*INICIALIZACION DE MATRIZ INTERNA EN CERO*/
	
	int i,j,k; 
	
	for(i=0;i<fila_max;i++){
		
		for(j=0;j<colum_max;j++){
			
			matriz_int[i][j]=0;
		}
	}
	
	k=0;
	
	/*ASIGNACION DE MINAS EN POSICIONES ALEATORIAS*/
	
	do{ 
		
		do{
			
			i=rand()%((fila_max-1)+1);
			j=rand()%((colum_max-1)+1);
				
		}while(matriz_int[i][j]==-1);
			
		matriz_int[i][j]=-1; k++;
		
	}while(k<num_minas);
	
	/*ASIGNACION DE CANTIDAD DE MINAS ALREDEDOR*/
	
	for(i=0;i<fila_max;i++){
		
		for(j=0;j<colum_max;j++){
			
			if(matriz_int[i][j]!=-1){ //SI EN LA POSICION NO HAY UNA MINA, LLAMA LA FUNCION PARA CONTAR LAS MINAS ALREDEDOR
				
				matriz_int[i][j]=f_recorrido(matriz_int,i,j,fila_max,colum_max);
			}	
		}
	}
	
	/*INICIALIZACION DE MATRIZ QUE INDICA SI UNA CASILLA ESTA ABIERTA O NO*/
	
	for(i=0;i<fila_max;i++){
		
		for(j=0;j<colum_max;j++){
			
			matrix_ext[i][j]=0;
		}
	}
}

/*-----------------------------------------------------------------------------------*/

/*MOSTRAR MATRIZ CON FORMATO PARA EL USUARIO*/

void f_muestra (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_max, int colum_max){ 
	
	int i,j,f,c=1;
	
	printf("\t");
	
	for(f=1;f<=colum_max;f++){
		
		printf("%2i\t",f); //MUESTRA EL NUMERO DE COLUMNAS
	}
	
	printf("\n\n\n");
	
	for(i=0,f;i<fila_max;i++){
		
		printf("%i\t",c); c++; //MUESTRA EL NUMERO DE FILAS
		
		for(j=0;j<colum_max;j++){
			
			//printf("%2d\t",matriz_int[i][j]);
			
			if(matriz_ext[i][j]==0){
				
				printf("%2c\t",219); /*SI ESTA TAPADA MUESTRA # */
			}
			else{
				
				if(matriz_ext[i][j]==1){
					
					if(matriz_int[i][j]==-1){
						
						printf("%2c\t",'*'); /*SI ESTA ABIERTA Y HAY UNA MINA MUESTRA * */
					}
					else{
						
						if(matriz_int[i][j]==0){
							
							printf("%2c\t",' '); /*SI ESTA ABIERTA Y NO HAY MINAS ALREDEDOR MUESTRA ESPACIO*/	
						}
						else{
							
							printf("%2i\t",matriz_int[i][j]); /*MUESTRA EL NUMERO DE MINAS ALREDEDOR*/
						}
					}
				}
			}
		}
		
		printf("\n\n\n");
	}
}

/*-----------------------------------------------------------------------------------*/

/*RECORRIDO Y VERIFICACION DEL NUMERO DE MINAS ALREDEDOR DE UNA CASILLA*/

int f_recorrido (int matriz_int[FM][CM],int fila,int colum, int fila_max, int colum_max){ 
	
	int i,j,n_mina=0;
			
	for(i=fila-1;i<=fila+1;i++){
		
		for(j=colum-1;j<=colum+1;j++){
			
			if( (i>=0 && i<fila_max) && (j>=0 && j<colum_max) ){ //SI ESTA ENTRE LOS LIMITES DEL TABLERO
				
				if(matriz_int[i][j]==-1){
					
					n_mina++;
				}
			}
		}
	}

return (n_mina);		
}

/*-----------------------------------------------------------------------------------*/

/*INGRESO DE DATOS POR EL USUARIO*/

void f_usr (int matriz_ext[FM][CM], int fila_max, int colum_max, int *fila_usr, int *colum_usr){
	
	int fila, colum, B;
	int V; /*CONTROLA UN VALOR BOOLEANO QUE DEVUELVE EL SCANF SEGUN EL TIPO DE DATO PEDIDO Y EL TIPO DE DATO INGRESADO*/
		
	do{	
		
		do{
			
			printf("Ingrese fila -> "); V=scanf("%d",&fila); buf(); //ENTRADA DE FILA POR USUARIO
			
			if(( !(fila>=1 && fila<=fila_max)) || (!V)){
				
				printf("\n\tValor incorrecto, vuelva a intentar\n\n");
			}
			
			
		}while( (!(fila>=1 && fila<=fila_max)) || (!V) );
		
		do{	
			
			printf("Ingrese columna -> "); V=scanf("%d",&colum); buf(); //ENTRADA DE COLUMNA POR USUARIO
			
			if( (!(colum>=1 && colum<=colum_max)) || (!V) ){
				
				printf("\n\tValor incorrecto, vuelva a intentar\n\n");
			}
			
		}while( (!(colum>=1 && colum<=colum_max)) || (!V) );
		
		fila-=1; colum-=1; B=f_abrir_casilla(matriz_ext, fila, colum);
		
	}while(B==0);	
	
	*fila_usr=fila; *colum_usr=colum;
}
	
/*-----------------------------------------------------------------------------------*/

/*ABRE LA CASILLA SELECCIONADA POR EL USUARIO*/

int f_abrir_casilla (int matriz_ext[FM][CM], int fila_usr, int colum_usr){
	
	int B;
	
	if(matriz_ext[fila_usr][colum_usr]==0){ //SI ESTA CERRADA, LA ABRE
		
		matriz_ext[fila_usr][colum_usr]=1; B=1;
	}
	else{
		
		if(matriz_ext[fila_usr][colum_usr]==1){ //SI YA ESTA ABIERTA, MUESTRA ERROR
			
			printf("\n\tYa abrio esta casilla, intente con otra\n\n"); B=0;
		}
	}

return (B);
}

/*-----------------------------------------------------------------------------------*/

/*SI SE ELIJE UNA CASILLA VACIA, ESTA FUNCION ABRE CASILLAS CERCANAS */

void f_casillas_cercanas (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_usr, int colum_usr, int fila_max, int colum_max){
	
	int i,j,B,cf,cc;
	
	if(matriz_int[fila_usr][colum_usr]==0){
		
		/*ABRIR PARTE SUPERIOR IZQUIERDA*/
		
		for(i=fila_usr, cf=0, B=1;(i>=0 && B==1);i--,cf++){
			
			for(j=colum_usr,cc=0;(j>=0 && B==1);j--,cc++){
				
				if( !(matriz_int[i][j]==-1) ){
					
					matriz_ext[i][j]=1;
				}
				else{
					
					B=0;
				}
			}
		}
		
		/*ABRIR PARTE SUPERIOR DERECHA*/
		
		for(i=fila_usr, cf=0, B=1;(i>=0 && B==1);i--, cf++){
			
			for(j=colum_usr, cc=0;(j<colum_max && B==1);j++, cc++){
				
				if( !(matriz_int[i][j]==-1) ){
					
					matriz_ext[i][j]=1;
				}
				else{
					
					B=0;
				}
			}
		}
		
		/*ABRIR PARTE INFERIOR IZQUIERDA*/
		
		for(i=fila_usr, cf=0, B=1;(i<fila_max && B==1);i++, cf++){
			
			for(j=colum_usr, cc=0;(j>=0 && B==1);j--, cc++){
				
				if( !(matriz_int[i][j]==-1) ){
					
					matriz_ext[i][j]=1;
				}
				else{
					
					B=0;
				}
			}
		}
		
		/*ABRIR PARTE INFERIOR DERECHA*/
		
		for(i=fila_usr, cf=0, B=1;(i<fila_max && B==1);i++, cf++){
			
			for(j=colum_usr, cc=0;(j<colum_max && B==1);j++, cc++){
				
				if( !(matriz_int[i][j]==-1) ){
					
					matriz_ext[i][j]=1;
				}
				else{
					
					B=0;
				}
			}
		}
	}	
}

/*-----------------------------------------------------------------------------------*/

/*ABRE LAS CASILLAS CERCANAS A LA PRIMERA CASILLA SELECCIONADA*/

void f_primeras_casillas (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_usr, int colum_usr, int fila_max, int colum_max){
	
	int i,j,sum=0;
			
	for(i=0;i<fila_max;i++){
		
		for(j=0;j<colum_max;j++){
			
			sum+=matriz_ext[i][j];	//SUMA LAS CASILLAS DE LA MATRIZ INTERNA
		}
	}
		
	if(sum==1){	
		
		matriz_int[fila_usr][colum_usr]=0;
		
		for(i=fila_usr-1;i<=fila_usr+1;i++){
			
			for(j=colum_usr-1;j<=colum_usr+1;j++){
				
				if( (i>=0 && i<fila_max) && (j>=0 && j<colum_max) ){
					
					if( !(matriz_int[i][j]==-1) ){
						
						matriz_ext[i][j]=1;
					}
				}
			}
		}
	}
}

/*-----------------------------------------------------------------------------------*/

/*MUESTRA UN PEQUEÑO MENU PARA JUGAR O SALIR*/

int f_menu(){
	
	int V,op,B;
	
	do{
		system("clear");
		
		printf("2018 by Adrian Moreno | Todos los derechos reservados\n\n"); printf(bar); printf("\n\n");
		
		printf(",;;;,.   ''    .;   .,::;.     ,ccc,     ;;.    ;,   .;.  ;;;;;;'  ,;.   .'    .;,      .;::;\n");
		printf("Xk'':X0  O0    cM  dX;'.''   lXl'.';    lXKO   .WX;  XXx  ''dM;'.  KWK   x0    XOW;   .Nx,.',.\n");
		printf("Xx  .Kk  O0    cM  kX;.     ;M'        .W,.W:  ,W,N.Olx0    cM     KdxK  x0   x0 oN.  'Wx'\n");
		printf("XKooxKo  O0    cM   .cx0O:  oM         Xx  lW. cN lNk dX    cM     Ko k0 x0  ;W.  Xk    ,oO0d.\n");
		printf("Xd   ;M: kK    oW       ,M: 'Ml       dWOxxkWO oX  '  lW    cM     Ko  O0k0  NXxxx0M;       OX\n");
		printf("XKdddkl  .0Ollx0,  xolldOx   'O0xddx.,W,    .Wcx0     cM. od0Mxd:  Ko   OM0 kK     dN.:dolox0;\n");
		printf("\n\n"); printf(bar); printf("\n\n");
		
		printf("1 -> JUGAR\n\n2 -> SALIR\n\nOpcion -> "); V=scanf("%d",&op); buf();
		
		if(!V){
			
			printf("Ha ingresado un valor incorrecto, intente otra vez\n\n"); getchar();
		}
		else{
		
			switch(op){
				
				case 1: B=1; break;
				case 2: B=0; break;
				default: printf("Opcion incorrecta, intente de nuevo\n\n"); B=2; getchar();
			}
		}
	}while(!V || B==2);
	
	system("clear");

return (B);	
}

/*-----------------------------------------------------------------------------------*/

/*ASIGNA LA DIFICULTAD DEL JUEGO*/

void f_dificultad(int *fila_max, int *colum_max, int *num_minas){
	
	int op,V,B=1;
	
	do{
		
		printf("Elija una dificultad:\n\n"); 
		printf("1-> FACIL --> Tamaño: 8x8 | No. minas: 10\n\n");
		printf("2-> MEDIO --> Tamaño: 10x10 | No. minas: 30\n\n");
		printf("3-> DIFICIL --> Tamaño: 12x16 | No. minas: 60\n\n");
		printf("4-> PERSONALIZADA\n\n");
		printf("Opcion: "); V=scanf("%d",&op); buf(); printf("\n\n");
		
		if(!V){
			
			printf("Ha ingresado un valor incorrecto, intente de nuevo"); getchar(); system("clear");
		}
		else{
			
			switch(op){
				
				case 1: *fila_max=8; *colum_max=8; *num_minas=10; B=1; break; //FACIL
				
				case 2: *fila_max=10; *colum_max=10; *num_minas=30; B=1; break; //MEDIO
				
				case 3: *fila_max=12; *colum_max=16; *num_minas=60; B=1; break; //DIFICIL
				
				case 4: system("clear"); f_dificultad_usr(fila_max, colum_max, num_minas); break; //PERSONALIZADA
				
				
				
				case 9: *fila_max=8; *colum_max=8; *num_minas=4; B=1; break; //DE PRUEBA
				
				default: printf("Opcion incorrecta, intente de nuevo"); B=0; getchar(); system("clear"); break; 
				
				
			}
			
		}
	}while(!V || B==0);	
	
	system("clear");
}

/*-----------------------------------------------------------------------------------*/

/*VERIFICA SI GANA, PIERDE O SIGUE JUGANDO*/

int f_verificar (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_max, int colum_max, int fila_usr, int colum_usr, int num_minas){
	
	int i,j,sum,B;
	
	if(matriz_int[fila_usr][colum_usr]==-1){
		
		B=-1;
	}
	else{
		
		sum=0;
		
		for(i=0;i<fila_max;i++){
			
			for(j=0;j<colum_max;j++){
				
				if(matriz_ext[i][j]==1){
					
					sum+=matriz_ext[i][j]; //SUMA LS CASILLAS ABIERTAS
				}
			}
		}
		
		if(sum==(fila_max*colum_max)-num_minas){
			
			B=1;
		}
		else{
			
			B=0;
		}
	}
	
return (B);	
}

/*-----------------------------------------------------------------------------------*/

/*EXPLOTA TODAS LAS MINAS*/

void f_explotar (int matriz_int[FM][CM], int matriz_ext[FM][CM], int fila_max, int colum_max){
	
	int i,j;
	
	for(i=0;i<fila_max;i++){
		
		for(j=0;j<colum_max;j++){
			
			if(matriz_int[i][j]==-1){
				
				matriz_ext[i][j]=1;
			}
			
		}
	}	
}

/*-----------------------------------------------------------------------------------*/

/*PREGUNTA SI DESEA VOLVER A JUGAR*/

int f_volver_jugar(){
	
	char op;
	int B,b;
	
	do{
		printf("\n\nDesea volver a intentar?\n\ns -> Si | n -> No\n\nOpcion: "); scanf("%c",&op); buf();
		
		switch(op){
			
			case 's':
			case 'S': B=1; b=0; system("clear"); break;
			
			case 'n':
			case 'N': B=0; b=0; system("clear"); printf("\n\nUsted ha salido, Gracias por jugar"); break;
			
			default: printf("Opcion incorrecta, intente de nuevo"); b=1; getchar(); break;
		}
		
	}while(b==1);

return (B);	
}

/*-----------------------------------------------------------------------------------*/

/*ASIGNA NUMERO DE FILAS, COLUMNAS Y MINAS INGRESADAS POR EL USUARIO*/

void f_dificultad_usr (int *fila_max, int *colum_max, int *num_minas){
	
	int V,t;
	
	do{
		
		printf("Ingrese el numero de filas [Tamaño min = 5 | Tamaño MAX = 20 ] -> "); V=scanf("%d",fila_max); 
		buf(); printf("\n");
		
		if(!V){
			
			printf("\nValor incorrecto, intente de nuevo\n\n");
		}
		else{	
			
			if( !(*fila_max>=5 && *fila_max<=20) ){
				
				printf("\nTamaño incorrecto, intente de nuevo\n\n");
			}
		}
		
	}while(!V || !(*fila_max>=5 && *fila_max<=20) );
	
	do{
		
		printf("Ingrese el numero de columnas [Tamaño min = 5 | Tamaño MAX = 20 ] -> "); V=scanf("%d",colum_max); 
		buf(); printf("\n");
		
		if(!V){
			
			printf("\nValor incorrecto, intente de nuevo\n\n");
			
		}
		else{
		
			if( !(*colum_max>=5 && *colum_max<=20) ){
				
				printf("\nTamaño incorrecto, intente de nuevo\n\n");
			}
		}
			
	}while(!V || !(*colum_max>=5 && *colum_max<=20) );
	
	do{
		
		t= (*fila_max) * (*colum_max);
		
		printf("Ingrese el numero de minas [Tamaño min = 8 | Tamaño MAX = %d ] -> ",t-10); 
		V=scanf("%d",num_minas); buf(); printf("\n");
		
		
		if(!V){
			
			printf("\nValor incorrecto, intente de nuevo\n\n");
			
		}
		else{
		
			if( !(*num_minas>=1 && *num_minas<=t-10) ){
				
				printf("\nTamaño incorrecto, intente de nuevo\n\n");
			}
			else{
				
				if(*num_minas<8){
				
					*num_minas=t-10;
					
				}
			}
		}
	}while(!V || !(*num_minas>=1 && *num_minas<=t-10) );	
}
