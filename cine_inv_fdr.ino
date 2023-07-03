//INCLUDES
#include <math.h>

//DEFINES
#define SIZE 3  //Grados de libertad

//VARIABLES
float dimensiones[SIZE] = { 7.7, 8.9, 3.6 };  //Distancias -conocidas -entre juntas
float coordenadas[SIZE] = { 1, 4, 3 };        //Coordenadas a ingresar
float angulos[SIZE] = { 0 };                  //Angulos resultantes

//FUNCTIONS
void helloWorld(void);  //Lleva a cabo las configuraciones iniciales del código
void goodNight(void);   //Muestra los valores resultantes y termina

/*
  MAIN
*/
void setup() {

  //HI
  helloWorld();

  //CALCULO DE DISTANCIAS 'R'
  float r1 = sqrt(coordenadas[0] * coordenadas[0] + coordenadas[1] * coordenadas[1]);  // raiz de x0^2 + y0^2
  float r2 = coordenadas[2] - dimensiones[0];                                          // Z0 - a1
  float r3 = sqrt(r1 * r1 + r2 * r2);

  //CALCULO DE ANGULOS 'PHI'
  float phi1 = 180 * acos((dimensiones[2] * dimensiones[2] - dimensiones[1] * dimensiones[1] - r3 * r3) / (-2 * dimensiones[1] * r3)) / PI;
  float phi2 = 180 * atan(r2 / r1) / PI;
  float phi3 = 180 * acos((r3 * r3 - dimensiones[1] * dimensiones[1] - dimensiones[2] * dimensiones[2]) / (-2 * dimensiones[1] * dimensiones[2])) / PI;  //phi3 da mal xq no esta bien usada la ley de cosenos - le saque los menos

  //CALCULO DE ANGULOS 'THETA'
  angulos[0] = 180 * atan(coordenadas[1] / coordenadas[0]) / PI;
  angulos[1] = phi2 - phi1;
  angulos[2] = 180 - phi3;

  //BYE BYE
  goodNight();
}

void loop(){};
/*
  Configura el serial y pide el punto referencial para calcular la cinematica inversa
*/
void helloWorld(void) {

  Serial.begin(9600);

  Serial.println("CALCULO DE CINEMATICA INVERSA");
  Serial.println("      robot 3gdl - 3 revoluta");
  Serial.println("");

  Serial.println("Las dimensiones del robot son:");

  for (int i = 0; i < SIZE; i++) {
    Serial.print("a");
    Serial.print(i + 1);
    Serial.print("       : ");
    Serial.println(dimensiones[i]);
  }
  Serial.println("----------------------------");

  Serial.println("!!INPUT DE COORDENADAS");
  /*for (int i = 0; i < SIZE; i++)
    if (Serial.available() != 0)
      coordenadas[i] = Serial.read();
*/
  Serial.println("");

  if (!coordenadas[0]) {
    Serial.println("ERROR");
    while (1)
      ;
  }
}
/*
  Enseña los angulos calculados finales correspondientes al movimiento de las juntas
*/

void goodNight(void) {
  Serial.println("");
  Serial.println("Los angulos resultantes son:");
  Serial.println("----------------------------");
  for (int i = 0; i < 3; i++) {
    Serial.print("theta ");
    Serial.print(i + 1);
    Serial.print("       : ");
    Serial.print(angulos[i]);
    Serial.println(" grados");
  }
  Serial.println("----------------------------");

  Serial.println("");
  Serial.println("... buenas noches");
}
