/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include<iostream>
#include <stdio.h>
#include <windows.h>

static int slices = 16;
static int stacks = 16;
static int eixoy, eixox;
float door_angle = 0;

#define PI 3.14159265359

using namespace std;

float camera_angle = 0;
float camera_x = -100;
float camera_y = 0;
float camera_height = 3;
float camera_rotate_speed = 0.003;
float camera_distance = 40;

float eye_x = 0;
float eye_y = 0;
float eye_z = 0;

float camera_x_angle = 0;
float camera_y_angle = 0;
float mouse_old_pos_x = 0;
float mouse_old_pos_y = 0;

GLboolean ambient = true;
GLboolean diffuse = true;
GLboolean specular = true;
GLuint texture[10];


GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 2.0, 25.0, 3.0, 1.0 };

GLfloat table_leg_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat table_leg_ambient[] = {1.000, 0.388, 0.278, 1.0};
GLfloat table_leg_diffuse[] = {1.000, 0.388, 0.278, 1.0};
GLfloat table_leg_specular[] = {1.000, 0.388, 0.278, 1.0};
GLfloat table_leg_shiness[] = {15};

GLfloat table_top_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat table_top_ambient[] = {1.000, 0.388, 0.278, 1.0};
GLfloat table_top_diffuse[] = {1.000, 0.388, 0.278, 1.0};
GLfloat table_top_specular[] = {1.000, 0.388, 0.278, 1.0};
GLfloat table_top_shiness[] = {17};

GLfloat chair_leg_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat chair_leg_ambient[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_leg_diffuse[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_leg_specular[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_leg_shiness[] = {15};

GLfloat chair_seat_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat chair_seat_ambient[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_seat_diffuse[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_seat_specular[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_seat_shiness[] = {17};

GLfloat chair_top_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat chair_top_ambient[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_top_diffuse[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_top_specular[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_top_shiness[] = {17};

GLfloat bed_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat bed_ambient[] = {0.859, 0.439, 0.576, 1.0};
GLfloat bed_diffuse[] = {0.8, 0.48, 0.6, 0.9};
GLfloat bed_specular[] = {0.86, 0.50, 0.60, 1.0};
GLfloat bed_shiness[] = {13};

GLfloat bed_head_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat bed_head_ambient[] = {0.545, 0.271, 0.075, 1.0};
GLfloat bed_head_diffuse[] = {0.58, 0.29, 0.06, 0.9};
GLfloat bed_head_specular[] = {0.545, 0.271, 0.075, 1.0};
GLfloat bed_head_shiness[] = {13};

GLfloat shelf_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat shelf_ambient[] = {1.000, 0.388, 0.278, 1.0};
GLfloat shelf_diffuse[] = {1.000, 0.388, 0.278, 0.9};
GLfloat shelf_specular[] = {1.000, 0.388, 0.278, 1.0};
GLfloat shelf_shiness[] = {13};


GLfloat wall_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat wall_ambient[] = {0.373, 0.620, 0.627, 1.0};
GLfloat wall_diffuse[] = {0.30, 0.6, 0.59, 0.9};
GLfloat wall_specular[] = {0.32,0.6, 0.61, 1.0};
GLfloat wall_shiness[] = {13};

GLfloat floor_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat floor_ambient[] = {0.184, 0.310, 0.310, 0.8};
GLfloat floor_diffuse[] = {0.19, 0.3, 0.33, 1.0};
GLfloat floor_specular[] = {0.184, 0.35, 0.35, 1.0};
GLfloat floor_shiness[] = {15};

GLfloat ceiling_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat ceiling_ambient[] = {0.373, 0.620, 0.627, 1.0};
GLfloat ceiling_diffuse[] = {0.35, 0.612, 0.65, 0.9};
GLfloat ceiling_specular[] = {0.4, 0.65, 0.647, 1.0};
GLfloat ceiling_shiness[] = {15};
void lighting(
    GLfloat no_mat[4],
    GLfloat mat_ambient[4],
    GLfloat mat_diffuse[4],
    GLfloat mat_specular[4],
    GLfloat shiness[1]
    )
{
    if(ambient)
    {
        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    }
    else
    {
        glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);

    }
    if(diffuse)
    {
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    }
    else
    {
        glMaterialfv(GL_FRONT,GL_DIFFUSE,no_mat);
    }
    if(specular)
    {
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);

    }
    else
    {
        glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    }
    glMaterialfv(GL_FRONT,GL_SHININESS,shiness);
}
struct Image
{
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
int ImageLoad(char *filename, Image *image)
{
    FILE *file;
    unsigned long size; ///size of the image in bytes
    unsigned long i; //standard counter
    unsigned short int planes; //number of planes in Image(must be 1)
    unsigned short int bpp; //number of bits per pixel(must be 24)
    char temp; //temporary color storage for bgr-rgb conversion

    //make sure the file in here
    file = fopen(filename, "rb");
    if(file==NULL)
    {
        printf("Can't open file! \n");
    }

   //seek through the bmp header, up to width/height
    fseek(file,18,SEEK_CUR);

    //read the width
    i = fread(&image->sizeX,4,1,file);
    //read the height
    i = fread(&image->sizeY,4,1,file);
    //calculate the size (assuming 24 bits or 3 bytes per pixel)
    size = image->sizeX * image->sizeY * 3;
    //read the plane
    fread(&planes, 2, 1, file);
    //read the bits per pixel
    fseek(file, 24, SEEK_CUR);
    //read the data
    image->data = (char*)malloc(size);

    i=fread(image->data, size, 1, file);

    for(i=0;i<size;i+=3) //reverse all ol color bgr -> rgb
    {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;

    }

    fclose(file);
    //we're done
return 1;

}
void loadTexture(char* file_name, int tex_id)
{
    Image *image1;
    //allocate space for texture
    image1 = (Image*) malloc(sizeof(Image));
    //Image not loaded
    if(!ImageLoad(file_name,image1))
    {
        exit(1);
    }

    texture[tex_id] = tex_id;

    glBindTexture(GL_TEXTURE_2D,tex_id);

    glTexImage2D(GL_TEXTURE_2D,0,3,image1->sizeX,image1->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,image1->data);

    //scale linearly when image is bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //scale linearly when image is smaller than texture

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}
/* GLUT callback Handlers */


void handleResize(int w, int h)
{
    glViewport(0,0,w,h);

}
void draw_solid_cube(GLfloat size)
{
    float x1,y1,z1;
    float x2,y2,z2;
    float x3,y3,z3;
    float x4,y4,z4;

    x1 = -size/2;
    y1 = -size/2;
    z1 = -size/2;

    x2 = size/2;
    y2 = -size/2;
    z2 = -size/2;

    x3 = size/2;
    y3 = -size/2;
    z3 = size/2;

    x4 = -size/2;
    y4 = -size/2;
    z4 = size/2;

    float x5,y5,z5;
    float x6,y6,z6;
    float x7,y7,z7;
    float x8,y8,z8;

    x5 = -size/2;
    y5 = size/2;
    z5 = -size/2;

    x6 = size/2;
    y6 = size/2;
    z6 = -size/2;

    x7 = size/2;
    y7 = size/2;
    z7 = size/2;

    x8 = -size/2;
    y8 = size/2;
    z8 = size/2;

    float n1_x = 0, n1_y = -1, n1_z = 0; //face that faces towards bottom
    float n2_x = 0, n2_y = 1, n2_z = 0; //up
    float n3_x = 0, n3_y = 0, n3_z = -1; //front
    float n4_x = 0, n4_y = 0, n4_z = 1; //back
    float n5_x = 1, n5_y = 0, n5_z = 0; //right
    float n6_x = -1, n6_y = 0, n6_z = 0; //left

    glBegin(GL_QUADS);
    //Quad 1

    glNormal3f(n1_x,n1_y,n1_z);

    glTexCoord2f(0,0);
    glVertex3f(x1,y1,z1);

    glTexCoord2f(1,0);
    glVertex3f(x2,y2,z2);

    glTexCoord2f(1,1);
    glVertex3f(x3,y3,z3);

    glTexCoord2f(0,1);
    glVertex3f(x4,y4,z4);

    //Quad 2

    glNormal3f(n2_x,n2_y,n2_z);

    glTexCoord2f(0,0);
    glVertex3f(x8,y8,z8);

    glTexCoord2f(1,0);
    glVertex3f(x7,y7,z7);

    glTexCoord2f(1,1);
    glVertex3f(x6,y6,z6);

    glTexCoord2f(0,1);
    glVertex3f(x5,y5,z5);
    //Quad 3

    glNormal3f(n3_x,n3_y,n3_z);

    glTexCoord2f(0,0);
    glVertex3f(x5,y5,z5);

    glTexCoord2f(1,0);
    glVertex3f(x6,y6,z6);

    glTexCoord2f(1,1);
    glVertex3f(x2,y2,z2);

    glTexCoord2f(0,1);
    glVertex3f(x1,y1,z1);
    //Quad 4


    glNormal3f(n4_x,n4_y,n4_z);

    glTexCoord2f(0,0);
    glVertex3f(x7,y7,z7);

    glTexCoord2f(1,0);
    glVertex3f(x8,y8,z8);

    glTexCoord2f(1,1);
    glVertex3f(x4,y4,z4);

    glTexCoord2f(0,1);
    glVertex3f(x3,y3,z3);
    //Quad 5

    glNormal3f(n5_x,n5_y,n5_z);

    glTexCoord2f(0,0);
    glVertex3f(x6,y6,z6);

    glTexCoord2f(1,0);
    glVertex3f(x7,y7,z7);

    glTexCoord2f(1,1);
    glVertex3f(x3,y3,z3);

    glTexCoord2f(0,1);
    glVertex3f(x2,y2,z2);

    //Quad 6

    glNormal3f(n6_x,n6_y,n6_z);

    glTexCoord2f(0,0);
    glVertex3f(x1,y1,z1);

    glTexCoord2f(1,0);
    glVertex3f(x4,y4,z4);

    glTexCoord2f(1,1);
    glVertex3f(x8,y8,z8);

    glTexCoord2f(0,1);
    glVertex3f(x5,y5,z5);


    glEnd();
}
void draw_bed()
{
    //bed
    lighting(bed_no_mat,bed_ambient,bed_diffuse,bed_specular,bed_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPushMatrix();
    glTranslatef(24.3,-8,-21);
    glScalef(12,3,10);
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //head
    lighting(bed_head_no_mat,bed_head_ambient,bed_head_diffuse,bed_head_specular,bed_head_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPushMatrix();
    glTranslatef(24.3,-6,-21);
    glScalef(2,2.5,10);
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void draw_shelf()
{
    lighting(shelf_no_mat,shelf_ambient,shelf_diffuse,shelf_specular,shelf_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glPushMatrix();
    glTranslatef(25,-8,-14);
    glRotatef(90,0,0,1);
    glScalef(3,5,3);
    glColor3f(0.4, 5.6, 4.3);
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void draw_table()
{
    //table legs
    float h = -0.6;
    lighting(table_leg_no_mat,table_leg_ambient,table_leg_diffuse,table_leg_specular,table_leg_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glPushMatrix();
    glScalef(.5,9,.5);
    glTranslatef(-18,-0.6,40);
    draw_solid_cube(1);
    glPopMatrix();


    glPushMatrix();
    glScalef(0.5,9,0.5);
    glTranslatef(-18, h, 47);
    draw_solid_cube(1);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,9,0.5);
    glTranslatef(15,h , 47);
    draw_solid_cube(1);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,9,0.5);
    glTranslatef(15,h, 40);
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //table top
    lighting(table_top_no_mat,table_top_ambient,table_top_diffuse,table_top_specular,table_top_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glPushMatrix();
    glTranslatef(0,-1,22);
    glScalef(20,0.5,7);
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void draw_chair(float x, float z, float r)
{
    //chair legs
    lighting(chair_leg_no_mat,chair_leg_ambient,chair_leg_diffuse,chair_leg_specular,chair_leg_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glPushMatrix();
    glTranslatef(-4+x, -6.5, 9.5+z);
    glScalef(0.35,4,0.35);
    draw_solid_cube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4+x, -6.5, 6.5+z);
    glScalef(0.35,4,0.35);
    draw_solid_cube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7+x, -6.5, 9.5+z);
    glScalef(0.35,4,0.35);
    draw_solid_cube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7+x, -6.5, 6.5+z);
    glScalef(0.35,4,0.35);
    draw_solid_cube(1);
    glPopMatrix();

    //chair seat
    lighting(chair_seat_no_mat,chair_seat_ambient,chair_seat_diffuse,chair_leg_specular,chair_seat_shiness);
    glPushMatrix();
    glTranslatef(-5.5+x, -4, 8+z);
    glScalef(4,1.0,4);
    draw_solid_cube(1);
    glPopMatrix();

    //chair top
    if(r == 0)
    {
        lighting(chair_top_no_mat,chair_top_ambient,chair_top_diffuse,chair_seat_specular,chair_top_shiness);
        glPushMatrix();
        glTranslatef(-7.5+x, -2.5, 8+z);
        glRotatef(90,0,0,1);
        glScalef(4,0.3,3.8);
        draw_solid_cube(1);
        glPopMatrix();
    }
    else if(r==1)
    {
        lighting(chair_top_no_mat,chair_top_ambient,chair_top_diffuse,chair_seat_specular,chair_top_shiness);
        glPushMatrix();
        glTranslatef(-8.0+x+2.5, 3.5, 8+z+1.8);
        glRotatef(90,1,0,0);
        glScalef(4,0.3,3.8);
        draw_solid_cube(1);
        glPopMatrix();
    }
    else if(r==2)
    {
        lighting(chair_top_no_mat,chair_top_ambient,chair_top_diffuse,chair_seat_specular,chair_top_shiness);

        glPushMatrix();
        glTranslatef(-8.0+x+2.5, -2, 8+z-1.8);
        glRotatef(90,1,0,0);
        glScalef(4,0.3,7);
        draw_solid_cube(1);
        glPopMatrix();
    }
    else if(r==3)
    {
        lighting(chair_top_no_mat,chair_top_ambient,chair_top_diffuse,chair_seat_specular,chair_top_shiness);
        glPushMatrix();
        glTranslatef(-7.5+x+4, 3.5, 8+z);
        glRotatef(90,0,0,1);
        glScalef(4,0.3,3.8);
        draw_solid_cube(1);
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
}
void draw_door()
{


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]); /// textura madeira
    glPushMatrix();

    glTranslatef(-25,5,0);
    glTranslatef(0, 0, 5);
    glRotatef(-door_angle,0,1,0);
    glTranslatef(0, 0, -5);
    glScalef(1, 30, 10);
    glColor3f(0.4f, 0.0f, 0.0f);
    draw_solid_cube(1);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();

    glPopMatrix();


}
void draw_window()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]); /// textura madeira
    glPushMatrix();
    glTranslatef(0,8,-25);
     glTranslatef(5, 0, 0);
    glRotatef(door_angle, 0,1,0);
    glTranslatef(-5, 0, 0);
    glScalef(10, 12, 0.2);
    glColor3f(0.4f, 0.0f, 0.0f);
    draw_solid_cube(1);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void draw_paiting(){
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[7]); /// texture parede / tijolinho
        glPushMatrix();
        glTranslatef(0,8,24.5);
        glScalef(15,18,0.2);
       // glColor3d(0, 0, 6); // white
        draw_solid_cube(0.5);
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void draw_wall() //paredes
{
    lighting(wall_no_mat,wall_ambient,wall_diffuse,wall_specular,wall_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]); /// texture parede / tijolinho
        glPushMatrix();
            glTranslatef(15,10,-25);
            glScalef(40,80,0.2);
            glColor3d(1.0, 0.0, 0.0); // red
            draw_solid_cube(0.5);
        glPopMatrix();

       /// glTranslatef(-25,10,0);
       glPushMatrix();
             glTranslatef(-15,10,-25);
            // glScalef(50,40,0.2)
            glScalef(40,80,0.2);
            glColor3d(1.0, 0.0, 0.0); // red
            draw_solid_cube(0.5);
        glPopMatrix();

        glPushMatrix();
       /// glTranslatef(-25,10,0);
            glTranslatef(0,25,-25);
            glScalef(20,44,0.2);
           glColor3d(1.0, 0.0, 0.0); // red
            draw_solid_cube(0.5);
        glPopMatrix();
         glPushMatrix();
       /// glTranslatef(-25,10,0);
            glTranslatef(0,-6,-25);
            glScalef(20,32,0.2);
           glColor3d(1.0, 0.0, 0.0); // red
            draw_solid_cube(0.5);
        glPopMatrix();
    glEnable(GL_TEXTURE_2D);
   /* glPushMatrix();
    glTranslatef(0,10,-25);
    glScalef(50,40,0.2);
    glColor3d(1.0, 0.0, 0.0); // red
    draw_solid_cube(1);
    glColor3f(0.4f, 0.0f, 0.0f);
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);*/


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[7]); /// texture parede / tijolinho
    glPushMatrix();
    glTranslatef(25,10,0);
    glScalef(0.2,40,50);
     glColor3d(0.0, 1.0, 0.0); // green
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]); /// texture parede / tijolinho
        glPushMatrix();
        /// glTranslatef(-25,10,0);
            glTranslatef(-25, 10,17.5);
            glScalef(0.2,80,50);
            glColor3d(0.0, 0.0, 1.0); // blue
            draw_solid_cube(0.5);
        glPopMatrix();

       /// glTranslatef(-25,10,0);
       glPushMatrix();
            glTranslatef(-25, 10,-17.5);
            glScalef(0.2,80,50);
            glColor3d(0.0, 0.0, 1.0); // blue
            draw_solid_cube(0.5);
        glPopMatrix();

        glPushMatrix();
       /// glTranslatef(-25,10,0);
            glTranslatef(-25,25,0);
            glScalef(0.2,20,20);
            glColor3d(0.0, 0.0, 1.0); // blue
            draw_solid_cube(0.5);
        glPopMatrix();
    glEnable(GL_TEXTURE_2D);




    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]); /// texture parede / tijolinho
    glPushMatrix();
    glTranslatef(0,10,25);
    glScalef(50,40,0.2);
     glColor3d(1.0, 1.0, 1.0); // white
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void draw_ceiling() // teto
{
    lighting(ceiling_no_mat,ceiling_ambient,ceiling_diffuse,ceiling_specular,ceiling_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();
    glTranslatef(0,25,0);
    glScalef(50,0.2,50);
    glColor3d(1.0, 0, 1.0);
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void draw_floor() //piso
{
    lighting(floor_no_mat,floor_ambient,floor_diffuse,floor_specular,floor_shiness);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glPushMatrix();
    glTranslatef(0,-10,0);
    glScalef(50,0.2,50);
    glColor3d(1.0, 3.0, 4.0);
    draw_solid_cube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void display(void)
{
    //glPushMatrix();
    glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,5,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
              camera_x, camera_height, camera_y,
              camera_x + cos(camera_x_angle),  camera_height, camera_y + sin(camera_y_angle),
               0, 1, 0);
   // gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
    //gluLookAt(eye_x,eye_y,eye_z,center_x,center_y,center_z,0,1,0);
    draw_table(); //4 cadeiras
    //draw_chair(0.0,0,0);
    //draw_chair(12.0,0,3);
    //draw_chair(5.0,5.8,1);
   draw_chair(6.0,10,2);

    draw_shelf();
    draw_paiting();
    draw_window();
    draw_door();
    draw_wall();
    draw_floor();
    draw_ceiling();
    draw_bed();

    //lighting in scene

    glEnable(GL_LIGHT0);
    if(ambient)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);

    }
    if(diffuse)
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
    }
    if(specular)
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    }
    else
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
    }
    glDisableClientState (GL_VERTEX_ARRAY);
   // glPopMatrix();
    glutSwapBuffers();

}
void handleKeyPressed(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
        exit(0);
    case 'a':
    case 'A':
        camera_y = camera_y - 0.5;
        //center_z = center_z - 0.5;
        break;
    case 'd':
    case 'D':
        camera_y = camera_y + 0.5;
        //center_z = center_z + 0.5;
        break;
    case 'w':
    case 'W':
        camera_x = camera_x + 0.5;
        //center_x = center_x + 0.5;
        break;
    case 'y':
        if(camera_height<15)
            camera_height = camera_height + 0.5;
        //center_x = center_x + 0.5;
        break;
    case 'Y':
        if(camera_height>-3)
            camera_height = camera_height - 0.5;
        //center_x = center_x + 0.5;
        break;
    case 's':
    case 'S':
        camera_x = camera_x - 0.5;
        //center_x = center_x - 0.5;
        break;
    case 'u':
    case 'U':
        camera_x_angle+=.15;
        camera_y_angle+=.15;
        break;
    case 'k':
    case 'K':
        break;
    case 'h':
    case 'H':
        camera_x_angle-=.15;
        camera_y_angle-=.15;
        break;
    case 'o':
        if(door_angle <= 108.0f) door_angle += 2.0f;
        glutPostRedisplay();
        break;
    case 'c':
        if(door_angle >= 2.0f) door_angle -= 2.0f;
        glutPostRedisplay();
        break;
    case 'j':
    case 'J':
        break;
    case '1':
        ambient=!ambient;
        break;
    case '2':
        diffuse=!diffuse;
        break;
    case '3':
        specular=!specular;
        break;
    }
}

static void idle(void)
{
    glutPostRedisplay();
}
void initRendering()
{
    glClearColor(1,1,1,1);

    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glCullFace(GL_BACK);
    glOrtho (-50, 50, -50, 50, -50 , 50);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

/*const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };*/

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Quarto 3D");
    initRendering();
    /**/

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    string path = (char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas";
    glGenTextures(10,texture);
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\bed_sheet.bmp", 0);  //Give full path of image else it will not work
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\wall.bmp", 1); /// textura da parede
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\ceiling.bmp", 2); /// textura teto
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\floor.bmp", 3); /// textura piso
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\table.bmp", 4); ///textura de madeira
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\shelf.bmp", 5); /// outra madeira
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\tabaco.bmp", 6); /// outra madeira
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\comamorvangogh.bmp", 7); /// outra madeira
    loadTexture((char*)"C:\\Workspace\\Computação Gráfica\\quarto3D\\assets\\texturas\\van-gogh-amendoeira-flor-d.bmp", 8); /// outra madeira

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPressed);
    glutReshapeFunc(handleResize);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
