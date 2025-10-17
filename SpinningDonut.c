#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 70
#define HEIGHT WIDTH/2
#define TDFS 7 //torus distance from screen
#define DOEFS 50 //distance of eye from screen
#define TORUS_RADIUS 10
#define TORUS_WIDTH 4
#define DEGREE_INCREMENT 0.009 //one degree in radiants
#define TPI 6.2831 //2pi

#define DDS '*' //default donut symbol

typedef signed short sshort;
typedef struct {
    double x;
    double y;
    double z;
} Cords_t;

char ** configure_points(float A, float B);
void print_matrix(char **);
Cords_t transform_coordinates(Cords_t cord);

int main(void) {
    char ** screen = configure_points(0.0,0.0);
    print_matrix(screen);
    return 0;
}

Cords_t transform_coordinates(Cords_t cord) {
    cord.x = (int) WIDTH/2 + (DOEFS/(DOEFS+cord.z)*cord.x);
    cord.y = (int) HEIGHT/2 - (DOEFS/(DOEFS+cord.z)*cord.y);

    return cord;
}

void print_matrix(char ** matrix) {
    for (int y = 0; y<HEIGHT; y++) {
        puts("");
        for (int x = 0; x<WIDTH; x++) printf("%c", matrix[y][x]);
    }
}

//function that calculated where each point is plotted
char ** configure_points(float A, float B){
    //precompute (not yet)
    double costheta, sintheta, cosw, sinw, w_increment, theta_increment;
    Cords_t at_point_cords, screen_cords;

    w_increment = DEGREE_INCREMENT;
    theta_increment = DEGREE_INCREMENT;

    char ** screen = calloc(HEIGHT+1, sizeof(char*)); //create a screen with the apropriate number of rows
    for (int i = 0; i<HEIGHT; i++){
        screen[i] = calloc(WIDTH+1, sizeof(char)); //for each row allocate corrent number of chars
        for (int j = 0; j<WIDTH; j++) screen[i][j] = ' '; //fill in each char with blank
    }

    for (double theta = 0; theta<TPI; theta += theta_increment){
        costheta = cos(theta); //precomputing variables for 360 w cycles
        sintheta = sin(theta);

        for (double w = 0; w<TPI; w += w_increment){
            cosw = cos(w); //neat mulitple uses
            sinw = sin(w);

            at_point_cords.x = costheta*(TORUS_WIDTH*cosw+TORUS_RADIUS); //one round just yet
            at_point_cords.y = sintheta*(TORUS_WIDTH*cosw+TORUS_RADIUS);
            at_point_cords.z = TORUS_WIDTH*sinw + TDFS;

            screen_cords = transform_coordinates(at_point_cords);

            //printf("%lf, %lf\n", at_point_cords.x, at_point_cords.y);

            if (screen_cords.y >= 0 && screen_cords.y < HEIGHT && screen_cords.x >= 0 && screen_cords.x < WIDTH) screen[(int) screen_cords.y][(int) screen_cords.x] = DDS;}
    }

    return screen;
}