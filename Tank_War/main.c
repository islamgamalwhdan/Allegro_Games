#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "tank_war.h"

int main()
{
    video_init() ;

    BITMAP *tank_bmp1 =  load_bitmap("tank1.bmp"   , NULL) ;
    BITMAP *tank_bmp2 =  load_bitmap("tank2.bmp"   , NULL) ;
    BITMAP *bullet_bmp1 = load_bitmap("bullet.bmp" , NULL) ;
    BITMAP *bullet_bmp2 = load_bitmap("bullet.bmp" , NULL) ;
    BITMAP *explode_bmp = load_bitmap("explode.bmp", NULL) ;

    TANK_CTRL t1_ctrl = { .forward = &key[KEY_W] , .back = &key[KEY_S] ,
                       .left = &key[KEY_LEFT] , .right = &key[KEY_RIGHT]  ,.fire = &key[KEY_SPACE] } ;

     TANK_CTRL t2_ctrl = { .forward = &key[KEY_Q] , .back = &key[KEY_A] ,
                       .left = &key[KEY_4_PAD] , .right = &key[KEY_6_PAD]  ,.fire = &key[KEY_ENTER] } ;

    TANK *tank1  = create_tank(tank_bmp1 , bullet_bmp1 , 0,0 , &t1_ctrl) ;
    TANK *tank2 =  create_tank(tank_bmp2 , bullet_bmp2 , SCREEN_W/2 , SCREEN_H/2 , &t2_ctrl) ;

    while(!key[KEY_ESC])
    {
         check_Tochage_dir(tank1) ;
         check_Tochage_dir(tank2) ;

        checkTomove(tank1) ;
        checkTomove(tank2) ;

        draw_sprite(screen,tank1->tank_bmp[tank1->dir] ,  tank1->x , tank1->y ) ;
        draw_sprite(screen,tank2->tank_bmp[tank2->dir] ,  tank2->x , tank2->y ) ;

        checkFire(tank1) ;
        checkFire(tank2) ;
        draw_bullet(tank1) ;
        draw_bullet(tank2) ;

       check_bullet_collision(tank1 , &tank2->ob_cor , explode_bmp ) ;
       check_bullet_collision(tank2 , &tank1->ob_cor , explode_bmp ) ;
       rest(5) ;
    }
    destroy_tank(tank1) ;
    destroy_tank(tank2) ;
    allegro_exit() ;
    return 0;
}
END_OF_MAIN()


