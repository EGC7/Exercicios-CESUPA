# <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Bomb.png" alt="Bomb" width="25" height="25" /> Gamer System <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Bomb.png" alt="Bomb" width="25" height="25" />
<!-- <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Alien%20Monster.png" alt="Alien Monster" width="25" height="25" /> -->

Sistema de jogos em console desenvolvido em **linguagem C**, com três minigames jogáveis diretamente pelo terminal.

## <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Dizzy.png" alt="Dizzy" width="25" height="25" /> Descrição

O Gamer System é um menu interativo de jogos para terminal que oferece três experiências distintas: um quiz de perguntas e respostas, um jogo de sorte com caixas misteriosas e um jogo de estratégia com criaturas chamadas Gousmas.

## <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Robot.png" alt="Robot" width="25" height="25" /> Jogos Disponíveis

### 1. Perguntas e Respostas
Quiz com **5 perguntas de múltipla escolha** (4 alternativas cada) sobre temas gerais como astronomia, ciências e geografia. Ao final, o jogador recebe sua pontuação.

Perguntas incluídas:
- Qual o planeta mais próximo do Sol?
- A que temperatura a água ferve?
- Qual o maior planeta do sistema solar?
- Quantas pedras preciosas têm 11 anéis com 3 pedras cada?
- Quantos continentes existem?

### 2. Cobra na Caixa!
Jogo de sorte para **2 jogadores** ambientado em uma tumba egípcia. Há 5 caixas: uma contém o botão para escapar e outra esconde uma cobra mortal. Os jogadores se revezam escolhendo caixas até que alguém encontre o botão (vitória) ou a cobra (derrota). A posição da cobra e do botão muda aleatoriamente a cada rodada.
<!-- <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Thinking%20Face.png" alt="Thinking Face" align="right" width="10%" /> -->
<img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Alien%20Monster.png" alt="Alien Monster" align="right" width="10%" />

Funcionalidades:
- Seleção de personagens a partir de uma lista de 7 nomes
- Turnos alternados entre os dois jogadores
- Caixas já abertas ficam marcadas com `[X]`

### 3. Gousmas War
Jogo de estratégia para 2 jogadores, onde cada um controla 2 criaturas chamadas Gousmas, cada uma com um nível de Fúria (1 a 5). A cada turno, o jogador escolhe um Gousma para atacar um inimigo (somando sua Fúria) ou dividir sua Fúria com o aliado. Um Gousma é desintegrado se sua Fúria sair do intervalo de 1 a 5. Vence quem desintegrar todos os Gousmas do adversário.

Mecânicas:
- Ataque: transfere a Fúria do Gousma escolhido para um inimigo
- Divisão: reparte a Fúria igualmente entre os dois aliados (Gousma morto pode ser revivido)
- Gousma com Fúria = 0 ou > 5 é desintegrado

## <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Face%20with%20Spiral%20Eyes.png" alt="Face with Spiral Eyes" width="25" height="25" /> Estrutura do Código

main.c
├── main()              — Inicialização, srand e loop principal do menu
├── showMenu()          — Exibe o menu e captura a escolha do usuário
├── game1()             — Lógica do jogo "Perguntas e Respostas"
├── game2()             — Lógica do jogo "Cobra na Caixa!"
├── game3()             — Lógica do jogo "Gousmas War"
├── again()             — Pergunta se o jogador deseja jogar novamente
├── exitGame()          — Encerra o sistema com animação
├── verificarInt()      — Validação de entrada inteira pelo usuário
└── pontosBonitoskkkj() — Animação de pontos com Sleep

Variáveis globais:
| Variável | Tipo  | Uso |
|----------|-------|-----|
| `resp`   | `int` | Resposta/escolha atual do usuário |
| `gaming` | `int` | Flag de controle do loop principal |
| `points` | `int` | Pontuação no Quiz |
| `pts`    | `int` | Largura das bordas decorativas do menu |

⚙️ Requisitos

- Compilador C (ex: GCC, MinGW)
- Sistema Operacional: Windows (utiliza `<windows.h>` para `Sleep()` e `system("cls")`)

🚀 Como Compilar e Executar

bash
Compilar com GCC (MinGW no Windows)
gcc main.c -o gamer_system.exe

Executar
./gamer_system.exe

⚠️ O código **não é compatível com Linux/macOS** por depender de `windows.h`. Para portar, substitua `Sleep(ms)` por `usleep(ms * 1000)` e `system("cls")` por `system("clear")`, além de remover o `#include <windows.h>, usamos o Cloud IA para fazer uma versão para os demais dispositivos.

📌 Observações

- A entrada do usuário é sempre validada pela função `verificarInt()`, que descarta entradas não inteiras e solicita nova digitação.
- O seed aleatório é inicializado com `srand(time(NULL))`, garantindo resultados diferentes a cada execução nos jogos que usam aleatoriedade.
- Após cada jogo, o jogador pode optar por jogar novamente ou retornar ao menu.
