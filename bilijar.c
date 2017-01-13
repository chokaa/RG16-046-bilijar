#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

#define TIMER 100
#define TIMER_BELE 10
#define TIMER_LOPTE 25
#define TIMER_UDARENA 25
#define TIMER_ID 1
#define TIMER_ID_BELA 2
#define TIMER_ID_OSTALE 3

static void onTimer(int id);
static void onTimerBela(int id);
static void onTimerOstale(int id);

static int intenzitet = 1750;
static int duzina_stola = 11;
static int sirina_stola = 7;



static float pozicija_stapa = -2.5;
static float duzina_stapa = 2.9;
static int ugao_kretanja = 0;

static float vektor_x = 0.001;
static float vektor_z = 0.1;

  static float pozicija_bela_z = 0.5;
  static float pozicija_crvena_z = 7;
  /*
  static float pozicija_plava_z = 4.0;
  static float pozicija_zelena_z = 3.8;
  static float pozicija_zuta_z = 3.8;
  */
  static float pozicija_bela_x = 3.5;
  static float pozicija_crvena_x = 3.5;
  /*
  static float pozicija_plava_x = 0;
  static float pozicija_zelena_x = -0.4;
  static float pozicija_zuta_x = 0.4;
  */
  static int odbijena = 0;
  
  
  static void pomeriBelu(int x,int z){
    /*pozicija_bela_z+=0.1;*/  

    glutTimerFunc(TIMER_BELE, onTimerBela, TIMER_ID_BELA);
    glutPostRedisplay();
  
}

static void onTimerOstale(int id){
    if (id != TIMER_ID_OSTALE) {
        return;
    }
    
    
/*    if(pozicija_zelena_z < 7 && pozicija_zelena_x > -3){
      pozicija_zelena_z+=0.1;
      pozicija_zelena_x-=0.1;
    }
    


    if(pozicija_plava_z < 7 && pozicija_plava_x > -3){
      pozicija_plava_z+=0.1;
      pozicija_plava_x-=0.05;
    }

    if(pozicija_zuta_z < 7 && pozicija_zuta_x < 3){
      pozicija_zuta_z+=0.1;
      pozicija_zuta_x+=0.1;
    }

    if(((pozicija_crvena_z+0.1) == (pozicija_bela_z-0.1)) || ((pozicija_crvena_z-0.1) == (pozicija_bela_z+0.1)) || 
       ((pozicija_crvena_x+0.1) == (pozicija_bela_x-0.1)) || ((pozicija_crvena_x-0.1) == (pozicija_bela_x+0.1))
    ){
    
*/  

    if(intenzitet >0){
      /*
      intenzitet-=0.1;
      if((pozicija_crvena_z+0.2)<=duzina_stola && (vektor_z>0) && ((pozicija_crvena_x+0.2)<=sirina_stola) ){
	pozicija_crvena_z += vektor_z;
	pozicija_crvena_x += vektor_x;
	glutPostRedisplay();
      }
      else{
	odbijena=1;
	pozicija_crvena_z -= vektor_z;
	pozicija_crvena_x += vektor_x;
	glutPostRedisplay();
      }
      */
      
      intenzitet-=0.1;
      
      if((pozicija_crvena_x+0.2) >= sirina_stola)
	vektor_x = vektor_x * (-1);
      if((pozicija_crvena_x-0.2) <= 0)
	vektor_x = vektor_x * (-1);
      if((pozicija_crvena_z+0.2) >= duzina_stola)
	vektor_z = vektor_z * (-1);
      if((pozicija_crvena_z+0.2) <= 0)
	vektor_z = vektor_z * (-1);
      
      pozicija_crvena_z += vektor_z;
      pozicija_crvena_x += vektor_x;
      glutPostRedisplay();
      
      
      /*
      if(pozicija_crvena_z <= (pozicija_bela_z+0.2) && ((pozicija_crvena_z+0.2)<=duzina_stola) && (pozicija_bela_x > sirina_stola || pozicija_bela_x < 0) ){
	vektor_x =  (pozicija_bela_x - pozicija_crvena_x);
	vektor_z = (pozicija_bela_z - pozicija_crvena_z);
	glutTimerFunc(TIMER_LOPTE,onTimerBela,TIMER_ID_BELA);
      }
      
       * pozicija_crvena_x -= vektor_x;
      */
    }
    
      glutTimerFunc(TIMER_LOPTE, onTimerOstale, TIMER_ID_OSTALE);
}

static void onTimerBela(int id)
{
    if (id != TIMER_ID_BELA) {
        return;
    }
    
    if((pozicija_bela_z <= (pozicija_crvena_z-0.2)) && (intenzitet>0)  ){
      intenzitet-=0.1;
      if(!(odbijena)){
      pozicija_bela_x +=vektor_x;
      pozicija_bela_z +=vektor_z;
      }
      else{
	 pozicija_bela_x -=vektor_x;
	 pozicija_bela_z -=vektor_z;
      }
      pomeriBelu(pozicija_bela_x,pozicija_bela_z);
      glutPostRedisplay();
    }
    
    if((pozicija_bela_z >= (pozicija_crvena_z-0.2))){
      vektor_x =  (pozicija_crvena_x - pozicija_bela_x);
      vektor_z = (pozicija_crvena_z - pozicija_bela_z);
      glutTimerFunc(TIMER_LOPTE,onTimerOstale,TIMER_ID_OSTALE);
    }
    
    
    
    
    /*glutTimerFunc(TIMER_LOPTE, onTimerOstale, TIMER_ID);*/
}

static void onTimer(int id)
{
    if (id != TIMER_ID) {
        return;
    }
    if((pozicija_stapa+duzina_stapa) < (pozicija_bela_z)){
    ugao_kretanja+=1;
    pozicija_stapa -= sin(ugao_kretanja);
    glutPostRedisplay();
    glutTimerFunc(TIMER, onTimer, TIMER_ID);
    }
    else{

      glutTimerFunc(TIMER_LOPTE,onTimerBela,TIMER_ID_BELA);
    }
/*
    if((pozicija_stapa+3.0) > (pozicija_bela_z) ){
      glutTimerFunc(TIMER_LOPTE,onTimerBela,TIMER_ID_BELA);
    }

    if(pozicija_bela_z > 6.25){
      glutTimerFunc(TIMER_LOPTE,onTimerOstale,TIMER_ID_OSTALE);
    }
*/

    

}
static int udarena = 1;

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
	if(udarena){
	  glutTimerFunc(TIMER,onTimer,TIMER_ID);
	  udarena=0;
	}
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
    gluLookAt(3, 10, -5, 3, 0, 3, 0, 1, 0);

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
    glVertex3f(0.0, -0.5,  13);
    glVertex3f(7.0, -0.5,  13);
    glVertex3f(7.0, -0.5, 1.5); 
    glVertex3f(0.0, -0.5, 1.5);
    glEnd();
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0,0.0,-1.5);
    glBegin(GL_POLYGON); 
    glColor3d(0.405,0.133,0.063);
    glVertex3f(-1.0, -0.7,  1.6);
    glVertex3f(8.0, -0.7,  1.6);
    glVertex3f(6.5, -0.7, 0.6); 
    glVertex3f(0.5, -0.7, 0.6);
    glEnd();
    glFlush();
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(0.0,0.0,-1.5);
    glBegin(GL_POLYGON); 
    glColor3d(0.405,0.133,0.063);
    glVertex3f(-1.0, -0.7,  1.6);
    glVertex3f(-1.0, -0.7,  16.6);
    glVertex3f(0, -0.7, 16.6); 
    glVertex3f(0, -0.7, 1.6);
    glEnd();
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0,0.0,-1.5);
    glBegin(GL_POLYGON); 
    glColor3d(0.405,0.133,0.063);
    glVertex3f(7.0, -0.7,  1.6);
    glVertex3f(7.0, -0.7,  16.6);
    glVertex3f(8, -0.7, 16.6); 
    glVertex3f(8, -0.7, 1.6);
    glEnd();
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0,0.0,-1.5);
    glBegin(GL_POLYGON); 
    glColor3d(0.405,0.133,0.063);
    glVertex3f(0.0, -0.7,  16.6);
    glVertex3f(7.0, -0.7,  16.6);
    glVertex3f(7, -0.7, 11.6); 
    glVertex3f(0, -0.7, 11.6);
    glEnd();
    glFlush();
    glPopMatrix();
    
    /* Crtanje rupa */
    glPushMatrix();
    glTranslatef(0.0,-0.5,0.0);
    glColor3f(0,0,0);
    glutSolidSphere(0.2,50,50);
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.0,-0.5,0.0);
    glColor3f(0,0,0);
    glutSolidSphere(0.2,50,50);
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0,-0.5,6.0);
    glColor3f(0,0,0);
    glutSolidSphere(0.2,50,50);
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.0,-0.5,6.0);
    glColor3f(0,0,0);
    glutSolidSphere(0.2,50,50);
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0,-0.5,11.5);
    glColor3f(0,0,0);
    glutSolidSphere(0.2,50,50);
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.0,-0.5,11.5);
    glColor3f(0,0,0);
    glutSolidSphere(0.2,50,50);
    glFlush();
    glPopMatrix();

    /*crtanje stapa*/
    glPushMatrix();
    glTranslatef(3.5,0.1,pozicija_stapa);
    glColor3f(0.5,0.25,0.0);
    GLUquadric* qobj = gluNewQuadric();
    gluCylinder(qobj,0.1,0.015,3,10,10);
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

    /*
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
    
    */
    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
