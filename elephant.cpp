/************************************************************/
/*                                                            */
/*        ESGI: algorithmique pour l'infographie            */
/*                                                            */
/************************************************************/


#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/GLUT.h>
#endif

#include<stdlib.h>
#include<stdio.h>
#include <math.h>

float angle = 0.0;
float angle2 = 0.0;
float brasRot = 0.0;
float bodyRot = 0.0;
float jambeDrRot = 0.0;
float genouxDrRot = 0.0;
float jambeGaRot = 0.0;
float genouxGaRot = 0.0;
float cameraAngle = 10.0;
bool go_left = true;

GLdouble    pos_x = 0., pos_y = 0., pos_z = 5., dist_r = 5., alpha = 0., beta = 0.;

/* prototypes de fonctions */
void initRendering();                           // Initialisation du rendu
void display();                             // modÈlisation
void reshape(int w,int h);                      // visualisation
void update(int value);                     // mise ‡ jour: appelle Timer pour l'animation de la scËne
void keyboard(unsigned char key, int x, int y); // fonction clavier
void SpecialKeyHandler(int key, int x, int y);


/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
          char **argv){  // argv: tableau de chaines de caractËres, argv[0] contient le nom du programme lancÈ (plus un Èventuel chemin)


    /* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);                       // Initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
    glutInitWindowSize(500, 500);                // dimension fenÍtre
    glutInitWindowPosition (100, 100);           // position coin haut gauche
    glutCreateWindow("TP1: formes 2D et transformation");  // nom

    /* Initialisation d'OpenGL */
    initRendering();

    /* Enregistrement des fonctions de rappel
     => initialisation des fonctions callback appelÈes par glut */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKeyHandler);
    glutKeyboardFunc(keyboard);

    /* rq: le callback de fonction (fonction de rappel) est une fonction qui est passÈe en argument ‡ une
    autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en mÍme temps)
    alors qu'il ne les connaÓt pas par avance.*/


    /* EntrÈe dans la boucle principale de glut, traitement des ÈvËnements */
    glutTimerFunc(20,update,0);
    glutMainLoop();         // lancement de la boucle de rÈception des ÈvËnements
    return 0;               // pour finir
}

/* textures*/


void Draw_rectangle(double length, double heigth, double width){
    length = length / 2;
    heigth = heigth / 2;
    width = width / 2;
    glBegin(GL_QUADS);
    //Front
    glVertex3f(-length, -heigth, width);
    glVertex3f(length, -heigth, width);
    glVertex3f(length, heigth, width);
    glVertex3f(-length, heigth, width);
    //Right
    glVertex3f(length, -heigth, -width);
    glVertex3f(length, heigth, -width);
    glVertex3f(length, heigth, width);
    glVertex3f(length, -heigth, width);
    //Back
    glVertex3f(-length, -heigth, -width);
    glVertex3f(-length, heigth, -width);
    glVertex3f(length, heigth, -width);
    glVertex3f(length, -heigth, -width);
    //Left
    glVertex3f(-length, -heigth, -width);
    glVertex3f(-length, -heigth, width);
    glVertex3f(length, heigth, width);
    glVertex3f(length, heigth, -width);
    //top
    glVertex3f(-length, heigth, -width);
    glVertex3f(-length, heigth, width);
    glVertex3f(length, heigth, width);
    glVertex3f(length, heigth, -width);
    //bot
    glVertex3f(-length, -heigth, -width);
    glVertex3f(-length, -heigth, width);
    glVertex3f(length, -heigth, width);
    glVertex3f(length, -heigth, -width);
    glEnd();
}

void Draw_sphere(double radius){
        glutSolidSphere(radius,100,100);
}


/* Initialisation d'OpenGL pour le rendu de la scËne */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

    /* Activation des couleurs */
    glEnable(GL_COLOR_MATERIAL);

    /* dÈfinit la couleur d'effacement et la couleur de fond */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /*  dÈfinit la taille d'un pixel*/
    glPointSize(2.0);

}

void calc_pos(void){
    pos_x = dist_r * cos(beta) * sin(alpha);
    pos_y = dist_r * sin(beta);
    pos_z = dist_r * cos(beta) * cos(alpha);
}

/* CrÈation de la scËne */
void display(){

    /* Efface les tampons de couleur et de profondeur de l'image avec la couleur de fond.
    rq: buffer: mÈmoire tampon, c'est donc une surface en memoire utilisÈe pour stocker une image*/
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    /* la mat de visualisation-modÈlisation est modifiable par dÈfaut */
    glMatrixMode(GL_MODELVIEW);

    /* on charge l'identitÈ dans la matrice de modÈlisation-visualisation*/
    glLoadIdentity();


    /* Permet de crÈer un point de vue. DÈfinit une matrice de modÈlisation-visualisation et la multiplie
    ‡ droite de lma matrice active, ici l'identitÈ*/
    calc_pos();
    gluLookAt(pos_x, pos_y, pos_z, 0.,0.,0.,0.,1.,0.);   // vecteur d'orientation camÈra

        glPushMatrix();
            //Tete
                    glTranslatef(0.0f, 0.0f, 0.0f);
                    glPushMatrix();
                        glScalef(1.4f, 1.4f, 1.4f);
                        Draw_sphere(0.5);
                    glPopMatrix();
                    
                    //oreilles droite
                    glTranslatef(0.0f, 0.7f, 0.0f);
                    glPushMatrix();
                        glScalef(0.4f, 0.2f, 0.4f);
                        Draw_sphere(0.5);
                    glPopMatrix();
            
                    //oreilles gauche
                    glTranslatef(0.0f, -1.4f, 0.0f);
                    glPushMatrix();
                        glScalef(0.4f, 0.2f, 0.4f);
                        Draw_sphere(0.5);
                    glPopMatrix();
            
                    //Le petit rond sur sa tete
                    glTranslatef(-0.4f, 0.7f, 0.0f);
                    glPushMatrix();
                        glScalef(0.5f, 0.5f, 0.5f);
                        Draw_sphere(0.8);
                    glPopMatrix();
            //Yeux
            
    
        glPopMatrix();

    
    
    
        glPushMatrix();
        //Body
            glRotatef(bodyRot,1.0f, 0.0f, 0.0f);
            glTranslatef(0.5f, 0.0f, 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(1.0f, 0.0f, 0.0f);
            glPushMatrix();
                Draw_rectangle(1.8, 1.6, 1.0);
            glPopMatrix();
    
            //Bras 1
            //epaule
            glTranslatef(-0.4f, -1.2f, 0.0f);
            glPushMatrix();
                Draw_sphere(0.5);
            glPopMatrix();

                glPushMatrix();
                        //debut du bras
                        glRotatef(brasRot,0.0f, 1.0f, 0.0f);
                        glTranslatef(-0.4f, 0.0f, 0.0f);
                        glRotatef(angle, 0.0f, 0.0f, 1.0f);
                        glTranslatef(1.0f, 0.0f, 0.0f);
                        glPushMatrix();
                            Draw_rectangle(0.5, 0.7, 0.9);
                        glPopMatrix();
                
                        glTranslatef(-0.65f, 0.0f, 0.0f);
                        glRotatef(angle, 0.0f, 0.0f, 1.0f);
                        glTranslatef(1.0f, 0.0f, 0.0f);
                        glPushMatrix();
                            Draw_rectangle(0.15, 0.5, 0.1);
                        glPopMatrix();
    
                        //articulation ronde au milieu du bras
                        
                        glTranslatef(0.35f, 0.0f, 0.0f);
                        glPushMatrix();
                            glScalef(0.6f, 0.6f, 0.6f);
                            Draw_sphere(0.5);
                        glPopMatrix();

    
    
                        glPushMatrix();
                                //avant bras
                                glRotatef(angle2,0.0f, 1.0f, 0.0f);
                                
                                glTranslated(0.5f, 0.0f, 0.0f);
                                glPushMatrix();
                                    Draw_rectangle(0.5, 0.5, 0.5);
                                glPopMatrix();
                        
                                //Main
                                glTranslated(0.3f, 0.0f, -0.2f);
                                glPushMatrix();
                                    Draw_rectangle(0.2, 0.5, 0.1);
                                glPopMatrix();
                            
                                glTranslated(0.15f, 0.0f, 0.1f);
                                glPushMatrix();
                                    Draw_rectangle(0.1, 0.5, 0.3);
                                glPopMatrix();
                        glPopMatrix();
                glPopMatrix();
    
            
    
            //Bras 2
                //epaule
                glTranslatef(0.0f,2.4f, 0.0f);
                glPushMatrix();
                    Draw_sphere(0.5);
                glPopMatrix();
    
                    glPushMatrix();
    
                            //debut du bras
                            glRotatef(brasRot,0.0f, 1.0f, 0.0f);
                            glTranslatef(-0.4f, 0.0f, 0.0f);
                            glRotatef(angle, 0.0f, 0.0f, 1.0f);
                            glTranslatef(1.0f, 0.0f, 0.0f);
                            glPushMatrix();
                                Draw_rectangle(0.5, 0.7, 0.9);
                            glPopMatrix();
                    
                            glTranslatef(-0.65f, 0.0f, 0.0f);
                            glRotatef(angle, 0.0f, 0.0f, 1.0f);
                            glTranslatef(1.0f, 0.0f, 0.0f);
                            glPushMatrix();
                                Draw_rectangle(0.15, 0.5, 0.1);
                            glPopMatrix();
        
                            //articulation ronde au milieu du bras
                            
                            glTranslatef(0.35f, 0.0f, 0.0f);
                            glPushMatrix();
                                glScalef(0.6f, 0.6f, 0.6f);
                                Draw_sphere(0.5);
                            glPopMatrix();

                            glPushMatrix();
    
                                    //avant bras
                                    glRotatef(angle2,0.0f, 1.0f, 0.0f);
                                    glTranslated(0.5f, 0.0f, 0.0f);
                                    glPushMatrix();
                                        Draw_rectangle(0.5, 0.5, 0.5);
                                    glPopMatrix();
                            
                                    //Main
                                    glTranslated(0.3f, 0.0f, -0.2f);
                                    glPushMatrix();
                                        Draw_rectangle(0.2, 0.5, 0.1);
                                    glPopMatrix();
                                
                                    glTranslated(0.15f, 0.0f, 0.1f);
                                    glPushMatrix();
                                        Draw_rectangle(0.1, 0.5, 0.3);
                                    glPopMatrix();

                            glPopMatrix();
    
                    glPopMatrix();
    glPopMatrix();
    
        
        
    
        
    
        //JAMBE DROITE
                //hanche DROITE
                glTranslated(2.5f, 0.5f, 0.0f);
                glPushMatrix();
                    glScalef(0.5f, 0.5f, 0.5f);
                    Draw_sphere(0.6);
                glPopMatrix();
    
                glPushMatrix();
        
                        //haut jambe DROITE
                        glRotatef(jambeDrRot,0.0f, 1.0f, 0.0f);
                        glTranslated(0.6f, 0.0f, 0.0f);
                        glPushMatrix();
                            Draw_rectangle(0.7, 0.5, 0.4);
                        glPopMatrix();
                
                        //genoux DROITE
                        glTranslated(0.45f, 0.0f, 0.0f);
                        glPushMatrix();
                            glScalef(0.5f, 0.5f, 0.5f);
                            Draw_sphere(0.5);
                        glPopMatrix();
    
                        glPushMatrix();
    
                                //bas jambe DROITE
                                glRotatef(genouxDrRot,0.0f, 1.0f, 0.0f);
                                glTranslated(0.4f, 0.0f, 0.0f);
                                glPushMatrix();
                                    Draw_rectangle(0.45, 0.5, 0.4);
                                glPopMatrix();
                        
                                //pied DROITE
                                glTranslated(0.2f, 0.0f, 0.3f);
                                glPushMatrix();
                                    glScalef(0.1f, 0.9f, 1.3f);
                                    Draw_sphere(0.5);
                                glPopMatrix();
    
                        glPopMatrix();
    
                glPopMatrix();
    
            //JAMBE GAUCHE
                        //hanche GAUCHE
                        glTranslated(0.0f, -1.0f, 0.0f);
                        glPushMatrix();
                            glScalef(0.5f, 0.5f, 0.5f);
                            Draw_sphere(0.6);
                        glPopMatrix();
            
                        glPushMatrix();
                
                                //haut jambe GAUCHE
                                glRotatef(jambeGaRot,0.0f, 1.0f, 0.0f);
                                glTranslated(0.6f, 0.0f, 0.0f);
                                glPushMatrix();
                                    Draw_rectangle(0.7, 0.5, 0.4);
                                glPopMatrix();
                        
                                //genoux GAUCHE
                                glTranslated(0.45f, 0.0f, 0.0f);
                                glPushMatrix();
                                    glScalef(0.5f, 0.5f, 0.5f);
                                    Draw_sphere(0.5);
                                glPopMatrix();
            
                                glPushMatrix();
            
                                        //bas jambe GAUCHE
                                        glRotatef(genouxGaRot,0.0f, 1.0f, 0.0f);
                                        glTranslated(0.4f, 0.0f, 0.0f);
                                        glPushMatrix();
                                            Draw_rectangle(0.45, 0.5, 0.4);
                                        glPopMatrix();
                                
                                        //pied GAUCHE
                                        glTranslated(0.2f, 0.0f, 0.3f);
                                        glPushMatrix();
                                            glScalef(0.1f, 0.9f, 1.3f);
                                            Draw_sphere(0.5);
                                        glPopMatrix();
            
                                glPopMatrix();
            
                        glPopMatrix();
            
    
            
    

        


    glFlush(); // nettoie les fenÍtres prÈcÈdentes
}





/*  Mise en forme de la scËne pour l'affichage */
void reshape(int w,  // w: largeur fenÍtre
             int h)  // h: hauteur fenÍtre
{
    /* Viewport: cadrage. SpÈcifie la rÈgion (position et taille en px) que l'image observÈe de la scËne occupe
    ‡ l'Ècran => rÈduction et agrandissement de l'image possible*/
    glViewport(0, 0,(GLsizei) w, (GLsizei) h);

    /* SpÈcifie que la matrice de projection va Ítre modifiÈe  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();             // matrice courante: l'identitÈ
    //glOrtho(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

    /* Perspective avec point de fuite */
    gluPerspective(60.0,                       // angle d'ouverture vertical camÈra
                   (GLfloat) w / (GLfloat) h,  // ratio largeur-hauteur
                   1.0,                           // plan proche z=1
                   200.0);                     // plan ÈloignÈ z=200


}

/* Fonction de gestion du clavier */
void keyboard(unsigned char key,       // Touche qui a ÈtÈ pressÈe
                    int x, int y) {    // CoordonnÈes courante de la souris

        switch (key){

            case 'z':   /* affichage du carrÈ plein*/
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                glutPostRedisplay();
                break;

            case 'f':   /* affichage en mode fil de fer*/
                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                glutPostRedisplay();
                break;

            case 's':   /* affichage en mode sommets seuls*/
                glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
                glutPostRedisplay();
                break;

            case 'b':
                if (angle2 < 90.)
                    angle2 += 1.6;
                break;

            case 'n':
                if (angle2 > -90.)
                    angle2 -= 1.6;
                break;
                
                case 'c':
                    if (brasRot < 90.)
                        brasRot += 1.6;
                    break;

                case 'v':
                    if (brasRot > -90.)
                        brasRot -= 1.6;
                    break;
                
                case 'w':
                    if (bodyRot < 90.)
                        bodyRot += 1.6;
                    break;

                case 'x':
                    if (bodyRot > -90.)
                        bodyRot -= 1.6;
                    break;
                
                case 'l':
                    if (jambeDrRot < 90.)
                        jambeDrRot+= 1.6;
                    break;

                case 'm':
                    if (jambeDrRot > -90.)
                        jambeDrRot -= 1.6;
                    break;
                
                case 'j':
                    if (jambeGaRot < 90.)
                        jambeGaRot+= 1.6;
                    break;

                case 'k':
                    if (jambeGaRot > -90.)
                        jambeGaRot -= 1.6;
                    break;
                
                case 'o':
                    if (genouxDrRot < 90.)
                        genouxDrRot+= 1.6;
                    break;

                case 'p':
                    if (genouxDrRot > -90.)
                        genouxDrRot -= 1.6;
                    break;
                
                case 'u':
                    if (genouxGaRot < 90.)
                        genouxGaRot+= 1.6;
                    break;

                case 'i':
                    if (genouxGaRot > -90.)
                        genouxGaRot -= 1.6;
                    break;
                
            case '+':
                if (dist_r > 0.2)
                    dist_r -= 0.1;
                break;
            case '-':
                dist_r += 0.1;
                break;
            case 'q':   /* Quitter le programme */
                exit(0);
        }
}

void SpecialKeyHandler(int key, int x, int y){
    switch (key){
        case GLUT_KEY_LEFT:
            alpha -= 0.1;
            break;
        case GLUT_KEY_UP:
            if (beta < M_PI / 2 -0.1)
                beta += 0.1;
            break;
        case GLUT_KEY_DOWN:
            if (beta > -M_PI / 2 + 0.1)
                beta -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            alpha += 0.1;
            break;
    }
    //printf("pouet\n");
}

void    update(int value){
    
    if (angle >= 360.)
        angle = 0.;

    /*if (go_left){
        angle2 += 0.8;
        if (angle2 >= 90.)
            go_left = false;
    }else{
        angle2 -= 0.8;
        if (angle2 <= -90.)
            go_left = true;
    }*/
    glutPostRedisplay();
    glutTimerFunc(10,update,0);
}

