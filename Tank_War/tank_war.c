// tank_war.c

                 /*Includes*/

#include <allegro.h>

#include "tank_war.h"


                /*Functiond definitions */
int video_init()
{
    allegro_init() ;
    install_keyboard() ;
    install_timer() ;

    set_color_depth(32);
   if(set_gfx_mode(GFX_AUTODETECT_WINDOWED , 640 , 480 , 0 , 0) )
    {
        allegro_message(allegro_error) ;
        return -1 ;
    }

    return 1 ;
}

TANK* create_tank(BITMAP *bmp , BITMAP *b_bmp , int x , int y ,TANK_CTRL *ctrl )
{
    TANK *tank = malloc(sizeof(TANK)) ;
    tank->x = x;
    tank->y = y;
    tank->xspeed = tank->yspeed = 3 ;
    tank->dir = NORTH ;
    tank->bullet_index = 0 ;
    tank->score = 0 ;

    //set 4 rectangle points
    tank->ob_cor.p_min.x = x ;
    tank->ob_cor.p_min.y = y ;
    tank->ob_cor.p_max.x = x + bmp->w ;
    tank->ob_cor.p_max.y = y + bmp->h ;

    for(Direction i = NORTH ; i <= NO_WE  ; i++)
  {
        tank->tank_bmp[i] = create_bitmap(bmp->w , bmp->h) ;
        clear_bitmap(tank->tank_bmp[i]) ;
        rotate_sprite( tank->tank_bmp[i] , bmp , 0 , 0 , itofix(i*32) ) ;
  }

    /*Create bullets */
    tank->bullet_bmp = b_bmp ;
    for(int i = 0 ; i < MAX_BULLETS ; i++)
    {
        tank->bullet[i].active = 0 ;
        tank->bullet[i].speed = 4  ;
    }

    /* Set control buttons */
    tank->control.forward = ctrl->forward ;
    tank->control.back = ctrl->back ;
    tank->control.left = ctrl->left ;
    tank->control.right = ctrl->right ;
    tank->control.fire = ctrl->fire ;
  return tank ;
}


void destroy_tank(TANK *t)
{
    if( t )
    {
        /*destroy tank bitmap directions */
        for(Direction i = NORTH ; i<= NO_WE ; i++ )
        {
            if(t->tank_bmp[i])
                destroy_bitmap(t->tank_bmp[i]) ;
        }

        /*destroy bullets bitmap */
        destroy_bitmap(t->bullet_bmp) ;

        free(t) ;
    }
}


int earse_tank( TANK *tank )
{
    int x = tank->x ;
    int y = tank->y ;

    rectfill( screen , x , y , x+tank->tank_bmp[tank->dir]->w , y+tank->tank_bmp[tank->dir]->w  , BLACK ) ;
    return 1 ;
}


int check_Tochage_dir(TANK *tank )
{
    int change = 0 ;

    if(*(tank->control.right))
    {
        tank->dir++ ;
        if(tank->dir > NO_WE)
            tank->dir = NORTH ;
        change =1 ;
        while(*(tank->control.right)) ;
    }

    if(*(tank->control.left))
    {
        tank->dir-- ;
        if(tank->dir < NORTH)
            tank->dir = NO_WE ;
        change =1 ;
        while(*(tank->control.left)) ;
    }

    return change ;
}

int checkTomove(TANK *tank )
{
    // check moving in which axis ?
    Direction dir = tank->dir ;
    int spx = tank->xspeed ;
    int spy = tank->yspeed ;

    int change = 0 ;

    char forward = *(tank->control.forward) ;
    char back = *(tank->control.back) ;
    // check moving Forward or backward ?
    if( forward || back )
  {
      change = 1 ;
     earse_tank(tank) ;
     if(back)
     {
         spx *= -1 ;
         spy *= -1 ;
     }

     switch(dir)
     {
     case NORTH :
        {
            tank->y -= spy ;
            break ;
        }
     case NO_ES :
        {
            tank->x += spx ;
            tank->y -= spy ;
            break ;
        }
     case EAST :
        {
            tank->x += spx ;
            break ;
        }
     case SO_EA :
        {
            tank->x += spx ;
            tank->y += spy ;
            break ;
        }
     case SOUTH :
         {
             tank->y += spy ;
             break ;
         }
     case SO_WE :
        {
            tank->x -= spx;
            tank->y += spy ;
            break ;
        }
     case WEST :
        {
            tank->x -= spx ;
            break ;
        }
     case NO_WE :
        {
            tank->x -= spx;
            tank->y -= spy ;
            break ;
        }
     default:
        {
            allegro_message("Wrong direction data") ;
            return -1 ;
        }
     }//End switch
  }//end if

    //adjust boundaries
    if(tank->x > ( SCREEN_W -tank->tank_bmp[dir]->w )  )  tank->x = SCREEN_W -tank->tank_bmp[dir]->w ;
    if(tank->x < 0 )                 tank->x = 0  ;
    if(tank->y >  (SCREEN_H -tank->tank_bmp[dir]->h)  )   tank->y =  SCREEN_H -tank->tank_bmp[dir]->h ;
    if(tank->y < 0 )                 tank->y = 0 ;

    // update object coordinates values
    tank->ob_cor.p_min.x = tank->x;
    tank->ob_cor.p_min.y = tank->y ;
    tank->ob_cor.p_max.x = tank->x + tank->tank_bmp[dir]->w ;
    tank->ob_cor.p_max.y = tank->y + tank->tank_bmp[dir]->h ;
    return change ;
}

int draw_bullet(TANK *tank)
{

  for(int i = 0  ; i<tank->bullet_index ; i++)
 {
   if( tank->bullet[i].active)
   {
    Direction dir = tank->bullet[i].dir ;
    int bullet_speed = tank->bullet[i].speed ;
    int x = tank->bullet[i].x ;
    int y = tank->bullet[i].y ;

    rectfill( screen , x,y , x+tank->bullet_bmp->w , y+tank->bullet_bmp->h ,  BLACK ) ;

       switch(dir)
       {
       case NORTH :
        {
            y -= bullet_speed ;
            break ;
        }
        case NO_ES :
        {
            x += bullet_speed ;
            y -= bullet_speed ;
            break ;
        }
        case EAST :
        {
            x += bullet_speed ;
            break ;
        }
        case SO_EA :
        {
            x += bullet_speed ;
            y += bullet_speed ;
            break ;
        }
        case SOUTH :
        {
            y += bullet_speed ;
            break ;
        }
        case SO_WE :
        {
            x -= bullet_speed ;
            y += bullet_speed ;
            break ;
        }
        case WEST :
        {
            x -= bullet_speed ;
            break ;
        }
        case NO_WE :
        {
            x -= bullet_speed ;
            y -= bullet_speed ;
            break ;
        }
        default:
            allegro_message("Direction error !!") ;
            return -1 ;
       }

      // bullet boundaries
      if(x > SCREEN_W || x <0 || y> SCREEN_H || y< 0 )
      {
          tank->bullet[i].active = 0 ; // kill bullet
          rectfill( screen , x,y , x+tank->bullet_bmp->w , y+tank->bullet_bmp->h ,  BLACK ) ;
          return 1 ;
      }
      tank->bullet[i].x = x ;
      tank->bullet[i].y = y ;

      draw_sprite(screen , tank->bullet_bmp , x , y) ;
   }//end if
 }//end for
    return 1 ;
}

int checkFire( TANK *tank )
{
    int fire = 0;
    if(*(tank->control.fire))
    {
        if(tank->bullet_index == MAX_BULLETS )
        {
            allegro_message("No ammo !!") ;
            return 0 ;
        }
        Direction dir = tank->dir ;

        fire = 1 ;
        tank->bullet[tank->bullet_index].active = 1 ;
        tank->bullet[tank->bullet_index].dir = dir ;

        // Adjust the ready bullet coordinates to be ready to fire ( draw)
        int w = tank->tank_bmp[dir]->w ;
        int h = tank->tank_bmp[dir]->h ;

        CORDINATES cor[8] = {
         {tank->x + w/2 -3   , tank->y -6 } ,//NORTH
         {tank->x + w-6  , tank->y+6 } ,    //NORTH-EAST
         {tank->x + w-6  , tank->y + h/2 } ,  //EAST
         { tank->x + w-6 , tank->y + h-6 } ,//SOUTH-EAST
         {tank->x + w/2 -3    , tank->y + h-6 } ,//SOUTH
         { tank->x + 6   , tank->y + h-6 } ,//SOUTH-WEST
         {tank->x -6    , tank->y + h/2 -3 } ,//WEST
         {tank->x + 6    , tank->y -6  }    //NORTH-WEST
                            } ;

         tank->bullet[tank->bullet_index].x = cor[dir].x ;
         tank->bullet[tank->bullet_index].y = cor[dir].y ;
         tank->bullet_index ++ ;
         while(*(tank->control.fire)) ;// wait until the current fire key released .
  }//if
    return fire ;
}


int check_bullet_collision( TANK *t  , OBJ_RECT_COR *obj_cor , BITMAP *ex_bmp)
{
    int obx_min = obj_cor->p_min.x ;
    int obx_max = obj_cor->p_max.x ;
    int oby_min = obj_cor->p_min.y ;
    int oby_max = obj_cor->p_max.y ;

    for( int i = 0 ; i < t->bullet_index ; i++)

  {
      if( t->bullet[i].active )
    {
           int x = t->bullet[i].x ;
           int y = t->bullet[i].y ;
           CORDINATES bullet_cor[4] = {
                      {x , y} , { x+t->bullet_bmp->w , y }  , { x+t->bullet_bmp->w  , y+t->bullet_bmp->h  } , { x , y+t->bullet_bmp->h }
                                      } ;
          for(int j = 0 ; j< 4 ; j++)
    {
        if( (bullet_cor[j].x  > obx_min) &&( bullet_cor[j].x < obx_max )&& ( bullet_cor[j].y  > oby_min) &&( bullet_cor[j].y < oby_max))
            {
                explode(&(t->bullet[i]) , ex_bmp) ;
                return 1 ;
            }
    }//inner for loop
   }//if
  }//outer loop
  return 0 ;
}

void explode(BULLET *b , BITMAP *ex_bmp )
{
    rectfill(screen , b->x , b->y , b->x , b->y ,BLACK ) ; //clear bullet .
     b->active = 0 ;
    for(int i = 0 ; i <5 ; i++)
    {
        draw_sprite( screen , ex_bmp , b->x -rand()%5 , b->y -rand()%5 ) ;
        rest(10) ;
        rectfill(screen ,b->x , b->y , b->x + ex_bmp->w , b->y + ex_bmp->h , BLACK  ) ;
    }
}
