#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "hashmap.h"
#include "list.h"

typedef struct{
  char nombre[50];
  char correo[50];
  char contraseña[20];
} tipoUsuario;

void registroUsuario(){
  tipoUsuario usuario;
  printf("Ingrese su nombre: ");
  scanf("%s", usuario.nombre);
  printf("Ingrese su correo: ");
  scanf("%s", usuario.correo);
  printf("Ingrese su contraseña: ");
  scanf("%s", usuario.contraseña);
}

void verifyUser(tipoUsuario *usuario){
  //if (searchMap()
}