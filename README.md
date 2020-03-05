
# Sonic-OpenGl-e-GLUT
Trabalho de faculdade consistindo em um jogo do sonic utilizando GLUT com sistema de colisão manual e animações nos aneis.

## Sistema de colisão
O sistema de colisão foi feito utilizando **matrizes**, por padrão preenchido com 0. 
Cada valor da matriz que possui o valor 1 corresponde a um lugar onde existe colisão.
Por exemplo, o trecho de código abaixo serve para definir as áreas que possuem colisão:

```c++
int linha;
    int cenario[100][100];
    for (linha = -10; linha <= 4; linha++)
        cenario[-8][linha] = 1;

    for (linha = 4; linha <= 9; linha++)
        cenario[-9][linha] = 1;

    for (linha = 9; linha <= 24; linha++)
        cenario[-10][linha] = 1;

    for (linha = 25; linha <= 29; linha++)
        cenario[-9][linha] = 1;

    for (linha = 30; linha <= 60; linha++)
        cenario[-8][linha] = 1;
```

>Nesse caso, por ser um programa orientado a Eventos, ele executa uma função dependendo da tecla pressionada, que aqui é responsável pela movimentação.

A cada tecla apertada checa se a próxima posição (Por exemplo, caso se mova para a esquerda, checa a posição -1 no eixo x) e verifica se o valor é diferente de 1. **ou seja, não existe colisão**.

Caso verdadeiro, ele permite alterar a posição do personagem. Caso contrário, o personagem não consegue se movimentar por ser um objeto sólido. 
Isso pode ser visto no trecho de código responsável por capturar as teclas:
```c
switch (key)
    {
    case 'r':
        eg = !eg;
        break;
    case 'a':
        if (cenario[posy][posx - 1] != 1)
        {
            dx -= 1;
            posx -= 1;
        }
        break;
    case 'd':
        if (cenario[posy][posx + 1] != 1)
        {
            dx += 1;
            posx += 1;
        }
        break;
    case 's':
        if (cenario[posy - 1][posx] != 1)
        {
            dy -= 1;
            posy -= 1;
        }
        break;
    case 'w':
        if (cenario[posy + 1][posx] != 1)
        {
            dy += 1;
            posy += 1;
        }
        break;   
    }
```

**Imagem do jogo**:
![Imagem do jogo](https://github.com/RobertoHigor/Sonic-OpenGl-e-GLUT/blob/master/exemploSonic.png)

