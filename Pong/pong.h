#ifndef PONG_H
#define PONG_H

/* Constants */

#define RED makecol(255,0,0 )

/*Data structures */

typedef struct
{
    int x , y , spx , spy  ;
    BITMAP *bmp ;
}BALL ;

typedef struct
{
    int x , y , spx , spy  ;
    BITMAP *bmp ;
    char *name ;
}PADDLE ;

typedef struct
{
    int x , y ;
}CORDINATE ;

/*Extern global variables */

extern int enemy_score ;
extern int player_score ;

/*Functions prototypes */

int update_paddle_position( PADDLE *paddle ) ;
int update_ball_position(BALL *ball , PADDLE paddle[]);
int check_collision(PADDLE *p , BALL *b) ;
int update_score(BALL *ball) ;
#endif
