// ****************************************************************************
//          key code
//  
// ****************************************************************************




	#define OSDK_BACKSPACE   8 
	#define OSDK_TAB         9 
	#define OSDK_CLEAR     0xC  // 12 
	#define OSDK_RETURN    0xD  // 13 
	#define OSDK_PAUSE     0x13 // 19 
	#define OSDK_ESCAPE    0x1B // 27 
	#define OSDK_SPACE     0x20 // 32 
	#define OSDK_EXCLAIM   0x21 // 33 
	#define OSDK_QUOTEDBL  0x22 // 34 
	#define OSDK_HASH      0x23 // 35 
	#define OSDK_DOLLAR    0x24 // 36 
	#define OSDK_AMPERSAND 0x26 // 38 
	#define OSDK_QUOTE     0x27 // 39 
	#define OSDK_LEFTPAREN 0x28 // 40 
	#define OSDK_RIGHTPAREN 0x29 //41 
	#define OSDK_ASTERISK   0x2A //42 
	#define OSDK_PLUS       0x2B //43 
	#define OSDK_COMMA      0x2C //44 
	#define OSDK_MINUS      0x2D //45 
	#define OSDK_PERIOD     0x2E //46 
	#define OSDK_SLASH      0x2F //47 
	#define OSDK_0 '0' 
	#define OSDK_1 '1' 
	#define OSDK_2 '2' 
	#define OSDK_3 '3' 
	#define OSDK_4 '4' 
	#define OSDK_5 '5' 
	#define OSDK_6 '6' 
	#define OSDK_7 '7' 
	#define OSDK_8 '8' 
	#define OSDK_9 '9' 
	#define OSDK_COLON     0x3A // 58 
	#define OSDK_SEMICOLON 0x3B // 59 
	#define OSDK_LESS      0x3C // 60 
	#define OSDK_EQUALS    0x3D // 61 
	#define OSDK_GREATER   0x3E // 62 
	#define OSDK_QUESTION  0x3F // 63 
	#define OSDK_AT        0x40 // 64 
	#define OSDK_UPPER     0x5e //0xDE

	#define OSDK_LEFTBRACKET  0x5B // 91 
	#define OSDK_BACKSLASH    0x5C // 92 
	#define OSDK_RIGHTBRACKET 0x5D // 93 
	#define OSDK_CARET        0x5E // 94 
	#define OSDK_UNDERSCORE   0x5F // 95 
	#define OSDK_BACKQUOTE    0x60 // 96 
	#define OSDK_A 'a' // 97 
	#define OSDK_B 'b' // 98 
	#define OSDK_C 'c' // 99 
	#define OSDK_D 'd' // 100 
	#define OSDK_E 'e' // 101 
	#define OSDK_F 'f' // 102 
	#define OSDK_G 'g' // 103 
	#define OSDK_H 'h' // 104 
	#define OSDK_I 'i' // 105 
	#define OSDK_J 'j' // 106 
	#define OSDK_K 'k' // 107 
	#define OSDK_L 'l' // 108 
	#define OSDK_M 'm' // 109 
	#define OSDK_N 'n' // 110 
	#define OSDK_O 'o' // 111 
	#define OSDK_P 'p' // 112 
	#define OSDK_Q 'q' // 113 
	#define OSDK_R 'r' // 114 
	#define OSDK_S 's' // 115 
	#define OSDK_T 't' // 116 
	#define OSDK_U 'u' // 117 
	#define OSDK_V 'v' // 118 
	#define OSDK_W 'w' // 119 
	#define OSDK_X 'x' // 120 
	#define OSDK_Y 'y' // 121 
	#define OSDK_Z 'z' // 122 
	#define OSDK_DELETE 0x7f //127 

	//#define OSDK_WORLD_0 160		


	#define OSDK_KP0 256 
	#define OSDK_KP1 257 
	#define OSDK_KP2 258 
	#define OSDK_KP3 259 
	#define OSDK_KP4 260 
	#define OSDK_KP5 261 
	#define OSDK_KP6 262 
	#define OSDK_KP7 263 
	#define OSDK_KP8 264 
	#define OSDK_KP9 265 
	#define OSDK_KP_PERIOD 266 
	#define OSDK_KP_DIVIDE  267 
	#define OSDK_KP_MULTIPLY 268 
	#define OSDK_KP_MINUS 269 
	#define OSDK_KP_PLUS 270 
	#define OSDK_KP _ENTER 271 
	#define OSDK_KP_EQUALS  272 


	#define OSDK_UP    0x111   // 273 
	#define OSDK_DOWN  0x112   // 274 
	#define OSDK_RIGHT 0x113    // 275 
	#define OSDK_LEFT  0x114    // 276 
	#define OSDK_INSERT 0x115   //277 
	#define OSDK_HOME  0x116    // 278 
	#define OSDK_END   0x117    // 279 
	#define OSDK_PAGEUP 0x118   //280 
	#define OSDK_PAGEDOWN 0x119 //281 

	#define OSDK_F1 282 
	#define OSDK_F2 283 
	#define OSDK_F3 284 
	#define OSDK_F4 285 
	#define OSDK_F5 286 
	#define OSDK_F6 287 
	#define OSDK_F7 288 
	#define OSDK_F8 289 
	#define OSDK_F9 290 
	#define OSDK_F10 291 
	#define OSDK_F11 292 
	#define OSDK_F12 293 
	#define OSDK_F13 294 
	#define OSDK_F14 295 
	#define OSDK_F15 296 

	#define OSDK_NUMLOCK 300 
	#define OSDK_CAPSLOCK 301 
	#define OSDK_SCROLLOCK 302 
	#define OSDK_RSHIFT 303 
	#define OSDK_LSHIFT 304
    #define OSDK_SHIFT  600
    
	#define OSDK_RCTRL 305 
	#define OSDK_LCTRL 306 
	#define OSDK_CTRL  601
	
	#define OSDK_RALT 307 
	#define OSDK_LALT 308 
	#define OSDK_ALT   602
	
	#define OSDK_RMETA 309 
	#define OSDK_LMETA 310 
	#define OSDK_LSUPER 311				/* Left "Windows" key */ 
	#define OSDK_RSUPER 312				/* Right "Windows" key */ 
	#define OSDK_MODE 313				  /* "Alt Gr" key */ 
	#define OSDK_COMPOSE 314		/* Multi-key compose key */ 


	#define OSDK_KANA 0x13f     /* add kana  2009/12/17 */

