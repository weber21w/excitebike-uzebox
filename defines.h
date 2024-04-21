#ifndef __DEFINES_H__
#define __DEFINES_H__


#define Activel								GrayGetPlane (LIGHT_PLANE)
#define Actived								GrayGetPlane (DARK_PLANE)
#define QUIT								 -1
#define Normal								0
#define End_Wheelie						1
#define Race_Finished					2
#define Game_Paused						3
#define Fast_Quit							4
#define Race_is_Running				(g->Status == Normal || g->Status == End_Wheelie)
#define LINK_NO								93 // random
#define Track_Magic						0x7D4  // 2004 :)
#define Best_Minutes					Best_Times(0)  // Track Records
#define Best_Seconds					Best_Times(1)
#define Best_Mseconds50				Best_Times(2)
#define Zeroy									((g->lcd_height - 100) >> 1)
#define A_DISSOLVE						(1 << 0)
#define A_WAITKEY							(1 << 1)
//#define SIGN(a)								(((a)<0) ? -1 : 1)
#define ABS(a)								(((a)<0) ? -(a) : (a))
//#define Real_x(x)							((x) - ((g->camera_x - (LCD_WIDTH >> 3)) << 3) + g->softx)
#define CopyScreens92Plus(p1,p2,p3,p4)	{ FastCopyScreen_R(p1,p3); FastCopyScreen_R(p2,p4); }
#define Toggle_Screens_Fast()	CopyGrayScreens(Hiddenl, Hiddend, Activel, Actived)
#define Toggle_Screens()			CopyScreens92Plus(Hiddenl, Hiddend, Activel, Actived)
//GrayDBufToggleSync(); if (HW1) GrayWaitNSwitches(2);
/*	Waits until the user press a key and then releases the key	*/
#define WaitKey()							while(_rowread(0)) continue; \
															while(!_rowread(0)) continue; \
															while(_rowread(0)) continue;
#define _KeyCheck(k) 					(_keytest(g->Keys[k].Row, g->Keys[k].Key))
#define SafeFree(Pointer)			if ((Pointer)) { free((Pointer)); (Pointer) = NULL; }
#define CopyGrayScreens(p1,p2,p3,p4)	if (TI89) \
																				CopyScreens89(p1,p2,p3,p4); \
																			else CopyScreens92Plus(p1,p2,p3,p4)
#define BULK_SIZE							LCD_SIZE * 4 +			\
															sizeof(Clock) +			\
															sizeof(GlobalVars)

enum Tile_Detections {
/*-------------       																		-----------       ----------  ---------
  Type Of Tiles       																		Description				Dimensions	ByteWidth
  -------------       																		-----------       ----------  --------- */
	Gra1,																									// Gray								8x48				1
	SL00, SL01, SL02, 																		// _Small Bump_				24x57				3
	SL10, SL11, SL12, SL13, SL14, 												// _Medium Bump_			40x65				5
	SL20, SL21, SL22, SL23, SL24, SL25, SL26, SL27, SL28, // _Large Bump_				72x81 			9
	SL30, SL31, SL32, SL33, SL34, SL35, SL36, SL37, SL38, // _Long Bump_				72x64				9
	SL40, SL41, SL42, SL43, SL44, 												// _Tall Bump_				40x81				5
	SL50, SL51, SL52, SL53, SL54, SL55,										// _Slanted Right_		48x73				6
	SL60, SL61, SL62, SL63, SL64, SL65,										// _Slanted Left_			48x73				6
	Jum1,	Jum2,																						// Small Jump					16x64				2
	Blo1,																									// Barricade Block		8x56				1
	Blo2, 																								// Barricade Block		8x48				1
	Rok1,	Rok2, Rok3,																			// Gravel 2 and 4			24x48				3
	Rok4,	Rok5, Rok6,																			// Gravel 1 and 3			24x48				3
	Tur1,	Tur2,																						// Turbo Arrow Top		16x48				2
	Tur3,	Tur4,																						// Turbo Arrow Low		16x48				2
	Dry0,	Dry1, 																					// Dry Pit Low				16x48				2
	Dry2, Dry3,																						// Dry Pit High				16x48				2
	Dry4, Dry5,																						// Dry Pit Full				16x48				2
	MO00, MO01, MO02, MO03, MO04, MO05, MO06, MO07, MO08, 
	MO09, MO10, MO11, MO12, MO13, MO14, MO15, MO16, MO17, 
	MO18, MO19, MO20, MO21, MO22, MO23, MO24, MO25, 			// Monster Jump				208x96			26
	MR00, MR01, MR02, MR03, MR04, MR05, MR06, MR07, MR08, 
	MR09, MR10, MR11, MR12, MR13, MR14, MR15, MR16, MR17, 
	MR18, MR19, MR20, MR21, MR22, MR23, MR24, MR25, MR26, // Monster Ramp				216x96			27
	Fin0, Fin1,	Fin2, Fin3, Fin4, Fin5, Fin6, Fin7, Fin8, 
	Fin9, Fi10, Fi11, 																		// Finish Line				96x72				12
};

enum bikegfx {
	Back1, Back2, Back3, Back4, Back5, Back6, 			// Slanting Backwards
	Regular1, Regular2, 														// Normal Riding, No Slant
	Forwards1, Forwards2, Forwards3, Forwards4, 		// Slanting Forwards
	Crash1, Crash2, Crash3, Crash4, 								// Crash Animation
	DownTurn, UpTurn, 															// Turning Down and Up
	Finish_Wheelie, 																// Race Finished Wheelie
	Crashed, 																				// Bike Crashed on its side
	Still, 																					// Bike, No Horizontal Movement
	EndCrash1, EndCrash2, 													// Rider getting back on Crashed Bike
	None = 255, 
};

// Calculator Key Constants
enum Game_Keys {
	ESCKEY, UPKEY, LEFTKEY, DOWNKEY, 
	RIGHTKEY, PAUSEKEY, GASKEY, TURBOKEY, 
	TEACHERKEY, CONFIRMKEY
};

enum Controls	{Host, Join, AI_SLOW, AI_MEDIUM, AI_FAST};
enum Errors   {MEMORY, LINK_ERROR};
enum Engine_Temps {Low_Temp = 12, Middle_Temp = 32, Max_Temp = 64};

/* - - - - - - - - - -
	 FUNCTION PROTOTYPES
	 - - - - - - - - - - */
// Many functions are not included here because they are declared static inline for optimization purposes

/*					Main.c					*/
void ERROR(const unsigned char) __attribute__ ((noreturn));
void LeadOut(void) __attribute__ ((noreturn));

/*				ScrollLib.c				*/
void Shift_Left(short);
void __attribute__((__regparm__)) DrawTerrain_Clipped8_OR_R(short x asm("%d0"), short y asm("%d1"), 
short h asm("%d2"), unsigned char* sprite1 asm("%a2"), unsigned char *sprite2 asm("%a3"));

void CopyScreens89(unsigned char *src0 asm("%a0"), unsigned char *src1 asm("%a1"), 
unsigned char *dest0 asm("%a2"), unsigned char *dest1 asm("%a3")) __attribute__((__regparm__));
/*void  __attribute__((__stkparm__)) CopyScreens92Plus(unsigned char *src0 asm("%a0"), unsigned char *src1, 
unsigned char *dest0 asm("%a1"), unsigned char *dest1);*/

/*					Game.c					*/
void MAIN_LOOP(void);
void Initialize_Race(short);

/*				 Bikes.c					*/
void Update_Bikes(void);
void Copy_Bike(Bike*, Bike*);
void Start_Crash(Bike*, short);
void Start_Jump(Bike*, unsigned long);
void Stop_Turning(Bike*);
void New_Text_Message(const char*);

/*				 Modes.c					*/
void Selection_A(void);
void Selection_B(void);
void Main_Game(short);
void Multiplayer(void);
short Choose_Track(void);
void Post_Race(short);

/*					Misc.c					*/
void Dissolve(void);
void Message(const char *const [], const short);
short Get_Input(const char*, char*, short);
void Draw_User_Input(const char*, const char*, const short);
void DecompressRLE(unsigned char*, unsigned char*, short);
short CompressRLE(unsigned char*, unsigned short);
void Display_Author(void);
void Pause_Game(void);
unsigned char Get_Number(const char*, short, short, short);
//short Delay_Calc(short);

/*				 Editor.c					*/
void Start_Track_Editor(void);
void Run_Editor(const char);
short Convert_Track(short, const unsigned char*);
void Draw_Editor(short, short*);
short Load_Track(unsigned char*);
short Select_External_Track(const char*);
short Best_Times(short);
short New_Track_Record(void);

/*					Link.c					*/
short Establish_Connection(void);
void Transfer_Data(void);
void Transfer(char*, char*, unsigned long);
void Exit_Linkplay(void);
void Notify_Linkplay_Exit(void);
short Align_Calcs(void);

short Menu(const char*, const char[], short, short, short);
void Options(void);

short Save_File(const char*, unsigned char*, unsigned long);
unsigned char *Get_Data_Ptr(const char*, short);
void Archive(const char*);
void UnArchive(const char*);

void FS_DrawString(short asm("%d5"), short asm("%d0"), const unsigned char* asm("%a0"), void* asm("%a3"), 
short asm("%d7")) __attribute__((__regparm__));  // Beta by TICT
void FS_InvertString(short asm("%d5"), short asm("%d0"), const unsigned char* asm("%a0"), void* asm("%a3"), 
short asm("%d7")) __attribute__((__regparm__));  // Beta by TICT
// Wrapper for easy Gray string drawing, using TICT's *FAST* Beta Routines
void FS_DrawGrayString(short,short,const char*,short,short) __attribute__((__stkparm__));

// Custom GraySprite8_OR_R function (modified version of the ExtGraph function)
// In some parts of Scrollib.c, the program is strapped for registers, producing 
// unoptimized code.  By customizing this function to not take two registers 
// for the destination planes, it frees up some more of those registers to make 
// for smaller/faster code.
void CGraySprite8_OR_R(register short x asm("%d0"),register short y asm("%d1"),
register short h asm("%d2"),register unsigned char *sprt0 asm("%a2"),
register unsigned char *sprt1 asm("%a3")) __attribute__((__stkparm__));


#define MAX_BIKES	4

typedef struct {
	unsigned char *PtrDark;
	unsigned char *PtrLight;
	unsigned char Height;
} Tile;

#define Bike_y(b)	((b)->attr & B_Y)  // Gives 0, 1, 2, or 3
#define RealBike_y(b) 	(((b)->attr & B_Y) + (((b)->attr & B_TURNING) != 0) * (((b)->Counter < -5) - \((b)->Counter > 5)))
#define Laps_Done(b)	(((b)->attr & B_LAPS) >> 8)
#define No_Laps		g->Track[g->Width + 1]
#define No_Tilt(b)	((b)->Tilt == None)
#define Is_Computer(c)	((c) >= AI_SLOW)
#define TEXT_DELAY	(~(1 << 15))
#define TEXT_ANIM	(1 << 15)

/* - - - - - - - - - - - - - - - - */
/* Bike Attributes                 */
/* - - - - - - - - - - - - - - - - */
#define B_Y						3							// Bits 1 and 2
#define B_JUMPING			(1<<2)				// Bit 3
#define B_CRASHING		(1<<3)				// Bit 4
#define B_OVERHEAT		(1<<4)				// Bit 5
#define B_TURBO				(1<<5)				// Bit 6
#define B_TURNING			(1<<6)				// Bit 7

#define B_MUD					(1<<7)				// Bit 8
#define B_LAPS				(15<<8)				// Bits 9, 10, 11, and 12 (max value of 15)
#define B_BLOCK				(1<<12)				// Bit 13
#define B_FLAG1				(1<<13)				// Bit 14 (used in Crashing)
#define B_FLAG2				(1<<14)				// Bit 15 (used in Crashing)
#define B_FLAG3				(1<<15)				// Bit 16 (used in Crashing)
/* - - - - - - - - - - - - - - - - */

// I wanted to keep the Bike structure as small as possible because they need to be sent and 
// received each frame in LinkPlay, but it was easier just to send the first 7 bytes, 
// which is all of the relevant information
typedef struct {
	/* These First 4 variables will be transferred each Frame in LinkPlay (7 bytes) */
	/* They MUST stay as the first 4 variables */
	// / // / // / // / // / // / //
	short x;
	short y;
	unsigned short attr;
	unsigned char Graphic;				// The current Graphic for the Bike
	// / // / // / // / // / // / //
	unsigned char Control;				// Host, Join, Computer
	short Counter;
	unsigned char Tilt;						// The Bike's Tilt
	unsigned char Temp;
	unsigned char addx;
	unsigned char Old_Graphic;
	char delay;
	unsigned char Bike_NO;
} Bike;  // The structure should be padded correctly (it's size is 16 bytes)

typedef struct {
	short y;
	short Original_x;
	long cosine_Velocity; // cos(angle) * Initial_Velocity
	long sine_Velocity;  // sin(angle) * Initial_Velocity
	short Original_y;
	short Last_Crash;
} JumpDat;

typedef struct {  //RowKey
  short Row;
  short Key;
} RowKey;

// Not included with the rest of the Global register variables because they are accessed in an 
// interrupt timer (could provide for whacky results if the cpu was using a4 at the time)
typedef struct {
	// Clock Variables
	short Mseconds50;
	short Seconds;
	short Minutes;
	short Reset_Time;
	short Running;
} Clock;

typedef struct {
	// Camera/Track Values
	short camera_x;
	short softx;
	short Width;
	short Old_x;
	short softy;  // Cisco ist h bsch!
	unsigned char *Track;
	// Current Game Values
	short No_Bikes;
	Bike bikes[MAX_BIKES];
	JumpDat jumpdat[MAX_BIKES];
	char Status;
	unsigned char delay;
	unsigned char Animation;
	char HW1;
	short Game_Progress;
	short Camera_Bike;
	short Zerox;
	// Configuration Settings
	RowKey Keys[10];
	// Miscellaneous
	unsigned char Cheats;
	unsigned char Back0;
	unsigned char Back1;
	char First;
	char Link;
	char Calc;
	unsigned char lcd_height;
	unsigned char Max_xspeed;
	short OldMseconds50;
	short OldSeconds;
	short OldMinutes;
	unsigned short text_attr;
	char LinkplayOffset;
	char Old_Status;
	unsigned char text[32];  // For text messages during the Race
	unsigned char Track_Name[9];
} GlobalVars;

/* - - - - - - - - - - - - - - - - */
/* Cheat Attributes                */
/* - - - - - - - - - - - - - - - - */
#define C_OVERHEAT	1
#define C_RECOVER	(1<<1)
#define C_HALF		(1<<2)
#define C_QUARTER	(1<<3)
#define C_MOON		(1<<4)
#define C_FASTBIKES	(1<<5)
#define C_BACKGROUND	(1<<6)
/* - - - - - - - - - - - - - - - - */


register GlobalVars *g asm("a4");
extern unsigned char Original_Rate;
extern Clock  *clock;
extern char   *Terrainl;
extern char   *Terraind;
extern void   *Hiddenl;
extern void   *Hiddend;

// Terrain.h
extern const Tile Tiles[129];
// Data.h
extern unsigned char Track1[];
extern unsigned char Track2[];
extern unsigned char Sin_Table128[5];
extern unsigned char *Tracks[5];
extern const char *exctimes;
extern unsigned short Default_Times[5];
extern const char *const cheats[8][2];
// Graphics.h
extern unsigned char Hedge[8*2];
extern unsigned char Shadow[3];
extern unsigned short Rider[3][16 * 3];
extern unsigned char Starting_Blocks[2][10 * 2];
extern unsigned char Sparks[2][8];
extern unsigned long BikeGfx[23][24*3];
extern unsigned char ExciteBike_Title[2][18 * 16];
extern unsigned char Trophy[2][2 * 15];
extern unsigned char Star[2][8];
extern unsigned char Podium[3 * 16];
extern unsigned char Dots[8];
extern unsigned char Celebrating[4][2 * 16];
extern unsigned char Mask[10];
extern unsigned short Beep_Mask[16];
extern unsigned short Beep[4][16 * 2];

static void ScrollText(const char *const[]);
static void Info(void);
static void Track_Records(void);
static void Cheats(void);

static void Start_Race(void);
static void Initiate_HUD(void);
static void Update_HUD(void);
static void Heat_Bar(unsigned char*, short);

static void Align_Bike(Bike*);
static void Draw_All_Bikes(void);
static void Draw_Bike(Bike*);
static void Handle_User_Bike(Bike*);
static void Move_Bike(Bike*);
static void Handle_Computer_Bike(Bike*);
static void Handle_Finish_Wheelie(Bike*);
static short Real_x(short);
#define GetTerrain(x) (g->Track[((x)>>3)+((x) < 0 ? (g->Width + 1) : 0)])
//(g->Track[((x)>>3)+((x) < 0) * (g->Width + 1)])


#endif //_DEFINES_H_