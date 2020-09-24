#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
HANDLE *device;
unsigned char dato;
DWORD aux;
void main() {
   device=CreateFile("\\\\.\\NombreDeviceDriver", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
   if (device!=INVALID_HANDLE_VALUE) {
   	  printf(" ... comunicacion establecida!\n");
      ReadFile(device,&dato,1,&aux,NULL);
      if(dato==0){
      	printf("Ninguna compuerta falla\n");
      }
      else if(dato==1){
      	printf("Falla(n) la(s) compuerta(s): 1\n");
      }
      else if(dato==2){
      	printf("Falla(n) la(s) compuerta(s): 2\n");
      }
      else if(dato==3){
      	printf("Falla(n) la(s) compuerta(s): 1 y 2\n");
      }
      else if(dato==4){
      	printf("Falla(n) la(s) compuerta(s): 3\n");
      }
      else if(dato==5){
      	printf("Falla(n) la(s) compuerta(s): 1 y 3\n");
      }
      else if(dato==6){
      	printf("Falla(n) la(s) compuerta(s): 2 y 3\n");
      }
      else if(dato==7){
      	printf("Falla(n) la(s) compuerta(s): 1, 2 y 3\n");
      }
      else if(dato==8){
      	printf("Falla(n) la(s) compuerta(s): 4\n");
      }
       else if(dato==9){
      	printf("Falla(n) la(s) compuerta(s): 1 y 4\n");
      }
      else if(dato==10){
      	printf("Falla(n) la(s) compuerta(s): 2 y 4\n");
      }
      else if(dato==11){
      	printf("Falla(n) la(s) compuerta(s): 1, 2 y 4\n");
      }
      else if(dato==12){
      	printf("Falla(n) la(s) compuerta(s): 3 y 4\n");
      }
      else if(dato==13){
      	printf("Falla(n) la(s) compuerta(s): 1, 3 y 4\n");
      }
      else if(dato==14){
      	printf("Falla(n) la(s) compuerta(s): 2, 3 y 4\n");
      }
      else if(dato==15){
      	printf("Falla(n) la(s) compuerta(s): 1, 2, 3 y 4\n");
      }
      CloseHandle(device);
   }
   printf("Fin\n");
   getchar();
}





#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HANDLE *device;
unsigned short dato=0x55;//dato de 16 bits
DWORD aux;

void main() {
	printf("Abriendo comunicacion con el dispositivo ... \n");
	device=CreateFile("\\\\.\\PTOPARRnW", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (device!=INVALID_HANDLE_VALUE) {
		printf(" ... comunicacion establecida!\n");
		printf("Dame el dato: ");
		scanf("%d",&dato);
		WriteFile(device,&dato,2,&aux,NULL);//dos ya van a escribir dos bytes 
		printf("Write: dato=%04x, aux=%04x\n",dato,aux);
		ReadFile(device,&dato,2,&aux,NULL);
		printf("Read: dato=%04x, aux=%04x\n",dato,aux);
		CloseHandle(device);
	}
	printf("Fin\n");
	getchar();
}