/*
 name: tic-tac-toe-arduino
 type: demo
 version: 01
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
                              {1,4,6},
                              {2,5,8},
                              {0,4,8},
                              {2,4,6}
                            };

byte pins_buttons[9] = {5,6,7,8,9,10,11,12,13}; // Lista de pinos digitais para os botões

bool debug    = true; // variável para mostrar todos os logs no serial monitor
bool gameover = false; 
bool symbols  = 1;    // 1 para [X] & 0 para [O]

#define calibrate_button 100 // delay para calibrar a leitura dos botões


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
  };

  winningSequencesIndex = checkWinningSequences(symbols); // verificar a sequência vencedora 

  if(winningSequencesIndex == -1){
    checkTie(); // verificar se deu um empate
  }
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

  // ativar os botões como entrada
  for(int i=0; i<9; i++){
    pinMode(pins_buttons[i], INPUT_PULLUP);
  };

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
      
      if(debug){
        // mostrar o tabuleiro na Serial
        Serial.println("Board:");
        showBoard();
      }
  };

  // resetar o jogo
  if(gameover){
    delay(2000);
    reset();

    if(debug){
      // mostrar o tabuleiro na Serial
      Serial.println("Gamer Over");
      showBoard();
    }
  };
  
  delay(calibrate_button);
}