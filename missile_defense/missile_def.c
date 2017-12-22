// missile_def.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "missile_def.h"

/* Global variables */

BITMAP *buffer ;
int curr_point = 0 ;
int total_points= 0 ;
Point points[MAX_POINTS] ;
int destroyed = 0 ;
int debug = 0 ;
int score =  0 ;
int enemy_hits = 0 ;


/* Functions definitions */

int creat_missile(Missile *m)
{
    m->x = SCREEN_W / 2 ;
    m->y = 10 ;
    m->destroyed = 0 ;
    return 1 ;
}

void doline(BITMAP *bmp , int x , int y , int d)
{
    points[total_points].x = x ;
    points[total_points++].y = y ;
}

int fire_new_missile(Missile *m)
{
    curr_point = 0 ;
    total_points = 0 ;
    destroyed = 0 ;
    m->destroyed = 0 ;
  int x1 = 2+(rand()%(SCREEN_W -2)) ;
  int x2 = 2+(rand()%(SCREEN_W -2)) ;
  int y1 = 10 ;
  int y2 = SCREEN_H-50 ;

  do_line(buffer,x1,y1,x2,y2,0,&doline);

  return 1 ;
}

int update_missile_position(Missile *m ,  BITMAP *mouse)
{

    int dx = points[curr_point].x  ;
    int dy = points[curr_point++].y  ;

    scare_mouse() ;
       rectfill(buffer,dx-6,dy-3,dx+6,dy+3,BLACK);
    // Check if missile is destroyed
    Circle missile_head  = {.x = dx , .y = dy , .r = 3} ;
    Circle mouse_gun     = {.x = mouse_x , .y = mouse_y , .r = mouse->w/2 } ;
    if(mouse_b &1)
    {
         make_explosion(screen , mouse_x , mouse_y) ;
        if(detect_circle_collison(&missile_head , &mouse_gun) )
       {
          m->destroyed = 1 ;
          destroyed = 1 ;
          curr_point = 0 ;
          total_points = 0 ;
          score++ ;
          update_score() ;
       }
       rest(20) ;
    }
    if(!destroyed)  // draw missile head and tail
      {
        putpixel(buffer , dx , dy-3 , WHITE) ;
        circlefill(buffer, dx , dy ,2, RED) ;
      }

    unscare_mouse() ;
    if(dy == SCREEN_H- 60)
    {
        make_explosion(screen , dx , dy) ;  // show firing explosions
        circlefill(buffer , dx , dy , 40 , BLACK) ;  // show damage by black on city .
        enemy_hits++ ;
         update_score() ;
        m->destroyed = 1 ;
        destroyed = 1 ;
        curr_point = 0 ;
        total_points = 0 ;
    }
    curr_point++ ;
    return 1 ;
}

int make_explosion(BITMAP *bmp , int x , int y)
{

    for(int i = 0 ; i < 15  ; i++)
    {
        int rad = 10+rand()%30 ;
        int color = makecol(rand()%255 , rand()%255,rand()%255) ;
        circlefill(bmp, x , y , rad , color) ;
        rest(3) ;
        circlefill(bmp, x , y , rad , BLACK) ;
    }
    circlefill(bmp , x , y , 17 , BLACK) ;
    return 1 ;
}

void update_score()
{
     textprintf_right_ex(buffer , font , SCREEN_W - 50 , 2 , RED , 0 , "Score : %d " , score);
     textprintf(buffer , font , 20 , 2 , RED , "Enemy hits : %d" , enemy_hits ) ;
}

int detect_circle_collison(Circle *cir1 , Circle *cir2)
{
    int dx = cir1->x - cir2->x ;
    int dy = cir1->y - cir2->y ;
    int rc2 = (cir1->r + cir2->r) * (cir1->r + cir2->r) ;
    int dc2 = (dx*dx + dy*dy) ;

    return(dc2 < rc2 ) ;
}


