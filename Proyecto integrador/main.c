//Marco Molina - Sebastian Urrutia 
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// Inicializamos tamaño del BUFFER
#define BUFFER_SIZE 256 // Tamaño del Buffer
// colores
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_ORANGE "\x1b[38;5;208m"

// Variables globales
int indiceActual = 0;                           // Indice para orden de llegada
pthread_mutex_t mutexIndice;                    // Mutex para FCFS
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Condicionante para FCFS
int canalAB[2];                                 // Canal de A a B
int canalBA[2];                                 // Canal de B a A

int tipoUsuario;
// Tipo de dato puntero para almacenar los procesos
typedef void *(*TaskFunction)(void *);

// Funcion para pintar los caracteres
void printColorMessage(const char *color, const char *format, ...) {
  va_list args;
  va_start(args, format);

  printf("%s", color);
  vprintf(format, args);

  printf("%s",ANSI_COLOR_ORANGE);
  va_end(args);
}

// Estructura para almacenar los procesos
typedef struct {
  TaskFunction task;
  const char *description;
  pthread_t thread_id;
  int taskOrder; // Identificador de hilo para esta tarea
} Task;

// Proceso calculo de promedios
void *promedio(void *arg) {
  int miIndice = *(int *)arg;
  free(arg);
  pthread_mutex_lock(&mutexIndice);
  while (miIndice != indiceActual) {
    pthread_cond_wait(&cond, &mutexIndice);
  }
  char buffer[BUFFER_SIZE];
  double suma = 0;
  int numeroDeNotas;
  printColorMessage(
      ANSI_COLOR_BLUE,
      "----------FUNCION CALCULAR PROMEDIO CON HILOS----------\n");
  printColorMessage(ANSI_COLOR_MAGENTA,
                    "Ingrese el numero de notas para ingresar\n");
  scanf("%d", &numeroDeNotas);
  for (int i = 0; i < numeroDeNotas; i++) {
    double nota;
    printColorMessage(ANSI_COLOR_MAGENTA, "Ingrese la nota %d: ", i + 1);
    scanf("%lf", &nota);
    suma += nota;
  }
  double promedio = (suma / numeroDeNotas);
  sprintf(buffer, "El promedio de las notas ingresadas es de: %lf", promedio);
  write(canalAB[1], buffer, strlen(buffer) + 1);
  return NULL;
}
// Proceso crear matriz y calcular determinante
void *matriz(void *arg) {
  int miIndice = *(int *)arg;
  free(arg);
  pthread_mutex_lock(&mutexIndice);
  while (miIndice != indiceActual) {
    pthread_cond_wait(&cond, &mutexIndice);
  }
  char buffer[BUFFER_SIZE];
  int matriz[3][3];
  double det = 0;
  printColorMessage(ANSI_COLOR_BLUE, "----------FUNCION CALCULAR DETERMINANTE "
                                     "DE MATRIZ 3X3 CON HILOS----------\n");

  // Captura de los valores de la matriz
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printColorMessage(ANSI_COLOR_MAGENTA,
                        "Ingrese el valor de la fila %d y columna %d: ", i + 1,
                        j + 1);
      scanf("%d", &matriz[i][j]);
    }
  }

  // Mostrar la matriz capturada
  printColorMessage(ANSI_COLOR_YELLOW, "Matriz ingresada:\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("[%d]", matriz[i][j]); // Usar tabulador para mejor alineación
    }
    printf("\n"); // Nueva línea después de cada fila
  }

  // Cálculo del determinante
  det += matriz[0][0] * matriz[1][1] * matriz[2][2];
  det += matriz[0][1] * matriz[1][2] * matriz[2][0];
  det += matriz[0][2] * matriz[1][0] * matriz[2][1];
  det -= matriz[0][2] * matriz[1][1] * matriz[2][0];
  det -= matriz[0][0] * matriz[1][2] * matriz[2][1];
  det -= matriz[0][1] * matriz[1][0] * matriz[2][2];
  sprintf(buffer, "La determinante de la matriz 3x3 es: %f\n", det);
  write(canalAB[1], buffer, strlen(buffer) + 1);
  pthread_mutex_unlock(&mutexIndice);
  return NULL;
}

// Proceso calcular Logaritmo
void *logaritmo(void *arg) {
  int miIndice = *(int *)arg;
  free(arg);
  pthread_mutex_lock(&mutexIndice);
  while (miIndice != indiceActual) {
    pthread_cond_wait(&cond, &mutexIndice);
  }
  double num;
  char buffer[BUFFER_SIZE];
  printColorMessage(ANSI_COLOR_BLUE, "----------FUNCION CALCULAR LOGARITMO EN "
                                     "BASE 10 DE UN NUMERO----------\n");
  printColorMessage(ANSI_COLOR_MAGENTA,
                    "Ingrese un numero para calcular su logaritmo:\n");
  scanf("%lf", &num);
  if (num > 0) {
    double logaritmo = log10(num);
    sprintf(buffer, "el logaritmo de %.1lf es: %.2lf\n", num, logaritmo);
    write(canalAB[1], buffer, strlen(buffer) + 1);
  } else {
    sprintf(buffer, "no se puede calcular el logaritmo de ese numero\n");
    write(canalAB[1], buffer, strlen(buffer) + 1);
  }
  sleep(1);
  return NULL;
}

// Proceso identificar tipo de Triangulo
void *tipoTriangulo(void *arg) {
  int miIndice = *(int *)arg;
  free(arg);
  pthread_mutex_lock(&mutexIndice);
  while (miIndice != indiceActual) {
    pthread_cond_wait(&cond, &mutexIndice);
  }
  printColorMessage(
      ANSI_COLOR_BLUE,
      "----------FUNCION DETERMINAR EL TIPO DE TRIANGULO----------\n");
  int lado1, lado2, lado3;
  char buffer[BUFFER_SIZE];
  printColorMessage(ANSI_COLOR_MAGENTA, "\nIngresar primer lado de triangulo ");
  scanf("\n%d", &lado1);
  printColorMessage(ANSI_COLOR_MAGENTA,
                    "\nIngresar segundo lado de triangulo ");
  scanf("\n%d", &lado2);
  printColorMessage(ANSI_COLOR_MAGENTA, "\nIngresar terce lado de triangulo ");
  scanf("\n%d", &lado3);
  if (lado1 == lado2 && lado2 == lado3) {
    sprintf(buffer, "\nEs un triangulo Equilatero");
    write(canalAB[1], buffer, strlen(buffer) + 1);
  } else if (lado1 == lado2 || lado1 == lado3 || lado2 == lado3) {
    sprintf(buffer, "\nEs un triangulo Isosceles");
    write(canalAB[1], buffer, strlen(buffer) + 1);
  } else {
    sprintf(buffer, "\nEs un triangulo Escaleno");
    write(canalAB[1], buffer, strlen(buffer) + 1);
  }
  return NULL;
}
// Proceso Calcular Factorial
unsigned long long factorial(int n) {
  if (n == 0) {
    return 1;
  }
  return n * factorial(n - 1);
}
// Proceso Principal para Calcular Factorial
void *calcularFactorial(void *arg) {
  int miIndice = *(int *)arg;
  free(arg);
  pthread_mutex_lock(&mutexIndice);

  while (miIndice != indiceActual) {
    pthread_cond_wait(&cond, &mutexIndice);
  }
  printColorMessage(
      ANSI_COLOR_BLUE,
      "----------FUNCION CALCULAR FACTORIAL DE UN NUMERO----------\n");
  printColorMessage(ANSI_COLOR_MAGENTA,
                    "Ingrese un numero para calcular su factorial\n");
  int num;
  scanf("%d", &num);
  unsigned long long result = factorial(num);

  char buffer[BUFFER_SIZE];
  sprintf(buffer, "Factorial de %d es: %llu\n", num, result);
  write(canalAB[1], buffer, strlen(buffer) + 1);
  return NULL;
}

// Proceso para calcular la raiz de un numero
void *enviarRaiz(void *arg) {
  int miIndice = *(int *)arg;
  free(arg);
  pthread_mutex_lock(&mutexIndice);

  while (miIndice != indiceActual) {
    pthread_cond_wait(&cond, &mutexIndice);
  }
  printColorMessage(ANSI_COLOR_BLUE,
                    "----------FUNCION CALCULAR RAIZ DE UN NUMERO----------\n");
  double numero;
  char buffer[BUFFER_SIZE];
  printColorMessage(ANSI_COLOR_MAGENTA,
                    "Ingrese un número para calcular su raíz cuadrada: ");
  scanf("%lf", &numero);
  sprintf(buffer, "La raíz cuadrada de %.2f es %.2f\n", numero, sqrt(numero));
  write(canalAB[1], buffer, strlen(buffer) + 1);
  return NULL;
}

// Funcion encargada de crear y ejecutar los hilos de acuerdo a FCFS
void ejecutarTareas(Task *taskSequence, int taskCount) {
  for (int i = 0; i < taskCount; i++) {
    // int taskIndex = taskOrder[i];
    int *arg = malloc(sizeof(*arg));
    if (arg == NULL) {
      perror("Error al asignar memoria");
      exit(EXIT_FAILURE);
    }
    *arg = taskSequence[i].taskOrder;

    if (pthread_create(&taskSequence[i].thread_id, NULL, taskSequence[i].task,
                       arg) != 0) {
      perror("Error al crear el hilo de la tarea");
      exit(EXIT_FAILURE);
    }
  }
  // Esperando a que todos los hilos terminen
  for (int i = 0; i < taskCount; i++) {
    if (pthread_join(taskSequence[i].thread_id, NULL) != 0) {
      perror("Error al unir con un hilo de tarea");
      exit(EXIT_FAILURE);
    }
  }
}

// Funcion del hilo que para que usuario ingrese tareas a ejecutar
void *hilo_canalA() {
  Task tasks[] = {
      {calcularFactorial, "Calcular el Factorial de un numero"},
      {enviarRaiz, "Calcular una raiz cuadrada"},
      {tipoTriangulo, "Determinar tipo de triangulo segun sus lados"},
      {matriz, "Calcular la determinante de una matriz 3x3"},
      {promedio, "Calcular un promedio común de notas"},
      {logaritmo, "Calcular un logaritmo de base 10"}};
  int taskCount = sizeof(tasks) / sizeof(tasks[0]);
  Task taskSequence[taskCount];
  int taskOrder[taskCount];
  if (tipoUsuario == 1) {
    printColorMessage(ANSI_COLOR_BLUE,
                      "\nComo usuario ADMINISTRADOR puede escoger una cantidad "
                      "de procesos que quiere realizar (MAX 20)\n");
    do {
      printColorMessage(ANSI_COLOR_BLUE,
                        "Indique la cantidad de tareas a realizar: ");
      if (scanf("%d", &taskCount) != 1) {
        printColorMessage(ANSI_COLOR_RED,
                          "Entrada inválida. Por favor, ingrese un número.\n");
        // Limpiar buffer de entrada
        while (getchar() != '\n')
          ;
      } else if (taskCount > 20 || taskCount < 1) {
        printColorMessage(
            ANSI_COLOR_RED,
            "Número fuera de rango. Ingrese un número entre 1 y 20.\n");
      } else {
        break;
      }
    } while (1);
  }
  printColorMessage(ANSI_COLOR_GREEN, "\n LISTAS DE TAREAS \n");
  printColorMessage(ANSI_COLOR_BLUE, "1)Calcular el Factorial de un numero\n");
  printColorMessage(ANSI_COLOR_BLUE, "2)Calcular una raiz cuadrada\n");
  printColorMessage(ANSI_COLOR_BLUE,
                    "3)Determinar tipo de triangulo segun sus lados\n");
  printColorMessage(ANSI_COLOR_BLUE,
                    "4)Calcular la determinante de una matriz 3x3\n");
  printColorMessage(ANSI_COLOR_BLUE, "5)Calcular un promedio común de notas\n");
  printColorMessage(ANSI_COLOR_BLUE, "6)Calcular un logaritmo de base 10\n");
  printColorMessage(ANSI_COLOR_CYAN,
                    "Ingrese el orden de las tareas a realizar (Puede ejecutar "
                    "%d procesos):\n",
                    taskCount);
  for (int i = 0; i < taskCount; i++) {
    scanf("%d", &taskOrder[i]);
    taskOrder[i]--;
    taskSequence[i] = tasks[taskOrder[i]];
    taskSequence[i].taskOrder = i;
  }
  ejecutarTareas(taskSequence, taskCount);
  char endMsg[] = "end";
  write(canalAB[1], endMsg, strlen(endMsg) + 1);
  pthread_exit(NULL);
}

// Función del hilo que recibe datos y los muestra
void *hilo_canalB() {
  char buffer[BUFFER_SIZE];
  while (read(canalAB[0], buffer, BUFFER_SIZE) > 0) {
    if (strcmp(buffer, "end") != 0) {
      printf("Canal B recibes: %s\n", buffer);
      sleep(1);
      indiceActual++;
      pthread_cond_broadcast(&cond);
      pthread_mutex_unlock(&mutexIndice);
    } else {
      printColorMessage(ANSI_COLOR_RED, "Canal B recibe: %s\n", buffer);
      pthread_exit(NULL);
    }
  }
  printf("Retornando NULL");
  return NULL;
}

int main() {
  pthread_mutex_init(&mutexIndice, NULL);
  pthread_cond_init(&cond, NULL);
  if (pipe(canalAB) == -1 || pipe(canalBA) == -1) {
    perror("Error al crear los pipes");
    exit(EXIT_FAILURE);
  }
  pthread_t canalA_ID, canalB_ID;
  // Crear hilos para los canales
  int opcion;
  char contra[] = "contraseñaSecreta"; // Contraseña de ejemplo
  char aux[50];                        // Buffer para la contraseña

  do {
    printColorMessage(ANSI_COLOR_BLUE, "¿Es usted un usuario administrador?\n");
    printColorMessage(ANSI_COLOR_YELLOW, "1) Si\n");
    printColorMessage(ANSI_COLOR_YELLOW, "2) No\n");
    if (scanf("%d", &opcion) != 1) {
      printColorMessage(ANSI_COLOR_RED, "Ingrese un número válido.\n");
      // Limpiar buffer de entrada
      while (getchar() != '\n')
        ;
      continue;
    }

    if (opcion != 1 && opcion != 2) {
      printColorMessage(ANSI_COLOR_RED, "Ingrese una opción válida.\n");
    } else if (opcion == 1) {
      do {
        printColorMessage(ANSI_COLOR_BLUE,
                          "\nIngrese su contraseña de administrador: ");
        scanf("%49s", aux); // Usar %49s para evitar desbordamiento de buffer

        if (strcmp(aux, contra) != 0) { // Comparar usando strcmp
          printColorMessage(ANSI_COLOR_RED, "Contraseña incorrecta.\n");
        }
      } while (strcmp(aux, contra) != 0);
      printColorMessage(ANSI_COLOR_GREEN,
                        "Contraseña correcta. Acceso concedido.\n");
      tipoUsuario = 1;
    }
  } while (opcion != 1 && opcion != 2);
  if (pthread_create(&canalA_ID, NULL, hilo_canalA, NULL) != 0 ||
      pthread_create(&canalB_ID, NULL, hilo_canalB, NULL) != 0) {
    perror("Error al crear los hilos");
    exit(EXIT_FAILURE);
  }

  // Esperando a que ambos hilos terminen
  pthread_join(canalA_ID, NULL);
  pthread_join(canalB_ID, NULL);

  pthread_mutex_destroy(&mutexIndice);
  pthread_cond_destroy(&cond);
  //  Cerrar los extremos de los pipes que ya no son necesarios
  close(canalAB[0]);
  close(canalAB[1]);
  close(canalBA[0]);
  close(canalBA[1]);

  return 0;
}