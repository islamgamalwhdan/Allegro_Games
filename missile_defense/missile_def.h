//missile_def.h

#ifndef MISSILE_DEFE_H
#define MISSILE_DEFE_H

/*Includes */

#include <allegro.h>

/*Constants */

#define BLACK 0
#define RED makecol(255,0,0)
#define WHITE makecol(255,255,255)
#define MAX_POINTS 2000

/*Data structures */

typedef struct
{
    int x , y , r ;
}Circle ;

typedef struct
{
    int x , y ;
}Point;

typedef struct
{
    int x , y , destroyed ;
}Missile ;


/* Global extern variables */

extern BITMAP *buffer ;
extern int curr_point  ;
extern int total_points;
extern Point points[MAX_POINTS] ;
extern int destroyed ;
extern int debug  ;
extern int score  ;
extern int enemy_hits  ;

/* Functions prototypes */

int creat_missile(Missile *m) ;
int fire_new_missile(Missile *m) ;
int update_missile_position(Missile *m , BITMAP *mouse) ;
int Is_missile_destroyed(Missile *m) ;
int detect_circle_collison(Circle *cir1 , Circle *cir2) ;
void doline(BITMAP *bmp , int x , int y , int d) ;
int make_explosion(BITMAP *bmp , int x , int y) ;
void update_score() ;



#endif