#include <stdio.h>

#include <allegro.h>

#include "missile_def.h"

int main()
{
    allegro_init() ;
    install_keyboard() ;
    install_mouse() ;
    install_timer() ;
     set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN , 640 , 480 , 0 , 0) ;
    srand(time(NULL)) ;

    buffer = create_bitmap(640,480);

    BITMAP *myCity = load_bitmap("city.bmp" , NULL) ;

    for(int i = 0 ;  i< 5 ; i++)
    {
        masked_blit(myCity , buffer , 0 , 0 , 50+120*i , SCREEN_H-64 , myCity->w , myCity->h) ;
    }
    rect(buffer , 1 , 1 , SCREEN_W-1 , SCREEN_H-1 , RED) ;
    BITMAP *crosshair = load_bitmap("crosshair.bmp", NULL);
    set_mouse_sprite(crosshair);
    set_mouse_sprite_focus(15,15);
    show_mouse(buffer);

    Missile missile1 ;
    creat_missile(&missile1) ;
    fire_new_missile(&missile1) ;
    update_score(score) ;
    while(!key[KEY_ESC])
    {
        if(missile1.destroyed)
        {
           destroyed=1;
           fire_new_missile(&missile1) ;
        }
        update_missile_position(&missile1 , crosshair) ;
        if(enemy_hits == 5)
        {
            textout_centre(screen , font , "GAME OVER !!" , SCREEN_W/2 , SCREEN_H/2 , RED) ;
            rest(5000) ;
            break ;
        }
        blit(buffer,screen,0,0,0,0,640,480);
        rest(10) ;
    }
     set_mouse_sprite(NULL);
    destroy_bitmap(myCity);
    destroy_bitmap(crosshair);
    allegro_exit() ;
    return 0 ;
}
END_OF_MAIN()
