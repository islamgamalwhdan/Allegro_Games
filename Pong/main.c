//main .c

#include <stdio.h>
#include <math.h>

#include <allegro.h>

#include "pong.h"

int main()
{
    allegro_init()     ;
    install_keyboard() ;
    install_mouse()    ;
    install_timer()    ;
    set_color_depth(16) ;
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN , 640 , 480 , 0 , 0) ;
    install_joystick(JOY_TYPE_AUTODETECT) ;
    poll_joystick() ;


    BITMAP *backgroud_bmp = load_bitmap("background.bmp" , NULL) ;
    blit(backgroud_bmp , screen , 0 , 0 , 0 , 0 , backgroud_bmp->w , backgroud_bmp->h) ;

    BITMAP *ball_bmp = load_bitmap("ball.bmp" , NULL) ;
    BALL ball = {.x = SCREEN_W/2 , .y = SCREEN_H/2 , .spx = 4 , .spy = 4 , .bmp = ball_bmp} ;

    //masked_blit(ball.bmp , screen , 0 , 0 , ball.x , ball.y , ball.bmp->w , ball.bmp->h ) ;

    BITMAP *paddle_bmp = load_bitmap("paddle.bmp" , NULL) ;
    PADDLE paddle[2] ={ { .x = (SCREEN_W-paddle_bmp->w)/2 , .y = SCREEN_H-paddle_bmp->h , .bmp=paddle_bmp , .spx = 7 , .spy = 7, .name = "paddle1" } ,
                        { .x = (SCREEN_W-paddle_bmp->w)/2 , .y = 1 , .bmp=paddle_bmp , .spx = 7 , .spy = 7 ,.name = "paddle2"}
                      } ;
    while(!key[KEY_ESC])
    {
        poll_joystick() ;
        blit(backgroud_bmp, screen , 0 , 0 , 0 , 0 , backgroud_bmp->w , backgroud_bmp->h) ;
        update_ball_position(&ball , paddle);
        update_score(&ball) ;
        update_paddle_position(paddle) ;


        for(int i = 0 ; i< 2 ; i++)
             masked_blit(paddle[i].bmp , screen , 0 , 0 , paddle[i].x , paddle[i].y , paddle[i].bmp->w , paddle[i].bmp->h ) ;

        masked_blit(ball.bmp , screen , 0 , 0 , ball.x , ball.y , ball.bmp->w , ball.bmp->h );
       rest(20) ;
    }
    destroy_bitmap(ball_bmp) ;
    destroy_bitmap( paddle_bmp ) ;
    destroy_bitmap(backgroud_bmp) ;
    allegro_exit() ;
    return 0;
}
END_OF_MAIN()
