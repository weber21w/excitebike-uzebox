
#include "defines.h"
#include "Data.h"

unsigned char Original_Rate;
Clock  *clock;
char   *Home;
void   *Bulk;
char   *Terrainl;
char   *Terraind;
void   *Hiddenl;
void   *Hiddend;

//https://www.ticalc.org/archives/files/fileinfo/340/34089.html

void Message(const char *const Str[], const int16_t Flag){
/*
	int16_t Pos = 0;
	memset(Hiddenl, 0xFF, LCD_SIZE + LCD_SIZE);
	GraySpriteX8_AND(g->Zerox + 8, 0, 16, ExciteBike_Title[1], ExciteBike_Title[0], 18, 
		Hiddenl, Hiddend);
	
	// Print all messages onto the hidden planes
	do 
	{
		FS_DrawGrayString(0, 28 + 10 * Pos, (char*)Str[Pos], A_SHADOWED|A_XOR|A_CENTERED, F_6x8);
	} while (Str[++Pos] != NULL);
	Display_Author();
	
	if(Flag & A_DISSOLVE){  // Sometimes, the dissolve effect is not needed
		Dissolve();
	}else Toggle_Screens();
	if(Flag & A_WAITKEY){  // Wait for the user to press a key
		while(_rowread(0)){
			if(_KeyCheck(TEACHERKEY))
				LeadOut();
		}
		while(!_rowread(0)) continue;
		while(_rowread(0)){
			if(_KeyCheck(TEACHERKEY))
				LeadOut();
		}
	}
*/
}

int16_t Get_Input(const char *Question, char *buffer, int16_t MaxLen){
/*
	int16_t key, pos = 0, Old_pos, width;
	void *kbq = kbd_queue();
	uint8_t temp[MaxLen + 1], a = 0;
	while(a < MaxLen)
		temp[a++] = 'G';
	
	temp[a]   = 0;
	width = DrawStrWidth(temp, F_6x8) + 6;
	buffer[0] = 0;
	
	while(_rowread(0));
	GraySetInt1Handler(interrupt1);  // Temporarily reinstall the original auto_int_1
	
	Draw_User_Input(Question, buffer, width);
	Dissolve();
	
	do 
	{
		Old_pos = pos;
		
		while (OSdequeue(&key, kbq)) continue;  // Get a keypress
		key = key & 0xf7ff;  // Mask out the repeat flag
		
		if(pos < MaxLen && ((toupper(key) >= 'A' && toupper(key) <= 'z') || (pos > 0 && isdigit(key))))
			buffer[pos++] = key;
		
		if(key == KEY_BACKSPACE && pos)
			pos--;
		if(key == KEY_CLEAR)
			pos = 0;
		
		if(pos != Old_pos){
			buffer[pos] = 0;
			Draw_User_Input(Question, buffer, width);  // Draws the text with a box around it
			Toggle_Screens();
		}
	} while (key != KEY_ESC && (pos <= 0 || key != KEY_ENTER));
	
	GraySetInt1Handler(DUMMY_HANDLER);
	if(key == KEY_ESC)
		return QUIT;
	while(_rowread(0));
	
	return 0;
*/
}

void Draw_User_Input(const char *Question, const char *buffer, const int16_t width){
/*
	memset(Hiddenl, 0xFF, LCD_SIZE + LCD_SIZE);
	GraySpriteX8_AND(g->Zerox + 8, 0, 16, ExciteBike_Title[1], ExciteBike_Title[0], 18, 
		Hiddenl, Hiddend);
	
	DrawGrayRect2B(((LCD_WIDTH - width) >> 1) + 1, 52, ((LCD_WIDTH - width) >> 1) + width - 1, 
		64, COLOR_WHITE, RECT_FILLED, Hiddenl, Hiddend);
	DrawGrayRect2B(((LCD_WIDTH - width) >> 1) + 1, 52, ((LCD_WIDTH - width) >> 1) + width - 1, 
		64, COLOR_DARKGRAY, RECT_EMPTY, Hiddenl, Hiddend);
	DrawGrayRect2B(((LCD_WIDTH - width) >> 1) + 2, 53, ((LCD_WIDTH - width) >> 1) + width - 2, 
		63, COLOR_LIGHTGRAY, RECT_EMPTY, Hiddenl, Hiddend);
	
	FS_DrawGrayString(0, 55, buffer, A_SHADOWED|A_CENTERED, F_6x8);
	FS_DrawGrayString(0, 22, Question, A_XOR|A_SHADOWED|A_CENTERED, F_6x8);
	FS_DrawGrayString(0, g->lcd_height - 6, "Press Enter when done", A_XOR|A_SHADOWED, F_4x6);
*/
}

void DecompressRLE(uint8_t *Dest, uint8_t *Src, int16_t Size){
/*
	register uint8_t a;
	// RLE = Flag (0x91), Value, Number of Repetitions
	
	while (Size > 0){
		// Decompress one run
		if(*Src == 0x91){
			Src++;
			for(a = *(Src + 1); a--;)
				*Dest++ = *Src;
			Size -= *(++Src);
		}else if(*Src == 0x92){
			Src++;
			for(a = 0; a < *(Src + 1); a++)
				*Dest++ = (*Src) + a;
			Size -= *(++Src);
		}else{
			*Dest++ = *Src;
			Size--;
		}
		Src++;
	}
*/
}

int16_t CompressRLE(uint8_t *Buf, uint16_t Size){
/*
	register uint8_t *Ptr   = Buf;
	const uint8_t *Original = Buf;
	register uint16_t a;
	uint8_t Val;
	
	while (Size > 0){
		a = 1;
		Val = *Ptr;
		while(Size - a > 0 && Val == *(Ptr + a)) a++;
		if(a > 3){  // We have a run to compress (this run looks like { x, x, x, x... })
			*Buf++ = 0x91;  // Flag
			*Buf++ = Val;   // Value being repeated
			*Buf++ = a;     // Number of Repititions
			Ptr   += a;
			Size  -= a;
		}else{
			a = 1;
			while(Size - a > 0 && Val + a == *(Ptr + a)) a++;
			if(a > 3){  // We have a secondary run to compress (this run looks like { x, x+1, x+2, x+3... })
				*Buf++ = 0x92;  // Second Flag
				*Buf++ = Val;   // Value being repeated
				*Buf++ = a;     // Number of Repititions
				Ptr   += a;
				Size  -= a;
			}else{
				*Buf++ = Val;
				Ptr   += 1;
				Size  -= 1;
			}
		}
	}
	
	return (Buf - Original);  // New size of Compressed Buffer
*/
}

#define HOST_NO								103 // random
#define JOIN_NO								71  // random

/* Establishes a Connection between two calcs.  The Calc to Join the Game first will be the Host */
short Establish_Connection(void){
/*
	char Send, Receive = 0, Signal = 0, join_no = JOIN_NO;
	Message((const char *const[]){"Attempting to", "Connect", NULL}, 0);
	g->Link = 1;
	
	// Clear the Link buffer until we empty it or receive the Host Calc's LINK_NO Signal
	while(OSReadLinkBlock(&Receive, 1) == 1){
		if(Receive == HOST_NO)
			Signal = 1;
		else if(Receive == LINK_NO){ // Backwards compatibility for Linking
			// Two different versions of Excitebike are attempting to connect
			Signal  = 1;
			join_no = LINK_NO;
		}else if(Receive == QUIT)
			Signal = QUIT;
	}
	
	if(Signal == 1){ // This calc is 2nd to join the game
		Send = join_no;
		OSWriteLinkBlock(&Send, 1);
		g->Calc = Join;
	}else{
		Send = HOST_NO;
		OSWriteLinkBlock(&Send, 1);
		// Tell the Host plr to wait and press Escape to cancel
		Message((const char *const[]){"Waiting for other", "player to join", "", "Press ESC to cancel", 
		"--", NULL}, 0);		
		g->Calc = Host;
		while(Receive != JOIN_NO){  // Wait until a signal is received from the Joining Calc
			OSReadLinkBlock(&Receive, 1);
			if(Receive == HOST_NO){
			// This calc entered Multiplayer before the other calc had even started the game.  Thus, this 
			// calc's original HOST_NO message to the other calc was disregarded by the other calc's AMS.
				OSLinkOpen();
				Send = JOIN_NO;
				OSWriteLinkBlock(&Send, 1);
				g->Calc = Join;
				break;
			}else if(Receive == LINK_NO){  // Two different versions of Excitebike are attempting to connect
				OSLinkOpen();
				Send = LINK_NO;
				OSWriteLinkBlock(&Send, 1);
				g->Calc = Join;
				break;
			}
			
			// Check if the Host wants to exit the game and send a Signal to the Other calc if so
			if(_KeyCheck(ESCKEY) || _KeyCheck(TEACHERKEY)){
				Exit_Linkplay();
				return QUIT;
			}
		}
	}
	Send = (CALCULATOR > 0);
	Transfer(&Receive, &Send, 1);
	
	g->LinkplayOffset = 0;
	if(Send != Receive)
		g->LinkplayOffset = (Send > 0 ? 28 : -28);
*/
	return 1;  // Connection successfully established
}

void Transfer_Data(void){
/*
	char Other_CalcStatus;
	
	Transfer(&Other_CalcStatus, &g->Status, sizeof(char));  // Synchronize Calc status'
	if(g->Status != Game_Paused)
		g->Old_Status = g->Status;
	if(g->Status == End_Wheelie){
		if(Other_CalcStatus == End_Wheelie)
			g->Status = Race_Finished;
		else if(g->First == 1) g->First = 2;
	}
	
	// Make sure both Calcs have the same Game Status (Normal, Quitting, Race_Over, etc)
	if(Other_CalcStatus != Normal && Other_CalcStatus != g->Status && Other_CalcStatus != End_Wheelie){
		if(Other_CalcStatus == Fast_Quit)
			g->Status = QUIT;
		else g->Status = Other_CalcStatus;
	}
	
	register short a = g->No_Bikes;
	for(; a--;){  // Transfer each Bike every Frame (only the first 7 bytes of each bike are important)
		if(g->Calc == g->bikes[a].Control || (Is_Computer(g->bikes[a].Control) && g->Calc == Host))
			OSWriteLinkBlock((char*)&g->bikes[a], 7);
		else{
			if(LIO_RecvData((char*)&g->bikes[a], 7, 20))
				ERROR(LINK_ERROR);
			
			// Adjustment for screen size differences between the Ti-89/Titanium and the Ti-92+/V200
			g->bikes[a].y += g->LinkplayOffset;
		}
	}
*/
}

void Transfer(char *Dest, char *Src, unsigned long Size){
/*
	if(g->Calc == Host){
		OSWriteLinkBlock(Src, Size);
		if(LIO_RecvData(Dest, Size, 20))
			ERROR(LINK_ERROR);
	}else{
		if(LIO_RecvData(Dest, Size, 20))
			ERROR(LINK_ERROR);
		OSWriteLinkBlock(Src, Size);
	}
*/
}

// Notify Other calc that the user has exited from the game
void Exit_Linkplay(void){
/*
	if(g->Link){
		const char Signal = QUIT;
		OSWriteLinkBlock(&Signal, 1);
	}
	
	if(_KeyCheck(TEACHERKEY))
		LeadOut();
*/
}

// Notify the user that the other calc has exited the game
void Notify_Linkplay_Exit(void){
/*
	OSLinkOpen();
	Message((const char *const[]){"Other calc has", "exited the game", "or", "encountered an error", NULL}, 
		A_DISSOLVE|A_WAITKEY);
*/
}

// Make sure Calcs are aligned before starting a game
short Align_Calcs(void){
/*
	char Send = LINK_NO, Receive = 0;
	Message((const char *const[]){"Waiting for other calc", 
		NULL}, 0);
	
	if(g->Link && g->Calc == Host){
		OSWriteLinkBlock(&Send, 1);
		// Wait until signal from the Joining calc
		while(Receive != LINK_NO){
			// Read the Link buffer and check if the other calc has exited the game
			if(OSReadLinkBlock(&Receive, 1) == 1 && Receive == QUIT){
				Notify_Linkplay_Exit();
				return QUIT;
			}
			// Break out of Loop and notify other calc
			if(_KeyCheck(ESCKEY) || _KeyCheck(TEACHERKEY)){
				Exit_Linkplay();
				return QUIT;
			}
		}
	}else if(g->Calc == Join){
		// Wait until signal from the Host
		while(Receive != LINK_NO){
			if(OSReadLinkBlock(&Receive, 1) == 1 && Receive == QUIT){
				Notify_Linkplay_Exit();
				return QUIT;
			}
			// Break out of Loop and notify other calc
			if(_KeyCheck(ESCKEY) || _KeyCheck(TEACHERKEY)){
				Exit_Linkplay();
				return QUIT;
			}
		}
		
		if(OSReadLinkBlock(&Receive, 1) == 1 && (Receive == QUIT))
			return QUIT;
		OSWriteLinkBlock(&Send, 1);
	}
*/
	return 0;
}

/*	Returns the option chosen by the user	 */
short Menu(const char *title, const char Options[], short Max_Length, short pos, short Fading){
/*
	short width = 0, No_Options = 0, Main_Pos = 0;
	short a, Changing = 0;
	
	while(_KeyCheck(ESCKEY));
	do 
	{
		if(DrawStrWidth(Options + (Max_Length * No_Options), F_6x8) > width)
			width = DrawStrWidth(Options + (Max_Length * No_Options), F_6x8);
	} while(*(Options + (Max_Length * (++No_Options))) != 0);
	
	do {
		
		memset(Hiddenl, 0xFF, LCD_SIZE + LCD_SIZE);
		GraySpriteX8_AND(g->Zerox + 8, 0, 16, ExciteBike_Title[1], ExciteBike_Title[0], 18, 
			Hiddenl, Hiddend);
		
		Display_Author();
		FS_DrawGrayString(0, 22, title, A_SHADOWED | A_XOR | A_CENTERED, F_6x8);
		for(a = (No_Options > 5 ? 6 : No_Options); a--;)
			FS_DrawGrayString(g->Zerox + 22, 34 + 10 * a, Options + (Max_Length * (Main_Pos + a)), 
			A_XOR, F_6x8);
		
		register short Offset = 2 + (g->Zerox >> 3) + 30 * (10 * pos + 0 + 36);
		*((char*)Hiddend + Offset +  0) &= 0x1F;
		*((char*)Hiddend + Offset + 30) &= 0x1F;
		*((char*)Hiddenl + Offset + 30) &= 0xBF;
		*((char*)Hiddend + Offset + 60) &= 0x1F;
		
		// Highlight the selected Option
		GrayInvertRect2B(g->Zerox + 21, 33 + 10 * pos, g->Zerox + 23 + width, 41 + 10 * pos, Hiddenl, Hiddend);
		
		if(!strcmp(title, "- Choose Mode -")){
			a = Zeroy + 75;
			if(pos == 0){
				FS_DrawGrayString(0, a, "(The fastest time at the end of the race wins)", A_CENTERED | A_XOR, F_4x6);
				FS_DrawGrayString(0, a + 7, "Hint: Perform flips to lower your time", A_CENTERED | A_XOR, F_4x6);
			}
			if(pos == 1){
				FS_DrawGrayString(0, a, "(The first person to cross the finish line wins)", A_CENTERED | A_XOR, F_4x6);
			}
		}
		
		if(Fading){  // Make a new menu screen fade in
			Dissolve();
			Fading = 0;
		}else{
			Toggle_Screens();
		}
		
		// Algorithm allows for any size menues to be scrolled easily
		if(_keytest(RR_UP)){
		 	if(Changing == 0){
				Changing = 1;
				if(--pos < 0){
					if(--Main_Pos < 0){
						pos = (No_Options > 5 ? 5 : No_Options - 1);
						Main_Pos = (No_Options > 5) * (No_Options - 6);
					}else pos = 0;
				}
			}
		}else if(_keytest(RR_DOWN)){
			if(Changing == 0){
				Changing = 1;
				if(++pos >= (No_Options > 5 ? 6 : No_Options)){
					if(++Main_Pos >= (No_Options > 5) * (No_Options - 5))
						pos = Main_Pos = 0;
					else pos = 5;
				}
			}
		}else Changing = 0;
		
		if(_KeyCheck(ESCKEY) || _KeyCheck(TEACHERKEY)){
			Exit_Linkplay();
			while(_KeyCheck(ESCKEY));
			
			return QUIT;
		}
	} while (!_KeyCheck(CONFIRMKEY) && !(_keytest(RR_ENTER) || (CALCULATOR && _keytest(RR_ENTER1)) || 
	(CALCULATOR && _keytest(RR_ENTER2))));
	
	while(_rowread(0));
	return Main_Pos + pos;  // Return the option chosen by the user
*/
}

static void Info(void){
}

void Options(void){
/*
	const char options[6][14] = { {"View Records"}, {"Clear Records"}, {"Information"}, {"Cheats"}, 
	{"Back"}, {0} };
	static const char Affirm_menu[][5] = { {"Yes"}, {"No"}, {0} };
	const char Choice = Menu("- Options -", (char*)options,
	14, 0, 1);
	
	if(Choice == 0)
		Track_Records();
	if(Choice == 2)
		Info();
	if(Choice == 3)
		Cheats();
	if(Choice == 1 && Menu("Reset Default Records?", 
	(char*)Affirm_menu, 5, 0, 1) == 0){
		UnArchive(exctimes);
		if(SymDel(SYMSTR(exctimes)) == 1){
			Message((const char *const[]){ "- Success -", "", "Default Track Records", "Have been Reset", 
				NULL }, A_DISSOLVE | A_WAITKEY);
		}else{
			Message((const char *const[]){ "- Error -", "", "Default Track Records", "Cannot be Reset", 
				NULL }, A_DISSOLVE | A_WAITKEY);
		}
	}
*/
}

// Allow the user to browse through each Track's best time
static void Track_Records(void){
/*
	char buf[30], Clear;
	
	while(Choose_Track() != QUIT){
		if(g->Game_Progress > QUIT){
			sprintf(g->Track_Name, "Track %d", g->Game_Progress + 1);
			
			clock->Minutes = (Default_Times[g->Game_Progress] & 0x07FF) / 60;
			clock->Seconds = (Default_Times[g->Game_Progress] & 0x07FF) % 60;
			clock->Mseconds50 = (Default_Times[g->Game_Progress] & 0xF800) >> 9;
		}else clock->Minutes = clock->Seconds = clock->Mseconds50 = 0;
		
		Clear = 0;
		do 
		{
			
			if(Clear == 0)
				sprintf(buf, "Best Time %d:%02d:%02d", 
				Best_Minutes, Best_Seconds, Best_Mseconds50);
			else sprintf(buf, "Best Time %d:%02d:%02d",
			clock->Minutes, clock->Seconds, clock->Mseconds50);
			
			Message((const char *const[]){ g->Track_Name, "", "--", buf, "--", NULL }, A_DISSOLVE * (!Clear));
			if(Clear == 0){
				FS_DrawGrayString(0, g->lcd_height - 6, "Clear resets record",A_SHADOWED|A_XOR, F_4x6);
				Toggle_Screens();
			}
			
			Clear = 0;
			
			while(_rowread(0)){  // while the user is holding a key down (except ON)
				if(_KeyCheck(TEACHERKEY))
					LeadOut();
				if(_keytest(RR_CLEAR) && Clear == 0){  // Erase (reset) this track's current best time
					if(New_Track_Record() == 0){
						Message((const char *const[]){ "- Error -", "", "Record Cannot be", "Cleared", NULL }, 
							A_DISSOLVE | A_WAITKEY);
					}
					
					Clear = 1;
					break;
				}
			}
			if(Clear == 1)
				continue;
			while(!_rowread(0))   // while no keys are pressed
				pokeIO(0x600005,0b11111);
			while(_rowread(0)){  // while the user is holding a key down (except ON)
				if(_KeyCheck(TEACHERKEY))
					LeadOut();
				if(_KeyCheck(ESCKEY))
					return;
				
				if(_keytest(RR_CLEAR)){  // Erase (reset) this track's current best time
					if(New_Track_Record() == 0){
						Message((const char *const[]){ "- Error -", "", "Record Cannot be", "Cleared", NULL }, 
							A_DISSOLVE | A_WAITKEY);
					}
					
					Clear = 1;
					break;
				}
			}
		} while(Clear == 1);
	}
*/
}

// Unlock new cheats by getting a time less than 50 seconds on Track 5
static void Cheats(void){
/*
	unsigned char Old_Cheats = g->Cheats, a = 0;
	char buf[35];
	
	if(Get_Input("Enter Cheat:", buf, 8) == QUIT)
		return;
	do
	{
		buf[a] = toupper(buf[a]);
	} while(buf[++a] != 0);
	
	// Most cheats are from the original NES GameShark.
	// I found these cheats on the web, so if they are 
	// incomplete and/or 0, please tell me.
	for(a = 0; a < 7; a++){
		if(!strcmp(buf, cheats[a][1])){
			g->Cheats ^= (1 << a);
			strcpy(buf, cheats[a][0]);
		}
	}
	
	if(!strcmp(buf, cheats[7][1])){  // Unlock All Cheats
		if(g->Cheats == 0xFF)
			g->Cheats = !g->Cheats;
		else g->Cheats = 0xFF;
		strcpy(buf, cheats[7][0]);
	}

	if(g->Cheats == Old_Cheats)
		strcpy(buf, "Sorry, try again");
	else strcat(buf, g->Cheats > Old_Cheats ? " Enabled" : " Disabled");
	Message((const char *const[]){ "", "--", buf, "--", NULL }, A_DISSOLVE | A_WAITKEY);
*/
}


void Pause_Game(void){
/*
	int16_t Redo;
	clock->Running = 0;  // Stop the Clock
	FS_DrawGrayString(0, 7, "(APPS shuts calc off)", 
		A_SHADOWED, F_4x6);
	FS_DrawGrayString(0, 18, "* Paused *", A_SHADOWED|A_CENTERED, F_8x10);
	
	Toggle_Screens();
	do 
	{
		Redo = 0;
		
		while(_rowread(0));
		OSTimerRestart(APD_TIMER);
		
		while(!_rowread(0)){
			pokeIO(0x600005,0b11111);
			// Check for APD
			if(OSTimerExpired(APD_TIMER)){
				off();
				Redo = 1;
				break;
			}
		}
		if(_KeyCheck(PAUSEKEY)){  // Turn calc off by tapping Pause (default APPS) twice
			off();
			Redo = 1;
		}
		if(_KeyCheck(ESCKEY) || _KeyCheck(TEACHERKEY)){
			Exit_Linkplay();
			g->Status = QUIT;
			return;
		}
	} while (Redo == 1);
	while(_rowread(0));
	g->Status = g->Old_Status;
	
	// Align the calcs in Linkplay before continuing the game
	if(g->Link == 1 && Align_Calcs() == QUIT)
		g->Status = QUIT;
*/
}

uint8_t Get_Number(const char *Question, int16_t No, int16_t Min, int16_t Max){
/*
	char buf[4] = { 0, 0, 0, 0 }, Fading = A_DISSOLVE;
	
	do
	{
		sprintf(buf, "%d", No);
		Message((const char *const[]){ Question, NULL }, Fading);
		FS_DrawGrayString(0, 40, buf, A_SHADOWED|A_CENTERED|A_XOR, F_8x10);
		FS_DrawGrayString(0, g->lcd_height - 6, "Up/Dn", A_SHADOWED|A_XOR, F_4x6);
		Toggle_Screens();
		
		// Delay Calc in Grayscale Low Power Mode
		while(_rowread(0) == 0){ buf[2] = buf[3] = 0; pokeIO(0x600005,0b11111); }
		
		if(_KeyCheck(UPKEY)){
			if(buf[2] == 0){
				buf[2] = 1;
				if(++No > Max) No = Min;
			}
		}else buf[2] = 0;
		if(_KeyCheck(DOWNKEY)){
			if(buf[3] == 0){
				buf[3] = 1;
				if(--No < Min) No = Max;
			}
		}else buf[3] = 0;
		
		Fading = 0;
		if(_KeyCheck(TEACHERKEY))
			LeadOut();
		if(_KeyCheck(ESCKEY))
			return 0;
	} while ((_KeyCheck(CONFIRMKEY) || (_keytest(RR_ENTER) || (CALCULATOR && _keytest(RR_ENTER1)) || 
	(CALCULATOR && _keytest(RR_ENTER2)))) == 0);
	
	return No;
*/
}

void Selection_A(void){
	Main_Game(1);
}

void Selection_B(void){
	Main_Game(Get_Number("Number of Bikes?", 4, 2, 4));
}

void Main_Game(short No_Bikes){
/*
	if(No_Bikes <= 0 || Choose_Track() == QUIT)
		return;
	
	do 
	{
		
		Initialize_Race(No_Bikes);
		MAIN_LOOP();
		
	} while(g->Game_Progress != QUIT && Load_Track(Tracks[g->Game_Progress]) != QUIT);
*/
}

void Multiplayer(void){
/*
	static const char mode_menu[][16] = { {"Fastest Time"}, {"First to Finish"}, {"Cancel Race"}, {0} };
	char Receive = 0;
	
	if(Establish_Connection() == 1){
		
		if(g->Calc == Host){
			if(Choose_Track() == QUIT || 
			(g->First = Menu("- Choose Mode -", 
			(char*)mode_menu, 16, 0, 1)) & ~0x1){
				Exit_Linkplay();
				return;
			}
			g->First++;
			
			if(OSReadLinkBlock(&Receive, 1) == 1 && Receive == QUIT){
				Notify_Linkplay_Exit();
				return;
			}
			
			const char Send = LINK_NO;
			OSWriteLinkBlock(&Send, 1);
			OSWriteLinkBlock((char*)&g->Width, 2);
			OSWriteLinkBlock((char*)&g->First, 1);
			if(LIO_SendData((char*)g->Track, g->Width + 4))  // Send Track Data
				ERROR(LINK_ERROR);
		}else{
			Message((const char *const[]){"Waiting for the Host", "to setup the Race", "--", NULL}, A_DISSOLVE);
			SafeFree(g->Track);
			
			while(Receive != LINK_NO){  // Wait until a signal is received from the Joining Calc
				OSReadLinkBlock(&Receive, 1);
				if(Receive == QUIT){
					Notify_Linkplay_Exit();
					return;
				}
				
				// Check if the Host wants to exit the game and send a Signal to the Other calc if so
				if(_KeyCheck(ESCKEY) || _KeyCheck(TEACHERKEY)){
					Exit_Linkplay();
					return;
				}
			}
			
			if(LIO_RecvData((char*)&g->Width, 2, 20))  // Receive Track Width
				ERROR(LINK_ERROR);
			if(LIO_RecvData((char*)&g->First, 1, 20))  // Receive Game Mode
				ERROR(LINK_ERROR);
			if((g->Track = malloc(g->Width + 4)) == NULL)
				ERROR(MEMORY);
			
			if(LIO_RecvData((char*)g->Track, g->Width + 4, 30))  // Receive Track Data
				ERROR(LINK_ERROR);
		}
		
		g->Game_Progress = QUIT;
		Initialize_Race(2);
		MAIN_LOOP();
	}
*/
}

short Choose_Track(void){
/*
	static const char tracks[7][11] = { 
		{"Track 1"}, {"Track 2"}, {"Track 3"}, {"Track 4"}, {"Track 5"}, 
		{"Load Track"}, {0}
	};
	short Choice = Menu("- Select Track -", 
	(char*)tracks, 11, 0, 1);
	
	if(Choice == 5){        // Load a Custom External Track
		g->Game_Progress = QUIT;
		return Select_External_Track("- Load Track -");
	}else if(Choice >= 0){ // Load a Built-In Track
		g->Game_Progress = Choice;
		return Load_Track(Tracks[Choice]);
	}else return QUIT;
*/
}

void Post_Race(short Recursive){
/*
	if(Recursive){
		clock->Running = 0; clock->Minutes = g->OldMinutes; clock->Seconds = g->OldSeconds;
		clock->Mseconds50 = g->OldMseconds50;
	}
	short Best_Time = 60 * Best_Minutes + Best_Seconds;
	short Time      = 60 * clock->Minutes + clock->Seconds;
	short Rank      = (Time - Best_Time) + (Best_Mseconds50 < (clock->Mseconds50 << 2));
	short a, y = 0, add = 0;
	char buf[30];
	
	if(Best_Time == 0)  // Track is new, its best time is 0:00:00
		Rank = -1;
	if(g->First)
		Rank = !(g->First - 1);
	
	memset(Hiddenl, 0xFF, LCD_SIZE + LCD_SIZE);
	GraySpriteX8_AND(g->Zerox + 68, Zeroy + 24, 16, Podium, Podium, 3, Hiddenl, Hiddend);
	GraySpriteX8_AND(g->Zerox, Zeroy + 7, 8, Star[0], Star[1], 1, Hiddenl, Hiddend);
	GraySpriteX8_AND(g->Zerox + 8, Zeroy + 7, 8, Star[0], Star[1], 1, Hiddenl, Hiddend);
	GraySpriteX8_AND(g->Zerox + 153, Zeroy + 7, 8, Star[0], Star[1], 1, Hiddenl, Hiddend);
	GraySpriteX8_AND(g->Zerox + 145, Zeroy + 7, 8, Star[0], Star[1], 1, Hiddenl, Hiddend);
	GraySpriteX8_AND(g->Zerox + 20, Zeroy, 15, Trophy[0], Trophy[1], 2, Hiddenl, Hiddend);
	GraySpriteX8_AND(g->Zerox + 124, Zeroy, 15, Trophy[0], Trophy[1], 2, Hiddenl, Hiddend);
	for(a = 0; a < 160; a+=8){
		GraySpriteX8_AND(g->Zerox + a, Zeroy + 44, 8, Dots, Dots, 1, Hiddenl, Hiddend);
		GraySpriteX8_AND(g->Zerox + a, Zeroy + 44 + 48, 8, Dots, Dots, 1, Hiddenl, Hiddend);
		if(a < 48){
			GraySpriteX8_AND(g->Zerox, Zeroy + 44 + a, 8, Dots, Dots, 1, Hiddenl, Hiddend);
			GraySpriteX8_AND(g->Zerox + 152, Zeroy + 44 + a, 8, Dots, Dots, 1, Hiddenl, Hiddend);
		}
	}
	
	sprintf(buf, "%s %d:%02d:%02d", g->Link ? "Player 2 " : "Best Time", Best_Minutes, Best_Seconds, Best_Mseconds50);
	FS_DrawGrayString(g->Zerox + 28, Zeroy + 44 + 10, buf, A_XOR, F_6x8);
	sprintf(buf, "Your Time %d:%02d:%02d", 
		clock->Minutes, clock->Seconds, (clock->Mseconds50 << 2));
	FS_DrawGrayString(g->Zerox + 28, Zeroy + 44 + 20, buf, A_XOR, F_6x8);
	
	sprintf(buf, "Game Over");
	if(Rank <= 0){  // New Best Time!!!
		Rank = 0;
		if(Recursive == 0 && g->Link == 0)
			sprintf(buf, "It's a New Record!");
	}else if(g->Link == 1 || (Rank /= 3) <= 0)
		Rank = 1;
	else if(Rank > 128)
		Rank = 128;
	if(g->Game_Progress != QUIT && (Rank == 1 || Rank == 2 || Recursive))
		sprintf(buf, "Try the Next Track");
	
	FS_DrawGrayString(0, Zeroy + 44 + 40, buf, A_XOR|A_CENTERED|A_SHADOWED, F_6x8);
	sprintf(buf, "Ranking   #%d", Rank + 1);
	FS_DrawGrayString(g->Zerox + 28, Zeroy + 44 + 30, buf, A_XOR, F_6x8);
	for(a = 3 - (g->Link == 1); a--;){
		if(Rank != (a + (a == 0) - (a == 1)))
			GraySpriteX8_AND(g->Zerox + 68 + (a << 3), Zeroy + 16 - ((a == 1) << 3), 16, 
			Celebrating[a == 1 ? 0 : (2 + (a == 2))], Celebrating[a == 1 ? 0 : (2 + (a == 2))] + 16, 1, 
			Hiddenl, Hiddend);
	}
	if(Recursive == 1)
		return;
	
	if(Recursive == 2){
		Toggle_Screens();
		while(_rowread(0));
	}else{
		Dissolve();
		if(Rank == 0){
			g->OldMinutes = clock->Minutes;
			g->OldSeconds = clock->Seconds;
			g->OldMseconds50 = clock->Mseconds50;
			clock->Running = 1;
		}
	}
	
	do 
	{
		y += add;
		Toggle_Screens();
		if(Rank < 3){
			GraySpriteX8_AND(g->Zerox + 68 + ((Rank != 1) << 3) + ((Rank == 2) << 3), Zeroy + 16 - 
			((Rank == 0) << 3) - y, 16, Celebrating[(y <= 0)], Celebrating[(y <= 0)] + 16, 1, 
			Activel, Actived);
			
			if(Rank == 0 && Recursive == 0 && 60 * clock->Minutes + clock->Seconds > 60 * g->OldMinutes + 
			g->OldSeconds + 5){
				Post_Race(1);
				Recursive = 1;
			}
		}
		
		for(a = 18; a--;){
			pokeIO(0x600005,0b11111); /* low power mode, wake up CPU only on AI 1 
		    	                         (grayscale), 2 (Keypress), 3 (AMS clock), 4 
		     	                         (Link), 5 (AMS timer base, needed for APD) 
		       	                       and 6 (ON, always wakes up the CPU)
		        	                      -- Saves Battery Power -- */
			if(_rowread(0))
				break;
		}
		
		if(y >= 8)
			add = -1;
		else if(y <= 0)
			add = !add;
		
		if(_KeyCheck(TEACHERKEY)){
			Recursive = QUIT;
			break;
		}
	} while ((_KeyCheck(CONFIRMKEY) || _KeyCheck(ESCKEY) || (_keytest(RR_ENTER) || (CALCULATOR &&
	 _keytest(RR_ENTER1)) || (CALCULATOR && _keytest(RR_ENTER2)))) == 0);
	if(Recursive == 2)
		return;
	if(Rank == 0 && Recursive == 0)
		Post_Race(2);
	
	if(Recursive >= 0 && Time < 50 && g->Game_Progress == 4 && g->Cheats == 0){
		a = random(8);
		Message((const char *const[]){ "New Cheat Unlocked", "", cheats[a][0], "--", cheats[a][1], NULL }, 
			A_DISSOLVE | A_WAITKEY);
	}
	
	// Top three place finishers continue
	if(Rank < 3){
		// Attempt to save a new track record
		if(Rank <= 0 && g->Calc == Host && New_Track_Record() == 0 && Recursive >= 0){
			Message((const char *const[]){ "- Error -", "", "New Record Cannot", "be Saved", NULL }, 
				A_DISSOLVE | A_WAITKEY);
		}
		
		if(g->Game_Progress != QUIT && ++g->Game_Progress >= 5)
			g->Game_Progress = 0;
	}else g->Game_Progress = QUIT;
	
	if(Recursive == QUIT)
		LeadOut();
*/
}

/*unsigned char Best_Time_Image[] = {
0xFB,0xFF,0xBE,0xF3,0xFF,0x9E,0xE3,0xFF,0x8E,0xC7,0xFF,0xC6,0x8F,0xFF,0xE2,0x1F,
0xFF,0xF0,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,
0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,
0x1F,0xFF,0xF0,0x8F,0xFF,0xE2,0xC7,0xFF,0xC6,0xE3,0xFF,0x8E,0xF0,0x00,0x1E,0xF8,
0x00,0x3E,0xFC,0x00,0x7E
}*/

void main(){
	
	Initialize_Game();  // Setup all necessary game components
	
	// Main Menu
	static const char Main[7][13] = { 
		{"Selection A"}, {"Selection B"}, {"Multiplayer"}, {"Track Editor"}, 
		{"Options"}, {"Exit"}, {0}

	};
	typedef void (*P2Func)(void);
	static const P2Func Menu_Funcs[] = 
	{&LeadOut, &Selection_A, &Selection_B, &Multiplayer, &Start_Track_Editor, &Options, &LeadOut};
	
	do {
		g->Link = 0;
		g->Game_Progress = -1;
		Menu_Funcs[Menu("- Main Menu -", (char*)Main, 
			13, 0, 1) + 1]();
	} while (1);  // Loop until Escape is pressed or the user chooses to Exit
}

/* Initializes and Preps the Game */
static void Initialize_Game(){
/*
	// Save older timer value
	//Original_Rate = *(volatile unsigned char*)0x600017;
	Home    = NULL;
	Bulk    = NULL;

	randomize();
	// Initiate Pointers within the allocated Bulk block
	Hiddenl  = Bulk;
	Hiddend  = (void*)((char*)Hiddenl + LCD_SIZE);
	g        = (GlobalVars*)((char*)Hiddend + LCD_SIZE);
	Terrainl = (char*)((char*)g + sizeof(GlobalVars));
	Terraind = (char*)((char*)Terrainl + LCD_SIZE);
	clock    = (Clock*)((char*)Terraind + LCD_SIZE);
	
	g->Track          = NULL;
	g->Cheats         = 0;
	clock->Reset_Time = 1;
	clock->Running    = 0;
*/
}

void Update_Bikes(void){

	short a;
	
	// Handle KeyPresses for Calc vs Calc Races -- Changing g->Camera_Bike
	/*if(Is_Computer(g->bikes[g->Camera_Bike].Control)){
		if(_KeyCheck(LEFTKEY) && --g->Camera_Bike < 0)
			g->Camera_Bike = g->No_Bikes - 1;
		if(_KeyCheck(RIGHTKEY) && ++g->Camera_Bike >= g->No_Bikes)
			g->Camera_Bike = 0;
	}*/
	g->Old_x = g->bikes[g->Camera_Bike].x;
	if(++g->delay >= 8){
		g->delay = 0;
		g->Animation = !g->Animation;
	}
	
	// Run Text Messages
	if(g->text[0]){
		if(g->delay == 0 && (++g->text_attr & 7) == 0)  // Make Message Blink
			g->text_attr ^= TEXT_ANIM;
		
		a = (g->text_attr & TEXT_DELAY);
		if(g->text_attr & TEXT_ANIM || a > 80)   // Draw Message
			FS_DrawGrayString(0, 10, g->text, A_CENTERED|A_SHADOWED, F_6x8);
		
		if(a > 56){
			if(a > 80){
				if(a > 90) g->text[0] = 0;
			}else if(g->bikes[g->Camera_Bike].attr & B_OVERHEAT){
				strcpy(g->text, "Go!");
				g->text_attr = 81 | TEXT_ANIM;
			}else g->text[0] = 0;
		}
	}
	
	// Loop through and update each Bike
	for(a = 0; a < g->No_Bikes; a++){
		if(Is_Computer(g->bikes[a].Control)){
			Handle_Computer_Bike(&g->bikes[a]); // A.I.
		}else if(g->Calc == g->bikes[a].Control){
			if(g->Status != End_Wheelie)
				Handle_User_Bike(&g->bikes[a]);  // Update Bike (being controlled by the User)
			else Handle_Finish_Wheelie(&g->bikes[a]);
		}else continue;  // This Bike will be handled by the other Calculator in LinkPlay
		
		// y - (x << 3) - (x << 2) = equals = y - 12 * x, but without the multiplication
		g->bikes[a].y = g->lcd_height - 29 - ((g->bikes[a].attr & B_Y) << 3) - ((g->bikes[a].attr & B_Y) << 2);
		Align_Bike(&g->bikes[a]);
	}
	
	if(g->Link == 1)
		Transfer_Data();
	Draw_All_Bikes();
	
	// Check for Front wheel to Back Wheel Bike Collisions -> Crashes
	register short b;
	for(/* a already equals g->No_Bikes from above*/; a--;){
		/* -- Make the Computer Bike Loop around the User's Screen instead of racing the entire Track --
		 If a Computer Bike gets too far off of the Screen, it will be 'teleported' to the other 
		 side, so the Camera will always have bikes on or near it.  This gives the user the feel of 
		 racing against more bikes, when at most, there will only be 4 Bikes in the race.  This is 
		 done for speed reasons and is also the way the bikes were handled in the original.
		*/
		if(Is_Computer(g->bikes[a].Control) && a != g->Camera_Bike){
			if(Real_x(g->bikes[a].x) > Real_x(g->bikes[g->Camera_Bike].x) + (160 * 2)){
				g->bikes[a].attr &= ~(B_OVERHEAT | B_CRASHING | B_FLAG1 | B_FLAG2 | B_FLAG3);
				
				/*if(_keytest (RR_CLEAR)){  // For Debugging Purposes
		PortSet(Hiddend, 239, 127);
		printf_xy(0, 0, "1) %d %d %d %d", Real_x(g->bikes[a].x), g->bikes[a].x, 
			Real_x(g->bikes[g->Camera_Bike].x) + (160 * 2), g->bikes[a].x - (160 * 4));
		PortSet(Hiddenl, 239, 127);
		printf_xy(0, 0, "1) %d %d %d %d", Real_x(g->bikes[a].x), g->bikes[a].x, 
			Real_x(g->bikes[g->Camera_Bike].x) + (160 * 2), g->bikes[a].x - (160 * 4));
		CopyGrayScreens(Hiddenl, Hiddend, Activel, Actived);
					
					while(_keytest(RR_CLEAR));
					while(!_keytest(RR_CLEAR));
					while(_keytest(RR_CLEAR));
				}*/
				
				g->bikes[a].x -= (160 * 4);
				g->jumpdat[g->bikes[a].Bike_NO].Original_x -= (160 * 4);
				g->jumpdat[g->bikes[a].Bike_NO].Last_Crash -= (160 * 4);
			}else if(Real_x(g->bikes[a].x) + (160 * 2) < Real_x(g->bikes[g->Camera_Bike].x)){
				g->bikes[a].attr &= ~(B_OVERHEAT | B_CRASHING | B_FLAG1 | B_FLAG2 | B_FLAG3);
				
				/*if(_keytest (RR_CLEAR)){  // For Debugging Purposes
		PortSet(Hiddend, 239, 127);
		printf_xy(0, 0, "2) %d %d %d %d", Real_x(g->bikes[a].x) + (160 * 2), g->bikes[a].x, 
			g->bikes[g->Camera_Bike].x, g->bikes[a].x - (160 * 4));
		PortSet(Hiddenl, 239, 127);
		printf_xy(0, 0, "2) %d %d %d %d", Real_x(g->bikes[a].x) + (160 * 2), g->bikes[a].x, 
			g->bikes[g->Camera_Bike].x, g->bikes[a].x - (160 * 4));
		CopyGrayScreens(Hiddenl, Hiddend, Activel, Actived);
					
					while(_keytest(RR_CLEAR));
					while(!_keytest(RR_CLEAR));
					while(_keytest(RR_CLEAR));
				}*/
				
				g->bikes[a].x += (160 * 4);
				g->jumpdat[g->bikes[a].Bike_NO].Original_x += (160 * 4);
				g->jumpdat[g->bikes[a].Bike_NO].Last_Crash += (160 * 4);
				if(g->bikes[a].x > (g->Width << 3) + 8 - LCD_WIDTH){
					g->bikes[a].x -= (g->Width << 3) + 8;
					g->jumpdat[g->bikes[a].Bike_NO].Original_x -= (g->Width << 3) + 8;
					g->jumpdat[g->bikes[a].Bike_NO].Last_Crash -= (g->Width << 3) + 8;
				}
			}
		}
		
		if((g->bikes[a].attr & (B_JUMPING | B_OVERHEAT | B_CRASHING)) != 0)
			continue;
		for(b = g->No_Bikes; b--;){
			if(b == a || (g->bikes[b].attr & (B_JUMPING | B_OVERHEAT | B_CRASHING)) != 0)
				continue;
			if(g->bikes[b].y > g->bikes[a].y - 2 && g->bikes[b].y < g->bikes[a].y + 2 && 
			Real_x(g->bikes[b].x) > Real_x(g->bikes[a].x) - 21 && 
			Real_x(g->bikes[b].x) < Real_x(g->bikes[a].x) - 14){
				Start_Crash(&g->bikes[b], 1);  // Crash!
				break;
			}
		}
	}
}

// Correct the Bike's current Tilt, x, y, and Graphic Values depending on the Terrain and the bike's current Behaviors (Jumping, Crashing, Mud...)
static void Align_Bike(Bike *b){
	Move_Bike(b);
	
	// If the Camera is centered on this Bike, then Update the Camera's position after moving the Bike
	if(b->Bike_NO == (unsigned short)g->Camera_Bike)
		Shift_Left(b->x - g->Old_x);
	
	// Set the Bike to the Default Graphic, depending on its behavior.  After this, adjustments are made to the Bike's Graphic depending on the Terrain
	if(b->Tilt != None && (b->attr & B_JUMPING) == 0)
		b->Graphic = b->Tilt; // Bike is doing a Wheelie
	else if(b->addx < 26){
		b->Graphic = Still; // Bike is not Moving
		b->attr   &= ~B_BLOCK;
	}else if(b->attr & B_TURNING)
		b->Graphic = DownTurn + (b->Counter < 0); // Turning Graphic
	else b->Graphic = Regular1 + g->Animation; // Riding Animation
	
	/* --------------------- */
	/* TERRAIN HIT DETECTION */
	/* --------------------- */
	register short x0 = GetTerrain(b->x + 6), x = GetTerrain(b->x + 10), x2 = GetTerrain(b->x + 18);
	register short xcnt = ((b->x + 2) & 7), Bikey = RealBike_y(b);  // + 2
	JumpDat *j = &g->jumpdat[b->Bike_NO];
	
	if(x0 + x + x2 != 0){  // There is no need to check ~50 if statements if we know that the 
		// bike is on level terrain (Gra1)
		
		if(x == MR26 && Bikey > 1){
			b->y      -= 48;
			
			b->Old_Graphic = Back5;
			Start_Jump(b, 25); // Monster Ramp //
			if(b->attr & B_JUMPING)
				b->Graphic = b->Tilt = Back6;
		}
		/* --- Front End of Bike --- */
		else if(x2 == SL00 || x2 == SL10 || x2 == SL20 || x2 == SL50 || x2 == MO00 || x2 == MR00 || x2 == Fin0)
			b->Graphic = Back6 - (GetTerrain(b->x + 16) == x2) - (GetTerrain(b->x + 13) == x2);
		else if(x2 == SL30)
			b->Graphic = Back6 - (GetTerrain(b->x + 16) == x2);
		else if(x2 == SL40)
			b->Graphic = Back6 - (GetTerrain(b->x + 17) == x2) - (GetTerrain(b->x + 16) == x2) - 
			(GetTerrain(b->x + 15) == x2);
		else if(x2 == SL60 && xcnt > 3)
			b->Graphic = Back6 - (GetTerrain(b->x + 14) == x2) - (GetTerrain(b->x + 12) == x2);
		else if(x2 == Jum1 && Bikey > 1 && xcnt > 2)
			b->Graphic = Back6 - (GetTerrain(b->x + 10) == x2);
		else if((b->attr & B_JUMPING) == 0 && ((Bikey == 3 && (x2 == Tur1 || x2 == Tur2)) || 
		(Bikey == 0 && (x2 == Tur3 || x2 == Tur4))))
			b->Temp = Low_Temp;  // Turbo Arrow
		else if(x2 == MO08){
			b->Graphic = Back6 - (GetTerrain(b->x + 17) == x2) - (GetTerrain(b->x + 16) == x2) - 
			(GetTerrain(b->x + 15) == x2);
			b->y      -= 16;
		}else if(x == Jum1 && Bikey > 1){													// Top Jump
			b->Graphic = Back5 - (xcnt == 7);
		}	else if(x == Jum2 && Bikey > 1){
			b->Graphic = Back4;
			b->y      -= xcnt + 1;
			
			Start_Jump(b, 62); // Top Jump //
		}else if((x2 == Blo1 && Bikey > 1) || (x2 == Blo2 && Bikey < 2)){
			// If you're leaning backwards and hit a block, you won't crash
			if(b->Tilt > Back5 || b->Tilt == None)
				Start_Crash(b, 1);  // Crash!
			else if((b->attr & (B_CRASHING | B_JUMPING)) == 0){
				b->Tilt = None;
				j->Last_Crash = b->x + 8;
				b->attr |= B_BLOCK;
			}
		}else if((x2 >= Rok1 && x2 <= Rok3 && (Bikey & 1)) || 
		(x2 >= Rok4 && x2 <= Rok6 && (Bikey & 1) == 0))
			b->attr |= B_MUD;
		else if((Bikey < 2 && (x2 == Dry0 || x2 == Dry1)) || 
		(Bikey > 1 && (x2 == Dry2 || x2 == Dry3)) || (x2 == Dry4 || x2 == Dry5))
			b->attr |= B_MUD;
		/* --- Middle of Bike --- */
		else if(x == SL00 || x == SL10 || x == SL20 || x == SL50 || x == MO00 || x == Fin0){
			b->Graphic = Back4 + (xcnt == 7 || xcnt < 2);
			b->y      -= xcnt;
		}	else if(x == SL01){
			b->y      -= 8;
			
			Start_Jump(b, 30); // Small Jump //
		}else if(x == SL12 || x == MO02){
			b->y      -= 16;
			
			Start_Jump(b, 40); // Medium Jump //
		}else if(x == SL24){
			b->y      -= 32;
			
			Start_Jump(b, 50); // Large Jump //
		}else if(x == SL34){
			b->y      -= 16;
			
			Start_Jump(b, 40); // Long Jump //
		}else if(x == SL42){
			b->y      -= 32;
			
			Start_Jump(b, 40); // Tall Jump //
		}else if(x == SL53 || x == SL62){
			b->y			-= 24;
			if(xcnt > 5)
				b->Graphic = Forwards1;
			
			Start_Jump(b, 45); // Slanted Jump //
		}else if(x >= Fin3 && x <= Fin8){
			b->y			-= 24;
			if(xcnt > 5 && x == Fin8){
				b->Graphic = Forwards1;
			}else if(x == Fin5 && GetTerrain(g->Old_x + 10) != x){  // New Lap!!!
				if(Laps_Done(b) + 1 < No_Laps)
					b->attr = (b->attr & ~B_LAPS) | ((Laps_Done(b) + 1) << 8);
				else if(b->Control == g->Calc){
					g->Status = End_Wheelie;
					clock->Running = 0;
				}
				/*if(Laps_Done(b) + 1 < No_Laps)
						sprintf(buf, "Lap %d", Laps_Done(b) + 1);
					else strcpy(buf, "Final Lap");*/
				if(b->Bike_NO == (unsigned short)g->Camera_Bike){
					char buf[25];
					short msecs = clock->Mseconds50 - g->OldMseconds50;
					register short time = (clock->Minutes - g->OldMinutes);
					if((time = ((time << 6) - (time << 2)) + (clock->Seconds - g->OldSeconds)) < 0)
						time = 0;
					
					sprintf(buf, "Lap %d:%02d:%02d", time / 60, 
						time % 60, (msecs + 19 * (msecs < 0)) << 2);
					New_Text_Message(buf);
					
					g->OldMinutes = clock->Minutes; g->OldSeconds = clock->Seconds;
					g->OldMseconds50 = clock->Mseconds50;
				}
			}else if(x == Fin3)
				Start_Jump(b, 45); // Finish Line Jump //
		}else if(x == MO10 || x == MR03){
			b->y      -= 48;
			
			Start_Jump(b, 40); // Monster Jump //
		}else if(x == SL02 || x == SL14 || x == SL28 || x == SL65 || x == MO25 || x == Fi11){
			b->Graphic = Forwards3;
			b->y      -= 7 - xcnt;
		}else if(x == SL11){																				// Medium
			b->Graphic = Back4;
			b->y      -= xcnt + 8;
		}else if(x == SL13 || x == MO24){
			b->Graphic = Forwards3;
			b->y      -= (7 - xcnt) + 8;
		}else if(x >= SL21 && x <= SL23){													// Large
			b->Graphic = Back4;
			b->y      -= xcnt + ((x - SL20) << 3);
		}else if(x >= SL25 && x <= SL27){
			b->Graphic = Forwards3;
			b->y      -= (7 - xcnt) + ((SL28 - x) << 3);
		}else if(x == SL30){																				// Long
			b->Graphic = Back5 + (xcnt == 5 || xcnt == 6);
			b->y      -= (xcnt >> 1);
		}else if(x >= SL31 && x <= SL33){
			b->Graphic = Back5;
			b->y      -= (xcnt + ((x - SL30) << 3)) >> 1;
		}else if(x >= SL35 && x <= SL37){
			b->Graphic = Forwards2;
			b->y      -= ((7 - xcnt) + ((SL38 - x) << 3)) >> 1;
		}else if(x == SL38){
			b->y      -= (7 - xcnt) >> 1;
			b->Graphic = Forwards2 - (xcnt == 5 || xcnt == 6);
		}else if(x == SL40 || x == SL41 || x == MR00){							// Tall
			b->Graphic = Back2;
			b->y      -= (xcnt + xcnt) + ((x == SL41) << 3) + 4;
		}else if(x == SL43 || x == SL44){
			b->Graphic = Forwards4;
			b->y      -= (((7 - xcnt) + ((x == SL43) << 3)) << 1) + 4;
		}else if(x == SL51 || x == SL52){													// Slanted Right
			b->Graphic = Back4;
			b->y      -= xcnt + ((x - SL50) << 3);
		}else if(x == SL54){
			b->Graphic = Forwards4 - (xcnt < 1) - (xcnt < 3);
			b->y      -= (26 - xcnt - xcnt);
		}else if(x == SL55){
			b->Graphic = Forwards4;
			b->y      -= (10 - xcnt - xcnt);
		}else if(x == SL60){																				// Slanted Left
			b->Graphic = Back2 + (xcnt < 2);
			if(xcnt > 3)
				b->y    -= (xcnt + xcnt) - 4;
		}else if(x == SL61){
			b->Graphic = Back2 + (xcnt > 4) + (xcnt > 6);
			b->y      -= (xcnt + xcnt) + 8;
		}else if(x == SL63 || x == SL64){
			b->Graphic = Forwards3;
			b->y      -= (7 - xcnt) + ((SL65 - x) << 3);
		}else if(x == MO01){																				// Monster Jump
			b->Graphic = Back4;
			b->y      -= xcnt + 8;
		}else if(x == MO23 || (x >= MO03 && x <= MO07)){
			b->y      -= 16;
		}else if(x == MO08 || x == MR01){
			b->Graphic = Back2;
			b->y      -= 16 + xcnt + xcnt + 4;
		}else if(x == MO09 || x == MR02){
			b->Graphic = Back2;
			b->y      -= 32 + xcnt + xcnt + 4;
		}else if(x >= MO11 && x <= MO17){
			b->y      -= 48;
		}else if(x >= MO18 && x <= MO21){
			b->Graphic = Forwards3;
			b->y      -= 16 + (7 - xcnt) + ((MO21 - x) << 3);
		}else if(x == MO22){
			b->Graphic = Regular1 + ((xcnt < 2) + (xcnt < 2));
			b->y      -= 16;
		}else if(x == MR04){																			// Monster Ramp
			if(Bikey < 2)
				b->Graphic = Regular1 + (xcnt > 2) + (xcnt > 2) + (xcnt > 4);
			b->y      -= 48;
		}else if(x >= MR05 && x <= MR07){
			if(Bikey > 1){
				b->y    -= 48;
			}else{
				b->Graphic = Forwards4;
				b->y      -= (((7 - xcnt) + ((MR07 - x) << 3)) << 1) + 4;
			}
		}else if(x == MR08 && Bikey > 1){
			b->y    -= 48;
		}else if(x >= MR09 && x <= MR25){
			if(Bikey > 1){
				b->y    -= 48;
			}else if((x >= MR11 && x <= MR13) || (x >= MR18 && x <= MR20)) b->attr |= B_MUD;
		}else if(xcnt < 3 && ((x == Blo1 && (Bikey > 1)) || (x == Blo2 && (Bikey < 2)))){
			// If you're leaning backwards and hit a block, you won't crash
			if(b->Tilt > Back5 || b->Tilt == None)
				Start_Crash(b, 1);  // Crash!
			else if((b->attr & (B_CRASHING | B_JUMPING)) == 0){
				b->Tilt = None;
				j->Last_Crash = b->x + 8;
				b->attr |= B_BLOCK;
			}
		}else if((x >= Rok1 && x <= Rok3 && (Bikey & 1)) || 				// Rock/Mud Patch
		(x >= Rok4 && x <= Rok6 && (Bikey & 1) == 0))
			b->attr |= B_MUD;
		else if((b->attr & B_JUMPING) == 0 && ((Bikey == 3 && (x == Tur1 || x == Tur2)) || // Turbo Strip
		(Bikey == 0 && (x == Tur3 || x == Tur4))))
			b->Temp = Low_Temp;  // Turbo Arrow
		else if((Bikey < 2 && (x == Dry0 || x == Dry1)) || 					// Dry Patch
		(Bikey > 1 && (x == Dry2 || x == Dry3)) || (x == Dry4 || x == Dry5))
			b->attr |= B_MUD;
		else if(x == Fin1 || x == Fin2){														// Finish Line
			b->Graphic = Back4;
			b->y      -= xcnt + ((x - Fin0) << 3);
		}else if(x == Fin9 || x == Fi10){
			b->Graphic = Forwards3;
			b->y      -= (7 - xcnt) + ((Fi11 - x) << 3);
		}
		/* --- Rear End of Bike --- */
		else if(x0 == SL02 || x0 == SL14 || x0 == SL28 || x0 == SL65 || x0 == MO25 || x0 == Fi11)
			b->Graphic = Forwards2 - (GetTerrain(b->x + 8) != x0);
		else if(x0 == SL38)
			b->Graphic = Forwards2 - (GetTerrain(b->x + 8) != x0);
		else if(x0 == SL44 || x0 == SL55 || x0 == MR07)
			b->Graphic = Forwards4 - (GetTerrain(b->x + 7) != x0) - (GetTerrain(b->x + 8) != x0) - 
			(GetTerrain(b->x + 9) != x0);
		else if((x0 >= Rok1 && x0 <= Rok3 && (Bikey & 1)) || 
		(x0 >= Rok4 && x0 <= Rok6 && (Bikey & 1) == 0))
			b->attr |= B_MUD;
		else if((b->attr & B_JUMPING) == 0 && ((Bikey == 3 && (x0 == Tur1 || x0 == Tur2)) || 
		(Bikey == 0 && (x0 == Tur3 || x0 == Tur4))))
			b->Temp = Low_Temp;  // Turbo Arrow
		else if((Bikey < 2 && (x0 == Dry0 || x0 == Dry1)) || 
		(Bikey > 1 && (x0 == Dry2 || x0 == Dry3)) || (x0 == Dry4 || x0 == Dry5))
			b->attr |= B_MUD;
		// ~50 if statements...
	}
	
	/* ------------- */
	/* HANDLE A JUMP */
	/* ------------- */
	if(b->attr & B_JUMPING){
		if(b->Counter > 2 && j->y >= b->y){  // Bike is Landing
			b->attr   &= ~B_JUMPING;
			b->Counter = 0;
			
			if(b->x > j->Original_x + 12 && ((b->Tilt < Regular1 && b->Graphic > Regular2) || 
				  (b->Tilt > Forwards1 && b->Graphic < Forwards1) || 
				  (b->Control < AI_SLOW && b->Graphic < Back6 && b->Tilt > b->Graphic + 2))){
				// B_FLAG1 = 1, B_FLAG2 = 0, Rest = 1
				Start_Crash(b, ((b->attr & B_FLAG2) == 0));  // Crash!
			}else if(b->attr & B_OVERHEAT){
				b->Tilt = None;
				b->attr |= B_FLAG1;
				b->delay = 0;
			}else{
				// Slow the Bike down if its Tilt is not centered when Landing
				b->addx -= (ABS((b->Tilt - (b->Tilt > Regular1)) - (b->Graphic - (b->Graphic > Regular1)))) * 12;
				if((signed char)b->addx < 0)
					b->addx = 0;
				
				// Check if a flip was performed during the Jump
				if(((b->attr & B_FLAG2) && b->Tilt > Back5) || ((b->attr & B_FLAG1) && b->Tilt < Back6)){
					if(clock->Seconds > 3)  // Timer Bonus
						clock->Seconds -= 3;
					b->attr &= ~(B_FLAG1 | B_FLAG2);
				}
				
				if(b->Graphic != b->Tilt && b->Graphic != Regular1 + g->Animation)
					b->Tilt = None;
				else if(b->Tilt > Back6){
					b->Tilt = None;
					b->Graphic = Regular1 + g->Animation;
				}else b->Graphic = b->Tilt;
			}
		}else if(b->Counter > 0){
			// Draw Bike's Shadow on Terrain beneath Bike
			GrayClipSprite8_OR_R(Real_x(b->x + 9), b->y + 21 - g->softy, 3, Shadow, Shadow, Hiddenl, Hiddend);
			
			b->Graphic = b->Tilt;
			b->y = j->y;
		}
	}else if(b->attr & B_CRASHING){
		
		/* -------------- */
		/* HANDLE A CRASH */
		/* -------------- */
		
		/* 
		There are 3 Stages to a Crash
			1) The Bike Tumbling
			2) The Bike and the Rider being thrown upward
			3) The Rider Running back towards the Bike
		*/
		
		if(b->Counter < 0){
			b->Graphic = Crashed;  // Bike Laying on its side
			b->delay++;
			
			if(b->attr & B_FLAG1){  // Rider and Bike are Sliding Upwards
				// Draw Rider on its side
				GrayClipSprite16_MASK_R(Real_x(b->x - b->Counter + 10), b->y + 10 + ((b->Counter * ((b->y + 10) - 
				j->y)) >> 4) - g->softy, 14, Rider[0], Rider[0] + 16, Rider[0] + 32, Rider[0] + 32, Hiddenl, 
				Hiddend);
				
				// Move Bike
				b->y += (b->Counter * (b->y - (g->lcd_height - 48 - 24))) >> 4;
				
				if(b->Counter < -16){
					b->attr &= ~B_FLAG1;
					b->Counter = -1;
				}else if(b->delay >= 5){
					b->delay = 0;
					b->Counter--;
				}
			}else{
				b->y = j->y - b->Counter;
				
				if(b->y >= g->lcd_height - 48 - 20){  // Rider is getting Back on the Bike
					
					if(b->delay >= 0){
						b->delay = 0;
						b->attr &= ~B_FLAG3;
					}
					if((b->delay -= 2) < -22)
						b->attr |= B_FLAG3;
					
					if(b->delay < -44){  // Crash is Completely Finished
						// Align Bike on the Top Edge of the Track and reset all Crashing Values
						b->attr = (b->attr & ~(B_CRASHING | B_FLAG1 | B_FLAG2 | B_FLAG3 | 3)) | B_TURNING | 
							(3 - ((x >= MR09 && x <= MR25) << 1));
						b->Counter = -5;
					}
					b->Graphic = EndCrash1 + ((b->attr & B_FLAG3) != 0);
					b->y = g->lcd_height - 48 - 24;
				}else{  // Rider is Running back towards Bike
					x2 = 1 + ((b->attr & B_FLAG3) == 0);
					
					/*  Tapping Gas or Turbo while Running Back to your Bike will speed up the Process */
					/* This is a Cheat from the Original NES Version */
					if(b->Control == g->Calc){
						if(_KeyCheck(GASKEY) || _KeyCheck(TURBOKEY) || g->Cheats & C_RECOVER){
							if((b->attr & B_FLAG2) == 0 || g->Cheats & C_RECOVER){
								b->Counter -= 2 + (g->Cheats & C_RECOVER);
								b->delay = 20;
								b->attr |= B_FLAG2;
							}
						}else if(b->attr & B_FLAG2) b->attr &= ~B_FLAG2;
					}
					
					// Draw Rider Running
					GrayClipSprite16_MASK_R(Real_x(b->x + 26 + ((b->Counter << 4) / ((g->lcd_height - 48 - 20) - 
					j->y))),b->y - g->softy, 16, Rider[x2], Rider[x2] + 16, Rider[x2] + 32, Rider[x2] + 32, 
					Hiddenl, Hiddend);
					
					if(b->delay >= 20){
						b->Counter--;
						b->attr ^= B_FLAG3;  // Animate Rider Running
						b->delay = 0;
					}else if(b->delay == 10) b->Counter--;
					
					b->y = g->lcd_height - 48 - 24;  // Bike sitting at Top of Track
				}
			}
		}else{  // Bike is Tumbling
			b->Graphic = (b->Counter & 15);
			if(b->attr & B_FLAG3)
				b->Graphic = 15 - b->Graphic;
			
			if(b->Counter > 7 && (g->delay & 3) == 0)
				b->Counter--;
			
			if(b->Counter <= 7 || (b->attr & B_FLAG1 && xcnt >= 5 && xcnt <= 6)){
				if(b->y == (signed short)(g->lcd_height-29-12*Bike_y(b))){  // First Part of Crash is Finished
					// Set up Variables for Second Part of Crash (Rider and Bike Sliding Up)
					b->attr = (b->attr & ~B_FLAG2) | B_FLAG1;
					b->Counter = -1;
					j->y = ((CALCULATOR > 0) << 5) + random(96 - 72) - (b->addx >> 2);
					//j->y = g->lcd_height - 48 - random(100 - 72) - (b->addx >> 2);
					g->jumpdat[b->Bike_NO].Last_Crash = b->x;
					b->addx = 0;
					b->delay = 0;
				}else{
					if(b->Counter <= 7)
						b->Counter += 16;
					b->attr |= B_FLAG1;
				}
			}
		}
	}else if(b->attr & B_OVERHEAT){  // Bike has Overheated
		if((g->text_attr & 1) == 0 && g->delay == 0)
			b->Temp = Max_Temp * (!b->Temp);
		
		if(b->Counter < 0){  // Bike is sitting at Top of Track
			b->Counter--;
			b->y -= (43 - 12 * Bike_y(b));
			
			if(b->Counter < -412){  // Bike's temp is back to normal  // -448
				// Align Bike on the Top Edge of the Track
				b->attr = (b->attr & ~(B_OVERHEAT | B_FLAG1 | 3)) | B_TURNING | 
					(3 - ((x >= MR09 && x <= MR25) << 1));
				b->Counter = -5;
				b->Temp = Low_Temp;
			}
		}else{  // Bike is drifting towards the top of the Track
			b->addx = (b->addx >> 1);
			
			if((g->delay & 3) == 0)
				b->Counter++;
			// Move Bike
			b->y -= (b->Counter * (43 - 12 * Bike_y(b))) >> 4;
			
			if(b->Counter > 15)
				b->Counter = -1;
		}
	}else{  // Bike is not Jumping, Overheated, or Crashing
		if(b->Graphic != b->Tilt && b->Graphic != Regular1 + g->Animation)
			b->Tilt = None;
		
		if(b->attr & B_MUD){
			b->attr &= ~(B_MUD | B_BLOCK);
			
			// Draw dirt flying up behind Bike
			if(b->addx > 28){
				Bikey = b->y + 16 - g->softy - ((b->Graphic == DownTurn) * 3);
				
				if(random(7)){
					if(random(4))
						GrayClipSprite8_OR_R(Real_x(b->x) - 9, Bikey, 8, Sparks[0], Sparks[0], Hiddenl, Hiddend);
					else GrayClipSprite8_OR_R(Real_x(b->x) - 9, Bikey, 8, Sparks[1], Sparks[1], Hiddenl, Hiddend);
				}
				if((g->delay & 3) == 3 || random(3) == 2)
					GrayClipSprite8_OR_R(Real_x(b->x) - 17, Bikey - 8, 8, Sparks[1], Sparks[1], Hiddenl, Hiddend);
			}
			
			b->addx = (b->addx >> 1);  // Slow Bike down in Mud
			if(b->addx < 32)
				b->addx = (28 + (((g->delay & 1) == 0) << 2)) * 
				(Is_Computer(b->Control) || _KeyCheck(GASKEY) || _KeyCheck(TURBOKEY));
		}
	}
	
	b->Old_Graphic = b->Graphic;
	// Adjustment for when the Bike enters a new 'Camera' Lap
	if(b->x > (g->Width << 3) + 8 - LCD_WIDTH){
		b->x -= (g->Width << 3) + 8;
		j->Original_x -= (g->Width << 3) + 8;
		j->Last_Crash -= (g->Width << 3) + 8;
	}
	
	/*if(b->x > (g->Width << 3) + 8 - (b->Bike_NO == (unsigned short)g->Camera_Bike ? LCD_WIDTH : 0)){
		b->x -= (g->Width << 3) + 8;
		j->Original_x -= (g->Width << 3) + 8;
		j->Last_Crash -= (g->Width << 3) + 8;
	}*/
	
	/*PortSet(Hiddend, 239, 127);
		printf_xy(0, 0, "%d %d", xcnt, b->y);
			PortSet(Hiddenl, 239, 127);
				printf_xy(0, 0, "%d %d", xcnt, b->y);
			if(_keytest(RR_CLEAR)) b->addx = 38;
		Draw_Bike(b);
	CopyGrayScreens(Hiddenl, Hiddend, Activel, Actived);*/
}

/. Draw the Bikes Layered, so the Bikes closest to the Screen will be drawn Last
static void Draw_All_Bikes(void){
	unsigned char Used[MAX_BIKES] = { 0, 0, 0, 0 };
	short a, b, Back_Bike, y;
	
	for(a = 0; a < g->No_Bikes; a++){
		Back_Bike = 0, y = 140;
		for(b = 0; b < g->No_Bikes; b++){
			if(Used[b] == 0 && g->bikes[b].y < y){
				Back_Bike = b;
				y = g->bikes[b].y;
			}
		}
		
		Used[Back_Bike] = 1;
		Draw_Bike(&g->bikes[Back_Bike]);
	}
}

// Draw one Clipped Bike
static void Draw_Bike(Bike *b){
/*
	GrayClipSprite32_MASK_R(Real_x(b->x), b->y - g->softy, 24, BikeGfx[b->Graphic], BikeGfx[b->Graphic] + 
	24, BikeGfx[b->Graphic] + 48, BikeGfx[b->Graphic] + 48, Hiddenl, Hiddend);
*/
}

static void Handle_User_Bike(Bike *b){
/*
	if(b->attr & B_OVERHEAT)
		return;
	
	// Check for KeyPresses
	if(_KeyCheck(RIGHTKEY) && ((b->attr & B_JUMPING) || b->Tilt < Regular1)){  // Tilt Forwards
		if(No_Tilt(b) || b->Tilt == Regular1)
			b->Tilt = Forwards1;
		else if(g->delay == 4 && _KeyCheck(UPKEY) && b->Tilt > Forwards4){
			// Allow for Frontflips by holding Up and Right when Jumping!
			if(++b->Tilt > Crash4){
				b->Tilt = Back1;
				b->attr |= B_FLAG1;
			}
		}else if(g->delay == 0){
			if(b->Tilt < Forwards4)
				b->Tilt++;
			else if(b->Tilt > Forwards4 && ++b->Tilt > Crash4)
				b->Tilt = Back1;
		}
	}	
		
		
		/*else if(g->delay == 0 || (g->delay == 4 && b->Tilt > Forwards4 && _KeyCheck(UPKEY))){
			// Allow for Frontflips by holding Up and Right when Jumping!
			if(_KeyCheck(UPKEY) || b->Tilt > Forwards4){
				if(++b->Tilt > Crash4){
					b->Tilt = Back1;
					if(_KeyCheck(UPKEY))
						b->attr |= B_FLAG1;
				}
			}else if(b->Tilt < Forwards4)
				b->Tilt++;
		}
	} */
	
	else if(_KeyCheck(LEFTKEY) && ((b->attr & B_JUMPING) || b->addx > 32)){  // Tilt Backwards
		if((b->attr & B_BLOCK) == 0){
			if(No_Tilt(b))
				b->Tilt = Back6;
			else if(g->delay == 0 || (g->delay == 4 && b->Tilt > Forwards4)){
				if(_KeyCheck(DOWNKEY)){  // Allow for Backflips by holding Down and Left when Jumping!
					if(b->Tilt-- <= Back1){
						if(b->attr & B_JUMPING){
							b->Tilt = Crash4;
							b->attr |= B_FLAG2;
						}else Start_Crash(b, 0);  // Crash!
					}
				}else if(b->Tilt > ((b->attr & B_JUMPING) != 0)){
					b->Tilt--;
				}else if((b->attr & B_JUMPING) == 0)
					Start_Crash(b, 0);  // Crash!
			}
		}
	}else{
		b->attr &= ~B_BLOCK;
		if(b->Tilt != None && g->delay == 0 && (b->attr & B_JUMPING) == 0 && ++b->Tilt >= Regular1)
			b->Tilt = None;
	}
	
	if(_KeyCheck(GASKEY) == 0 && _KeyCheck(TURBOKEY) == 0 && g->delay==0 && b->Temp>Low_Temp)
		b->Temp--;
	
	if((b->attr & B_CRASHING) == 0){
		if(_KeyCheck(TURBOKEY)){
			b->attr |= B_TURBO;
			
			if((b->attr & B_JUMPING) == 0)
				b->addx += 6;
			if(g->delay == 0 && ++b->Temp > Max_Temp){
				b->Temp = Max_Temp;
				
				if((g->Cheats & C_OVERHEAT) == 0){  // Never Overheat Cheat
					b->attr = (b->attr & ~B_BLOCK) | B_OVERHEAT;
					New_Text_Message("OVER HEAT");
					
					if((b->attr & B_JUMPING) == 0){
						b->Tilt = None;
						b->attr |= B_FLAG1;
						Stop_Turning(b);
					}
					
					return;
				}
			}
		}else{
			b->attr &= ~B_TURBO;
			
			if(_KeyCheck(GASKEY)){
				if(g->delay == 0 && (b->Temp > Middle_Temp || ++b->Temp > Middle_Temp))
					b->Temp--;
				if((b->attr & B_JUMPING) == 0)
					b->addx += 4;
			}
		}
		
		if((b->attr & B_JUMPING) == 0 && (b->attr & B_TURNING) == 0){
			if(_KeyCheck(UPKEY)){
				b->Counter = -1;
				b->attr |= B_TURNING;
			}else if(_KeyCheck(DOWNKEY)){
				b->Counter = 1;
				b->attr |= B_TURNING;
			}
		}
	}
*/
}

// Update a Bike's x and y coordinates
static void Move_Bike(Bike *b){
/*
	if(Is_Computer(b->Control) == 0){
		if((b->attr & B_JUMPING) == 0 && (b->attr & B_CRASHING) == 0)
			b->addx -= ((b->addx > 0)) + (b->addx > 1);  // Friction
		
		if(b->addx > (g->Max_xspeed + ((b->attr & B_TURBO) != 0)) << 5)  // Restrict Speed of Bike
			b->addx = (g->Max_xspeed + ((b->attr & B_TURBO) != 0)) << 5;
	}
	
	// Handle a Bike's turn
	if(b->attr & B_TURNING){
		register char Track_y = Bike_y(b) + (b->Counter < 0) - (b->Counter > 0);
		if(GetTerrain(b->x + 10) >= MR05 && GetTerrain(b->x + 10) <= MR26){
			if(Bike_y(b) == 2 && Track_y == 1)
				Track_y = -1;
			else if(Bike_y(b) == 1 && Track_y == 2)
				Track_y = 4;
		}
		b->Counter += (b->Counter > 0) - (b->Counter < 0);
		
		// Make sure bike does not turn off of the track
		if(Track_y < 0){
			if(!_KeyCheck(DOWNKEY) || b->Control != g->Calc){
				b->Counter -= 2 - (b->Counter == 1);
				if(b->Counter <= 0)
					b->attr &= ~B_TURNING;  // Bike is no longer Turning
			}else if(b->Counter > 5){ b->attr |= B_MUD; b->Counter = 5; }
		}else if(Track_y > 3){
			if(!_KeyCheck(UPKEY) || b->Control != g->Calc){
				b->Counter += 2 - (b->Counter == -1);
				if(b->Counter >= 0)
					b->attr &= ~B_TURNING;  // Bike is no longer Turning
			}else if(b->Counter < -5){ b->attr |= B_MUD; b->Counter = -5; }
		}
		
		// Check if Bike should no longer be Turning
		if(ABS(b->Counter) >= 12){
			Stop_Turning(b);
			if(g->Calc == b->Control){
				if(_KeyCheck(UPKEY)){
					b->Counter = -1;
					b->attr |= B_TURNING;
				}else if(_KeyCheck(DOWNKEY)){
					b->Counter = 1;
					b->attr |= B_TURNING;
				}
			}
		}else b->y += b->Counter;
	}
	
	if(b->attr & B_JUMPING){
		JumpDat *j = &g->jumpdat[b->Bike_NO];
		b->Counter++;
		
		// The Formula for Bike Jumping Physics
		// Several multiplactions and divisions are saved by only calculating certain variables once
		// at the beginning of a Jump
		b->x = j->Original_x + ((b->Counter * j->cosine_Velocity) / 12);
		j->y = j->Original_y - (((b->Counter * j->sine_Velocity) >> 4) - (((5 * ((long)b->Counter * 
					 b->Counter))) >> 7));
	}else if(b->attr & B_CRASHING){
		if(b->Counter >= 0 && g->delay != 0)
			b->x++;
	}else b->x += (b->addx >> 5);  // Bike is moving normally
*/
}

static void Handle_Computer_Bike(Bike *b){
/*
	if(b->attr & B_CRASHING)
		return;
	register short x = 64 + ((b->Control - AI_MEDIUM) << 5) + random(28);
	if(g->delay == 0)
		b->Temp += (b->Temp < Middle_Temp) - (b->Temp > Middle_Temp);
	
	// Make adjustments to the Bike's behavior
	if(b->attr & B_JUMPING){
		if(b->Tilt != None && g->delay == 0)  // Align Bike's Tilt to Regular Terrain
			b->Tilt += (b->Tilt < Regular1) - (b->Tilt > Regular1);
	}else{
		b->addx += (random(12) != 0) << 2;
		if(b->addx > x)  // Restrict Speed of Bike
			b->addx = x;
		
		if((b->attr & B_TURNING) == 0 && b->addx > 28){
			register short Bikey = RealBike_y(b), x2 = GetTerrain(b->x + 28 + 24);
			if(x2 == Gra1)
				x2 = GetTerrain(b->x + 28 + 12);
			x = GetTerrain(b->x + 28);
			
			// Basic Bike AI -- Avoid Hazardous Obstacles
			if((Bikey & 1 && x >= Rok1 && x <= Rok3) || ((Bikey & 1) == 0 && x >= Rok4 && x <= Rok6)){
				b->Counter = (Bikey != 0) - (((random(2) || Bikey == 0) && Bikey != 3) << 1);
				b->attr |= B_TURNING;
			}else if((Bikey>1 && (x==Blo1||x==Dry2||x==Dry3))||(Bikey==3&&(x2==Blo1||x2==Dry2||x2==Dry3))){
				b->Counter = 1;
				b->attr |= B_TURNING;
			}else if((Bikey<2 && (x==Blo2||x==Dry0||x==Dry1))||(Bikey==0&&(x2==Blo2||x2==Dry0||x2==Dry1))){
				b->Counter = -1;
				b->attr |= B_TURNING;
			}else if(random(180) == 4){
				b->Counter = 1 - (random(2) << 1);
				b->attr |= B_TURNING;
			}
		}
	}
*/
}

// Check if it is valid for the bike to crash and if so, Initiate the bike's crash
void Start_Crash(Bike *b, short Direction){
/*
	// Check if Bike is already Jumping or Crashing
	if(b->attr & B_JUMPING || b->attr & B_CRASHING || (b->x < g->jumpdat[b->Bike_NO].Last_Crash + 8) || 
	(g->Status == End_Wheelie && g->Calc == b->Control))
		return;
	Stop_Turning(b);
	
	// Set up all variables needed to run a Crash
	b->attr    = (b->attr & ~(B_OVERHEAT | B_FLAG3 | B_BLOCK)) | B_CRASHING;
	b->Counter = (b->addx - 24 - (((b->attr & B_TURBO) != 0) << 4)) & ~15;
	b->Tilt    = None;
	if(b->Counter < 16)  // Bike has to flip at least once
		b->Counter = 16;
	if(Direction){  // Bike will be flipping forwards
		b->Counter += (14 - b->Old_Graphic);
		b->attr    |= B_FLAG3;
	}
*/
}

// Check if it is valid for the bike to start a jump and if so, Initiate the bike's jump
void Start_Jump(Bike *b, unsigned long Initial_Velocity){
/*
	register JumpDat *j  = &g->jumpdat[b->Bike_NO];
	
	// Check if Bike is able to Jump
	if(b->attr & (B_JUMPING | B_CRASHING) || (b->x < j->Original_x + 8))
		return;
	
	// Allow for the Bike's speed to (partly) determine the speed of the Bike's Initial Velocity
	if(b->addx < (g->Max_xspeed << 5))
		Initial_Velocity -= ((g->Max_xspeed << 5) - b->addx) >> 1;
	else Initial_Velocity += (b->addx >> 4);
	
	if(b->addx < 45 && b->Control != AI_SLOW)
		Initial_Velocity = 10;
	Stop_Turning(b);
	
	if(g->Cheats & C_MOON)  // Moon Gravity
		Initial_Velocity += (Initial_Velocity >> 2);
	
	b->attr              = (b->attr & ~(B_FLAG1 | B_FLAG2 | B_BLOCK)) | B_JUMPING;
	b->Tilt              = b->Old_Graphic;
	b->Graphic           = b->Old_Graphic;
	b->Counter           = 0;

	j->Original_x        = b->x;
	j->Original_y        = b->y;
	// Tell Angle of the Jump by the Bike's Tilt  (cos[x] = Sin_Table128[4 - x];)
	j->cosine_Velocity   = (Initial_Velocity * Sin_Table128[4 - (Back6 - b->Old_Graphic)]) >> 7;
	j->sine_Velocity     = (Initial_Velocity * Sin_Table128[Back6 - b->Old_Graphic]) >> 7; // x >> 7 = x / 128
	if(b->Control == g->Calc){
		// Allow the User to determine which type of Jump they want by which way they want 
		// the Bike to tilt.  Pressing Back (Left) will give a shorter, higher Jump.  
		// Pressing Forwards (Right) will give a longer, lower Jump.
		j->cosine_Velocity += ((_KeyCheck(RIGHTKEY)) - (_KeyCheck(LEFTKEY))) << 2;
		j->sine_Velocity   -= ((_KeyCheck(RIGHTKEY)) - (_KeyCheck(LEFTKEY))) << 2;
	}else{  // Computer AI has more random jumping
		j->cosine_Velocity += 1 - (random(2) << 1);
		j->sine_Velocity   -= 1 - (random(2) << 1);
	}
	if(j->cosine_Velocity < 0)
		j->cosine_Velocity = 0;
	if(j->sine_Velocity < 0)
		j->sine_Velocity = 0;
*/
}

void Stop_Turning(Bike *b){
/*
	if(b->attr & B_TURNING){
		b->attr &= ~B_TURNING;
		if(ABS(b->Counter) > 5 && !((Bike_y(b)==0 && b->Counter>0) || (Bike_y(b)==3 && b->Counter<0))){
			b->attr = (b->attr & ~B_Y) | (Bike_y(b) + (b->Counter < 0) - (b->Counter > 0));
			b->y += 12 * ((b->Counter > 0) - (b->Counter < 0));
		}
		b->Counter = 0;
	}
*/
}

void New_Text_Message(const char *text){
/*
	strcpy(g->text, text);
	g->text_attr = TEXT_ANIM;
*/
}

static void Handle_Finish_Wheelie(Bike *b){
/*
	b->attr &= ~(B_TURNING | B_CRASHING | B_OVERHEAT);
	
	if(b->Counter < 160 || b->attr & B_JUMPING){
		if(No_Tilt(b))
			b->Tilt = Regular1;
		else if((b->attr & B_JUMPING) == 0 && (b->Tilt == Back4 || b->Tilt == Finish_Wheelie))
			b->Tilt = Finish_Wheelie;
		else if(g->delay == 0)
			b->Tilt += (b->Tilt < Back4) - (b->Tilt > Back4);
		
		b->addx = 40;
		b->Counter++;
	}else if(g->Link == 1){
		b->addx = 0;
		b->Tilt = None;
	}else g->Status = Race_Finished;
*/
}

// Returns an x coordinate in relation to the Camera
static short Real_x(short x){
/*
	register short __x = x - ((g->camera_x - (LCD_WIDTH >> 3)) << 3) + g->softx;
	//register short __x = x + (LCD_WIDTH - (g->camera_x << 3)) + g->softx;
	
	// Correction if a Rider is on a different Lap than the Camera
	while(__x < -((g->Width << 3) + 8 - LCD_WIDTH))
		__x += (g->Width << 3) + 8;
	
	return __x;
*/
}

void MAIN_LOOP(void){
/*
	short Starting = TRUE;
	
	do 
	{
		
		if(g->bikes[g->Camera_Bike].y < 0){
			g->softy = g->bikes[g->Camera_Bike].y;
			
			if(g->softy <= -94){  // Bike is -Completely- off of the screen
				//GrayClearScreen2B_R(Hiddenl, Hiddend);
				memset(Hiddenl + 150, g->Back0, LCD_SIZE - 150);
				memset(Hiddend + 150, g->Back1, LCD_SIZE - 150);
				memcpy(Hiddenl, Terrainl, 150);
				memcpy(Hiddend, Terraind, 150);
			}else{
				register unsigned short offset = -((g->softy << 5) - g->softy - g->softy);  // -30 * g->softy
				/*if(g->softx & 1){
					memset(Hiddenl + 150, (g->Back0 >> 1) | ((g->Back0 & 1) << 7), offset);
					memset(Hiddend + 150, (g->Back1 >> 1) | ((g->Back1 & 1) << 7), offset);
				}else{*/
				memset(Hiddenl + 150, g->Back0, offset);
				memset(Hiddend + 150, g->Back1, offset);
				short No_Lines = g->lcd_height + g->softy - 6;
				
				//											%1								 %2								 %3								 %4
				unsigned char *src0 = Terrainl, *src1 = Terraind, *dest0 = Hiddenl, *dest1 = Hiddend;
				// Copy the Terrain planes (and HUD) onto the Hidden Gray Planes with an offset because 
				// the Camera bike is off the top of the screen
				asm volatile("
				movem.l %%d0-%%d7,-(%%sp);
				
				| Copy the HUD onto the Hidden Gray Planes
				moveq #4,%%d0;
				0:;
				movem.l (%1)+,%%d1-%%d7;  | Light
				movem.l %%d1-%%d7,(%3);
				movem.l (%2)+,%%d1-%%d7;  | Dark
				movem.l %%d1-%%d7,(%4);
				lea (%3,28),%3;
				lea (%4,28),%4;
				move.w (%1)+,(%3)+;  			| Extra 2 Bytes on the Right of the Screen
				move.w (%2)+,(%4)+;
				
				dbra %%d0,0b;             | Loop until we copy all 5 Lines of the HUD
				
				movem.l  (%%sp)+,%%d0-%%d7;
				movem.l %%d0-%%d7,-(%%sp);
				add.l %5,%3;
				add.l %5,%4;
				
				| Copy the Terrain with an offset onto the Hidden Gray Planes
				1:;
				movem.l (%1)+,%%d1-%%d7;  | Light
				movem.l %%d1-%%d7,(%3);
				movem.l (%2)+,%%d1-%%d7;  | Dark
				movem.l %%d1-%%d7,(%4);
				lea (%3,28),%3;
				lea (%4,28),%4;
				move.w (%1)+,(%3)+;   		| Extra 2 Bytes on the Right of the Screen
				move.w (%2)+,(%4)+;
				
				dbra %0,1b;             	| Loop until we copy each Line
				
				movem.l  (%%sp)+,%%d0-%%d7;"
				: "=g" (No_Lines),"=a" (src0),"=a" (src1),"=a" (dest0),"=a" (dest1), "=g" (offset)
				: "0"  (No_Lines),"1"  (src0),"2"  (src1),"3"  (dest0),"4"  (dest1), "5"  (offset));
			}
		}else{  // No Vertical Shifting necessary
			g->softy = 0;
			// Copy Terrain buffers into Secondary, Hidden Gray Planes
			CopyGrayScreens(Terrainl, Terraind, Hiddenl, Hiddend);
			
			//CopyTerrain_ToHidden(Terrainl, Terraind, Hiddenl, Hiddend);
		}
		
		if(_KeyCheck(PAUSEKEY)){
			g->Old_Status = g->Status;
			g->Status = Game_Paused;
		}
		
		if(_KeyCheck (ESCKEY)){
			if(g->Status == End_Wheelie){
				if(g->Link == FALSE) g->Status = Race_Finished;
			}else g->Status = QUIT;
		}
		if(_KeyCheck (TEACHERKEY))
			g->Status = Fast_Quit;
		Update_HUD();
		Update_Bikes();
		
		if(Starting){
			if(Starting == TRUE)
				Start_Race();
			else Dissolve();
			clock->Running = TRUE;
			Starting = FALSE;
		}else{
			// From my benchmarks, just using two plane virtual planes and a custom 
			// Copyscreen function to "switch" the hidden and active plane contents 
			// is much faster than using the built-in Doublebuffering.
			Toggle_Screens_Fast();
		}

		if(g->Status == Game_Paused){
			Pause_Game();
			if(g->Status == Normal){
				if(g->Link == TRUE)
					Starting = 2;
				else clock->Running = TRUE;
			}
		}

		/*if(_keytest (RR_CLEAR)){  // For Debugging Purposes
			while(_keytest(RR_CLEAR));
			while(!_keytest(RR_CLEAR));
			while(_keytest(RR_CLEAR));
		}*/

	} while(Race_is_Running);
	
	clock->Running = FALSE;
	*(volatile unsigned char*)0x600017 = Original_Rate;
	//PRG_setStart(Original_Rate);
	//pokeIO(0x600017, 257 - (g->HW1 ? 79 : 53));  // Restore normal timer speed
	
	if(g->Status == Fast_Quit)
		LeadOut();
	
	if(g->Status == Race_Finished){
		if(g->Link){
			unsigned short Time = (60 * clock->Minutes + clock->Seconds) | (clock->Mseconds50 << 11);
			
			// Exchange times after a Linkplay race
			Transfer(&g->Track[g->Width + 2], (char*)&Time, sizeof(short));
		}
		
		Post_Race(FALSE);
	}else g->Game_Progress = QUIT;
*/
}

void Initialize_Race(short No_Bikes){
/*
	unsigned short Seed = random(3) + 2;
	register unsigned short a;
	
	clock->Reset_Time = TRUE;
	GrayClearScreen2B_R(Terrainl, Terraind);
	g->camera_x    = 0;
	g->softx       = 0;
	g->Old_x       = 0;
	g->No_Bikes    = No_Bikes;
	g->Status      = Normal;
	g->Max_xspeed  = 2 + ((g->Cheats & C_FASTBIKES) != FALSE);  // Fast Bikes Cheat
	g->delay       = 0;
	g->First       = 0;
	g->Animation   = 0;
	g->text[0]     = 0;
	g->OldMinutes  = 0;
	g->OldSeconds  = 0;
	g->OldMseconds50 = 0;
	Initiate_HUD();
	
	static const unsigned char _backs_[6] = {
// Light, Dark
	0x55, 0x00, 
	0x00, 0xFF, 
	0xFF, 0xFF, 
	};
	
	if(g->Cheats & C_BACKGROUND){
		a = 2*random(3);
		g->Back0 = _backs_[a];
		g->Back1 = _backs_[a + 1];
	}else{
		g->Back0 = g->Back1 = FALSE;
	}
	
	for(a = g->No_Bikes; a--;){
		memset(&g->bikes[a], 0, sizeof(Bike));
		g->bikes[a].Control = Seed + a;
		if(g->bikes[a].Control > AI_FAST)
			g->bikes[a].Control -= 3;
		
		g->bikes[a].x       = 13 + (a << 4);
		g->bikes[a].y       = g->lcd_height - 29 - (12 * a);
		g->bikes[a].attr    = a | ((g->bikes[a].Control == AI_FAST) * B_TURBO);
		g->bikes[a].Tilt    = None;
		g->bikes[a].Temp    = Low_Temp;
		g->bikes[a].Bike_NO = a;
		g->jumpdat[a].Original_x = -8;
		g->jumpdat[a].Last_Crash = -8;
	}
	
	if(g->Link){
		g->Camera_Bike      = g->Calc;
		g->bikes[0].Control = Host;
		g->bikes[1].Control = Join;
	}else{
		g->Camera_Bike      = 0;
		g->bikes[0].Control = Host;
		g->Calc             = Host;
	}
	
	// Draw Initial Terrain
	for(; g->camera_x < (LCD_WIDTH>>3) + (TI89); g->camera_x++){
		Tile tile = Tiles[g->Track[g->camera_x]];
		CGraySprite8_OR_R(g->camera_x<<3, g->lcd_height - tile.Height, tile.Height, 
			tile.PtrLight, tile.PtrDark);
		
		if(g->camera_x & 1 && Tiles[g->Track[g->camera_x]].Height <= 56)
			CGraySprite8_OR_R(g->camera_x << 3, g->lcd_height - 64, 8, Hedge, Hedge + 8);
	}
	
	if(g->Cheats & C_BACKGROUND){
		register short b;
		
		for(a = TI89 ? 47 : (47+28); a--;){
			for(b = TI89 ? 21 : 30; b--;){
				unsigned char temp1 = ~(*(Terrainl + 150 + 30*a+b)), temp2 = ~(*(Terraind + 150 + 30*a+b));
				
				*(Terrainl + 150 + 30*a+b) |= (g->Back0 & temp2);
				*(Terraind + 150 + 30*a+b) |= (g->Back1 & temp1);
			}
		}
	}
	
	if(TI89)
		g->camera_x--;
	
	// Draw the 4 Starting Blocks
	for(a = 4; a--;){
		GraySprite8_MASK_R(35 + (a << 4), g->lcd_height - 13 - (12 * a), 10, Starting_Blocks[0], 
			Starting_Blocks[0] + 10, Mask, Mask, Terrainl, Terraind);
	}
*/
}

static void Start_Race(void){
/*
	short Time, a = 3;
	
	for(; a--;)
		GrayClipSprite16_MASK_R(g->Zerox + 44 + 8 + 24 * a, Zeroy + 10, 16, Beep[0], Beep[0] + 16, 
			Beep_Mask, Beep_Mask, Hiddenl, Hiddend);
	
	Dissolve();
	for(a = 0; a < 3; a++){
		for(Time = 158; Time--;){
			pokeIO(0x600005,0b11101); /* low power mode, wake up CPU only on AI 1 
		                                (grayscale), 3 (AMS clock), 4 (Link), 5 
		                                (AMS timer base, needed for APD) and 6 (ON, 
		                                always wakes up the CPU)
		                                -- Saves Battery Power -- */
		if(_KeyCheck (ESCKEY))
			g->Status = QUIT;
		else if(_KeyCheck(TEACHERKEY))
			g->Status = Fast_Quit;
		else continue;
		
		if(g->Link == FALSE)
			return;
	}
		if(TI89){
			GrayClipSprite16_MASK_R(g->Zerox + 44 + 8 + 24 * a, Zeroy + 10, 16, Beep[a + 1], 
				Beep[a + 1] + 16, Beep_Mask, Beep_Mask, Terrainl, Terraind);
		}
		GrayClipSprite16_MASK_R(g->Zerox + 44 + 8 + 24 * a, Zeroy + 10, 16, Beep[a + 1], 
			Beep[a + 1] + 16, Beep_Mask, Beep_Mask, Activel, Actived);
	}
	
	for(a = 4; a--;)
		GraySprite8_MASK_R(35 + (a << 4), g->lcd_height - 13 - (12 * a), 10, Starting_Blocks[1], 
			Starting_Blocks[1] + 10, Mask, Mask, Terrainl, Terraind);
*/
}

#define EXT_SETBLACKPIX(x,y,p0,p1)		EXT_SETPIX(p0,x,y); EXT_SETPIX(p1,x,y)
static void Initiate_HUD(void){
/*
	char buf[40];
	
	// -- Time Limit -- //
	short Seconds = Best_Seconds + 8;
	short Minutes = Best_Minutes;
	if(Seconds >= 60){
		Seconds -= 60;
		Minutes++;
	}else if(Seconds == 8 && Minutes == 0)
		Seconds = 0;
	sprintf(buf, "%d:%02d:%02d - 3rd", Minutes, Seconds, 
		Best_Mseconds50);
	
	FS_DrawString(0, 0, buf, Terrainl, F_4x6);
	FS_DrawString(0, 0, buf, Terraind, F_4x6);
	FS_DrawString(g->Zerox + g->Zerox + 111, 0, "Time -", Terrainl, 
		F_4x6);
	FS_DrawString(g->Zerox + g->Zerox + 111, 0, "Time -", Terraind, 
		F_4x6);
	
	// -- Temp -- //
	Heat_Bar(Terrainl + (TI89 ? 30 + 8 : 30 + 13), Max_Temp >> 1);
	
	// Draw the Heat Box
	EXT_SETPIX(Terraind, g->Zerox + 63, 1);
	EXT_SETPIX(Terraind, g->Zerox + 63 + 33, 1);
	EXT_SETPIX(Terraind, g->Zerox + 63, 2);
	EXT_SETPIX(Terraind, g->Zerox + 63 + 33, 2);
	EXT_SETPIX(Terraind, g->Zerox + 63, 3);
	EXT_SETPIX(Terraind, g->Zerox + 63 + 33, 3);
	const unsigned char Offset = TI89 ? 8 : 13;
	unsigned char a = 4;
	static const unsigned char hud[2][4] = { // (long) 0xEF7BDEF7, 0xD6B5AD6B
		{ 0xD6, 0xB5, 0xAD, 0x6B }, 
		{ 0xEF, 0x7B, 0xDE, 0xF7 }
	};
	
	for(; a--;){
		*((char*)Terrainl + Offset + a) = hud[0][a];
		*((char*)Terrainl + Offset + 120 + a) = hud[0][a];
		*((char*)Terraind + Offset + a) = hud[1][a];
		*((char*)Terraind + Offset + 120 + a) = hud[1][a];
	}
*/
}

static void Update_HUD(void){
/*
	// -- Temp -- //
	Heat_Bar(Hiddend + (TI89 ? 30 + 8 : 30 + 13), g->bikes[g->Camera_Bike].Temp >> 1);
	
	// -- Race Time -- //
	char buf[40];
	sprintf(buf, "%d:%02d:%02d", clock->Minutes, clock->Seconds, (clock->Mseconds50 << 2));
	FS_DrawGrayString(LCD_WIDTH - DrawStrWidth(buf,F_4x6) - 1, 0, buf, A_NORMAL, F_4x6);
*/
}


static inline void Heat_Bar(unsigned char *Dest, short Len){
/*
	register const unsigned char Extra = 0xFF << (8 - (Len & 7));
	register short a = Len >> 3;
	
	for(; a--; Dest++){
		*Dest = 0xFF;
		*(Dest + 30) = 0xFF;
		*(Dest + 60) = 0xFF;
	}
	
	// Remaining Bits
	*Dest |= Extra;
	*(Dest + 30) |= Extra;
	*(Dest + 60) |= Extra;
*/
}

#define Max_Terrain		20
static void Save_Track(unsigned char*);
static short Find_All_Files(char (*)[9], const unsigned short);

void Start_Track_Editor(void){
/*
	static const char edit_menu[][13] = { {"New Track"}, {"Edit Track"}, {"Delete Track"}, {"Back"}, {0} };
	
	short Choice;
	
	do
	{
		Choice = Menu("- Track Editor -",, (char*)edit_menu, 
			13, 0, TRUE);
		
		if(Choice == 0){
			if(Get_Input("New Track Name:", 
			g->Track_Name, 8) != QUIT)
				Run_Editor(FALSE);
			
			return;
		}else if(Choice == 1 || Choice == 2){
			if(Select_External_Track(Choice == 1 ? "- Edit Track -" : "- Delete Track -") == QUIT){
				continue;
			}else if(Choice == 1){  // Edit Track
				Run_Editor(TRUE);
				return;
			}else if(Choice == 2){  // Delete Track
				UnArchive(g->Track_Name);
				if(SymDel(SYMSTR(g->Track_Name)) == TRUE){  // Track successfully deleted
					Message((const char *const[]){ "- Success -", "", "The Track", g->Track_Name, "Has been Deleted", 
						NULL }, A_DISSOLVE | A_WAITKEY);
				}else{
					Message((const char *const[]){ "- Error -", "", "The Track", g->Track_Name, "Cannot be Deleted", 
						NULL }, A_DISSOLVE | A_WAITKEY);
				}
			}
		}else return;
	} while(1);
*/
}

// Returns the bytewidth of a given Terrain type
#define track_width(No) ((widths[(No)] >> 3) + (((No) == 15 || (No) == 16) * 54) + (((No) == 17) * 22))

void Run_Editor(const char Edit_Track){
/*
	static const char edit_menu[][7] = { {"Yes"}, {"No"}, {"Cancel"}, {0} };
	short pos = 0, a, b, Cur_Piece, Fading = TRUE, On = FALSE, wait = 120;
	unsigned char Track[4000], keys[5] = { 0 } /* Left, Right, Gas, Backspace, Turbo */;
	unsigned char Old_Cheats = g->Cheats;
	Tile tile;
	memset(Track, 0, 4000);
	static const unsigned char widths[Max_Terrain + 1] =  // Width for each type of Terrain
	{ 8, 24, 40, 72, 72, 40, 48, 48, 16, 8, 8, 24, 24, 16, 16, 16, 16, 16, 208, 216, 96 };
	//A,  B,  C,  D,  E,  F,  G,  H,  I, J, K,  L,  M,  N,  O,  P,  Q,  R,   S,   T,  /
	
	/* NOTE:
	For a brief description of each type of terrain, see enum Tile_Detections in the 
	file Definitions.h -- */
	
	if(Edit_Track == TRUE){
		a = 0;
		
		do 
		{
			Track[a] = g->Track[a];
		} while(g->Track[a++] < Fi11);
	}
	SafeFree(g->Track);
	
	memset(clock, 0, sizeof(Clock));
	g->camera_x  = 50;
	g->softx     = -1;
	g->Width     = 4000;
	g->Track     = Track;
	g->Cheats    = FALSE;
	
	do 
	{
		GrayClearScreen2B_R(Terrainl, Terraind);
		for(a = 0; a < LCD_WIDTH + (TI89 << 3); a+=8){
			b = g->camera_x - (LCD_WIDTH >> 3) + (a >> 3);
			
			if(On == FALSE && (a > 24 && a < 
			(track_width(Convert_Track(g->camera_x - ((LCD_WIDTH - 32) >> 3), widths)) << 3) + 32)){
				if(Track[g->camera_x - ((LCD_WIDTH - 32) >> 3)] == Gra1)
					continue;
				tile = Tiles[Gra1];
			}else tile = Tiles[Track[b]];
			
			short cut = (TI89 && tile.Height == 96);
			CGraySprite8_OR_R(a, g->lcd_height - tile.Height + cut, tile.Height + cut, 
				tile.PtrLight + cut, tile.PtrDark + cut);
			
			if(b & 1 && tile.Height <= 56)
				CGraySprite8_OR_R(a, g->lcd_height - 64, 8, Hedge, Hedge + 8);
		}
		if(keys[4] != 2) keys[4] = On;
		Draw_Editor(pos, &Fading);
		
		// Delay in Terrain Blinking
		if(keys[4] != 2){
			for(; wait--;){
				pokeIO(0x600005,0b11111); /* low power mode, wake up CPU only on AI 1 
		     	                          (grayscale), 2 (Keypress), 3 (AMS clock), 4 
		      	                         (Link), 5 (AMS timer base, needed for APD) 
		        	                       and 6 (ON, always wakes up the CPU)
		         	                      -- Saves Battery Power -- */
		    if(_rowread(0)){
		    	wait -= 5;
		    	break;
		    }
		  }
		  if(wait <= 0){  // Make the Terrain Blink
				wait = 120;
				On = !On;
			}
			
			if(_KeyCheck(LEFTKEY)){
				if(keys[0] == FALSE || ++keys[0] > 5){
					keys[0] = TRUE;
					if(--pos < 0) pos = Max_Terrain;
				}
			}else keys[0] = FALSE;
			if(_KeyCheck(RIGHTKEY)){
				if(keys[1] == FALSE || ++keys[1] > 5){
					keys[1] = TRUE;
					if(++pos > Max_Terrain) pos = 0;
				}
			}else keys[1] = FALSE;
			
			if(_KeyCheck(ESCKEY)){
				b = FALSE;
				for(a = 0; a < 4000; a++){  // Search for a Finish Line
					if(Track[a] == Fi11){
						b = TRUE;
						break;
					}
				}
				
				g->Track = NULL;
				a = Menu("Save Track?", (char*)edit_menu, 7, 0, TRUE);
				g->Track = Track;
				if(a == 0){   // Exit and save the Track
					if(b == TRUE)
						break;
					// Display Message telling the User to place a Finish Line before saving
					Message((const char *const[]){ "- Save Error -", "", "Must Place Finish Line!", NULL }, 
						A_WAITKEY);
				}else if(a != 2){  // Exit without saving the Track
					g->Cheats = Old_Cheats;
					g->Track  = NULL;
					return;
				}
				
				// Return to the Editor
				Fading = TRUE;
			}
			
			if(_KeyCheck(GASKEY)){  // Choose a piece to set down
				if(keys[2] == FALSE){
					keys[2] = TRUE;
					Cur_Piece = 0;
					for(b = 0; b < pos; b++)
						Cur_Piece += (widths[b] >> 3);
					
					for(a = 0; a < track_width(pos); a++){
						for(b = track_width(Convert_Track(g->camera_x - ((LCD_WIDTH - 32) >> 3) + a, widths)); b--;)
							Track[g->camera_x - ((LCD_WIDTH - 32) >> 3) + a + b] = Gra1;
						
						if(pos == 15 || pos == 16)
							Track[g->camera_x - ((LCD_WIDTH - 32) >> 3) + a] = Cur_Piece + (a != 0 && a != 55);
						else if(pos == 17)
							Track[g->camera_x - ((LCD_WIDTH - 32) >> 3) + a] = Cur_Piece + (a != 0 && a != 23);
						else Track[g->camera_x - ((LCD_WIDTH - 32) >> 3) + a] = Cur_Piece + a;
					}
					On = TRUE;
					wait = 120;
				}
			}else keys[2] = FALSE;
			
			if(_keytest (RR_BCKSPC)){
				if(g->camera_x > 50 && (keys[3] == FALSE || ++keys[3] > 5)){
					keys[3] = TRUE;
					g->camera_x -= track_width(Convert_Track(g->camera_x - ((LCD_WIDTH - 24) >> 3), widths));
					continue;
				}
			}else keys[3] = FALSE;
		}
		
		if(_KeyCheck(TEACHERKEY)){
			g->Track = NULL;
			LeadOut();
		}
		
		if(keys[4] == 2 || (_KeyCheck(TURBOKEY) && keys[4] == TRUE)){
			
			do 
			{
				// Retrieve the currently selected Terrain type
				Cur_Piece = Convert_Track(g->camera_x - ((LCD_WIDTH - 32) >> 3), widths);
				
				// Scroll past the currently selected Terrain
				for(a = 0; a < (track_width(Cur_Piece) << 3); a+=2){
					Shift_Left(2);
					Draw_Editor(pos, &Fading);
				}
				
			} while(_KeyCheck(TURBOKEY) && Cur_Piece != Max_Terrain);
			
			if(Cur_Piece == Max_Terrain)  // Finish Line (End of Track)
				break;
			keys[4] = FALSE;
			On = FALSE;
			wait = 120;
		}
		if(_KeyCheck(TURBOKEY)){
			keys[4] = 2;
			On = TRUE;
		}
	} while (1);
	while(_KeyCheck(ESCKEY));
	
	g->Cheats = Old_Cheats;
	g->Track  = NULL;
	Save_Track(Track);
*/
}

short Convert_Track(short x, const unsigned char *widths){
/*
	short Cur = g->Track[x], b = -1;
	do 
	{
		Cur -= (widths[++b] >> 3);
	} while (Cur >= 0);
	
	return b;
*/
}

void Draw_Editor(short pos, short *Fading){
/*
	short a = Max_Terrain;
	unsigned char No[2] = {0, 0};
	
	CopyGrayScreens(Terrainl, Terraind, Hiddenl, Hiddend);
	GrayClipSprite32_MASK_R(12, g->lcd_height - 24, 24, BikeGfx[Regular1], BikeGfx[Regular1] + 24, 
		BikeGfx[Regular1] + 48, BikeGfx[Regular1] + 48, Hiddenl, Hiddend);
	for(; a--;){
		No[0] = 'A' + a;
		FS_DrawGrayString(7 * a, 0, No, A_SHADOWED, F_6x8);
	}
	
	FS_DrawGrayString(7 * Max_Terrain, 0, "/", A_SHADOWED, F_6x8);
	GrayInvertRect2B(7 * pos, 0, 7 * pos + 6, 7, Hiddenl, Hiddend);

	if(*Fading == TRUE){
		*Fading = FALSE;
		Dissolve();
	}else Toggle_Screens_Fast();
*/
}

static void Save_Track(unsigned char *Track){
/*
	g->Width = 0;
	
	while(Track[++g->Width] < Fi11);
	// Ask User for the Number of Laps in their custom level
	if((Track[g->Width + 1] = Get_Number("Number of Laps?", 
		2, 1, 9)) == FALSE)
		return;
	//Track[g->Width + 2] = 0;
	//Track[g->Width + 3] = 0;

	if(Save_File(g->Track_Name, Track, g->Width + 2) == FALSE)
		Message((const char *const[]){ "- Error -", "", "Track save has Failed", NULL }, 
			A_DISSOLVE | A_WAITKEY);
	else Message((const char *const[]){ "- Success -", "", "Track has been Saved", NULL }, 
			A_DISSOLVE | A_WAITKEY);
*/
}

// Decompress, allocate, and Load a Track
short Load_Track(unsigned char *Track){
/*
	if(Track == NULL)
		return QUIT;
	
	SafeFree(g->Track);
	char Best_Time1 = *Track++, Best_Time2 = *Track++;
	if((g->Track = malloc(*(unsigned short*)Track + 2)) == NULL)
		return QUIT;
	
	// Decompress the external track's data into the newly allocated Track buffer
	DecompressRLE(g->Track, (Track + 2), *(unsigned short*)Track);
	
	// Determine the Track's Length by searching for the End of the Finish Line
	//g->Width = 0;
	//g->Width = *(unsigned short*)Track - 2 - 2 * (g->Game_Progress == QUIT);
	g->Width = *(unsigned short*)Track - 2;
	g->Track[g->Width + 2] = Best_Time1;
	g->Track[g->Width + 3] = Best_Time2;
	//while(g->Track[++g->Width] < Fi11);
	return 0;
*/
}

short Select_External_Track(const char *Title){
/*
	char tracks[99][9];
	short Choice;
	
	if(Find_All_Files(tracks, Track_Magic) > 0){
		if((Choice = Menu(Title, (char*)tracks, 9, 0, TRUE)) != QUIT){
			if(Load_Track(Get_Data_Ptr(tracks[Choice], 2)) != QUIT){
				strcpy(g->Track_Name, tracks[Choice]);
				return 0;  // Track Successfully Decompressed and Loaded
			}else{
				Message((const char *const[]){ "- Error -", "", "Loading Track has", "Failed", NULL }, 
					A_DISSOLVE | A_WAITKEY);
			}
		}
	}else{
		Message((const char *const[]){ "- Error -", "", "No External Tracks", "Located on Calc", NULL }, 
			A_DISSOLVE | A_WAITKEY);
	}
	
	return QUIT;
*/
}

static short Find_All_Files(char (*File_Names)[9], const unsigned short Magic_NO){
/*
	short Counter = 0;
	SYM_ENTRY *SymPtr = SymFindFirst (NULL, FO_RECURSE);
	
	while(SymPtr != NULL){
		if(*(unsigned short*)(HeapDeref(SymPtr->handle) + 2) == Magic_NO)
			strcpy(File_Names[Counter++], SymPtr->name);
		SymPtr = SymFindNext();
	}
	
	File_Names[Counter][0] = 0;
	return Counter;
*/
}

short Best_Times(short i){
/*
	unsigned short *file = NULL, Time;
	
	if(g->Game_Progress == QUIT || (file = (short*)Get_Data_Ptr(exctimes, g->Game_Progress * 2)) == NULL)
		Time = (short)((g->Track[g->Width + 2] << 8) + (g->Track[g->Width + 3]));
	else Time = *file;
	
	if(i == 0)  // Minutes
		Time = (Time & 0x07FF) / 60;
	if(i == 1)  // Seconds
		Time = (Time & 0x07FF) % 60;
	if(i == 2)  // Mseconds50
		Time = (Time & 0xF800) >> 9;
	
	return Time;
*/
}

short New_Track_Record(void){
/*
	unsigned short Time = (60 * clock->Minutes + clock->Seconds) | (clock->Mseconds50 << 11);
	char *Base;
	
	if(g->Game_Progress == QUIT){ // Track is loaded from an external file
		UnArchive(g->Track_Name);
		
		// Locate File Base
		if((Base = Get_Data_Ptr(g->Track_Name, 2)) == NULL)
			return FALSE;
		
		/*short a;
		for(a = -5; a < 5; a++){
			PortSet(Hiddend, 239, 127);
			printf_xy(0, 7*(a + 5), "%d %d", *(char*)(Base + (*(unsigned short*)Base - 6 - 
				((*(short*)(Base + 4)) & 1)) + a), ((*(short*)(Base + 4)) & 1));
			PortSet(Hiddenl, 239, 127);
			printf_xy(0, 7*(a + 5), "%d %d", *(char*)(Base + (*(unsigned short*)Base - 6 - 
				((*(short*)(Base + 4)) & 1)) + a), ((*(short*)(Base + 4)) & 1));
		}
		CopyGrayScreens(Hiddenl, Hiddend, Activel, Actived);
		
		while(!_keytest(RR_CLEAR));
		while(_keytest(RR_CLEAR));*/
		//Base += *(unsigned short*)Base - 6 - ((*(short*)(Base + 4)) & 1);
		
		// Write record to the file
		*(Base + 0) = (char)(Time >> 8);
		*(Base + 1) = (char)Time;
		
		Archive(g->Track_Name);
	}else{  // One of the Default Tracks
		const unsigned char Tag[6] = { 0, 'r', 'e', 'c', 0, OTH_TAG };
		unsigned short Size = sizeof(Default_Times) + sizeof(Tag) + 2;
		HANDLE h;
		
		UnArchive(exctimes);  // Make sure that before writing to the file, it is not archived
		
		if((Base = Get_Data_Ptr(exctimes, 0)) == NULL){
			if((h = HeapAlloc(Size)) == H_NULL)
				return FALSE;
			if((Base = HeapDeref(DerefSym(SymAdd(SYMSTR(exctimes)))->handle = h)) == NULL){
				HeapFree(h);
		    return FALSE;
			}
			*(short*)Base = Size - 2;
			Base += 2;
			memcpy(Base, &Default_Times, sizeof(Default_Times));
			memcpy(Base + sizeof(Default_Times), &Tag, sizeof(Tag));
		}
		// Write the new record time to the file
		*(short*)(Base + 2 * g->Game_Progress) = Time;
		
		Archive(exctimes);    // Automatically Archive the file in case of a crash
	}
	
	return TRUE;
*/
}

short Save_File(const char *FileName, unsigned char *Data, unsigned long Size){
/*
	const unsigned char Tag[6] = { 0, 'l', 'v', 'l', 0, OTH_TAG };
	const unsigned short Uncompressed_Size = Size;
	char *Base;
	HANDLE h;
	Size = CompressRLE(Data, Size);  // RLE Compress the File
	struct {
		unsigned short size;
		unsigned short Magic_No;
		unsigned short Best_Time;
		unsigned short Track_Size;
		unsigned char Data[Size + (Size & 1)];
		unsigned char Tag[6];
	} Save_File;
	
	Save_File.Magic_No = Track_Magic;
	Save_File.Best_Time = 0;
	Save_File.Track_Size = Uncompressed_Size;
	memcpy(&Save_File.Data, Data, Size);
	memcpy(&Save_File.Tag, Tag, 6);
	Size = sizeof(Save_File);
	Save_File.size = Size - 2;
	
	UnArchive(FileName);  // Make sure that before writing to the file, it is not archived
	
	if((h = HeapAlloc(Size)) == H_NULL)
		return FALSE;
	if((Base = HeapDeref(DerefSym(SymAdd(SYMSTR(FileName)))->handle = h)) == NULL){
		HeapFree(h);
    return FALSE;
	}
	memcpy(Base, &Save_File, Size);
	
	Archive(FileName);    // Automatically Archive the file in case of a crash
	return TRUE;
*/
}

unsigned char *Get_Data_Ptr(const char *Filename, short Offset){
/*
	unsigned char *Location;
	SYM_ENTRY *SymPtr;
	
	if((SymPtr = SymFindPtr(SYMSTR(Filename), 0)) == NULL)
		return NULL;  // File not found
	
	if((Location = (unsigned char*) HeapDeref(SymPtr->handle)) == NULL)
		return NULL;
	return (Location + 2 + Offset);
*/
}

void Archive(const char *Filename){
/*
	SYM_ENTRY *SymPtr = NULL;
	HSym hsym = SymFind(SYMSTR(Filename));
	
	SymPtr = DerefSym (hsym);
	
	if(EM_findEmptySlot(*Get_Data_Ptr(Filename, -2)) == NULL)
		return;  // Make sure Garbage Collection will not occur
	if(!SymPtr->flags.bits.archived)
		EM_moveSymToExtMem(SYMSTR(Filename), HS_NULL);
*/
}

void UnArchive(const char *Filename){
/*
	SYM_ENTRY *SymPtr = NULL;
	HSym hsym = SymFind(SYMSTR(Filename));
	
	SymPtr = DerefSym (hsym);
	
	if(SymPtr->flags.bits.archived)
		EM_moveSymFromExtMem(SYMSTR(Filename), HS_NULL);
*/
}