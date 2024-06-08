#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(x, y) _mkdir(x)
#else
#include <unistd.h>
#endif

// Definir la función limpiarPantalla
void limpiarPantalla() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

typedef struct {
  int id;
  char nombre[50];
  char correo[50];
  char contraseña[50];
  float saldo;
} Usuario;

typedef struct {
  int id;
  char fecha[20];
  int *caballos;
  int resultado;
} Carrera;

typedef struct {
  int id;
  char nombre[50];
  int edad;
  char raza[50];
  int velocidad;
} Caballo;

typedef struct {
  int usuario_id;
  int id;
  int carrera_id;
  int caballo_id;
  float monto;
  char estado[10];
} Apuesta;

// Declaración de las funciones
void registrar_usuario(const char *nombre, const char *correo,
                       const char *contraseña);
int obtener_siguiente_id();
int verificar_usuario(const char *nombre, const char *correo,
                      const char *contraseña);
Carrera crear_carrera(int id_carrera, int *caballos, int resultado,
                      time_t inicio_semana);
void mostrar_menu();

// Implementación de las funciones
int obtener_siguiente_id() {
  FILE *file = fopen("last_id.txt", "r+");
  int id;

  // Si no existe el archivo, se crea con el primer ID
  if (file == NULL) {
    file = fopen("last_id.txt", "w");
    if (file == NULL) {
      perror("Error al crear el archivo last_id.txt");
      exit(EXIT_FAILURE);
    }
    id = 1;
    fprintf(file, "%d\n", id);
  } else {
    // Leer el último ID
    fscanf(file, "%d", &id);
    // Incrementar el ID
    id++;
    // Mover el puntero al principio del archivo y actualizar el ID
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d\n", id);
  }
  fclose(file);
  return id;
}

void registrar_usuario(const char *nombre, const char *correo,
                       const char *contraseña) {
  int id = obtener_siguiente_id(); // Obtener el ID automáticamente

  // Construcción del path del archivo
  char filepath[100];
  snprintf(filepath, sizeof(filepath), "users_data/%s.txt", nombre);

  // Verificación de la existencia del archivo
  FILE *file = fopen(filepath, "r");
  if (file != NULL) {
    fclose(file);
    printf("Usuario ya existe\n");
    return;
  }

  // Creación del archivo y almacenamiento de los datos
  file = fopen(filepath, "w");
  if (file == NULL) {
    perror("Error al crear el archivo");
    return;
  }
  fprintf(file, "ID: %d\nNombre: %s\nCorreo: %s\nContraseña: %s\n", id, nombre,
          correo, contraseña);
  fclose(file);
  printf("Usuario registrado exitosamente\n");
}

int verificar_usuario(const char *nombre, const char *correo,
                      const char *contraseña) {
  // Verificar si el archivo de usuario existe
  char filepath[100];
  snprintf(filepath, sizeof(filepath), "users_data/%s.txt", nombre);
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Usuario no encontrado\n");
    return -1;
  }

  // Leer los datos del archivo
  int file_id;
  char file_nombre[50];
  char file_correo[100];
  char file_contraseña[50];
  fscanf(file, "ID: %d\nNombre: %s\nCorreo: %s\nContraseña: %s\n", &file_id,
         file_nombre, file_correo, file_contraseña);
  fclose(file);

  // Comparar los datos
  if (strcmp(file_nombre, nombre) == 0 && strcmp(file_correo, correo) == 0 &&
      strcmp(file_contraseña, contraseña) == 0) {
    printf("Datos verificados correctamente. ID: %d\n", file_id);
    return file_id;
  } else {
    printf("Los datos no coinciden\n");
    return -1;
  }
}

Carrera crear_carrera(int id_carrera, int *caballos, int resultado,
                      time_t inicio_semana) {
  Carrera nueva_carrera;
  nueva_carrera.id = id_carrera;

  // Obtenemos la fecha de la carrera como la fecha actual más el número de días
  // desde el inicio de la semana
  time_t tiempo_carrera = inicio_semana + (id_carrera - 1) * 24 * 3600;
  struct tm *tiempo_info = localtime(&tiempo_carrera);
  strftime(nueva_carrera.fecha, sizeof(nueva_carrera.fecha), "%d/%m/%Y",
           tiempo_info);

  nueva_carrera.caballos = caballos;
  nueva_carrera.resultado = resultado;
  return nueva_carrera;
}

void mostrar_menu() {
  printf("=====================================\n");
  printf(" Bienvenido a la app de apuestas\n");
  printf("=====================================\n\n");
  printf("1) Crear cuenta\n");
  printf("2) Iniciar sesión\n");
}

int main() {
  // Crear el directorio de datos de usuario si no existe
  struct stat st = {0};
  if (stat("users_data", &st) == -1) {
    mkdir("users_data", 0700);
  }

  int opcion;
  char nombre[50], correo[50], contraseña[50];

  while (1) {
    limpiarPantalla();
    mostrar_menu();
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      limpiarPantalla();
      printf("Ingrese su nombre: ");
      scanf("%s", nombre);
      printf("Ingrese su correo: ");
      scanf("%s", correo);
      printf("Ingrese su contraseña: ");
      scanf("%s", contraseña);
      registrar_usuario(nombre, correo, contraseña);
      break;
    case 2:
      limpiarPantalla();
      printf("Ingrese su nombre: ");
      scanf("%s", nombre);
      printf("Ingrese su correo: ");
      scanf("%s", correo);
      printf("Ingrese su contraseña: ");
      scanf("%s", contraseña);
      verificar_usuario(nombre, correo, contraseña);
      break;
    default:
      printf("Opción no válida\n");
      break;
    }

    printf("Presione Enter para continuar...");
    getchar(); // Para consumir el '\n' dejado por scanf
    getchar(); // Para esperar al usuario
  }

  return 0;
}