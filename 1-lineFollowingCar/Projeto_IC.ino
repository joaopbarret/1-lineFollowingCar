#include "Ultrasonic.h"
//variaveis para declarar os pinos
int Motor_E1 = 6;
int Motor_E2 = 7;
int Motor_EV = 9;
int Motor_DV = 3;
int Motor_D2 = 4;
int Motor_D1 = 5;


#define echoPin 10 //Pino 10 recebe o pulso do echo
#define trigPin 8 //Pino 8 envia o pulso para gerar o echo

Ultrasonic ultrasonic(trigPin,echoPin);


int inPin = 2; //pino de entrada no sensor
int valor = 0; //Inteiro que armazena o valor lido pelo sensor infravermelho
int cont = 0; //contador utilizador para escolher se o carrinho vai dobrar para direita ou esquerda
int passado = 0; // armazena o valor antigo da leitura do sensor, permitindo uma comparação entre a leitura atual e a anterior


//a função recebe o valor captado pelo sensor(ainda na função main)
//E utiliza dessa informação para decidir se deve dobrar à esquerda ou direita
void andar(){
    //O carrinho começa na linha branca("valor"=1), logo o valor de "passado"(que começa como zero, ou seja, preto)
    //permite que o programa ja entre no segundo if, o que fará com que ele atualize o valor de "passado"(que passará a ser 1).
    //Como o contador foi inicializado com o valor 0(par), o carrinho entrará na função "curva_direita",
    //com isso, ele sai da linha branca, atualizando a variável "valor" para 0(preto).
    //assim, o carrinho entra no primeiro if, que, além de atualizar o "passado", soma mais um ao contador, fazendo com que 
    //o contador se torne ímpar e agora execute a funcão "curva_esquerda"

    //ao fim, percebe-se que o carrinho continua com esse ciclo, sempre comparando o valor atual e passado do sensor, para
    //manipular o valor do contador(entre ímpar e par), visando alternar curvas para ambos os lados
    if (valor == LOW && valor != passado){
        passado = valor;
        cont++;
    }

    else if (valor == HIGH && valor !=passado){
        passado = valor;
    }
   


    if (cont % 2 == 0){
        curva_direita();
   
    }

    else if((cont % 2)==1){
      curva_esquerda();
    }
}
//as funções de curva tem velocidades diferentes, pois o carrinho tem uma diferença de forca entre os motores.
//Após testes, constatamos que o motor esquerdo tem uma força superior ao direito, com isso
//deixamos com essas velocidades para tentar balancear
void curva_direita(){
    
    analogWrite(Motor_EV,60 );
    analogWrite(Motor_DV, 0);
    digitalWrite(Motor_E1, LOW);
    digitalWrite(Motor_E2, HIGH);
    digitalWrite(Motor_D1, LOW);
    digitalWrite(Motor_D2, HIGH);
 
 

}
 
void curva_esquerda(){
    analogWrite(Motor_EV, 0);
    analogWrite(Motor_DV, 120);
    digitalWrite(Motor_E1, LOW);
    digitalWrite(Motor_E2, HIGH);
    digitalWrite(Motor_D1, LOW);
    digitalWrite(Motor_D2, HIGH);

}
//Criamos a função desvio para tentar desviar do obstáculo
//o carrinho não consegui efetuar o desvio, por isso deixamos o código comentado

/*void desvio (int distancia){
  if ( ( distancia >= 1 ) && ( distancia <= 15 ) ){
  analogWrite(Motor_EV, 90);
  analogWrite(Motor_DV, 0);
  digitalWrite(Motor_E1, LOW);
  digitalWrite(Motor_E2, HIGH);
  digitalWrite(Motor_D1, LOW);
  digitalWrite(Motor_D2, HIGH);
 delay(450);
 analogWrite(Motor_EV, 90);
  analogWrite(Motor_DV, 90);
  digitalWrite(Motor_E1, LOW);
  digitalWrite(Motor_E2, HIGH);
  digitalWrite(Motor_D1, LOW);
  digitalWrite(Motor_D2, HIGH);
  delay(500);
  analogWrite(Motor_EV, 0);
  analogWrite(Motor_DV, 90);
  digitalWrite(Motor_E1, LOW);
  digitalWrite(Motor_E2, HIGH);
  digitalWrite(Motor_D1, LOW);
  digitalWrite(Motor_D2, HIGH);
  delay(450);
   analogWrite(Motor_EV, 90);
  analogWrite(Motor_DV, 90);
  digitalWrite(Motor_E1, LOW);
  digitalWrite(Motor_E2, HIGH);
  digitalWrite(Motor_D1, LOW);
  digitalWrite(Motor_D2, HIGH);
  delay(500);
 analogWrite(Motor_EV, 0);
  analogWrite(Motor_DV, 90);
  digitalWrite(Motor_E1, LOW);
  digitalWrite(Motor_E2, HIGH);
  digitalWrite(Motor_D1, LOW);
  digitalWrite(Motor_D2, HIGH);
  delay(450);
  analogWrite(Motor_EV, 90);
  analogWrite(Motor_DV, 90);
  digitalWrite(Motor_E1, LOW);
  digitalWrite(Motor_E2, HIGH);
  digitalWrite(Motor_D1, LOW);
  digitalWrite(Motor_D2, HIGH);
  }
}*/

 
void setup()
{
 
   
    pinMode(Motor_E1, OUTPUT);
    pinMode(Motor_E2, OUTPUT);
    pinMode(Motor_EV, OUTPUT);
    pinMode(Motor_DV, OUTPUT);
    pinMode(Motor_D2, OUTPUT);
    pinMode(Motor_D1, OUTPUT);
    pinMode(echoPin, INPUT); // define o pino 10 como entrada (recebe)
    pinMode(trigPin, OUTPUT); // define o pino 8 como saida (envia)
    Serial.begin(9600); //inicializando a porta serial
    pinMode(inPin, INPUT); //colocando a porta 2 como entrada
  }
 
void loop () {
    //a variável valor é responsável por receber o resultado do digitalRead
    valor = digitalRead(inPin);//realizando a leitura no sensor optico
    //LOW ou 0 -> Preto
    //High ou 1 -> Branco
   andar();
   // desvio(distancia);
   // int distancia = pre_obstaculo();
    //obstaculo();
   
     

               
}
