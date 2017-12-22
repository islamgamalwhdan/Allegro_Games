//Pong.c

/*Includes */

#include <stdio.h>
#include <math.h>

#include <allegro.h>

#include "pong.h"

/*Global variables */

int enemy_score = 0  , player_score = 0;

/*Functions definitions */

int update_paddle_position( PADDLE paddle[] )
{
    for(int i = 0 ; i <2  ;i++)
    {
        int d1x = joy[i].stick[0].axis[0].d1 ; // x negative direction
        int d2x = joy[i].stick[0].axis[0].d2 ; // x positive direction
        int d1y = joy[i].stick[0].axis[1].d1 ; // y negative direction
        int d2y = joy[i].stick[0].axis[1].d2 ; // y positive direction
        int paddlex = paddle[i].x ;
        int paddley = paddle[i].y ;

        paddlex += (i== 0)? paddle[i].spx * ( d2x || key[KEY_RIGHT]): paddle[i].spx * ( d2x || key[KEY_6_PAD] ) ;
        paddlex -= (i== 0)? paddle[i].spx * ( d1x || key[KEY_LEFT] ): paddle[i].spx * ( d1x || key[KEY_4_PAD] ) ;
        paddley += (i== 0)? paddle[i].spy * ( d2y || key[KEY_DOWN] ): paddle[i].spx * ( d2y || key[KEY_2_PAD] ) ;
        paddley -= (i== 0)? paddle[i].spy * ( d1y || key[KEY_UP] )  : paddle[i].spx * ( d1y || key[KEY_8_PAD] ) ;

        if(paddlex > SCREEN_W -paddle[i].bmp->w-1)
        {
            paddlex = SCREEN_W - paddle[i].bmp->w -1 ;
        }
        if(paddlex < 1)
        {
            paddlex =  1 ;
        }

        if(paddley > SCREEN_H -paddle[i].bmp->h-1)
        {
            paddley = SCREEN_H - paddle[i].bmp->h -1 ;
        }
        if(paddley <   1)
        {
            paddley =   1 ;
        }

        paddle[i].x = paddlex ;
        paddle[i].y = paddley ;
    }
        return 1 ;
}


int update_ball_position(BALL *ball , PADDLE paddle[])
{
    int x = ball->x ;
    int y = ball->y ;
    int spx = ball->spx ;
    int spy = ball->spy ;

    x += spx ;

    if(x> SCREEN_W-ball->bmp->w || x<0)
    {
        spx *= -1 ;
        x = (x<0)? x : SCREEN_W-ball->bmp->w -1 ;
    }

    y += spy ;
    if( y > SCREEN_H - ball->bmp->h || y< 0)
    {
        /* Update score value */
        if( y< 0 )
            ++player_score ;
        else
            ++enemy_score ;
        spy *= -1 ;
        y = (y<0)? 0: SCREEN_H - ball->bmp->h- 1 ;

    }
    ball->x = x ;
    ball->y = y ;
    ball->spx = spx ;
    ball->spy = spy ;

    /* Detect ball collision with paddle */

    check_collision(&paddle[0] , ball);
    check_collision(&paddle[1] , ball);

    return 1 ;
}

int check_collision(PADDLE *p , BALL *b)
{
    CORDINATE ball_cor[4] = { {b->x , b->y} , { b->x+ b->bmp->w , b->y } , { b->x+b->bmp->w , b->y + b->bmp->h } , {b->x , b->y + b->bmp->h} } ;

    /* Paddle rectangle boundaries */

    int px_min = p->x;
    int px_max = px_min + p->bmp->w ;
    int py_min = p->y ;
    int py_max = py_min + p->bmp->h ;

    for(int j = 0 ; j < 4 ; j++)
    {
        if(key[KEY_SPACE] &&p->name[6] == '2')//paddle2
            allegro_message("paddle min_x = %d  , max_x = %d , ball_x = %d , paddle_miny = %d , max_y=%d , ball_y = %d   "
                            , px_min, px_max , ball_cor[j].x , py_min , py_max,  ball_cor[j].y);
        if( (ball_cor[j].x > px_min)&& (ball_cor[j].x < px_max) && (ball_cor[j].y > py_min) && (ball_cor[j].y < py_max)  )
        {
            b->spy *= -1 ;

            return 1 ;

        }
    }
    return 0 ;
}

int update_score(BALL *ball)
{
    textprintf_right_ex(screen , font , SCREEN_W/2 , 2 , RED , 0 , "Enemy Score = %d " , enemy_score ) ;
    textprintf_right_ex(screen , font , SCREEN_W - 50 , 2 , RED , 0 , "Player Score = %d " , player_score ) ;
    return 1 ;
}