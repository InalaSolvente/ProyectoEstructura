#include <stdio.h>
#include <stdbool.h>
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
  float dinero;
  List *historialApuestas;
} tipoUsuario;

void registroUsuario(HashMap *mapa){
  tipoUsuario usuario;
  printf("Ingrese su nombre: ");
  scanf("%s", usuario.nombre);
  printf("Ingrese su correo: ");
  scanf("%s", usuario.correo);
  printf("Ingrese su contraseña: ");
  scanf("%s", usuario.contraseña);
  usuario.dinero = 0;
  usuario.historialApuestas = createList();
  insertMap(mapa,usuario.nombre, &usuario);
}

bool verifyUser(HashMap *mapa, tipoUsuario usuario){
  if (searchMap(mapa, usuario.nombre) != NULL){
    tipoUsuario usuarioEncontrado = *(tipoUsuario *)searchMap(mapa, usuario.nombre);
    if (strcmp(usuarioEncontrado.contraseña, usuario.contraseña)==0)
      return true;
  }
  return false;
}

void realizarApuesta(tipoUsuario *usuario, List *carreras){
  
}