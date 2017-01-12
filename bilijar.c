#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

#define TIMER 100
#define TIMER_LOPTE 20
#define TIMER_ID 1
#define TIMER_ID_BELA 2
#define TIMER_ID_OSTALE 3

static void onTimer(int id);

static float ugao = 0;

static float pozicija_stapa = -4.5;

static int ugao_kretanja = 0;

static float pozicija_bela_z = -1.5;
static float pozicija_crvena_z = 3.6;
static float pozicija_plava_z = 4.0;
static float pozicija_zelena_z = 3.8;
static float pozicija_zuta_z = 3.8;

static float pozicija_bela_x = 0;
static float pozicija_crvena_x = 0;
static float pozicija_plava_x = 0;
static float pozicija_zelena_x = -0.4;
static float pozicija_zuta_x = 0.4;


static void onTimerOstale(int id){
    if (id != TIMER_ID_OSTALE) {
        return;
    }
    
    
    if(pozicija_zelena_z < 7 && pozicija_zelena_x > -3){
      pozicija_zelena_z+=0.1;
      pozicija_zelena_x-=0.1;
    }
    
    if(pozicija_crvena_z < 7 && pozicija_zelena_x < 3){
      pozicija_crvena_z+=0.1;
      pozicija_crvena_x+=0.05;
    }

    if(pozicija_plava_z < 7 && pozicija_plava_x > -3){
      pozicija_plava_z+=0.1;
      pozicija_plava_x-=0.05;
    }

    if(pozicija_zuta_z < 7 && pozicija_zuta_x < 3){
      pozicija_zuta_z+=0.1;
      pozicija_zuta_x+=0.1;
    }
    
    glutPostRedisplay();
    glutTimerFunc(TIMER_LOPTE, onTimer, TIMER_ID);
}

static void onTimerBela(int id)
{
    if (id != TIMER_ID_BELA) {
        return;
    }
    pozicija_bela_z+=0.1;
    if(pozicija_bela_z < 3.3){
    pozicija_bela_z+=0.1;
    glutPostRedisplay();
    glutTimerFunc(TIMER_LOPTE, onTimer, TIMER_ID);
    }
}

static void onTimer(int id)
{
    if (id != TIMER_ID) {
        return;
    }
    ugao_kretanja+=1;
    if(pozicija_stapa < -4.4){
    pozicija_stapa -= sin(ugao_kretanja);
    glutPostRedisplay();
    glutTimerFunc(TIMER, onTimer, TIMER_ID);
    }
    if(pozicija_stapa > -4.4 && pozicija_bela_z < 5){
      glutTimerFunc(TIMER_LOPTE,onTimerBela,TIMER_ID_BELA);
    }
    if(pozicija_bela_z > 3.25){
      glutTimerFunc(TIMER_LOPTE,onTimerOstale,TIMER_ID_OSTALE);
    }
}


int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
    case 'G':
        glutTimerFunc(TIMER,onTimer,TIMER_ID);
        break;
    }
}

static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 20);
}

static void on_display(void)
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 0, 5, 0, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.8, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 8, -5, 0, 0, 0, 0, 1, 0);

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    /* Kreira se objekat. */
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    
    /*crtanje stola*/
    glPushMatrix();
    glTranslatef(0.0,0.0,-1.5);
    glBegin(GL_POLYGON); 
    glColor3d(0.0,1.0,0.4);
    glVertex3f(-3.5, -0.5,  10.0);
    glVertex3f(3.5, -0.5,  10.0);
    glVertex3f(3.5, -0.5, -1.0); 
    glVertex3f(-3.5, -0.5, -1.0);
    glEnd();
    glFlush();
    glPopMatrix();

    /*crtanje stapa*/
    glPushMatrix();
    glTranslatef(0.0,0.1,pozicija_stapa);
    
    glColor3f(0.5,0.3,0.0);
    GLUquadric* qobj = gluNewQuadric();
    
    gluCylinder(qobj,0.1,0.01,3,10,10);
    
    glFlush();
    glPopMatrix();
    
    /*crtanje bele*/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(pozicija_bela_x,0.0,pozicija_bela_z);
    glutSolidSphere(0.2, 50, 50);  
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_crvena_x,0.0,pozicija_crvena_z);
    glColor3f(1, 0, 0);
    glutSolidSphere(0.2, 40, 40);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_plava_x,0.0,pozicija_plava_z);
    glColor3f(0, 0, 1);
    glutSolidSphere(0.2, 40, 40);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_zelena_x,0.0,pozicija_zelena_z);
    glColor3f(0, 1, 0);
    glutSolidSphere(0.2, 40, 40);
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(pozicija_zuta_x,0.0,pozicija_zuta_z);
    glColor3f(1, 1, 0);
    glutSolidSphere(0.2, 40, 40);
    glFlush();
    glPopMatrix();
    
    
    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
