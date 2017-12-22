#ifndef TANK_WAR_H
#define TANK_WAR_H


#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

                      /*CONSTANTS */

#define GREEN 10
#define BLUE  9
#define BLACK 0
#define YELLOW 14
#define WHITE makecol(255 , 255  , 255)
#define TURRET_COLOR makecol( 220 , 98 , 16 )
#define MAX_BULLETS 30

                   /* Data structures */

typedef enum { NEGATIVE =-1 , NORTH , NO_ES ,  EAST , SO_EA ,  SOUTH , SO_WE , WEST  , NO_WE }Direction ;

typedef struct
{
    int x , y ;
}CORDINATES ;

typedef struct
{
    CORDINATES p_min , p_max ;
}OBJ_RECT_COR ;

typedef struct bullet_tag
{
    int x , y ;
    int speed ;
    int active  ;
    Direction dir ;
}BULLET ;

typedef struct
{
   volatile char *forward , *back;
   volatile char *left , *right;
   volatile char *fire ;

}TANK_CTRL ;

typedef struct tank_tag
{
    int x , y ;   ;
    OBJ_RECT_COR ob_cor ;
    Direction dir ;
    int xspeed , yspeed  , score ;
    BITMAP *tank_bmp[8] ;

    // Control buttons
    TANK_CTRL control ;

    //Bullets
    BULLET bullet[MAX_BULLETS] ;
    BITMAP *bullet_bmp ;
    int bullet_index ;
}TANK ;



           /*Functions Prototypes */


int video_init() ;
TANK* create_tank(BITMAP *bmp , BITMAP *b_bmp , int x , int y , TANK_CTRL *ctrl ) ;
void destroy_tank(TANK* t) ;
int draw_tank( TANK *tank  ) ;
int earse_tank( TANK *tank ) ;
int check_Tochage_dir(TANK *tank );
int checkTomove(TANK *tank) ;
int draw_bullet(TANK *tank) ;
int checkFire(TANK *tank) ;
int check_bullet_collision( TANK *t  , OBJ_RECT_COR *obj_cor , BITMAP *ex_bmp) ;
void explode(BULLET *b , BITMAP *ex_bmp ) ;

#endif