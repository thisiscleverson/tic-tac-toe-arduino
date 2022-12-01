/*
 tic-tac-toe-arduino
 by thisiscleverson
 version: 01
 github: https://github.com/thisiscleverson
 repository: https://github.com/thisiscleverson/tic-tac-toe-arduino.git
*/

//variáveis




int board[9] = { // tabuleiro vazio
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1
                }; 


int winningSequences[8][3] = {
                              {0,1,2},
                              {3,4,5},
                              {6,7,8},
                              {0,3,6},
                              {1,4,7},
                              {2,5,8},
                              {0,4,8},
                              {2,4,6}
                            };


byte pins_buttons[9] = {5,6,7,8,9,10,11,12,13};      // Lista de pinos digitais para os botões
byte pins_relay_x[9] = {14,15,16,17,18,19,20,21,22}; // pinos digitais para o relé da fita de led [X]
byte pins_relay_o[9] = {23,24,25,26,27,28,29,30,31}; // pinos digitais para o relé da fita de led [O]

bool active_piezo = true;
bool debug        = true; // variável para mostrar todos os logs no serial monitor
bool gameover     = false; 
bool symbols      = 1;    // 1 para [X] & 0 para [O]


#define effect1 32 // pino de efeito de vencedor ou perdedor  
#define effect2 33 // pino de efeito de vencedor ou perdedor 

#define time_to_reset 2000   // delay para poder resetar o tabuleiro (milissegundos) --> 1s = 1000ms
#define calibrate_button 50 // delay para calibrar a leitura dos botões

#define piezo 3

//Funções
bool change(){
  symbols = !symbols;
  return symbols;
}


int getButtonAction(){ // capturar qual botão foi precionado
  for(int x=0; x<9; x++){
    if(digitalRead(pins_buttons[x]) != 1){
      return x; // retornar o index do botão precionado
    };
  };
  return -1; // retornar -1 se nenhum botão foi apertado
}


void make_play(int position){ // inserir o [X] ou [O] no tabuleiro
  bool symbols;
  int winningSequencesIndex;

  if(board[position] == -1){
    symbols = change();
    board[position] = symbols;
    ledEffect(position, symbols);
    //ativar/desativar o buzzer
    if(active_piezo){
      digitalWrite(piezo, HIGH);
      delay(500);
      digitalWrite(piezo, LOW);
    }
  };

  winningSequencesIndex = checkWinningSequences(symbols); // verificar a sequência vencedora 

  if(winningSequencesIndex == -1){
    checkTie(); // verificar se deu um empate
  }else{
    winnerOrLoserEffect(symbols);
  }
}


void ledEffect(int position, bool symbols){
  
  if(symbols == 0){      // ligar o led do [O]
    digitalWrite(pins_relay_o[position], HIGH);    
  }
  else if(symbols == 1){ // ligar o led do [X]
    digitalWrite(pins_relay_x[position], HIGH); 
  }
}

void winnerOrLoserEffect(int effects){
  if(effects == 0){
    digitalWrite(effect1, HIGH);
  }
  else if(effects == 1){
    digitalWrite(effect2, HIGH);
  }
}

void cleanLedEffect(int position){

    // desligar os leds de [X] & [O]  
    digitalWrite(pins_relay_o[position], LOW);
    digitalWrite(pins_relay_x[position], LOW);   

    // desligar os leds de vencedor ou perdedor
    digitalWrite(effect1, LOW); 
    digitalWrite(effect2, LOW);
}


int checkWinningSequences(bool symbols){
  for(int i=0; i<8; i++){
    if(board[winningSequences[i][0]] == symbols && board[winningSequences[i][1]] == symbols && board[winningSequences[i][2]] == symbols){
      gameover = true;
      return i; 
    };
  };
  return -1;
}


void checkTie(){ // verificar empate
  for(int i=0; i<9; i++){
    if(board[i] == -1){
      return;
    }
  };
  gameover = true;
}


void reset(){
  // limpar o tabuleiro  
  for(int i=0; i<9; i++){
    board[i] = -1;
    cleanLedEffect(i); // função para desligar todos os leds
  };  
  symbols  = 1;
  gameover = false;  
}


void showBoard(){ // mostrar o tabuleiro no monitor serial
  for(int i=0; i<9;){
      for(int r=0; r<3; r++){
        Serial.print(String(board[i]) + " ");
        i++;      
      };
      Serial.println();
    };
}


//setup
void setup() {
  Serial.begin(9600);

  // ativar os pinos digitais do botões como entrada
  for(int i=0; i<9; i++){
    pinMode(pins_buttons[i], INPUT_PULLUP);
  };


  // ativar os pinos digitais do relé como saida
  for(int i=0; i<9; i++){
    pinMode(pins_relay_x[i], OUTPUT); // pinos digitais do relé x
    pinMode(pins_relay_o[i], OUTPUT); // pinos digitais do relé o
  };  

  // definir os pinos de efeito de vencedor ou perdedor como saida
  pinMode(effect1, OUTPUT);
  pinMode(effect2, OUTPUT);
  //definir o pino do buzzer como saida
  pinMode(piezo,   OUTPUT);

  // mostrar o tabuleiro no monitor serial
  if(debug){
    Serial.println("Board:");
    showBoard(); 
  }
}

void loop() {
  
  // fazer a leitura de todos os botões
  // e retornar o index do botão precionado
  int buttonIndex = getButtonAction(); 
  
  if(buttonIndex != -1 && !gameover){
      make_play(buttonIndex);
      
      // mostrar o tabuleiro na Serial
      if(debug){
        Serial.println("Board:");
        showBoard();
      }
  };

  // resetar o jogo
  if(gameover){
    //ativar o som de gamerover
    active_piezo == true? digitalWrite(piezo, HIGH):  // operador ternario para ativar/desativar o buzzer    
    delay(time_to_reset);                             // esperar 2 segundos para reiniciar o jogo
    active_piezo == true? digitalWrite(piezo, LOW):   // operador ternario para ativar/desativar o buzzer  
    reset();                                          // resetar o tabuleiro

    // mostrar o tabuleiro na Serial
    if(debug){
      Serial.println("Gamer Over");
      showBoard();
    }
  };
  
  delay(calibrate_button);
}