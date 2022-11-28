# tic-tac-toe-arduino

**tic-tac-toe-arduino** é um jogo da velha que usa um `arduino mega` e relés para controlar as fitas de leds que são representadas como **[X]** ou **[O]**.

# SETUP

no arquivo `tic-tac-toe-arduino.ino` você pode definir algumas variáveis ​​para configurar seu ambiente.

**Portas digitais para os botões**

```arduino
    byte pins_buttons[9] = {5,6,7,8,9,10,11,12,13};
```

**Portas digitais para os relés do [X]**
```arduino
    byte pins_relay_x[9] = {14,15,16,17,18,19,20,21,22}; // pinos digitais para o relé da fita de led [X]
```

**Portas digitais para os relés do [O]**
```arduino
    byte pins_relay_o[9] = {23,24,25,26,27,28,29,30,31}; // pinos digitais para o relé da fita de led [O]
```

**Portas digitais para os efeitos de vencendor ou perdedor**
```arduino
    #define effect1 32 // pino de efeito de vencedor ou perdedor 
    #define effect2 33 // pino de efeito de vencedor ou perdedor 
```

**Alterar os símbolos de [X] ou [O]**

```arduino
    bool symbols = 1; // 1 para [X] & 0 para [O]
```

**Variável para ver todos os logs no monitor serial**

```arduino
    bool debug = true; // variável para mostrar todos os logs no serial monitor
```

**Variável para alterar o tempo do reset**
```arduino
    #define time_to_reset 2000  
```

# TODO 
- [x] montagem do algoritmo do jogo da velha.
    - [x] fazer leitura de todos os botões
    - [x] criar o alternador para o **[x]** & **[O]**
    - [x] função para inserir os **[X]** e **[O]** no tabuleiro
    - [X] verificar a sequência vencedora ou se houve um empate
    - [X] função para reinicar o jogo
- [X] criar os efeitos na fita de led.
    - [X] ligar as fitas de led do **[X]** ou **[O]**
    - [X] efeito de `gameover` 
    - [X] desligar leds quando reiniciar o jogo

#
