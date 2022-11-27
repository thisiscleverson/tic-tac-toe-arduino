# tic-tac-toe-arduino

**tic-tac-toe-arduino** é um jogo da velha que usa um `arduino mega` e relés para controlar as fitas de leds que são representadas como **[X]** ou **[O]**.

# SETUP

no arquivo `tic-tac-toe-arduino.ino` você pode definir algumas variáveis ​​para configurar seu ambiente.

**Portas digitais para os botões**

```arduino
    byte pins_buttons[9] = {5,6,7,8,9,10,11,12,13};
```

**Alterar os símbolos de [X] ou [O]**

```arduino
    bool symbols = 1; // 1 para [X] & 0 para [O]
```

**Variável para ver todos os logs no monitor serial**

```arduino
    bool debug = true; // variável para mostrar todos os logs no serial monitor
```

# TODO 
- [x] montagem do algoritmo do jogo da velha.
    - [x] fazer leitura de todos os botões
    - [x] criar o alternador para o **[x]** & **[O]**
    - [x] função para inserir os **[X]** e **[O]** no tabuleiro
    - [X] verificar a sequência vencedora ou se houve um empate
    - [X] função para reinicar o jogo
- [ ] criar os efeitos na fita de led.
    - [ ] ligar as fitas de led do **[X]** ou **[O]**
    - [ ] efeito de `gameover` 
    - [ ] desligar leds quando reiniciar o jogo

#

>❗ no momentos o tabuleiro só pode ser visto no monitor serial, com a variável `debug` ativada.