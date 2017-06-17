#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

#define TIMER_ID 1
#define TIMER_ID_BELA 2
#define TIMER_ID_OSTALE 3
#define PI 3.14159265

float angle = 0.0f;

float lx = 0.0f, lz = -1.0f;

float x = 0.0f, z = 5.0f;

float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

static float val = PI / 180.0;

static int TIMER = 25;
static int TIMER_BELE = 25;
static int TIMER_LOPTE = 25;

static void onTimer(int id);
static void onTimerBela(int id);
static void onTimerOstale(int id);
static void pomeri_stap(void);

static int intenzitet_bela = 1500;
static int intenzitet_crvena = 1500;

static int duzina_stola = 11;
static int sirina_stola = 7;

static float vektor_x_bela = 0.0;
static float vektor_z_bela = 0.0;
static float vektor_y_bela = -0.01;

static float vektor_pravca_x_bela = 0.0;
static float vektor_pravca_z_bela = 0.1;

static float pozicija_stapa_x;
static float pozicija_stapa_z;

static float duzina_stapa = 3;

static float vektor_x_crvena = 0.0;
static float vektor_z_crvena = 0.0;
static float vektor_y_crvena = -0.01;

static float pozicija_crvena_x = 3.5;
static float pozicija_crvena_z = 7;
static float pozicija_crvena_y = 0;

static float pozicija_bela_x = 3.5;
static float pozicija_bela_z = 0.5;
static float pozicija_bela_y = 0;

static int ugao_kretanja = 0;

static int udarena_bela = 0;
static int pritisnuto_dugme = 0;
static int loptice_se_krecu = 0;
static int usla_bela=0;
static int usla_crvena=0;



static int pozicija_prve_rupe_x = 0.0;
static int pozicija_prve_rupe_z = 0.0;

static int pozicija_druge_rupe_x = 7.0;
static int pozicija_druge_rupe_z = 0.0;


static int pozicija_trece_rupe_x = 0.0;
static int pozicija_trece_rupe_z = 6.0;

static int pozicija_cetvrte_rupe_x = 7.0;
static int pozicija_cetvrte_rupe_z = 6.0;

static int pozicija_pete_rupe_x = 0.0;
static int pozicija_pete_rupe_z = 11.5;

static int pozicija_seste_rupe_x = 7.0;
static int pozicija_seste_rupe_z = 11.5;

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;
    }
}

void computePos(float deltaMove)
{

    x += deltaMove * vektor_x_bela * 0.1f;
    z += deltaMove * vektor_z_bela * 0.1f;
}

static void onTimerOstale(int id)
{
    if (id != TIMER_ID_OSTALE) {
        return;
    }
    
    
    if ((pozicija_bela_z >= (pozicija_crvena_z + 0.3)) && (pozicija_bela_z <= (pozicija_crvena_z - 0.3)) && (pozicija_bela_x <= (pozicija_crvena_x + 0.3)) && (pozicija_bela_x >= (pozicija_crvena_x - 0.3))) {
        intenzitet_bela -= 100;
        intenzitet_crvena = intenzitet_bela;
        vektor_x_crvena = (pozicija_bela_x + 0.2 - pozicija_bela_x - 0.2)/5;
        vektor_z_crvena = -(pozicija_crvena_z + 0.2 - pozicija_bela_z - 0.2)/5;
        vektor_x_bela = (pozicija_bela_x + 0.2 - pozicija_crvena_x - 0.2)/5;
        vektor_z_bela = -(pozicija_crvena_z + 0.2 - pozicija_bela_z - 0.2)/5;
    }
	else
    if ((pozicija_crvena_z >= (pozicija_bela_z + 0.3)) && (pozicija_crvena_z <= (pozicija_bela_z - 0.3)) && (pozicija_crvena_x <= (pozicija_bela_x + 0.3)) && (pozicija_crvena_x >= (pozicija_bela_x - 0.3))) {
        intenzitet_bela -= 100;
        intenzitet_crvena = intenzitet_bela;
        vektor_x_crvena = (pozicija_crvena_x + 0.2 - pozicija_bela_x - 0.2)/5;
        vektor_z_crvena = -(pozicija_bela_z + 0.2 - pozicija_crvena_z - 0.2)/5;
        vektor_x_bela = (pozicija_crvena_x + 0.2 - pozicija_bela_x - 0.2)/5;
        vektor_z_bela = -(pozicija_bela_z + 0.2 - pozicija_crvena_z - 0.2)/5;
    }

    if (intenzitet_crvena > 0 && intenzitet_bela > 0) {

        intenzitet_crvena -= 0.2;
        intenzitet_bela -= 0.2;

        if ((pozicija_crvena_x + 0.3) >= sirina_stola)
            vektor_x_crvena = vektor_x_crvena * (-1);
        else if ((pozicija_crvena_x - 0.3) <= 0)
            vektor_x_crvena = vektor_x_crvena * (-1);
        else if ((pozicija_crvena_z + 0.3) >= duzina_stola)
            vektor_z_crvena = vektor_z_crvena * (-1);
        else if ((pozicija_crvena_z - 0.3) <= 0)
            vektor_z_crvena = vektor_z_crvena * (-1);
            

        pozicija_bela_z += (vektor_z_bela) / 3;
        pozicija_bela_x += (vektor_x_bela) / 3;


        pozicija_crvena_z += vektor_z_crvena;
        pozicija_crvena_x += vektor_x_crvena;
        glutPostRedisplay();
        
    glutTimerFunc(TIMER_LOPTE, onTimerOstale, TIMER_ID_OSTALE);
    }
    else{
    	udarena_bela=0;
	}
}

static void onTimerBela(int id)
{
    if (id != TIMER_ID_BELA) {
        return;
    }
    
    
    if( 
	( pozicija_bela_z <= (pozicija_prve_rupe_z+ 0.6) && pozicija_bela_x <= (pozicija_prve_rupe_x +0.6) ) 
	
	 ){
    	usla_bela=1;
        glutTimerFunc(TIMER, onTimer, TIMER_ID); 
    }
    else
	
	if( 
	( pozicija_crvena_z <= pozicija_prve_rupe_z+ 0.6 && pozicija_crvena_x <= pozicija_prve_rupe_x +0.6 ) 
	
	 ){
    	usla_crvena=1;
        glutTimerFunc(TIMER, onTimer, TIMER_ID); 
    }
    else
	
	
	{
    
     	
    

    if ((pozicija_bela_z <= (pozicija_crvena_z + 0.2)) && (pozicija_bela_z >= (pozicija_crvena_z - 0.2)) && (pozicija_bela_x <= (pozicija_crvena_x + 0.2)) && (pozicija_bela_x >= (pozicija_crvena_x - 0.2))) {
        
        vektor_x_crvena = (pozicija_crvena_x - pozicija_bela_x) / 7;
        vektor_z_crvena = (pozicija_crvena_z - pozicija_bela_z) / 7;

        vektor_x_bela = (pozicija_bela_x - pozicija_crvena_x) / 7;
        vektor_z_bela = -(pozicija_bela_z - pozicija_crvena_z) / 7;

        glutPostRedisplay();
        glutTimerFunc(TIMER_LOPTE, onTimerOstale, TIMER_ID_OSTALE);
    }

    if (intenzitet_bela > 0) {
        intenzitet_bela -= 0.1;

        if ((pozicija_bela_x + 0.3) >= sirina_stola)
            vektor_x_bela = vektor_x_bela * (-1);
        if ((pozicija_bela_x - 0.3) <= 0)
            vektor_x_bela = vektor_x_bela * (-1);
        if ((pozicija_bela_z + 0.3) >= duzina_stola)
            vektor_z_bela = vektor_z_bela * (-1);
        if ((pozicija_bela_z - 0.3) <= 0)
            vektor_z_bela = vektor_z_bela * (-1);

        pozicija_bela_z += (vektor_z_bela / 20);
        pozicija_bela_x += (vektor_x_bela / 20);

        glutPostRedisplay();
        glutTimerFunc(TIMER_BELE, onTimerBela, TIMER_ID_BELA);
    }
}
}

static void onTimer(int id)
{
    if (id != TIMER_ID) {
        return;
    }
	/*
    if (((pozicija_stapa_z - 2.2) > (pozicija_bela_z)) && (((pozicija_stapa_x - 2.2) > (pozicija_bela_x)))) {
        pozicija_stapa_z += (vektor_z_bela);
        pozicija_stapa_x += (vektor_x_bela);
        glutPostRedisplay();
        glutTimerFunc(TIMER, onTimer, TIMER_ID);
    }
    else {
        udarena_bela = 1;
        glutTimerFunc(TIMER_LOPTE, onTimerBela, TIMER_ID_BELA);
    }
    */	if( usla_bela || usla_crvena){
	    	if(usla_bela){
		    	pozicija_bela_y+=vektor_y_bela;
		    	pozicija_bela_x= (vektor_x_bela / 200);
		    	pozicija_bela_z= ((vektor_z_bela) / 130);
		    	if(pozicija_bela_y < (-0.4))
		    		pozicija_bela_y=-500;
		        glutPostRedisplay();
		        glutTimerFunc(TIMER, onTimer, TIMER_ID);   
	    	}
	    	else
	    	{
		    	pozicija_crvena_y+=vektor_y_crvena;
		    	pozicija_crvena_x= (vektor_x_crvena / 200);
		    	pozicija_crvena_z= (vektor_z_crvena / 130);
		    		if(pozicija_crvena_y < (-0.4))
		    			pozicija_crvena_y=-500;
		        glutPostRedisplay();
		        glutTimerFunc(TIMER, onTimer, TIMER_ID);   
	    	}
	    }
    	else{
    	udarena_bela=1;
        glutTimerFunc(TIMER_LOPTE, onTimerBela, TIMER_ID_BELA);
    	}
}

void SpecialInput(int key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case GLUT_KEY_UP:
        if (!udarena_bela){
        	loptice_se_krecu=1;
            glutTimerFunc(TIMER, onTimer, TIMER_ID);   
    		intenzitet_bela=500;
    	}
        break;

    case GLUT_KEY_LEFT:
        ugao_kretanja -= 1;
        pritisnuto_dugme = 1;
        glutPostRedisplay();
        pomeri_stap();
        glutDisplayFunc(on_display);
        break;

    case GLUT_KEY_RIGHT:
        ugao_kretanja += 1;
        pritisnuto_dugme = 1;
        glutPostRedisplay();
        pomeri_stap();
        glutDisplayFunc(on_display);
        break;
    case GLUT_KEY_F5:
    	loptice_se_krecu=0;
    	udarena_bela=0;
    	intenzitet_bela=1500;
    	intenzitet_crvena=1500;
    	pomeri_stap();
        glutDisplayFunc(on_display);
    	break;
    }
}

int main(int argc, char** argv)
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
    glutSpecialFunc(SpecialInput);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glEnable(GL_DEPTH_TEST);
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void pomeri_stap(void)
{

    if (!(udarena_bela) && loptice_se_krecu==0 ) {
        /*pozicioniranje stapa*/
        pozicija_stapa_x = (pozicija_bela_x + (duzina_stapa * (sin(ugao_kretanja * val))));
        pozicija_stapa_z = (pozicija_bela_z - (duzina_stapa * (cos(ugao_kretanja * val))));

        vektor_x_bela = -(pozicija_stapa_x - pozicija_bela_x);
        vektor_z_bela = -(pozicija_stapa_z - pozicija_bela_z);


        vektor_pravca_x_bela = vektor_x_bela;
        vektor_pravca_z_bela = vektor_z_bela;

        glLineWidth(1.5);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(pozicija_stapa_x, 0.0, pozicija_stapa_z);
        glVertex3f(pozicija_stapa_x + vektor_x_bela * 3, 0, pozicija_stapa_z + vektor_z_bela * 3);
        glEnd();

        /*
        if(pozicija_stapa_x+vektor_x_bela*3 >= sirina_stola-0.4 ){
        vektor_pravca_x_bela*=(-1);
        
        glLineWidth(1.5); 
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        
        glVertex3f(sirina_stola + sirina_stola-(pozicija_stapa_x+vektor_x_bela*3), 0.1, pozicija_stapa_z+vektor_pravca_z_bela*3);
        vektor_pravca_z_bela*=(2);
        glVertex3f( pozicija_stapa_x+vektor_pravca_x_bela*3, 0.1, pozicija_stapa_z+vektor_pravca_z_bela*3);
        
        glutPostRedisplay();
        glEnd();
        }
        */
    }
}

static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1, 25);
}

static void on_display(void)
{

    if (deltaMove)
        computePos(deltaMove);

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
    if (!udarena_bela)
        gluLookAt(pozicija_stapa_x - vektor_x_bela * 3, 10, pozicija_stapa_z - vektor_z_bela, 3 + vektor_x_bela * 3, 0, 3 + vektor_z_bela, 0, 1, 0);
    else
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
    glTranslatef(0.0, 0.0, -1.5);
    glBegin(GL_POLYGON);
    glColor3d(0.0, 1.0, 0.4);
    glVertex3f(0.0, -0.5, 13);
    glVertex3f(7.0, -0.5, 13);
    glVertex3f(7.0, -0.5, 1.5);
    glVertex3f(0.0, -0.5, 1.5);
    glEnd();
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.5);
    glBegin(GL_POLYGON);
    glColor3d(0.405, 0.133, 0.063);
    glVertex3f(-1.0, -0.7, 1.6);
    glVertex3f(8.0, -0.7, 1.6);
    glVertex3f(6.5, -0.7, 0.6);
    glVertex3f(0.5, -0.7, 0.6);
    glEnd();
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.5);
    glBegin(GL_POLYGON);
    glColor3d(0.405, 0.133, 0.063);
    glVertex3f(-1.0, -0.7, 1.6);
    glVertex3f(-1.0, -0.7, 14.0);
    glVertex3f(0, -0.7, 14.0);
    glVertex3f(0, -0.7, 1.6);
    glEnd();
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.5);
    glBegin(GL_POLYGON);
    glColor3d(0.405, 0.133, 0.063);
    glVertex3f(7.0, -0.7, 1.6);
    glVertex3f(7.0, -0.7, 14.0);
    glVertex3f(8, -0.7, 14.0);
    glVertex3f(8, -0.7, 1.6);
    glEnd();
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.5);
    glBegin(GL_POLYGON);
    glColor3d(0.405, 0.133, 0.063);
    glVertex3f(0.0, -0.7, 14.0);
    glVertex3f(7.0, -0.7, 14.0);
    glVertex3f(7, -0.7, 11.6);
    glVertex3f(0, -0.7, 11.6);
    glEnd();
    glFlush();
    glPopMatrix();

    /* Crtanje rupa */
    glPushMatrix();
    glTranslatef(pozicija_prve_rupe_x, -0.5, pozicija_prve_rupe_z);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.3, 50, 50);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_druge_rupe_x, -0.5, pozicija_druge_rupe_z);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.3, 50, 50);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_trece_rupe_x, -0.5, pozicija_trece_rupe_z);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.3, 50, 50);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_cetvrte_rupe_x, -0.5, pozicija_cetvrte_rupe_z);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.3, 50, 50);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_pete_rupe_x, -0.5, pozicija_pete_rupe_z);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.2, 50, 50);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_seste_rupe_x, -0.5, pozicija_seste_rupe_z);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.2, 50, 50);
    glFlush();
    glPopMatrix();

    /*crtanje bele*/
    glPushMatrix();
    glTranslatef(pozicija_bela_x, pozicija_bela_y, pozicija_bela_z);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.2, 50, 50);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    
    glTranslatef(pozicija_crvena_x, pozicija_crvena_y, pozicija_crvena_z);
    glColor3f(1, 0, 0);
    glutSolidSphere(0.2, 40, 40);
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pozicija_stapa_x, 0.0, pozicija_stapa_z);
    glRotatef(-ugao_kretanja, 0, 1, 0);
    glColor3f(0.5, 0.25, 0.0);
    GLUquadric* qobj = gluNewQuadric();
    gluCylinder(qobj, 0.1, 0.015, duzina_stapa, 10, 10);
    glutPostRedisplay();
    glPopMatrix();
    pomeri_stap();
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
