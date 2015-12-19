//
//  main.c
//  GLTest
//
//  Created by Pouya Kary on 9/26/15.
//  Copyright (c) 2015 Pouya Kary. All rights reserved.
//



/* ──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────── *
 * :::::::::::::::::::::::::::::::::::::::::::: T H E   K A R Y   S T O P P E R ::::::::::::::::::::::::::::::::::::::::::: *
 * ──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────── */


//
// ────────────────────────────────────────────────────────────── 1 ─────────
//  :::::: D E F I N I T I O N S : :  :  :   :     :        :          :
// ───────────────────────────────────────────────────────────────────────
//


//
// ─── LIBRARIES ────────────────────────────────────────────────────────────────────────────
//

    #ifdef __APPLE__

        #include <GLUT/glut.h>
        #include <stdlib.h>

    #else

        #include <GL/glut.h>

    #endif

    #include <math.h>

    #include <time.h>

    #include <iostream>


//
// ─── CONSTANTS ────────────────────────────────────────────────────────────────────────────
//

    //
    // ─── SCREEN SIZES ───────────────────────────────────────────────────────────────
    //

        const int       screen_width                    = 800;

        const int       screen_height                   = 500;

    //
    // ─── PAD SETTINGS ───────────────────────────────────────────────────────────────
    //

        const GLfloat   pad_width_half                  = 0.01f;

        const GLfloat   pad_height_half                 = 0.15f;

        const GLfloat   pad_spacing_from_half_line      = 0.15f;


    //
    // ─── BALL SETTINGS ──────────────────────────────────────────────────────────────
    //

        const GLfloat   ball_width                      = 0.05f;

        const GLfloat   ball_heigt                      = 0.1f;


    //
    // ─── HALF LINE SIZES ────────────────────────────────────────────────────────────
    //

        const GLfloat   half_line_blocks_width          = 0.005f;

        const GLfloat   half_line_blocks_height         = 0.008f;

        const GLfloat   half_line_blocks_spacing        = half_line_blocks_height * 10;

        const GLfloat   half_line_spacing_from_center   = 0.4f;


    //
    // ─── LINE BAR ───────────────────────────────────────────────────────────────────
    //

        const GLfloat   line_color                      = 0.6f;


    // ────────────────────────────────────────────────────────────────────────────────





//
// ─── GLOBAL VARIABLES ─────────────────────────────────────────────────────────────────────
//

    //
    // ─── USER INFO ──────────────────────────────────────────────────────────────────
    //

        GLfloat mouse_glut_x_position                   = 0.0f;

        GLfloat mouse_glut_y_position                   = 0.0f;

    //
    // ─── BALL INFO ──────────────────────────────────────────────────────────────────
    //

        GLfloat         ball_speed                      = 0.03;

        GLfloat         ball_positions_x                = -2.0f;

        GLfloat         ball_positions_y                = 0.0f;

    //
    // ─── GAME INFO ──────────────────────────────────────────────────────────────────
    //

        int             life_count                      = 0;

        int             game_cycles                     = 0;

        const GLfloat   life_bar_height                 = 0.03f;


    // ────────────────────────────────────────────────────────────────────────────────


//
// ─── FRAMEWORK ────────────────────────────────────────────────────────────────────────────
//

    GLfloat mouse_x_to_opengl_coordinates( int x );

    GLfloat mouse_y_to_opengl_coordinates( int y );

    void    display();


// ──────────────────────────────────────────────────────────────────────────────────────────





//
// ────────────────────────────────────────────────────────── 3 ─────────
//  :::::: R E N D E R E R S : :  :  :   :     :        :          :
// ───────────────────────────────────────────────────────────────────
//


//
// ─── PONG'S PAD  ──────────────────────────────────────────────────────────────────────────
//

    void draw_pong_pad( GLfloat x , GLfloat y ) {
        
        glColor3f( 0.533333f , 0.686275f , 0.819608f );
    
        glBegin( GL_POLYGON );
    
            glVertex2f( x - pad_width_half , y + pad_height_half );
     
            glVertex2f( x + pad_width_half , y + pad_height_half );
    
            glVertex2f( x + pad_width_half , y - pad_height_half );
    
            glVertex2f( x - pad_width_half , y - pad_height_half );
    
        glEnd();
    
    }


//
// ─── HALF LINE ────────────────────────────────────────────────────────────────────────────
//

    void draw_half_line ( ) {
        
        // - - - - -
        
        glColor3f( 0.556863f , 0.317647f , 0.749020f );
        
        // - - - - -
    
        for ( GLfloat counter = -1 ; counter < 1 ; counter += half_line_blocks_spacing ) {
            
            glBegin( GL_POLYGON );
            
                glVertex2f( half_line_spacing_from_center - half_line_blocks_width , counter + half_line_blocks_height );
            
                glVertex2f( half_line_spacing_from_center + half_line_blocks_width , counter + half_line_blocks_height );
            
                glVertex2f( half_line_spacing_from_center + half_line_blocks_width , counter - half_line_blocks_height );
            
                glVertex2f( half_line_spacing_from_center - half_line_blocks_width , counter - half_line_blocks_height );
            
            glEnd( );
            
        }
        
        // - - - - -
        
        glColor3f( 1 , 1 , 1 );
    
    }

// ────────────────────────────────────────────────────────────────────────────────────────


    void draw_life_count( ) {
        
        glColor3f( line_color , line_color , line_color );
    
        GLfloat life_lenght = (GLfloat)life_count * 0.5f;
        
        glBegin( GL_POLYGON );
            
            glVertex2f( -1.0f           , 1.0f                     );
        
            glVertex2d( 1 - life_lenght , 1.0f                     );
        
            glVertex2f( 1 - life_lenght , 1.0f - life_bar_height   );
        
            glVertex2f( -1.0f           , 1.0f - life_bar_height   );
        
        glEnd();
    
    }


// ────────────────────────────────────────────────────────────────────────────────────────


    void print_score() {
        
        system( "clear" );
        
        std::cout                                                               << std::endl;
        
        std::cout << "   ──────────────────────────────────────────────────"    << std::endl;
        
        std::cout << "      Y O U R   S C O R E   I S : " << game_cycles        << std::endl;
        
        std::cout << "   ──────────────────────────────────────────────────"    << std::endl;
        
        std::cout                                                               << std::endl;
    
    }


// ────────────────────────────────────────────────────────────────────────────────────────






//
// ────────────────────────────────────────────────── 4 ─────────
//  :::::: L O G I C : :  :  :   :     :        :          :
// ───────────────────────────────────────────────────────────
//


//
// ─── MAIN DISPLAY RENDERER ────────────────────────────────────────────────────────────────
//

    void display( ) {
        
        // - - - - -
    
        glClear( GL_COLOR_BUFFER_BIT );
        
        // - - - - -
        
        draw_half_line( );

        draw_pong_pad( half_line_spacing_from_center + pad_spacing_from_half_line , mouse_glut_y_position );

    }


//
// ─── USER INPUTS ──────────────────────────────────────────────────────────────────────────
//

    void mouse ( int x , int y ) {

        mouse_glut_x_position = mouse_x_to_opengl_coordinates( x );
        
        mouse_glut_y_position = mouse_y_to_opengl_coordinates( y );
    
    }


// ────────────────────────────────────────────────────────────────────────────────────────


    void keyboard ( unsigned char key , int x , int y ) {
        
        //
        // 101 IS THE ASCII FOR 'E' IN LOWERCASE
        //
        
        if ( key == 101 ) exit( 0 );
        
    }


// ────────────────────────────────────────────────────────────────────────────────────────


    void update_ball( GLfloat x , GLfloat y ) {
        
        glColor3f( 0.207843f , 0.584314f , 0.137255f );
        
        glBegin( GL_POLYGON );
        
            glVertex2f( x - ball_width , y + ball_heigt );
        
            glVertex2f( x + ball_width , y + ball_heigt );
        
            glVertex2f( x + ball_width , y - ball_heigt );
        
            glVertex2f( x - ball_width , y - ball_heigt );
        
        glEnd();
    
        
    }


// ────────────────────────────────────────────────────────────────────────────────────────


    bool isPadCuttingTheBall( ) {
        
        // - - - - -
    
        if ( ball_positions_x < pad_spacing_from_half_line + half_line_spacing_from_center - ball_width ) {
            
            return false;
            
        }
        
        // - - - - -
        
        if ( ball_positions_y < mouse_glut_y_position - pad_height_half ) {
            
            return false;
            
        }
        
        // - - - - -
        
        if ( ball_positions_y > mouse_glut_y_position + pad_height_half ) {
            
            return false;
            
        }
        
        // - - - - -
        
        return true;
    
    }


// ────────────────────────────────────────────────────────────────────────────────────────


    void update_y_position_randomly( ) {
        
        // - - - - -
    
        ball_positions_y = 1.0f - ( GLfloat )( ( GLfloat )( rand() % 20 ) / 10.0f );
        
        // - - - - -
        
        game_cycles++;
        
        print_score();
        
        if ( game_cycles % 10 == 0 ) {
            
            ball_speed += 0.001;
            
        }
    
    }


// ────────────────────────────────────────────────────────────────────────────────────────


    void update_ball_positions( ) {
        
        // - - - -
    
        update_ball( ball_positions_x , ball_positions_y );
        
        // - - - - -
        
        if ( ball_positions_x > 1.0f ) {
            
            // - - - - -
            
            ball_positions_x = -2.0f;
            
            update_y_position_randomly( );
            
            // - - - - -
            
            life_count++;
            
            if ( life_count == 4 ) {
                
                exit( 0 );
                
            }
        
        }
    
        ball_positions_x += ball_speed;
        
        // - - - - -
        
        if ( isPadCuttingTheBall() ) {
            
            ball_positions_x = -1.3f;
            
            update_y_position_randomly( );
            
        }
        
    }


// ────────────────────────────────────────────────────────────────────────────────────────


    void background_animation ( ) {
        
        update_ball_positions();
        
        draw_life_count();
        
        glSwapAPPLE();
        
        glutPostRedisplay();
    
    }


// ────────────────────────────────────────────────────────────────────────────────────────





//
// ──────────────────────────────────────────────────────── 5 ─────────
//  :::::: S E T U P E R S : :  :  :   :     :        :          :
// ─────────────────────────────────────────────────────────────────
//


//
// ─── OPENGL SETUP ────────────────────────────────────────────────────────────────────────
//

    void init ( ) {
        
        // - - - - -
        
        glutSetCursor( GLUT_CURSOR_NONE );
        
        // - - - - -

        glClearColor( 0.0 , 0.0 , 0.0 , 1.0 );
    
        glColor3f( 1.0 , 1.0 , 1.0 );
        
        // - - - - -
    
        glMatrixMode( GL_PROJECTION );
        
        // - - - - -
    
        glLoadIdentity( );
        
        // - - - - -
    
        gluOrtho2D( -1.0 , 1.0 , -1.0 , 1.0 );
    
    }

//
// ─── MAIN ─────────────────────────────────────────────────────────────────────────────────
//

    int main ( int argc , char ** argv ) {
        
        // - - - - -
        
        system( "clear" );
        
        // - - - - -
    
        glutInit( &argc , argv );
        
        // - - - - -
    
        glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
        
        // - - - - -
    
        glutInitWindowSize( screen_width , screen_height );
    
        glutInitWindowPosition( 100 , 100 );
        
        // - - - - -
    
        glutCreateWindow( "T H E    K A R Y    S T O P P E R" );
        
        // - - - - -
        
        unsigned int speed = 50;
        
        glutIdleFunc( background_animation );
    
        glutDisplayFunc( display );
        
        glutKeyboardFunc( keyboard );
        
        glutPassiveMotionFunc( mouse );
        
        // - - - - -
    
        init( );
    
        glutMainLoop( );
    
    }


// ────────────────────────────────────────────────────────────────────────────────────────






//
// ────────────────────────────────────────────────────────── 6 ─────────
//  :::::: F R A M E W O R K : :  :  :   :     :        :          :
// ───────────────────────────────────────────────────────────────────
//


//
// ─── COORDINATION CONVERTORS ────────────────────────────────────────────────────────────
//

    GLfloat mouse_x_to_opengl_coordinates( int x ) {
    
        return ( ( x / ( float ) screen_width ) - 0.5f ) * 2.0f;
    
    }


// ────────────────────────────────────────────────────────────────────────────────────────


    GLfloat mouse_y_to_opengl_coordinates( int y ) {
    
        return - ( ( ( y / ( float ) screen_height ) - 0.5f ) * 2.0f );
        
    }


// ────────────────────────────────────────────────────────────────────────────────────────



