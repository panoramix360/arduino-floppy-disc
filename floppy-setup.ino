// Array de segmentos do display7
/*
 *   A
   F   B
     G 
   E   C
     D   DP
*/
byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = Digito 0
                                 { 0,1,1,0,0,0,0 },  // = Digito 1
                                 { 1,1,0,1,1,0,1 },  // = Digito 2
                                 { 1,1,1,1,0,0,1 },  // = Digito 3
                                 { 0,1,1,0,0,1,1 },  // = Digito 4
                                 { 1,0,1,1,0,1,1 },  // = Digito 5
                                 { 1,0,1,1,1,1,1 },  // = Digito 6
                                 { 1,1,1,0,0,0,0 },  // = Digito 7
                                 { 1,1,1,1,1,1,1 },  // = Digito 8
                                 { 1,1,1,0,0,1,1 }  // = Digito 9
                                 };

// Pin do Botão
int buttonPin = 11;
// Estado do botão (começa desligado)
int buttonState = 0;

// Velocidade do leitor floppy
int velSpeed = 0;
// Usado para cálculo do map
int x = 0;

// Pino do direct
int dir_pin = 12;
// Pino do step
int step_pin = 13;
// Potenciômetro
int potenciometer = A0;

// Init
void setup() {
  // Iniciar o display
  setupDisplay();
  // Iniciar o floppy disk   
  setupFloppy();
  // Iniciar o botão
  setupButton();
  // Inicializa o ponto do display desligado
  ligarPonto(0);  // Inicia com o ponto desligado
}

int count = 0;

// Loop principal
void loop() {
  // leitura do estado do botão
  buttonState = digitalRead(buttonPin);
  
  // checa se o botão foi pressionado
  if (buttonState == HIGH) {
    // Mostra o número no display
    displayLigar(count);
     
    // verifica a velocidade do potenciometro
    velSpeed = analogRead(potenciometer);
    x = map(velSpeed, 0, 1023, 1880, 6000);
    velSpeed = x;
    
    // move o leitor floppy para trás e para frente
    moveBack();
    moveUp();
     
    // aumenta o número
    count++;
    // se chegar a 10, ele reinicia
    if(count >= 10) {
      count = 0; 
    }
  }
}

// Função para ligar o ponto do display
void ligarPonto(byte dot) {  
  digitalWrite(9, dot);
}

// Aciona um display em um digito
void displayLigar(byte digit) {
  byte pin = 2;
  //Percorre o array ligando os segmentos correspondentes ao digito
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
  ligarPonto(1);  //Liga o ponto
  delay(100);   //Aguarda 100 milisegundos
  ligarPonto(0);  //Desliga o ponto
}

// move o leitor de floppy para trás
void moveBack() {
  digitalWrite(dir_pin, LOW);
  delay(1);   
  perform_step(100);
  delay(100); 
}

// move o leitor de floppy para frente
void moveUp() {
  digitalWrite(dir_pin, HIGH);
  delay(1);
  perform_step(100);
  delay(100);
}

// move o step
void perform_step(long steps) {
  for (long i=0; i < steps; i++) {
    digitalWrite(step_pin, LOW);
    delayMicroseconds(100);
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(velSpeed);
  }
  // Set the pin low before we end
  digitalWrite(step_pin, LOW);
}

// SETUPS
void setupDisplay() {
  pinMode(2, OUTPUT); //Pino 2 do Arduino ligado ao segmento A  
  pinMode(3, OUTPUT); //Pino 3 do Arduino ligado ao segmento B
  pinMode(4, OUTPUT); //Pino 4 do Arduino ligado ao segmento C
  pinMode(5, OUTPUT); //Pino 5 do Arduino ligado ao segmento D
  pinMode(6, OUTPUT); //Pino 6 do Arduino ligado ao segmento E
  pinMode(7, OUTPUT); //Pino 7 do Arduino ligado ao segmento F
  pinMode(8, OUTPUT); //Pino 8 do Arduino ligado ao segmento G
  pinMode(9, OUTPUT); //Pino 9 do Arduino ligado ao segmento PONTO 
}

void setupFloppy() {
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT); 
}

void setupButton() {
  pinMode(buttonPin, INPUT); 
}
