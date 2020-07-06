/*  CONIO.H style Text mode support  for the Mega65 libC

    Copyright (c) 2020 Hernán Di Pietro

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 
    Version   0.4
    Date      2020-06-28
*/

#ifndef M65LIBC_CONIO_H
#define M65LIBC_CONIO_H
#include "../include/memory.h"

#define VIC_BASE            0xD000UL
#define REG_H640            (PEEK(VIC_BASE+0x31) & 128)
#define REG_V400            (PEEK(VIC_BASE+0x31) & 8)
#define REG_16BITCHARSET    (PEEK(VIC_BASE + 0x54) & 1)
#define SCREEN_RAM_BASE_B0  (PEEK(VIC_BASE + 0x60)) // LSB
#define SCREEN_RAM_BASE_B1  (PEEK(VIC_BASE + 0x61))
#define SCREEN_RAM_BASE_B2  (PEEK(VIC_BASE + 0x62))
#define SCREEN_RAM_BASE_B3  (PEEK(VIC_BASE + 0x63) & 7) // upper nybble
#define SCREEN_RAM_BASE     ( ((long)SCREEN_RAM_BASE_B3 << 24) | ((long)SCREEN_RAM_BASE_B2 << 16) | ((long)SCREEN_RAM_BASE_B1 << 8) | (SCREEN_RAM_BASE_B0) )  
#define COLOR_RAM_BASE      0x1F800UL

#define ATTRIB_BLINK      0x10
#define ATTRIB_REVERSE    0x20
#define ATTRIB_UNDERLINE  0x80
#define ATTRIB_HIGHLIGHT  0x40

#define COLOUR_BLACK        0
#define COLOUR_WHITE        1
#define COLOUR_RED          2
#define COLOUR_CYAN         3
#define COLOUR_PURPLE       4
#define COLOUR_GREEN        5
#define COLOUR_BLUE         6
#define COLOUR_YELLOW       7
#define COLOUR_ORANGE       8
#define COLOUR_BROWN        9
#define COLOUR_PINK         10
#define COLOUR_GREY1        11
#define COLOUR_DARKGREY     11
#define COLOUR_GREY2        12
#define COLOUR_GREY         12
#define COLOUR_MEDIUMGREY   12
#define COLOUR_LIGHTGREEN   13
#define COLOUR_LIGHTBLUE    14
#define COLOUR_GREY3        15
#define COLOUR_LIGHTGREY    15

/*------------------------------------------------------------------------
  Keyboard ASCII codes 
  -----------------------------------------------------------------------*/
#define ASC_A
#define ASC_B
#define ASC_C
#define ASC_D
#define ASC_E
#define ASC_F
#define ASC_G
#define ASC_H
#define ASC_I
#define ASC_J
#define ASC_K
#define ASC_L
#define ASC_M
#define ASC_N
#define ASC_O
#define ASC_P
#define ASC_Q
#define ASC_R
#define ASC_S
#define ASC_T
#define ASC_U
#define ASC_V
#define ASC_W
#define ASC_X
#define ASC_Y
#define ASC_Z
#define ASC_F1
#define ASC_F3
#define ASC_F5
#define ASC_F7
#define ASC_F9
#define ASC_F11
#define ASC_F13
#define ASC_CRSR_RIGHT
#define ASC_CRSR_LEFT
#define ASC_CRSR_UP
#define ASC_CRSR_DOWN
/*------------------------------------------------------------------------
  Keyboard modifiers
  -----------------------------------------------------------------------*/

#define KEYMOD_RSHIFT   1
#define KEYMOD_LSHIFT   2
#define KEYMOD_CTRL     4
#define KEYMOD_MEGA     8
#define KEYMOD_ALT      16
#define KEYMOD_NOSCRL   32
#define KEYMOD_CAPSLOCK 64

/*------------------------------------------------------------------------
  Screen configuration and setup
  -----------------------------------------------------------------------*/

/* Initialize library internal state */
void conioinit(void);

/* Sets the active screen RAM address */
void setscreenaddr(long addr);

/* Gets the currently active screen RAM address */
long getscreenaddr(void);

 /* Clear the text screen. Color RAM will be cleared with current text color */
void clrscr(void); 

 /* Returns the dimensions of the text mode screen.  
    Ignores any virtual chargen dimensions */
void fastcall screensize(unsigned char* width, unsigned char* height);

/*------------------------------------------------------------------------
  Color and Attributes
  -----------------------------------------------------------------------*/

/* Set the current border color */
void fastcall bordercolor(unsigned char c);

/* Set the current screen color */
void fastcall bgcolor(unsigned char c);

/* Set the current text color*/
void fastcall textcolor(unsigned char c);

/* Enable the reverse attribute */
void fastcall revers(unsigned char enable);

/* Enable the highlight attribute */
void fastcall highlight(unsigned char enable);

/* Enable the highlight attribute */
void fastcall blink(unsigned char enable);

/* Enable the highlight attribute */
void fastcall underline(unsigned char enable);

/* Set color of character cell */
void cellcolor(unsigned char x, unsigned char y, unsigned char c);


/*------------------------------------------------------------------------
  Cursor Movement
  -----------------------------------------------------------------------*/

/* Put cursor at home (0,0) */
void fastcall gohome(void);

/* Put cursor at X,Y. 
   The function does not check for screen bounds! */
void fastcall gotoxy(unsigned char x, unsigned char y);

/* Put cursor at column X. The function does not check for screen bounds */
void fastcall gotox(unsigned char x);

/* Put cursor at row Y. The function does not check for screen bounds */
void fastcall gotoy(unsigned char x);

/* Move cursor up X times with wraparound */
void fastcall moveup(unsigned char count);

/* Move cursor down X times with wraparound */
void fastcall movedown(unsigned char count);

/* Move cursor left X times, going to next line.*/ 
void fastcall moveleft(unsigned char count);

/* Move cursor right X times, going to prev line*/
void fastcall moveright(unsigned char count);

/* Enable cursor */
void fastcall cursor(unsigned char enable);

/*------------------------------------------------------------------------
  Text output
  -----------------------------------------------------------------------*/

/* Output a single character at current position */
void fastcall cputc(unsigned char c);

/* Output an hex-formatted number at current position with prec digits */
void cputhex(long n, unsigned char prec);

/* Output a decimal number at current position with padding digits */
void cputdec(long n, unsigned char padding, unsigned char leadingZ);

/* Output a string at current position */
void fastcall cputs(const char* s);

/* Output a string at x,y */
void cputsxy (unsigned char x, unsigned char y, const char* s);

/* Output a character at x,y */
void cputcxy (unsigned char x, unsigned char y, char c);

/*  Print formatted output. 
    
    Escape strings can be used to modify attributes, move cursor,etc,
    similar to PRINT in CBM BASIC. Available escape codes:
   
    Cursor positioning 

    \t           Go to next tab position (multiple of 8s)
    \r           Return
    \n           New-line (assume \r like in C printf)

    \{clr}       Clear screen       \{home}      Move cursor to home (top-left)
    \{down}      Move cursor down   \{up}        Move cursor up
    \{right}     Move cursor right  \{left}      Move cursor left

    Attributes

    \{rvson}     Reverse attribute ON   \{rvsoff}    Reverse attribute OFF
    \{blinkon}   Reverse attribute ON   \{blinkoff}  Reverse attribute OFF
    \{hiliteon}  Reverse attribute ON   \{hiliteoff} Reverse attribute OFF
    \{underon}   Reverse attribute ON   \{underoff}  Reverse attribute OFF

    Colors (default palette 0-15)

    \{black}    \{white}    \{red}      \{cyan}     \{purple}   
    \{green}    \{blue}     \{yellow}   \{orange}   \{brown}    
    \{pink}     \{grey1}    \{grey2}    \{grey2}    \{ltgreen} 
    \{ltblue}   \{grey3}
*/

unsigned char cprintf (const unsigned char* format, ...);

/*------------------------------------------------------------------------
  Keyboard input 
  -----------------------------------------------------------------------*/
/* Wait until a character is in the keyboard buffer and return it */
unsigned char fastcall cgetc (void);

/* Return the character in the keyboard buffer, if any */
unsigned char fastcall kbhit (void);

/* Return the key modifiers state, where bits:

    Bit           Meaning
    -----------------------------------------
    0             Right SHIFT state
    1             Left  SHIFT state
    2             CTRL state
    3             MEGA/C= state
    4             ALT state
    5             NOSCRL state
    6             CAPSLOCK state
    7             Reserved
*/
unsigned char fastcall getkeymodstate(void);

void cscanf(const char* format, ...);


#endif //M65LIBC_CONIO_H


