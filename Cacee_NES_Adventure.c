

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

const unsigned char ball[]={
        0,      0,      TILE2+0,   ATTR2, 
        0,      8,      TILE2+1,   ATTR2, 
        8,      0,      TILE2+2,   ATTR2, 
        8,      8,      TILE2+3,   ATTR2, 
        128};

const unsigned char* const caceeRunSeq[16] = {
  caceeLRun1, caceeLRun2, caceeLRun3, 
  caceeLRun1, caceeLRun2, caceeLRun3, 
  caceeLRun1, caceeLRun2,
  caceeRRun1, caceeRRun2, caceeRRun3, 
  caceeRRun1, caceeRRun2, caceeRRun3, 
  caceeRRun1, caceeRRun2,
};



/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x03,			// screen color

  0x11,0x30,0x27,0x00,	// background palette 0
  0x1C,0x20,0x2C,0x00,	// background palette 1
  0x00,0x10,0x20,0x00,	// background palette 2
  0x06,0x16,0x26,0x00,	// background palette 3

  0x2A,0x16,0x27,0x00,	// sprite palette 0
  0x00,0x37,0x0A,0x00,	// sprite palette 1
  0x0D,0x2D,0x28,0x00,	// sprite palette 2
  0x0D,0x27,0x16	// sprite palette 3
};



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

int MINX;
int MAXX;













// game bool value
bool game = true;
//score value
int score;
// lives value
int lives; 

// level value

int level;

char i;	// actor index
char oam_id;	// sprite ID
char pad;// controller flags





 

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
  
  
  level = 1;
}

void levelTwo()
{
  
  level = 2;
}



	


// main program

void main() {
  
  
 
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
  
  startingSpace();
  levelOne();
  while (game) {
    
    MINX = 10;
    MAXX = 220;
    if (actor_x[0] >= MAXX && level == 1)
      {
      	sfx_play(2,2);
      	levelTwo();
      	startingSpace();
        
      }
      
      if (actor_x[0] <= MINX && level ==2)
      {
        sfx_play(2,2);
        
      	levelOne();
        startingSpaceR();
        
      }
    
   
     
    // start with OAMid/sprite 0
    oam_id = 0;
    oam_id = oam_spr(100, 100, 48+level, level+1, oam_id);
    
    // set player 0/1 velocity based on controller
    for (i=0; i<2; i++) {
      // poll controller i (0-1)
      pad = pad_poll(i);
      // move actor[i] left/right
      if (pad&PAD_LEFT && actor_x[i]>10) actor_dx[i]=-2;
      else if (pad&PAD_RIGHT && actor_x[i]<230) actor_dx[i]=2;
      else actor_dx[i]=0;
      
    }
    // draw and move cacee
    for (i=0; i<1; i++) {
      byte runseq = actor_x[i] & 6;
      if (actor_dx[i] >= 0)
        runseq+=8;
      
      oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, caceeRunSeq[runseq]);
      actor_x[i] += actor_dx[i];
      actor_y[i] += actor_dy[i];
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