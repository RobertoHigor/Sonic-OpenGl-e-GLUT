#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

bool eg = true;

float dx = 0.0, dy = 0.0;
// posicao do personagem
int posx = -7, posy = -7;

float ex = 1.0, ey = 1.0;
float ang = 0.0;
float rotacao = 0;
float ypiranha = -6.0;
int timerLigado = 0;

// Prototipos
void circulo(float raio, float cx, float cy, int tipo);
void palmeira(int altura, int posx);
void eixoGlobal();
void eixoLocal();
void quadChao(int altura, int larguraInicio, int larguraFinal);
void quadCeu(int altura, int alturaFinal, int larguraInicio, int larguraFinal);
void quadAgua(int altura, int alturaFinal, int larguraInicio, int larguraFinal);
void quadTerra(int alturaInicio, int larguraInicio, int larguraFinal);
void quadPonte(int altura, int larguraInicio, int larguraFinal);
void montanha(double altura, double larguraInicio, double larguraFinal);
void cachoeira(int altura, int larguraInicio, int larguraFinal);
void personagem(int posx, int posy);
void piranha(int x);
void projecao();
static void resize(int width, int height);
void timer(int);
void timerPiranha(int subindo);
static void display(void);
static void key(unsigned char key, int x, int y);

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Sanic");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    // Funcoes timer
    glutTimerFunc(300, timer, 1);
    glutTimerFunc(300, timerPiranha, 1);
    
    glutMainLoop();

    return EXIT_SUCCESS;
}

// callbacks ----------------------------------------------------------------------
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //if(eg){ eixoGlobal(); eixoLocal(); }

    // Ceu e agua
    quadCeu(-5, 20, -50, 100);
    quadAgua(-10, -5, -50, 100);

    // Montanhas
    montanha(0.5, -10, -5);
    montanha(0.5, -7, -1);
    montanha(1, -1, 6);
    montanha(0.4, 7, 15);
    montanha(0.6, 25, 30);

    // Cenario
    palmeira(-8, -6);
    palmeira(-8, -2);

    palmeira(-8, 26);
    palmeira(-7, 33);
    palmeira(-7, 37);

    // Ch?o
    quadChao(-8, -50, 5);
    quadChao(-9, 5, 10);
    quadChao(-10, 10, 25);

    quadChao(-9, 25, 30);
    quadChao(-8, 30, 40);

    quadChao(-8, 47, 60);

    // Terra
    quadTerra(-10, -50, 55);
    quadTerra(-9, -50, 55);

    quadTerra(-10, 5, 5);

    quadTerra(-9, 17, 7); // Embaixo da plataforma
    quadTerra(-8, 17, 7);
    quadTerra(-7, 17, 7);
    quadTerra(-6, 17, 7);
    quadTerra(-5, 17, 7);

    quadTerra(-10, 25, 15); // Antes da ponte
    quadTerra(-9, 30, 10);

    // Aneis
    glPushMatrix();
    glTranslatef(-4, -6, 0);
    glRotatef(rotacao, 0, 1, 0);
    circulo(0.5, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, -6, 0);
    glRotatef(rotacao, 0, 1, 0);
    circulo(0.5, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -6, 0);
    glRotatef(rotacao, 0, 1, 0);
    circulo(0.5, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, -6, 0);
    glRotatef(rotacao, 0, 1, 0);
    circulo(0.5, 0, 0, 0);
    glPopMatrix();

    // Aneis em cima da plataforma
    glPushMatrix();
    glTranslatef(20, -2, 0);
    glRotatef(rotacao, 0, 1, 0);
    circulo(0.5, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(18, -2, 0);
    glRotatef(rotacao, 0, 1, 0);
    circulo(0.5, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22, -2, 0);
    glRotatef(rotacao, 0, 1, 0);
    circulo(0.5, 0, 0, 0);
    glPopMatrix();

    // Cachoeira
    cachoeira(-7, 40, 47);

    // Piranhas
    glPushMatrix();
    glTranslatef(0, ypiranha, 0);
    piranha(40);
    piranha(42);
    piranha(44);
    piranha(46);
    glPopMatrix();

    // Ponte
    quadPonte(-8, 40, 41);
    quadPonte(-8, 41, 42);
    quadPonte(-8, 42, 43);
    quadPonte(-8, 43, 44);
    quadPonte(-8, 44, 45);
    quadPonte(-8, 45, 46);
    quadPonte(-8, 46, 47);

    // Plataformas
    quadChao(-4, 17, 24);

    // Sol
    circulo(2, 15 - dx / 1.5, 8 - dx / 2.5, 1);
    circulo(2.1, 15 - dx / 2, 8 - dx / 3, 0);

    glPushMatrix();
    glTranslatef(dx, dy, 0);
    personagem(-7, -7);
    glPopMatrix();

    glutSwapBuffers();
}

// callback de tecla
static void key(unsigned char key, int x, int y)
{
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
    projecao();
    glutPostRedisplay();
}

void circulo(float raio, float cx, float cy, int tipo)
{
    float ang, x, y;

    glColor3f(0, 1, 0);
    if (tipo == 1)
    {

        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++)
        {
            ang = (i * M_PI) / 180.0;
            x = cx + (cos(ang) * raio);
            y = cy + (sin(ang) * raio);
            glVertex2f(x, y);
        }
        glEnd();
    }
    else
    {
        glColor3f(0, 1, 0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i++)
        {
            ang = (i * M_PI) / 180.0;
            x = cx + (cos(ang) * raio);
            y = cy + (sin(ang) * raio);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

void palmeira(int altura, int posx)
{
    // Tronco
    glBegin(GL_QUADS);
    glColor3f(183.0 / 255, 78.0 / 255, 39.0 / 255);
    glVertex2f(posx, altura + 5);
    glVertex2f(posx + 0.5, altura + 5);
    glVertex2f(posx + 0.5, altura);
    glVertex2f(posx, altura);
    glEnd();

    // Folhas
    glBegin(GL_POLYGON);
    glColor3f(0, 0.7, 0);
    glVertex2f(posx - 1.7, altura + 4.2);
    glVertex2f(posx - 1.7, altura + 4.4);

    glVertex2f(posx - 1.5, altura + 4.7);
    glVertex2f(posx - 0.9, altura + 5.1);
    glVertex2f(posx, altura + 5);
    glVertex2f(posx, altura + 4.9);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.7, 0);
    glVertex2f(posx + 0.5, altura + 4.85);
    glVertex2f(posx + 0.5, altura + 5);

    glVertex2f(posx + 1.2, altura + 5.1);
    glVertex2f(posx + 1.6, altura + 4.9);
    glVertex2f(posx + 2, altura + 4.5);
    glEnd();

    // Coco
    glColor3f(1, 0, 0);
    circulo(0.12, posx - 0.1, altura + 4.85, 1);
    circulo(0.12, posx + 0.6, altura + 4.85, 1);
}

// callbacks de eixo
void eixoGlobal()
{
    glLineWidth(1.5);

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(-10, 0);
    glVertex2f(10, 0);

    glColor3f(0, 1, 0);
    glVertex2f(0, -10);
    glVertex2f(0, 10);
    glEnd();
}

void eixoLocal()
{
    glLineWidth(1.5);

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(-2, 0);
    glVertex2f(2, 0);

    glColor3f(0, 1, 0);
    glVertex2f(0, -2);
    glVertex2f(0, 2);
    glEnd();
}

void quadChao(int altura, int larguraInicio, int larguraFinal)
{
    // Plataforma de chao com altura fixa
    glBegin(GL_QUADS);
    glColor3f(51.0 / 255, 1, 51.0 / 255);
    glVertex2f(larguraInicio, altura + 1);
    glVertex2f(larguraInicio, altura);
    glVertex2f(larguraFinal, altura);
    glVertex2f(larguraFinal, altura + 1);
    glEnd();
}

void quadCeu(int altura, int alturaFinal, int larguraInicio, int larguraFinal)
{
    glBegin(GL_QUADS);
    glColor3f(82.0 / 255, 126.0 / 255, 243.0 / 255);
    glVertex2f(larguraInicio, alturaFinal);
    glVertex2f(larguraInicio, altura);
    glVertex2f(larguraFinal, altura);
    glVertex2f(larguraFinal, alturaFinal);
    glEnd();
}

void quadAgua(int altura, int alturaFinal, int larguraInicio, int larguraFinal)
{
    glBegin(GL_QUADS);
    glColor3f(107.0 / 255, 202.0 / 255, 222.0 / 255);
    glVertex2f(larguraInicio, alturaFinal);
    glVertex2f(larguraInicio, altura);
    glVertex2f(larguraFinal, altura);
    glVertex2f(larguraFinal, alturaFinal);
    glEnd();
}

void quadTerra(int alturaInicio, int larguraInicio, int larguraFinal)
{
    int i = 0;
    glBegin(GL_QUADS);

    // For para variar a cor da terra
    for (int i = 0; i < larguraFinal; i++)
    {

        glColor3f(195.0 / 255, 98.0 / 255, 0);
        glVertex2f(larguraInicio + i, alturaInicio + 1);
        glVertex2f(larguraInicio + i, alturaInicio);
        glVertex2f(larguraInicio + i + 1, alturaInicio);
        glVertex2f(larguraInicio + i + 1, alturaInicio + 1);

        if (++i < larguraFinal)
        {

            glColor3f(114.0 / 255, 61.0 / 255, 8.0 / 255);
            glVertex2f(larguraInicio + i, alturaInicio + 1);
            glVertex2f(larguraInicio + i, alturaInicio);
            glVertex2f(larguraInicio + i + 1, alturaInicio);
            glVertex2f(larguraInicio + i + 1, alturaInicio + 1);
        }
    }
    glEnd();
}

void quadPonte(int altura, int larguraInicio, int larguraFinal)
{
    // Quadrado de somente linha para desenhar a ponte
    glBegin(GL_LINE_LOOP);
    glColor3f(221.0 / 255, 121.0 / 255, 40.0 / 255);
    glVertex2f(larguraInicio, altura + 1);
    glVertex2f(larguraInicio, altura);
    glVertex2f(larguraFinal, altura);
    glVertex2f(larguraFinal, altura + 1);
    glEnd();
}

void montanha(double altura, double larguraInicio, double larguraFinal)
{
    // Triangulo da montanha
    glBegin(GL_TRIANGLES);
    glColor3f(121.0 / 255, 79.0 / 255, 72.0 / 255);
    glVertex2f(larguraInicio, -5);
    glVertex2f(larguraFinal, -5);
    glVertex2f((larguraFinal + larguraInicio) / 2, altura);
    glEnd();
}

void cachoeira(int altura, int larguraInicio, int larguraFinal)
{
    // Agua da cachoeira
    glBegin(GL_QUADS);
    glColor3f(170.0 / 255, 224.0 / 255, 236.0 / 255);
    glVertex2f(larguraInicio, altura);
    glVertex2f(larguraInicio, -10);
    glVertex2f(larguraFinal, -10);
    glVertex2f(larguraFinal, altura);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);

    // Triangulos da agua para tentar fazer um efeito de espuma
    // For para a quantidade de quadrados verticais
    for (int j = altura; j > -10; j--)
    {
        // For para a largura de quadrados
        for (double i = 0; i < larguraFinal - larguraInicio; i++)
        {
            glColor3f(211.0 / 255, 239.0 / 255, 245.0 / 255);
            glVertex2f(larguraInicio + i, j);     //0 //
            glVertex2f(larguraInicio + i + 1, j); //1
            glVertex2f(larguraInicio + i + ((i + (i == 0) ? 1.0 : 0) / 2), j - 1);
        }
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void personagem(int posx, int posy)
{
    // Retangulo do personagem
    glColor3f(51.0 / 255, 51.0 / 255, 1);
    glBegin(GL_QUADS);
    glVertex2f(posx, posy + 2);
    glVertex2f(posx, posy);
    glVertex2f(posx + 1, posy);
    glVertex2f(posx + 1, posy + 2);
    glEnd();

    // Espinhos do sonic
    glBegin(GL_TRIANGLES);
    glVertex2f(posx, posy + 2);
    glVertex2f(posx - 0.5, (posy + posy + 3.5) / 2);
    glVertex2f(posx, posy + 1.5);

    glVertex2f(posx, posy + 1.5);
    glVertex2f(posx - 0.5, (posy + posy + 2.5) / 2);
    glVertex2f(posx, posy + 1);

    glEnd();
}

void piranha(int x)
{
    glBegin(GL_QUADS);
    glColor3f(209.0 / 255, 16.0 / 255, 26.0 / 255);
    glVertex2f(x, 2 + ypiranha);
    glVertex2f(x, ypiranha);
    glVertex2f(x + 1, ypiranha);
    glVertex2f(x + 1, 2 + ypiranha);
    glEnd();
}

void projecao()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10 + dx, 10 + dx, -10 + dy, 10 + dy, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    projecao();
}

// callbacks de timer
void timer(int)
{
    rotacao += 30;

    if (rotacao >= 5000)
    {
        rotacao = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(500, timer, 1);
}

void timerPiranha(int subindo)
{
    if (subindo == 1)
    {
        ypiranha++;
        if (ypiranha == -2)
        {
            subindo = 0;
        }
    }
    else
    {
        ypiranha--;
        if (ypiranha == -6)
        {
            subindo = 1;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(300, timerPiranha, subindo);
}

