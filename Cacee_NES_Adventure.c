

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


extern const byte Title_Screen_pal[16];
extern const byte Title_Screen_rle[];

extern const byte Test_Screen_pal[16];
extern const byte Test_Screen_rle[];

extern const byte Test_Screen2_pal[16];
extern const byte Test_Screen2_rle[];

extern const byte Test_Screen3_pal[16];
extern const byte Test_Screen3_rle[];

extern const byte Game_Over_Screen_pal[16];
extern const byte Game_Over_Screen_rle[];

extern const byte Win_Screen_pal[16];
extern const byte Win_Screen_rle[];
// link the pattern table into CHR ROM






//#link "chr_generic.s"

//#link "Title_Screen.s"

//#link "Test_Screen.s"

//#link "Test_Screen2.s"


//#link "Test_Screen3.s"


//#link "Game_Over_Screen.s"

//#link "Win_Screen.s"









//#link "famitone2.s"


void __fastcall__ famitone_update(void);

//#link "journey_to_silius.s"
extern char journey_to_silius_music_data[];
// CREDIT FOR JOURNEY GOES TO FAMISTUDIO, THIS IS 
// ONE OF THEIR DEFAULT SONGS


//#link "rickroll.s"
extern char rickroll_music_data[];
// credit for rickroll goes to Amilgi
// http://famitracker.com/forum/posts.php?id=5856

//#link "music_aftertherain.s"
extern char after_the_rain_music_data[];

//#link "megalovania.s"
extern char megalovania_music_data[];
// CREDIT FOR MEGALOVANIA GOES TO mentlegen
// http://forums.famitracker.com/viewtopic.php?f=9&t=4834&p=23911&hilit=megalovania#p23911


//#link "my_lost_soul_danmaku.s"
extern char my_lost_soul_danmaku_music_data[];
// CREDIT FOR MY LOST SOUL GOES TO DRILLIMATION
// http://forums.famitracker.com/viewtopic.php?f=8&t=4865&p=23965&hilit=sad+song#p23965





//#link "demosounds.s"
extern char demo_sounds[];


//#link "custom_sounds.s"
extern char custom_sounds[];


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

#define thwomp(name,code,pal)\
const unsigned char name[]={\
        0,      0,      (code)+0,   pal, \
        0,      8,      (code)+1,   pal, \
        8,      0,      (code)+2,   pal, \
        8,      8,      (code)+3,   pal, \
        128};

#define powerup(name,code,pal)\
const unsigned char name[]={\
        0,      0,      (code)+0,   pal, \
        0,      8,      (code)+1,   pal, \
        8,      0,      (code)+2,   pal, \
        8,      8,      (code)+3,   pal, \
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

thwomp(thwompRStand, 0xc8, 3);

powerup(powerupRStand, 0xd0, 2);

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
  0x16,0x0D,0x0D	// sprite palette 3
};


byte sprite = 0x02;



byte sprite_y1 = 100;

byte sprite_y2 = 108;





// number of actors (4 h/w sprites each)
#define NUM_ACTORS 1

// actor x/y positions
byte actor_x[NUM_ACTORS];
byte actor_y[NUM_ACTORS];
// actor x/y deltas per frame (signed)
sbyte actor_dx[NUM_ACTORS];
sbyte actor_dy[NUM_ACTORS];

// thwomp x/y position
byte thwomp_x;
byte thwomp_y;

//thwomp x/y deltas per frame (signed)
sbyte thwomp_dx;
sbyte thwomp_dy;
///default thwomp height
sbyte def_thwomp_y;

// stars x and y coordinates

byte powerup_x;
byte powerup_y; 

byte starOne_x = 145;
byte starOne_y = 120;

byte starTwo_x = 80;
byte starTwo_y = 120;

byte starThree_x = 160;
byte starThree_y = 105;
//min and max X screen values
byte MINX;
byte MAXX;

// game bool value
bool game = true;
// if cacee is facing right bool
bool right = true; 
// if its first time loading first level bool
bool first = true;

bool twoLeft = true;

bool jump = false;

bool levelChange;
bool starOne = true;
bool starTwo = true;
bool starThree = true;
bool onPlatform;

//score value
byte score = 0;
// lives value
byte lives = 3; 

// level value

int level;

char i;	// actor index
char oam_id;	// sprite ID
char pad;// controller flags

byte ground= 200;
byte def_ground = 200; 
byte jumpHeight = 40;
byte gravity = 2;
byte iFrames = 0;
// used for for loops that require int
byte num;
// used to determine the x value of collision; 
byte collision;

//platform struct
typedef struct Platform{
  byte _x;		// platforms x/y positions
  byte _y;		
  byte sprite; 
  
};
//fill our struct with 10 to use
struct Platform platform_one[10];

typedef struct Thwomps{
  byte _x;		// platforms x/y positions
  byte _y;		
  byte meta_sprite; 
  
};

struct Thwomps thwomp[10];

void setup_graphics() {
  // clear sprites
  oam_hide_rest(0);
  // set palette colors
  pal_all(PALETTE);
  // turn on PPU
  ppu_on_all();
}

void fade_in() {
  byte vb;
  for (vb=0; vb<=4; vb++) {
    // set virtual bright value
    pal_bright(vb);
    // wait for 4/60 sec
    //ppu_wait_frame();
   // ppu_wait_frame();
   // ppu_wait_frame();
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ppu_wait_frame();
  }
}
void show_screen(const byte* pal, const byte* rle) {
  // disable rendering
  ppu_off();
  // set palette, virtual bright to 0 (total black)
  pal_bg(pal);
  pal_bright(0);
  // unpack nametable into the VRAM
  vram_adr(0x2000);
  vram_unrle(rle);
  // enable rendering
  ppu_on_all();
  // fade in from black
  fade_in();
}
void title()
{
  
  bool bool1 = true;
  char pad;
  
  setup_graphics();
  ppu_off();
  show_screen(Title_Screen_pal, Title_Screen_rle);
  
  // Loop until user hits Start, then enters game state. 
 
  while (bool1) {
    pad = pad_trigger(0);
    if (pad & PAD_START) 
    {
      
      ppu_off();
      vram_adr(NAMETABLE_A);
      vram_fill(0,1024);
      bool1 = false; 
      ppu_on_all();
    }
  }
  music_play(0);
}

//
void create_platforms(byte x, byte y, byte z)
{
  platform_one[z]._x = x;
  platform_one[z]._y = y;
  //platform_one[z].sprite = sprite;
  
  platform_one[z+1]._x = x+8;
  platform_one[z+1]._y = y;
 // platform_one[z+1].sprite = sprite;
}


void clear_platforms()
{
  for (num = 0; num<= 10; num++)
 {
    platform_one[num]._x = NULL;
    platform_one[num]._y = NULL;
    //platform_one[num].sprite = NULL; 
  }
}

//this is our starting level platforms
void level_one_platforms() {
  
  create_platforms(70, 175, 0);
  
  create_platforms(105, 145, 2);
  
  create_platforms(140, 120, 4);
  //platform_one[0]._x = 70;
  //platform_one[0]._y = 173;
  //platform_one[0].sprite = sprite;
  
  //platform_one[1]._x = 78;
  //platform_one[1]._y = 173;
  //platform_one[1].sprite = sprite;
}

void level_two_platforms() {
  create_platforms(90, 175, 0);
  
  create_platforms(125, 145, 2);
  
  create_platforms(80, 120, 4); 
}

void level_three_platforms() {
  create_platforms(85, 175, 0);
  
  create_platforms(55, 150, 2);
  
  create_platforms(85, 120, 4); 
  
  create_platforms(100, 90, 6);
  
  create_platforms(160, 105, 8);
  
  
}






// setup PPU and tables



//This checks if player has collided with a platform and returns true if so.
void platform_collision(){
  // loops through all our struct of platforms
  for( num = 0; num <= 20; num++)
  {
    //checks if actor has collided with our platforms
    if(((platform_one[num]._x >= actor_x[0]-4 && platform_one[num]._x <= actor_x[0]+8)&& (platform_one[num]._y >= actor_y[0]-2 && platform_one[num]._y <= actor_y[0]+4))) //collision detected
    {
      collision = platform_one[num]._y;
      onPlatform = true;
      
            
    }
  
  }
  
}

bool thwomp_see(byte x, byte y){
  if (thwomp_x == x && thwomp_y < y)
  {
    return true;
  }
  else
    return false;
}

bool thwomp_collision()
{
  if(((thwomp_x >= actor_x[0]-4 && thwomp_x <= actor_x[0]+8)&& (thwomp_y >= actor_y[0]-2 && thwomp_y <= actor_y[0]+4))) //collision detected
  {
    
    return true;      
  }
  else
    return false;
}

bool powerup_collision()
{
  if(((powerup_x >= actor_x[0]-4 && powerup_x <= actor_x[0]+8)&& (powerup_y >= actor_y[0]-2 && powerup_y <= actor_y[0]+4))) //collision detected
  {
    sfx_play(2,1);
    score+= 1; 
    return true;      
  }
  else 
    return false;
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

void create_thwomp(byte x, byte y)
{
  thwomp_x = x;
  def_thwomp_y = y;
  thwomp_y = def_thwomp_y;
}
void clear_thwomp()
{
  thwomp_x = NULL;
  def_thwomp_y = NULL;
  thwomp_y = NULL;
}

void create_powerup(byte x, byte y)
{
  powerup_x = x;
  powerup_y = y;
}

void clear_powerup()
{
  powerup_x = NULL;
  powerup_y = NULL;
}
void levelOne()
{
  ppu_off();
  clear_platforms();
  clear_thwomp();
  //clear_powerup();
  setup_graphics();
  show_screen(Test_Screen_pal, Test_Screen_rle);
  level_one_platforms();
  create_thwomp(190, 95);
  if(starOne)
  {
    create_powerup(starOne_x, starOne_y);
  }
  
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
    //sfx_play(4,2);
  }
  
    
  
  level = 1;
  
}
// level 2
void levelTwo()
{
  ppu_off();
  clear_platforms();
  clear_thwomp();
  setup_graphics();
  show_screen(Test_Screen2_pal, Test_Screen2_rle);
  level_two_platforms();
  
  create_thwomp(100, 43);
  if(starTwo)
  {
    create_powerup(starTwo_x, starTwo_y);
  }
  //sfx_play(3,2);
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
  ppu_off();
  clear_platforms();
  clear_thwomp();
  setup_graphics();
  show_screen(Test_Screen3_pal, Test_Screen3_rle);
  level_three_platforms();
  create_thwomp(130, 120);
  if(starThree)
  {
    create_powerup(starThree_x, starThree_y);
  }
  //sfx_play(3,2);
  startingSpace();
  level = 3;
  
  
}

void game_reset()
{
  thwomp_y = def_thwomp_y;
  thwomp_dy = 0;
  first = true;
  starOne = true;
  starTwo = true;
  starThree = true; 
  level = 1; 
  levelOne();
  lives = 3;
  score = 0;
  ground = def_ground;
  
}

void game_over()
{
  bool game_over = true;
  char pad; 
 
  music_stop();
  //famitone_init(my_lost_soul_danmaku_music_data);
  famitone_init(rickroll_music_data);
  music_play(0);
  setup_graphics();
  ppu_off();
  show_screen(Game_Over_Screen_pal, Game_Over_Screen_rle);
  ppu_on_all();

 
  while(game_over) 
  { 
    pad = pad_trigger(0);
    if (pad & PAD_START) 
    {
      
      ppu_off();
      
      vram_adr(NAMETABLE_A);
      vram_fill(0,1024);
      
      
      game_over = false;
      music_stop();
      famitone_init(journey_to_silius_music_data);
      music_play(0); 
      ppu_on_all();
      
    }
  }
  
  // reset lives and score and variables
  setup_graphics();
  game_reset();
  
}

// our win function
void winner()
{
  //setup variables and stop music
  bool game_over = true;
  char pad; 
  music_stop();
  famitone_init(megalovania_music_data);
  music_play(0);
  setup_graphics();
  ppu_off();
  show_screen(Win_Screen_pal, Win_Screen_rle);
  //while we are on this screen check if player hit start
  while(game_over) 
  { 
    pad = pad_trigger(0);
    if (pad & PAD_START) 
    {
      
      ppu_off();
      vram_adr(NAMETABLE_A);
      vram_fill(0,1024);
      
      
      
      game_over = false;
      music_stop();
      famitone_init(journey_to_silius_music_data);
      music_play(0); 
      ppu_on_all();
      
    }
  }
  // reset lives and score and variables
  setup_graphics();
  game_reset();
}


	


// main program

void main() {
  
  
 
  //score = 0;
  //lives = 3; 
  
 
 
  

  // setup graphics
  setup_graphics();
  
  

  //PLAY MUSIC 
  famitone_init(journey_to_silius_music_data);
  
  // Set custom sounds
  sfx_init(custom_sounds); 
   // set music callback function for NMI
  nmi_set_callback(famitone_update);
  // play music
  //music_play(0);
  
  title();

  // loop until game is over
  
  //load up our level 1 
  
  levelOne();
  
  while (game) {
    levelChange = false;
    // set our minx and maxx values
    MINX = 10;
    MAXX = 225;
    // start with OAMid/sprite 0
    oam_id = 0;
    
    
    //if we've reached the right side of the screen transition based on 
    // what level we are currently at
    if (actor_x[0] >= MAXX)
      {
      
      	if(level == 1)
        {
          levelChange = true;
          twoLeft = true;
      	  levelTwo();
        }
        else if (level == 2)
        {
          levelChange = true;
          levelThree();
        }
        
        
      }
    // if we've reached the left side of the screen transition based on
    // what level we are currently at
     else if (actor_x[0] <= MINX)
      {
       
        if(level == 2)
        {
          levelChange = true;
          levelOne();
        }
        else if(level == 3)
        {
          levelChange = true;
          twoLeft = false;
          levelTwo();
        }
        
        
        
      }
    
   
     
    
    
     //if we've changed levels, destroy thwomps
    
    // loop through our platforms. 
    
    if(level == 1)
    {
      for (i = 0; i<= 5; i++)
      {
      // add 17 to y in order for us to stand on top of platform
       //oam_id = oam_spr(platform_one[i]._x, platform_one[i]._y+17, platform_one[i].sprite, 0x01, oam_id);
       //oam_id = oam_spr(platform_one[i]._x, platform_one[i]._y+17, platform_one[i].sprite, 0x01, oam_id);
        
      }
      oam_id = oam_meta_spr(thwomp_x, thwomp_y, oam_id, thwompRStand);
      if (powerup_collision())
      {
        starOne = false;
        clear_powerup();
      }
      if (starOne)
      {
        oam_id = oam_meta_spr(powerup_x, powerup_y, oam_id, powerupRStand);
      }
    }
    
    else if(level == 2)
    {
      for (i = 0; i<= 5; i++)
      {
      // add 17 to y in order for us to stand on top of platform
        //oam_id = oam_spr(platform_one[i]._x, platform_one[i]._y+17, platform_one[i].sprite, 0x01, oam_id);
        //oam_id = oam_spr(platform_one[i]._x, platform_one[i]._y+17, platform_one[i].sprite, 0x01, oam_id);
        
        
        
      }
      oam_id = oam_meta_spr(thwomp_x, thwomp_y, oam_id, thwompRStand);
      
      if (powerup_collision())
      {
        starTwo = false;
        clear_powerup();
      }
      if (starTwo)
        {
          oam_id = oam_meta_spr(powerup_x, powerup_y, oam_id, powerupRStand);
        }
    }
    
    else if(level == 3)
    {
      for (i = 0; i<= 9; i++)
      {
      // add 17 to y in order for us to stand on top of platform
       //oam_id = oam_spr(platform_one[i]._x, platform_one[i]._y+17, platform_one[i].sprite, 0x01, oam_id);
        //oam_id = oam_spr(platform_one[i]._x, platform_one[i]._y+17, platform_one[i].sprite, 0x01, oam_id);
        
      }
      oam_id = oam_meta_spr(thwomp_x, thwomp_y, oam_id, thwompRStand);
        //check if we've grabbed the star yet
      
      if (powerup_collision())
      {
        starThree = false;
        clear_powerup();
      }
        if (starThree)
        {
          
          oam_id = oam_meta_spr(powerup_x, powerup_y, oam_id, powerupRStand);
        }
    }
     // oam_id = oam_spr(platform_one[i]._x, platform_one[i]._y, platform_one[i].sprite, 0x00, oam_id);
   //  
    // displays our current level for debug purposes
    //oam_id = oam_spr(100, 100, 48+level, level, oam_id);
    
    
    // 1 player controller setup. 
      pad = pad_poll(0);
      
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
        sfx_play(6,2);
        jump = true; 
        actor_dy[0]=-gravity;
       
        
      }
      
    
    // if we have are on top of the platform
    platform_collision();
    if (onPlatform)
    {
      // set ground to platform height 
      if (!jump)
      {
      ground = collision;
      onPlatform = false;
        
      }
      
    }
    // if we are not on top of the platform, and our actor is higher than default ground, and our actor 
    else if ((!onPlatform && actor_y[0] < def_ground && actor_y[0] < ground-jumpHeight) || (actor_x[0]-4 > platform_one[0]._x) || (actor_x[0]+4 < platform_one[0]._x) )
    {
      // set ground back to default
      if (!jump)
      {
        
      ground = def_ground;
      }

    }
   
    
    //fall if we are above ground 
    if (actor_y[0] < ground-jumpHeight)
    {
      jump = false; 
      actor_dy[0] = gravity; 
    }
   
    
    
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
      {
        actor_y[i] = ground;
        
      }
      
       
      if (thwomp_see(actor_x[i], actor_y[i]))
      {
        thwomp_dy = gravity +2; 
        oam_id = oam_meta_spr(thwomp_x, thwomp_y, oam_id, thwompRStand);
      }
      thwomp_y += thwomp_dy;
      // if thwomp has hit the ground, start rising again.
      
      if( thwomp_y >= def_ground)
      {
        if (iFrames == 0)
        {
          sfx_play(9,3);
        }
        thwomp_y = def_ground;
        thwomp_dy = -1; 
      }
      // if thwomp has reached its default height then stop rising
      if(thwomp_y == def_thwomp_y)
        thwomp_dy = 0;
      if(levelChange)
      {
        thwomp_y = def_thwomp_y;
        thwomp_dy = 0;
        oam_id = oam_meta_spr(thwomp_x, thwomp_y, oam_id, thwompRStand);
      }
      if(iFrames == 0) 
      {
        if(thwomp_collision())
        {
          sfx_play(9,3);
          lives -= 1;
           
          iFrames = 60;
        }
      }
      else
      {
        iFrames -= 1; 
      }
      
      //if our lives has gone below one we have lost and its game over
      if (lives < 1)
      {
        // run our game over
        game_over();
        
        
        
      }
      // if we have all the pickups, then we win 
      if (score == 3)
      {
        //run our winner 
        winner();
      }
      
      
      
      
      
    }

    //Draws and updates Scoreboard
    oam_id = oam_spr(176, 10, 83, 2, oam_id);
    oam_id = oam_spr(184, 10, 67, 2, oam_id);
    oam_id = oam_spr(192, 10, 79, 2, oam_id);
    oam_id = oam_spr(200, 10, 82, 2, oam_id);
    oam_id = oam_spr(208, 10, 69, 2, oam_id);
    oam_id = oam_spr(216, 10, 58, 2, oam_id);
    oam_id = oam_spr(224, 10, (score/10%10)+48, 2, oam_id);
    oam_id = oam_spr(232, 10, (score%10)+48, 2, oam_id);
    
    //Draws and updates Lives
    oam_id = oam_spr(16, 10, 76, 1, oam_id);
    oam_id = oam_spr(24, 10, 73, 1, oam_id);
    oam_id = oam_spr(32, 10, 86, 1, oam_id);
    oam_id = oam_spr(40, 10, 69, 1, oam_id);
    oam_id = oam_spr(48, 10, 83, 1, oam_id);
    oam_id = oam_spr(56, 10, 58, 1, oam_id);
    oam_id = oam_spr(64, 10, (lives%10)+48, 1, oam_id);
    
    // hide rest of sprites
    // if we haven't wrapped oam_id around to 0
    if (oam_id!=0) oam_hide_rest(oam_id);
    // wait for next frame
    ppu_wait_frame();
  }
}