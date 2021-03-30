

// angle frame before, frame after
//sprites can be multiple bricks
// or can be background image

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// include NESLIB header
#include "neslib.h"

// include CC65 NES Header (PPU)
#include <nes.h>





// 0 = horizontal mirroring
// 1 = vertical mirroring
#define NES_MIRRORING 1

// VRAM update buffer
#include "vrambuf.h"
//#link "vrambuf.c"


// link the pattern table into CHR ROM
//#link "chr_generic.s"

//#link "famitone2.s"


void __fastcall__ famitone_update(void);
//#link "music_aftertherain.s"
extern char after_the_rain_music_data[];
//#link "demosounds.s"
extern char demo_sounds[];

// create easy to track tile/attr for metasprites 
#define TILE 0xd8
#define ATTR 0x00

#define TILE2 0xdc
#define ATTR2 0x02
///// METASPRITES


///// METASPRITES

// define a 2x2 metasprite
#define cacee(name,code,pal)\
const unsigned char name[]={\
        0,      0,      (code)+0,   pal, \
        0,      8,      (code)+1,   pal, \
        8,      0,      (code)+2,   pal, \
        8,      8,      (code)+3,   pal, \
        128};

// define a 2x2 metasprite, flipped horizontally
#define cacee_flip(name,code,pal)\
const unsigned char name[]={\
        8,      0,      (code)+0,   (pal)|OAM_FLIP_H, \
        8,      8,      (code)+1,   (pal)|OAM_FLIP_H, \
        0,      0,      (code)+2,   (pal)|OAM_FLIP_H, \
        0,      8,      (code)+3,   (pal)|OAM_FLIP_H, \
        128};

cacee(caceeRStand, 0xd8, 0);
cacee(caceeRRun1, 0xdc, 0);
cacee(caceeRRun2, 0xe0, 0);
cacee(caceeRRun3, 0xe4, 0);
cacee(caceeRJump, 0xe8, 0);
cacee(caceeRClimb, 0xec, 0);
cacee(caceeRSad, 0xf0, 0);

cacee_flip(caceeLStand, 0xd8, 0);
cacee_flip(caceeLRun1, 0xdc, 0);
cacee_flip(caceeLRun2, 0xe0, 0);
cacee_flip(caceeLRun3, 0xe4, 0);
cacee_flip(caceeLJump, 0xe8, 0);
cacee_flip(caceeLClimb, 0xec, 0);
cacee_flip(caceeLSad, 0xf0, 0);

// define a 2x2 metasprites
const unsigned char cacee[]={
        0,      0,      TILE+0,   ATTR, 
        0,      8,      TILE+1,   ATTR, 
        8,      0,      TILE+2,   ATTR, 
        8,      8,      TILE+3,   ATTR, 
        128};



const unsigned char* const caceeRunSeq[16] = {
  caceeLRun1, caceeLRun2, caceeLRun3, 
  caceeLRun1, caceeLRun2, caceeLRun3, 
  caceeLRun1, caceeLRun2,
  caceeRRun1, caceeRRun2, caceeRRun3, 
  caceeRRun1, caceeRRun2, caceeRRun3, 
  caceeRRun1, caceeRRun2,
};

const unsigned char* const caceeStandSeq[2] = {
  caceeLStand, 
  caceeRStand, 
};




/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x03,			// screen color

  0x11,0x30,0x27,0x00,	// background palette 0
  0x1C,0x20,0x2C,0x00,	// background palette 1
  0x00,0x10,0x20,0x00,	// background palette 2
  0x06,0x16,0x26,0x00,	// background palette 3

  0x2A,0x16,0x27,0x00,	// sprite palette 0
  0x00,0x37,0x2C,0x00,	// sprite palette 1
  0x0D,0x2D,0x27,0x00,	// sprite palette 2
  0x0D,0x26,0x16	// sprite palette 3
};


byte sprite = 0x02;



byte sprite_y1 = 100;

byte sprite_y2 = 108;
//platform struct
typedef struct Platform{
  byte _x;		// platforms x/y positions
  byte _y;		
  byte sprite; 
  
};

struct Platform platform_one[20];
//This is our starting bricks, what the starting area looks like. 
void level_one_platforms() {
  char oam_id;
  
  oam_id = 0;
  
  platform_one[0]._x = 70;
  platform_one[0]._y = 190;
  platform_one[0].sprite = sprite;
  
  

 
    
  
}





// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_hide_rest(0);
  // set palette colors
  pal_all(PALETTE);
  // turn on PPU
  ppu_on_all();
}




// number of actors (4 h/w sprites each)
#define NUM_ACTORS 1

// actor x/y positions
byte actor_x[NUM_ACTORS];
byte actor_y[NUM_ACTORS];
// actor x/y deltas per frame (signed)
sbyte actor_dx[NUM_ACTORS];
sbyte actor_dy[NUM_ACTORS];
//min and max X screen values
int MINX;
int MAXX;
//bool jump
bool jump = false; 
// game bool value
bool game = true;
// if cacee is facing right bool
bool right = true; 
// if its first time loading first level bool
bool first = true;

bool twoLeft = true;
//score value
int score;
// lives value
int lives; 

// level value

int level;

char i;	// actor index
char oam_id;	// sprite ID
char pad;// controller flags

int ground = 200; 
int jumpHeight = 40;
int gravity = 2;


//This checks if player has collided with a platform and returns true if so.
bool platform_collision(){
  if(((platform_one[0]._x >= actor_x[0]-4 && platform_one[0]._x <= actor_x[0]+8)&& (platform_one[0]._y >= actor_y[0]-2 && platform_one[0]._y <= actor_y[0]+4))) //hits floor or collision detected
      {
       
        return true;     // erase brick that was hit. 
        
      }
  
}



 

//set actor x and y
void startingSpace()
{
   
  actor_x[0] = 12;
  actor_y[0] = 200;
  actor_dx[0] = 0;
  actor_dy[0] = 0;
}

void startingSpaceR()
{
  actor_x[0] = 220;
  actor_y[0] = 200;
  actor_dx[0] = 0;
  actor_dy[0] = 0;
}
void levelOne()
{
  level_one_platforms();
  //check if its our first load into game
  if(first)
  {
    // if it is, set are initial starting state and set first to false
    startingSpace();
    first = false;
  }
  // if its not, then we must be coming from right set right starting space
  else
  {
    startingSpaceR();
    sfx_play(3,2);
  }
  
    
  
  level = 1;
  
}
// level 2
void levelTwo()
{
  
  sfx_play(3,2);
  if (twoLeft)
  {
    twoLeft = false;
    startingSpace();
    
  }
  else
  {
    twoLeft = true;
    startingSpaceR();
     
  }
    
  level = 2;
  
}
// level 3 
void levelThree()
{
  sfx_play(3,2);
  startingSpace();
  level = 3;
  
  
}



	


// main program

void main() {
 char pad2;  
  
 
  //score = 0;
  //lives = 3; 
  
 
 
  

  // setup graphics
  setup_graphics();

  //PLAY MUSIC 
  famitone_init(after_the_rain_music_data);
  // Set demosounds
  sfx_init(demo_sounds); 
   // set music callback function for NMI
  nmi_set_callback(famitone_update);
  // play music
  //music_play(0);

  // loop until game is over
  
  //load up our level 1 
  
  levelOne();
  
  while (game) {
    // set our minx and maxx values
    MINX = 10;
    MAXX = 220;
    
    //if we've reached the right side of the screen transition based on 
    // what level we are currently at
    if (actor_x[0] >= MAXX)
      {
      	if(level == 1)
        {
          twoLeft = true;
      	  levelTwo();
        }
        else if (level == 2)
          levelThree();
        
        
      }
    // if we've reached the left side of the screen transition based on
    // what level we are currently at
     else if (actor_x[0] <= MINX)
      {
        if(level == 2)
          levelOne();
        else if(level == 3)
        {
          twoLeft = false;
          levelTwo();
        }
        
        
        
      }
    
   
     
    // start with OAMid/sprite 0
    oam_id = 0;
    
     
      
      
     oam_id = oam_spr(platform_one[0]._x, platform_one[0]._y, platform_one[0].sprite, 0x01, oam_id);
     // oam_id = oam_spr(platform_one[i]._x, platform_one[i]._y, platform_one[i].sprite, 0x00, oam_id);
   //  
    
    oam_id = oam_spr(100, 100, 48+level, level, oam_id);
    
    
    // 1 player controller setup. 
      pad = pad_poll(0);
      pad2 = pad_trigger(0);
      // move actor[i] left/right
      if (pad&PAD_LEFT && actor_x[0]>10) 
      {
        actor_dx[0]=-2;
        right = false;
      }
      else if (pad&PAD_RIGHT && actor_x[0]<230)
      {
        actor_dx[0]=2;
        right = true;
      }
      
      else actor_dx[0]=0;
      
      //Make Cacee Jump
       
      if (pad & PAD_A &&  actor_y[0] == ground)			//Prototype jumping
      { 
        
        actor_dy[0]=-gravity;
        jump = true;
      }
      
    
    // if we have are on top of the platform
    if (platform_collision())
    {
      // set ground to platform height - 17
      ground = 173;
    }
    else
    {
      // set ground back to default
      ground = 200;
      
    //fall if we are above ground
      
    }
    if (actor_y[0] < ground-jumpHeight)
    {
      
      actor_dy[0] = gravity; 
    }
    //if (actor_y[0] == ground - jumpHeight)
      //{
        //actor_dy[0] = gravity;
      //}
    
    // draw and move cacee
    for (i=0; i<1; i++) {
      byte runseq = actor_x[i] & 7;
      
      
      
      //if cacee is not moving
      if (actor_dx[i] == 0)
      {
        // If facing right, draw right standing
        if(right)
          oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, caceeStandSeq[1]);
        // else draw left standing
        else
          oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, caceeStandSeq[0]);
      }
      // If cacee is moving
      else{
        //If Cacee is moving to the right, increase runseq to use R animation
        if (actor_dx[i] >= 0)
      {
        runseq+=8;
      }
      //animate running based on runseq and move cacee
      oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, caceeRunSeq[runseq]);
      actor_x[i] += actor_dx[i];
      actor_y[i] += actor_dy[i];
      
      }
      if(actor_y[i] <= ground)
      {
      actor_y[i] += actor_dy[i];
      }
      //Set actor back on Plane after jumping if he falls too far
      if(actor_y[i] >= ground)
        actor_y[i] = ground;
      
      
      
      
    }
   
     
  
    
    
    
    
   
      
          
      
      
      
      
   
    //Draws and updates Scoreboard
    //oam_id = oam_spr(184, 10, 83, 3, oam_id);
    //oam_id = oam_spr(192, 10, 67, 3, oam_id);
    //oam_id = oam_spr(200, 10, 79, 3, oam_id);
    //oam_id = oam_spr(208, 10, 82, 3, oam_id);
    //oam_id = oam_spr(216, 10, 69, 3, oam_id);
    //oam_id = oam_spr(224, 10, 58, 3, oam_id);
    //oam_id = oam_spr(232, 10, (score/10%10)+48, 3, oam_id);
    //oam_id = oam_spr(240, 10, (score%10)+48, 3, oam_id);
    
    //Draws and updates Lives
    //oam_id = oam_spr(8, 10, 76, 1, oam_id);
    //oam_id = oam_spr(16, 10, 73, 1, oam_id);
    //oam_id = oam_spr(24, 10, 86, 1, oam_id);
    //oam_id = oam_spr(32, 10, 69, 1, oam_id);
    //oam_id = oam_spr(40, 10, 83, 1, oam_id);
    //oam_id = oam_spr(48, 10, 58, 1, oam_id);
    //oam_id = oam_spr(56, 10, (lives%10)+48, 1, oam_id);
    
    // hide rest of sprites
    // if we haven't wrapped oam_id around to 0
    if (oam_id!=0) oam_hide_rest(oam_id);
    // wait for next frame
    ppu_wait_frame();
  }
}