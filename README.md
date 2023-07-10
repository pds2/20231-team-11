# Invaders

<!---Esses são exemplos. Veja https://shields.io para outras pessoas ou para personalizar este conjunto de escudos. Você pode querer incluir dependências, status do projeto e informações de licença aqui--->

![GitHub repo size](https://img.shields.io/github/repo-size/iuricode/README-template?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/iuricode/README-template?style=for-the-badge)
![Bitbucket open issues](https://img.shields.io/bitbucket/issues/iuricode/README-template?style=for-the-badge)
![Bitbucket open pull requests](https://img.shields.io/bitbucket/pr-raw/iuricode/README-template?style=for-the-badge)

<img src="images/auxiliar/game01.png" alt="Kamikazes se aproximando da nave do jogador">

> Desenvolvimento de um jogo baseado no Invaders Clássico, utilizando-se a biblioteca gráfica Raylib.

## 🎮 Introdução

Este projeto foi desenvolvido para a disciplina de Programação e Desenvolvimento de Software II, apresentando a implementação de um jogo inspirado no clássico Space Invaders. Assim, com o objetivo de aplicar e consolidar os conceitos e técnicas aprendidos durante o semestre letivo, o trabalho abrange uma ampla gama de tópicos fundamentais no desenvolvimento de software.

A principal ênfase aqui encontrada está na utilização de conceitos como Tipos Abstratos de Dados, Prática de Containers, Modularização, Programação Orientada à Objetos, Modelagem, Polimorfismo, Herança e Testes de Unidade. Esses conceitos serão explorados de forma integrada, permitindo uma compreensão mais profunda de como aplicar cada um deles no desenvolvimento de um software completo.

## 🧩 Ajustes e melhorias

Durante o desenvolvimento do projeto, foram realizadas atualizações específicas nas seguintes tarefas:

- [x] Testes de unidade
- [x] Implementação do objeto bullet
- [x] Funções de colisão e destruição de objetos
- [x] Refatorar as classes de comportamento
- [x] Implementar classe Fleet para refatorar Game::_build_objects()

## 💻 Pré-requisitos

Antes de começar, verifique se você atendeu aos seguintes requisitos:
* Compilador `g++`, para Windowns é recomendado o `mingw32`
* O jogo é compatível com versões recentes de `<Windows / Linux / MacOS>`


## 🚀 Instalando e rodando o Invaders

Para instalar o Invaders, siga estas etapas:

Clonagem do Repositório:
```
    git clone https://github.com/pds2/20231-team-11.git
```

Linux e macOS:
```
    make
```

Windows:
```
    mingw32-make
```
## 🎯 Testes

Para gerar o executável de teste, utilize o seguinte comando:
```
    g++ -std=c++11 ./logic/src/*.cpp ./logic/program/*.cpp -Iinclude -Ithirdy_party -o teste
```

## 📖 User Stories

### Game

Como jogador, quero um Game baseado em Galaxian que crie todos os objetos do jogo, incluindo uma nave controlada pelo jogador e inimigos para interagir.

### Alien

Como jogador, quero que um Alien que se movimente, com uma pontuação diferente para cada tipo de alien, proporcionando interações únicas com base em seu comportamento e textura.

### Ship

Como jogador, quero um Ship que eu posso controlar, permitindo-me navegar e interagir com o jogo.

### Boss

Como jogador, quero um alien especial chamado Boss que tenha uma barra de vida e não possa ser morto com um único tiro, proporcionando uma experiência de jogo mais desafiadora e estratégica. Ele deve ter seu próprio comportamento e textura distintiva.

### MotionObject

Como jogador, quero um MotionObject que esteja relacionado a todos os objetos em movimento do jogo, permitindo-me definir sua velocidade, aceleração e posição com precisão.

### Behaviour

Como jogador, quero um Behaviour que possa modificar a velocidade, aceleração e/ou posição de um objeto, permitindo comportamentos e movimentos personalizados para os MotionObjects.

### Bullet

Como jogador, quero que uma Bullet seja um MotionObject que se relacione com outros objetos em movimento, com o objetivo de causar dano ou destruí-los.

### Fleet

Como jogador, quero uma Fleet que seja um vetor de aliens, permitindo definir a quantidade de aliens que aparecem na tela para interação durante o jogo.

### Texture

Como jogador, quero que uma Texture defina as imagens de todos os objetos do jogo, facilitando a identificação visual dos elementos do jogo.



## 🤝 Colaboradores

<table>
  <tr>
    <td align="center">
      <a href="#">
        <sub>
          <b><a href="https://github.com/joao-jcc">João Costa</a></b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <sub>
          <b><a href="https://github.com/luccaamp">Lucca Alvarenga</a></b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <sub>
          <b><a href="https://github.com/lucaspedras8">Lucas Pedras</a></b>
        </sub>
      </a>
    </td>
     <td align="center">
      <a href="#">
        <sub>
          <b><a href="https://github.com/LrcSantos">Lucas Santos</a></b>
        </sub>
      </a>
    </td>
     <td align="center">
      <a href="#">
        <sub>
          <b><a href="https://github.com/Fissicaro">Arthur Fissicaro</a></b>
        </sub>
      </a>
    </td>
  </tr>
</table>

