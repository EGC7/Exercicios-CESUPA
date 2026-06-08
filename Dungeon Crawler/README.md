<img src="./Assets/Groomspire-poster.png" algin="center" width="100%">

<h1 align="center">Groomspire</h1>

<!-- <img src="https://user-images.githubusercontent.com/74038190/225813708-98b745f2-7d22-48cf-9150-083f1b00d6c9.gif" width="500"> -->


O GroomSpire é um projeto que tem como objetivo integrar os conceitos de programação estudados em Linguagem C.
O Projeto utiliza o Console como único meio de interação com o usuário, mostrando tudo com tabela ASCCI.
No fim, tudo se resume a uma aplicação prática, criativa e funcional. Incentivando a criatividade.

## História

A vila no Reino de ELDORIA precisa da sua ajuda para enfrentar o Cavaleiro Maligno e seu Exército de Trolls e Esqueletos que está atormentando a vida dos moradores.  

## Objetivo

- Explorar a vila.
- Escolher uma arma.
- Sobreviver aos três andares da masmorra.
- Derrotar o boss final.

## Como Jogar

### Controles

| Tecla | Ação |
|---------|---------|
| W | Mover para cima |
| A | Mover para esquerda |
| S | Mover para baixo |
| D | Mover para direita |
| E | Interagir |
| I | Abrir Inventário |
| O | Atacar |

### Sistema de Vidas

O jogador possui 3 vidas. Ao tocar em espinhos ou monstros, perde uma vida e retorna ao início da fase.

## Armas

### ⚔️ Espada
Ataque em Área na frente do Jogador. 6 Células (2x3); </br>

### VERTICAL
<img src="./Assets/player-SwordAttack.png" width="300px">

### HORIZONTAL
<img src="./Assets/player-SwordAttack2.png" width="300px">

### 🏹 Arco e Flecha
Ataque Reto na frente do Jogador. 4 Células (1x4); </br>

### VERTICAL
<img src="./Assets/player-ArrowAttack.png" width="300px">

### HORIZONTAL
<img src="./Assets/player-ArrowAttack2.png" width="300px">

### 🪄 Cajado
Ataque em Área em volta do Jogador. 8 Células; </br>

### VERTICAL
<img src="./Assets/player-MagicAttack.png" width="300px">

### HORIZONTAL
<img src="./Assets/player-MagicAttack2.png" width="300px">

## Símbolos do Jogo

| Símbolo | Significado |
|----------|-------------|
| ^ < > v &| Jogador |
| ■ | Parede |
| # | Espinho |
| k | Caixa |
| O | Botão |
| o | Botão Pressionado |
| D | Porta Fechada |
| = | Porta Aberta |
| @ | Chave |
| L | Escada |
| ☻ | NPC (Edward) |
| ⍙ | Poção de Vida |
| ⚇ | Monstro Tipo 1 |
| ⍾ | Monstro Tipo 2 |
| ⌹ | Boss Final |

## Estrutura das Fases

### Vila
Local onde o Jogador inicia sua jornada. Ele encontra um NPC que será seu guia e o ajudará a entender os perigos desse mundo.
Também é um local que ele sente que deve proteger, por isso ele segue subindo os andares da Torre.

### Andar 1
Descrição dos desafios.

### Andar 2
Descrição dos desafios.

### Andar 3
Descrição dos desafios e do boss.

## Tecnologias Utilizadas

- Linguagem C
- Console ASCII
- Git
- GitHub
  
## Como Executar

```bash
gcc main.c -o GroomSpire
./GroomSpire
```

## Capturas de Tela

### MENU

<img src="./Assets/gameMenu.png" width="500px">

### TUTORIAL

<img src="./Assets/gameTutorial.png" width="300px">

### FINISH TUTORIAL

<img src="./Assets/gameFinTutorial.png" width="500px">

### TELA DE GAMEOVER

<img src="./Assets/gameOver.png" width="500px">

(Imagens do menu, vila e masmorra)


## Status

O projeto está atualmente em versão:

```txt
Beta 1.7
```

Esta versão apresenta um mapa genérico de Tutorial com algumas interações limitadas, movimentação do Player, funcionalidade das Armas e Monstro tipo 1, com o objetivo de ajudar no aprendizado das funções basicas de Jogo. Além de uma mapa genérico de Vila, com a presença de um Personagem Não Jogável (NPC), que ajudará o jogador em sua jornada pelo mundo de ELDORIA.  

---

⚙️ Requisitos

- Compilador C (ex: GCC, MinGW)
- Sistema Operacional: Windows (utiliza `<windows.h>` para `Sleep()` e `system("cls")`)

⚠️ O código **não é compatível com Linux/macOS** por depender de `windows.h`.

## Roadmap

### Versão 1.0

* [x] Movimentação do Player
* [x] Atualização de Mapa em Tempo Real
* [x] Tutorial com Funcionalidades Básicas 
* [x] Inventário do Player funcional 
* [x] Menu Inicial com Todas as Opções Funcionando
* [x] Ataque Individual de Cada Arma
* [x] Diálogos de Tutorial
* [x] Inimigos nivel 1 
* [x] Vida do Player
* [x] Tela de Game Over
* [x] Vila com NPC(s) e Casas
* [x] Espinhos de Masmorra
* [x] Regeneração de Vida do Player
* [x] Masmorra Nível 1
* [x] Masmorra Nível 2
* [ ] Masmorra Nível 3
* [ ] Inimigos nivel 2 (Nivel de Perseguição médio)
* [ ] Algoritmo de Perseguição do Boss Final

### Versão 2.0

* [ ] Itens Deixados por Inimigos
* [ ] Trilhas Sonoras entre Mapas
* [ ] Equipamentos
  * [ ] Armaduras
  * [x] Poções 
* [ ] Habilidades de Dash e Corrida
* [ ] Ataques Especiais com Armas
* [ ] Pets (Player se sente Sozinho)
---

## Objetivo

O **GroomSpire** é mais do que uma atividade de Universidade.

Ele foi criado para ajudar estudantes a treinarem racicínio lógico, resolver problemas, lidar com desafios e desenvolver autonomia.

## Autor

Desenvolvido por **Eduardo Cajueiro**. <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Face%20with%20Spiral%20Eyes.png" alt="Face with Spiral Eyes" width="25" height="25" />

Projeto criado com o objetivo de praticar e fixar conteúdos de programação em C. Além de construir um algoritmo divertido para compartilhar com amigos.

---

<div align="center">
  <p>
    <strong>GroomSpire</strong>
  </p>

  <p>

  </p>
</div>

## Licença

Projeto acadêmico desenvolvido para a disciplina de Programação.
