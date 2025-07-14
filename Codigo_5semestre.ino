// Bibliotecas que serão utilizados no programa
#include <Ultrasonic.h>
#include <FalconRobot.h>  

FalconRobotMotors motors; // Inicia os motores do Projeto Falcon

FalconRobotLineSensor left(A5); // Localiza o Sensor de Luz ESQUERDO
FalconRobotLineSensor right(A3); // Localiza o Sensor de Luz DIREITO
FalconRobotLineSensor middle(A0);


Ultrasonic ultrassom(3,2); // Localiza o ECHO(2) e TRIG(3) do Sensor de proximidade, no caso o receptor da onda (ECHO) e o emissor da onda (TRIGGER) para detecção da proximidade de objetos
 
int distancia;

int velo_DIR;   // Variável que vai guardar a VELOCIDADE do motor ESQUERDO
int velo_ESQ;  // Variável que vai guardar a VELOCIDADE do motor DIREITO

int val_ESQ;  // Variável que vai guardar O VALOR do sensor de LUZ ESQUERDO
int val_DIR;  // Variável que vai guardar O VALOR do sensor de LUZ DIREITO
int val_M;
int val_MR;


#define LIMITADOR 750 // Define um limite com a média dos valores da detecção da luz em ambiente branco e ambiente ESCURO, para definir como o veículo irá tracejar
#define SPEED 60 // Define um parâmetro inicial da velocidade dos motores do projeto



// NO VOID SETUP: Coloca configurações que seria processados uma só vez por iniciallização  
void setup() {
  Serial.begin(9600); // Define a taxa de dados, em bits por segundo (baud)
  pinMode(LED_BUILTIN, OUTPUT); 
  delay(5000); // Demora 5000 milissegundos (5 segundos) para começar

}

void Luz1(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);

}

void Luz2(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);

}


// Função para definir como o carrinho comporta com objetos em sua frente
void Sensordistancia() {
  distancia = ultrassom.Ranging(CM);
  Serial.println("distancia Sensor Readings: " + distancia);

  if((distancia > 0) && (distancia <= 10)) {
    motors.stop();
    velo_DIR = SPEED - 60;
    velo_ESQ = SPEED - 60;
    motors.leftDrive(velo_DIR, FORWARD);
    motors.rightDrive(velo_ESQ, FORWARD);
    motors.stop();
    Serial.println("PAROU PARA EVITAR A BATIDA"); 
    Luz1();

  }
}

// FUNÇÃO LOOP: cria-se um ciclo de repetição para que as instruções dentro do mesmo sejam repetidas
void loop() {
  val_ESQ = left.read(); //COLETA O DADO NUMÉRICO DO SENSOR DE LUZ ESQUERDO
  val_DIR = right.read(); //COLETA O DADO NUMÉRICO DO SENSOR DE LUZ DIREITO
  val_M = middle.read();
  Sensordistancia(); //COLOCA A FUNÇÃO DO SENSOR PARA EXECUTAR

    contador = millis();

  if ((val_ESQ > LIMITADOR ) && (val_DIR > LIMITADOR ) && (val_M > LIMITADOR ) ){
    velo_DIR = SPEED - 30;
    velo_ESQ = SPEED - 20;

    Sensordistancia();
    
    motors.leftDrive(velo_DIR, BACKWARD);
    motors.rightDrive(velo_ESQ, BACKWARD);

  }


  if ((val_ESQ > LIMITADOR ) && (val_DIR > LIMITADOR ) && (val_M < LIMITADOR )){

    velo_DIR = SPEED;
    velo_ESQ = SPEED;

    Sensordistancia();

    motors.leftDrive(velo_DIR, FORWARD);
    motors.rightDrive(velo_ESQ, FORWARD);
  }


  if ((val_ESQ < LIMITADOR ) && (val_DIR > LIMITADOR ) && (val_M > LIMITADOR )){

    velo_DIR = SPEED - 20;
    velo_ESQ = SPEED - 60;

    Sensordistancia();
    
    motors.leftDrive(velo_DIR, FORWARD);
    motors.rightDrive(velo_ESQ, FORWARD);
  }


  if ((val_ESQ < LIMITADOR ) && (val_DIR < LIMITADOR ) && (val_M < LIMITADOR )){

    velo_DIR = SPEED - 30;
    velo_ESQ = SPEED - 20;

    Sensordistancia();
    
    Luz1();

    motors.leftDrive(velo_DIR, FORWARD);
    motors.rightDrive(velo_ESQ, FORWARD);
  }

  if ((val_ESQ > LIMITADOR ) && (val_DIR < LIMITADOR ) && (val_M < LIMITADOR )){

    velo_DIR = SPEED - 60;
    velo_ESQ = SPEED - 20;

    Sensordistancia();
    
    Luz1();

    motors.leftDrive(velo_DIR, FORWARD);
    motors.rightDrive(velo_ESQ, FORWARD);
  }
  if ((val_ESQ < LIMITADOR ) && (val_DIR > LIMITADOR ) && (val_M < LIMITADOR )){

    velo_DIR = SPEED - 30;
    velo_ESQ = SPEED - 60;

    Sensordistancia();
    
    Luz1();

    motors.leftDrive(velo_DIR, FORWARD);
    motors.rightDrive(velo_ESQ, FORWARD);
  }
    
}