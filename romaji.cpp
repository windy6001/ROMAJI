/*
name is romaji.c

Copyright (c) 2020-2022 Windy
Version 2.0

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

 https://github.com/windy6001/ROMAJI/
*/

#include <memory.h>
#include "keys.h"
#include "romaji.h"
#include "log.h"


int kanaMode=1;
int katakana=1;

// ****************************************************************************
//      P6 キーコード
// ****************************************************************************

enum {
P6_WO=0x86, 
P6_LA,     P6_LI,  P6_LU  ,P6_LE, P6_LO, P6_LYA, P6_LYU ,P6_LYO ,P6_LTU,
P6_A =0x91,P6_I ,  P6_U   ,P6_E  ,P6_O , P6_KA , P6_KI  ,P6_KU  ,P6_KE  ,P6_KO,
P6_SA,     P6_SI,  P6_SU  ,P6_SE ,P6_SO, 
P6_DOKUTEN=0xA1 ,P6_KUTOUTEN=0xA4,P6_CYOUON= 0xB0,
P6_TA=0xE0,P6_TI , P6_TU  ,P6_TE,  P6_TO,
P6_NA     ,P6_NI , P6_NU  ,P6_NE , P6_NO, 
P6_HA     ,P6_HI , P6_HU  ,P6_HE , P6_HO,
P6_MA     ,P6_MI , P6_MU  ,P6_ME , P6_MO ,
P6_YA     ,P6_YU , P6_YO  , 
P6_RA     ,P6_RI , P6_RU  ,P6_RE , P6_RO , P6_WA , P6_N,
P6_DD=0xDE , P6_HD=0xDF		// P6_DD=濁点、 P6_HD=半濁点
};




// ****************************************************************************
//          ローマ字変換テーブル
// ****************************************************************************
struct _romaji_tbl {
    int num;
    const char romaji[4];
    const unsigned char keycode[7];
};

static struct _romaji_tbl romaji_tbl[] = {

{2,{ OSDK_L ,OSDK_L  ,0      ,0}, {P6_LTU}},	// っ        一番最初のデータは、「っ」でないといけない
{3,{ OSDK_L ,OSDK_T  ,OSDK_U ,0}, {P6_LTU}},	// っ

{1,{ OSDK_A , 0      , 0    ,0}, {P6_A }},		// あいうえお
{1,{ OSDK_I , 0      , 0    ,0}, {P6_I }},
{1,{ OSDK_U , 0      , 0    ,0}, {P6_U }},
{1,{ OSDK_E , 0      , 0    ,0}, {P6_E }},
{1,{ OSDK_O , 0      , 0    ,0}, {P6_O }},

{2,{ OSDK_L ,OSDK_A  ,0      ,0}, {P6_LA}},	// ぁ
{2,{ OSDK_L ,OSDK_I  ,0      ,0}, {P6_LI}},	// ぃ
{2,{ OSDK_L ,OSDK_U  ,0      ,0}, {P6_LU}},	// ぅ
{2,{ OSDK_L ,OSDK_E  ,0      ,0}, {P6_LE}},	// ぇ
{2,{ OSDK_L ,OSDK_O  ,0      ,0}, {P6_LO}},	// ぉ

{ 2,{ OSDK_X ,OSDK_A  ,0      ,0 },{P6_LA} },	// ぁ
{ 2,{ OSDK_X ,OSDK_I  ,0      ,0 },{P6_LI} },	// ぃ
{ 2,{ OSDK_X ,OSDK_U  ,0      ,0 },{P6_LU} },	// ぅ
{ 2,{ OSDK_X ,OSDK_E  ,0      ,0 },{P6_LE} },	// ぇ
{ 2,{ OSDK_X ,OSDK_O  ,0      ,0 },{P6_LO} },	// ぉ

{ 3,{ OSDK_W ,OSDK_H  ,OSDK_A ,0 },{P6_U, P6_LA} },	// うぁ
{ 3,{ OSDK_W ,OSDK_H  ,OSDK_I ,0 },{P6_U, P6_LI} },	// うぃ
{ 2,{ OSDK_W ,OSDK_I  ,0      ,0 },{P6_U, P6_LI} },	// うぃ
{ 2,{ OSDK_W ,OSDK_U  ,0      ,0 },{P6_U       } },  // う
{ 3,{ OSDK_W ,OSDK_H  ,OSDK_E ,0 },{P6_U, P6_LE} },	// うぇ
{ 2,{ OSDK_W ,OSDK_E  ,0      ,0 },{P6_U, P6_LE} },	// うぇ
{ 3,{ OSDK_W ,OSDK_H  ,OSDK_O ,0 },{P6_U, P6_LO} },	// うぉ


{2,{ OSDK_K ,OSDK_A  , 0    ,0}, {P6_KA}},		// かきくけこ
{2,{ OSDK_K ,OSDK_I  , 0    ,0}, {P6_KI}},
{2,{ OSDK_K ,OSDK_U  , 0    ,0}, {P6_KU}},
{2,{ OSDK_K ,OSDK_E  , 0    ,0}, {P6_KE}},
{2,{ OSDK_K ,OSDK_O  , 0    ,0}, {P6_KO}},

{3,{ OSDK_K ,OSDK_Y  ,OSDK_A ,0}, {P6_KI,P6_LYA}},	// きゃきぃきゅきぇきょ
{3,{ OSDK_K ,OSDK_Y  ,OSDK_I ,0}, {P6_KI,P6_LI}},
{3,{ OSDK_K ,OSDK_Y  ,OSDK_U ,0}, {P6_KI,P6_LYU}},
{3,{ OSDK_K ,OSDK_Y  ,OSDK_E ,0}, {P6_KI,P6_LE}},
{3,{ OSDK_K ,OSDK_Y  ,OSDK_O ,0}, {P6_KI,P6_LYO}},

{2,{ OSDK_G ,OSDK_A  ,0      ,0}, {P6_KA,P6_DD}},	// がぎぐげご
{2,{ OSDK_G ,OSDK_I  ,0      ,0}, {P6_KI,P6_DD}},
{2,{ OSDK_G ,OSDK_U  ,0      ,0}, {P6_KU,P6_DD}},
{2,{ OSDK_G ,OSDK_E  ,0      ,0}, {P6_KE,P6_DD}},
{2,{ OSDK_G ,OSDK_O  ,0      ,0}, {P6_KO,P6_DD}},

{3,{ OSDK_G ,OSDK_Y  ,OSDK_A ,0}, {P6_KI, P6_DD, P6_LYA}},// ぎゃぎぃぎゅぎぇぎょ
{3,{ OSDK_G ,OSDK_Y  ,OSDK_I ,0}, {P6_KI, P6_DD, P6_LI}},
{3,{ OSDK_G ,OSDK_Y  ,OSDK_U ,0}, {P6_KI, P6_DD, P6_LYU}},
{3,{ OSDK_G ,OSDK_Y  ,OSDK_E ,0}, {P6_KI, P6_DD, P6_LE}},
{3,{ OSDK_G ,OSDK_Y  ,OSDK_O ,0}, {P6_KI, P6_DD, P6_LYO}},

{3,{ OSDK_G ,OSDK_W  ,OSDK_A ,0}, {P6_KU, P6_DD, P6_LA}},// ぐぁぐぃぐぅぐぇぐぉ
{3,{ OSDK_G ,OSDK_W  ,OSDK_I ,0}, {P6_KU, P6_DD, P6_LI}},
{3,{ OSDK_G ,OSDK_W  ,OSDK_U ,0}, {P6_KU, P6_DD, P6_LU}},
{3,{ OSDK_G ,OSDK_W  ,OSDK_E ,0}, {P6_KU, P6_DD, P6_LE}},
{3,{ OSDK_G ,OSDK_W  ,OSDK_O ,0}, {P6_KU, P6_DD, P6_LO}},

{2,{ OSDK_S ,OSDK_A  , 0     ,0}, {P6_SA}},		// さしすせそ
{2,{ OSDK_S ,OSDK_I  , 0     ,0}, {P6_SI}},
{3,{ OSDK_S ,OSDK_H  ,OSDK_I ,0}, {P6_SI}},
{2,{ OSDK_S ,OSDK_U  , 0     ,0}, {P6_SU}},
{2,{ OSDK_S ,OSDK_E  , 0     ,0}, {P6_SE}},
{2,{ OSDK_S ,OSDK_O  , 0     ,0}, {P6_SO}},

{3,{ OSDK_S ,OSDK_Y  ,OSDK_A ,0}, {P6_SI, P6_LYA}},	// しゃしぃしゅしぇしょ
{3,{ OSDK_S ,OSDK_Y  ,OSDK_I ,0}, {P6_SI, P6_LI}},
{3,{ OSDK_S ,OSDK_Y  ,OSDK_U ,0}, {P6_SI, P6_LYU}},
{3,{ OSDK_S ,OSDK_Y  ,OSDK_E ,0}, {P6_SI, P6_LE}},
{3,{ OSDK_S ,OSDK_Y  ,OSDK_O ,0}, {P6_SI, P6_LYO}},

{3,{ OSDK_S ,OSDK_H  ,OSDK_A ,0}, {P6_SI, P6_LYA}},	// しゃしゅ　しぇしょ
{3,{ OSDK_S ,OSDK_H  ,OSDK_U ,0}, {P6_SI, P6_LYU}},
{3,{ OSDK_S ,OSDK_H  ,OSDK_E ,0}, {P6_SI, P6_LE}},
{3,{ OSDK_S ,OSDK_H  ,OSDK_O ,0}, {P6_SI, P6_LYO}},

{3,{ OSDK_S ,OSDK_W  ,OSDK_A ,0}, {P6_SU, P6_LA}},	// すぁすぃすぅすぇすぉ
{3,{ OSDK_S ,OSDK_W  ,OSDK_I ,0}, {P6_SU, P6_LI}},
{3,{ OSDK_S ,OSDK_W  ,OSDK_U ,0}, {P6_SU, P6_LU}},
{3,{ OSDK_S ,OSDK_W  ,OSDK_E ,0}, {P6_SU, P6_LE}},
{3,{ OSDK_S ,OSDK_W  ,OSDK_O ,0}, {P6_SU, P6_LO}},

{2,{ OSDK_Z ,OSDK_A  ,0      ,0}, {P6_SA, P6_DD}},	// ざじずぜぞ
{2,{ OSDK_Z ,OSDK_I  ,0      ,0}, {P6_SI, P6_DD}},
{2,{ OSDK_J ,OSDK_I  ,0      ,0}, {P6_SI, P6_DD}},
{2,{ OSDK_Z ,OSDK_U  ,0      ,0}, {P6_SU, P6_DD}},
{2,{ OSDK_Z ,OSDK_E  ,0      ,0}, {P6_SE, P6_DD}},
{2,{ OSDK_Z ,OSDK_O  ,0      ,0}, {P6_SO, P6_DD}},

{3,{ OSDK_Z ,OSDK_Y  ,OSDK_A ,0}, {P6_SI, P6_DD, P6_LYA}},	// じゃじぃじゅじぇじょ
{3,{ OSDK_Z ,OSDK_Y  ,OSDK_I ,0}, {P6_SI, P6_DD, P6_LI }},
{3,{ OSDK_Z ,OSDK_Y  ,OSDK_U ,0}, {P6_SI, P6_DD, P6_LYU}},
{3,{ OSDK_Z ,OSDK_Y  ,OSDK_E ,0}, {P6_SI, P6_DD, P6_LE }},
{3,{ OSDK_Z ,OSDK_Y  ,OSDK_O ,0}, {P6_SI, P6_DD, P6_LYO}},

{2,{ OSDK_J ,OSDK_A  ,0      ,0}, {P6_SI, P6_DD, P6_LYA}},	// じゃじゅじぇじょ
{2,{ OSDK_J ,OSDK_U  ,0      ,0}, {P6_SI, P6_DD, P6_LYU}},
{2,{ OSDK_J ,OSDK_E  ,0      ,0}, {P6_SI, P6_DD, P6_LE }},
{2,{ OSDK_J ,OSDK_O  ,0      ,0}, {P6_SI, P6_DD, P6_LYO}},

{3,{ OSDK_J ,OSDK_Y  ,OSDK_A ,0}, {P6_SI, P6_DD, P6_LYA}},	// じゃじぃじゅじぇじょ
{3,{ OSDK_J ,OSDK_Y  ,OSDK_I ,0}, {P6_SI, P6_DD, P6_LI }},
{3,{ OSDK_J ,OSDK_Y  ,OSDK_U ,0}, {P6_SI, P6_DD, P6_LYU}},
{3,{ OSDK_J ,OSDK_Y  ,OSDK_E ,0}, {P6_SI, P6_DD, P6_LE }},
{3,{ OSDK_J ,OSDK_Y  ,OSDK_O ,0}, {P6_SI, P6_DD, P6_LYO}},



{2,{ OSDK_T ,OSDK_A  , 0    ,0},  {P6_TA}},		// たちつてと
{2,{ OSDK_T ,OSDK_I  , 0    ,0},  {P6_TI}},
{3,{ OSDK_C ,OSDK_H  ,OSDK_I,0},  {P6_TI}},
{2,{ OSDK_C ,OSDK_I  , 0    ,0},  {P6_TI}},
{2,{ OSDK_T ,OSDK_U  , 0    ,0},  {P6_TU}},
{3,{ OSDK_T ,OSDK_S  ,OSDK_U,0},  {P6_TU}},
{2,{ OSDK_T ,OSDK_E  , 0    ,0},  {P6_TE}},
{2,{ OSDK_T ,OSDK_O  , 0    ,0},  {P6_TO}},

{3,{ OSDK_T ,OSDK_Y  ,OSDK_A  ,0}, {P6_TI,P6_LYA}},	// ちゃちぃちゅちぇちょ
{3,{ OSDK_T ,OSDK_Y  ,OSDK_I  ,0}, {P6_TI,P6_LI }},
{3,{ OSDK_T ,OSDK_Y  ,OSDK_U  ,0}, {P6_TI,P6_LYU}},
{3,{ OSDK_T ,OSDK_Y  ,OSDK_E  ,0}, {P6_TI,P6_LE }},
{3,{ OSDK_T ,OSDK_Y  ,OSDK_O  ,0}, {P6_TI,P6_LYO}},

{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_A  ,0}, {P6_TI,P6_LYA}},	// ちゃちぃちゅちぇちょ
{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_I  ,0}, {P6_TI,P6_LI }},
{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_U  ,0}, {P6_TI,P6_LYU}},
{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_E  ,0}, {P6_TI,P6_LE }},
{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_O  ,0}, {P6_TI,P6_LYO}},

{ 3,{ OSDK_T ,OSDK_S  ,OSDK_A  ,0}, {P6_TU,P6_LA}},	// つぁつぃつぇつぉ
{ 3,{ OSDK_T ,OSDK_S  ,OSDK_I  ,0}, {P6_TU,P6_LI}},
{ 3,{ OSDK_T ,OSDK_S  ,OSDK_E  ,0}, {P6_TU,P6_LE}},
{ 3,{ OSDK_T ,OSDK_S  ,OSDK_O  ,0}, {P6_TU,P6_LO}},

{ 3,{ OSDK_T ,OSDK_H  ,OSDK_A  ,0}, {P6_TE,P6_LYA}},	// てゃてぃてゅてぇてょ
{ 3,{ OSDK_T ,OSDK_H  ,OSDK_I  ,0}, {P6_TE,P6_LI }},
{ 3,{ OSDK_T ,OSDK_H  ,OSDK_U  ,0}, {P6_TE,P6_LYU}},
{ 3,{ OSDK_T ,OSDK_H  ,OSDK_E  ,0}, {P6_TE,P6_LE }},
{ 3,{ OSDK_T ,OSDK_H  ,OSDK_O  ,0}, {P6_TE,P6_LYO}},

{3,{ OSDK_T ,OSDK_W  ,OSDK_A  ,0}, {P6_TO,P6_LA}},	// とぁとぃとぅとぇとぉ
{3,{ OSDK_T ,OSDK_W  ,OSDK_I  ,0}, {P6_TO,P6_LI}},
{3,{ OSDK_T ,OSDK_W  ,OSDK_U  ,0}, {P6_TO,P6_LU}},
{3,{ OSDK_T ,OSDK_W  ,OSDK_E  ,0}, {P6_TO,P6_LE}},
{3,{ OSDK_T ,OSDK_W  ,OSDK_O  ,0}, {P6_TO,P6_LO}},

{2,{ OSDK_D ,OSDK_A  ,0      ,0}, {P6_TA,P6_DD}},	// だぢづでど
{2,{ OSDK_D ,OSDK_I  ,0      ,0}, {P6_TI,P6_DD}},
{2,{ OSDK_D ,OSDK_U  ,0      ,0}, {P6_TU,P6_DD}},
{2,{ OSDK_D ,OSDK_E  ,0      ,0}, {P6_TE,P6_DD}},
{2,{ OSDK_D ,OSDK_O  ,0      ,0}, {P6_TO,P6_DD}},

{3,{ OSDK_D ,OSDK_Y  ,OSDK_A  ,0}, {P6_TI,P6_DD,P6_LYA}},	// ぢゃぢぃぢゅぢぇぢょ
{3,{ OSDK_D ,OSDK_Y  ,OSDK_I  ,0}, {P6_TI,P6_DD,P6_LI }},
{3,{ OSDK_D ,OSDK_Y  ,OSDK_U  ,0}, {P6_TI,P6_DD,P6_LYU}},
{3,{ OSDK_D ,OSDK_Y  ,OSDK_E  ,0}, {P6_TI,P6_DD,P6_LE }},
{3,{ OSDK_D ,OSDK_Y  ,OSDK_O  ,0}, {P6_TI,P6_DD,P6_LYO}},


            // DHA...
            // DWA...

{2,{ OSDK_N ,OSDK_A  , 0    ,0}, {P6_NA}},		// なにぬねの
{2,{ OSDK_N ,OSDK_I  , 0    ,0}, {P6_NI}},
{2,{ OSDK_N ,OSDK_U  , 0    ,0}, {P6_NU}},
{2,{ OSDK_N ,OSDK_E  , 0    ,0}, {P6_NE}},
{2,{ OSDK_N ,OSDK_O  , 0    ,0}, {P6_NO}},

{3,{ OSDK_N ,OSDK_Y  ,OSDK_A ,0}, {P6_NI,P6_LYA}},	// にゃにぃにゅにぇにょ
{3,{ OSDK_N ,OSDK_Y  ,OSDK_I ,0}, {P6_NI,P6_LI }},
{3,{ OSDK_N ,OSDK_Y  ,OSDK_U ,0}, {P6_NI,P6_LYU}},
{3,{ OSDK_N ,OSDK_Y  ,OSDK_E ,0}, {P6_NI,P6_LE }},
{3,{ OSDK_N ,OSDK_Y  ,OSDK_O ,0}, {P6_NI,P6_LYO}},

{2,{ OSDK_H ,OSDK_A  , 0    ,0}, {P6_HA}},		//  はひふへほ
{2,{ OSDK_H ,OSDK_I  , 0    ,0}, {P6_HI}},
{2,{ OSDK_H ,OSDK_U  , 0    ,0}, {P6_HU}},
{2,{ OSDK_H ,OSDK_E  , 0    ,0}, {P6_HE}},
{2,{ OSDK_H ,OSDK_O  , 0    ,0}, {P6_HO}},

{3,{ OSDK_H ,OSDK_Y  ,OSDK_A ,0}, {P6_HI,P6_LYA}},	// ひゃひぃひゅひぇひょ
{3,{ OSDK_H ,OSDK_Y  ,OSDK_I ,0}, {P6_HI,P6_LI }},
{3,{ OSDK_H ,OSDK_Y  ,OSDK_U ,0}, {P6_HI,P6_LYU}},
{3,{ OSDK_H ,OSDK_Y  ,OSDK_E ,0}, {P6_HI,P6_LE }},
{3,{ OSDK_H ,OSDK_Y  ,OSDK_O ,0}, {P6_HI,P6_LYO}},

{3,{ OSDK_B ,OSDK_Y  ,OSDK_A  ,0}, {P6_HI,P6_DD,P6_LYA}},	// びゃびぃびゅびぇびょ
{3,{ OSDK_B ,OSDK_Y  ,OSDK_I  ,0}, {P6_HI,P6_DD,P6_LI }},
{3,{ OSDK_B ,OSDK_Y  ,OSDK_U  ,0}, {P6_HI,P6_DD,P6_LYU}},
{3,{ OSDK_B ,OSDK_Y  ,OSDK_E  ,0}, {P6_HI,P6_DD,P6_LE }},
{3,{ OSDK_B ,OSDK_Y  ,OSDK_O  ,0}, {P6_HI,P6_DD,P6_LYO}},

{3,{ OSDK_P ,OSDK_Y  ,OSDK_A ,0}, {P6_HI,P6_HD,P6_LYA}},    // ぴゃぴぃぴゅぴぇぴょ
{3,{ OSDK_P ,OSDK_Y  ,OSDK_I ,0}, {P6_HI,P6_HD,P6_LI }},
{3,{ OSDK_P ,OSDK_Y  ,OSDK_U ,0}, {P6_HI,P6_HD,P6_LYU}},
{3,{ OSDK_P ,OSDK_Y  ,OSDK_E ,0}, {P6_HI,P6_HD,P6_LE }},
{3,{ OSDK_P ,OSDK_Y  ,OSDK_O ,0}, {P6_HI,P6_HD,P6_LYO}},

                // FWA....

{2,{ OSDK_F ,OSDK_A  , 0     ,0}, {P6_HU,P6_LA}},	//ふぁふぃふふぇふぉ
{2,{ OSDK_F ,OSDK_I  , 0     ,0}, {P6_HU,P6_LI}},
{2,{ OSDK_F ,OSDK_U  , 0     ,0}, {P6_HU      }},
{2,{ OSDK_F ,OSDK_E  , 0     ,0}, {P6_HU,P6_LE}},
{2,{ OSDK_F ,OSDK_O  , 0     ,0}, {P6_HU,P6_LO}},


{2,{ OSDK_B ,OSDK_A  ,0      ,0}, {P6_HA,P6_DD}},	// ばびぶべぼ
{2,{ OSDK_B ,OSDK_I  ,0      ,0}, {P6_HI,P6_DD}},
{2,{ OSDK_B ,OSDK_U  ,0      ,0}, {P6_HU,P6_DD}},
{2,{ OSDK_B ,OSDK_E  ,0      ,0}, {P6_HE,P6_DD}},
{2,{ OSDK_B ,OSDK_O  ,0      ,0}, {P6_HO,P6_DD}},

{2,{ OSDK_P ,OSDK_A  ,0      ,0}, {P6_HA,P6_HD}},	// ぱぴぷぺぽ
{2,{ OSDK_P ,OSDK_I  ,0      ,0}, {P6_HI,P6_HD}},
{2,{ OSDK_P ,OSDK_U  ,0      ,0}, {P6_HU,P6_HD}},
{2,{ OSDK_P ,OSDK_E  ,0      ,0}, {P6_HE,P6_HD}},
{2,{ OSDK_P ,OSDK_O  ,0      ,0}, {P6_HO,P6_HD}},


{2,{ OSDK_M ,OSDK_A  ,0      ,0}, {P6_MA}},		// まみむめも
{2,{ OSDK_M ,OSDK_I  ,0      ,0}, {P6_MI}},
{2,{ OSDK_M ,OSDK_U  ,0      ,0}, {P6_MU}},
{2,{ OSDK_M ,OSDK_E  ,0      ,0}, {P6_ME}},
{2,{ OSDK_M ,OSDK_O  ,0      ,0}, {P6_MO}},

{3,{ OSDK_M ,OSDK_Y  ,OSDK_A ,0}, {P6_MI,P6_LYA}},	// みゃみぃみゅみぇみょ
{3,{ OSDK_M ,OSDK_Y  ,OSDK_I ,0}, {P6_MI,P6_LI }},
{3,{ OSDK_M ,OSDK_Y  ,OSDK_U ,0}, {P6_MI,P6_LYU}},
{3,{ OSDK_M ,OSDK_Y  ,OSDK_E ,0}, {P6_MI,P6_LE }},
{3,{ OSDK_M ,OSDK_Y  ,OSDK_O ,0}, {P6_MI,P6_LYO}},

{2,{ OSDK_Y ,OSDK_A  , 0     ,0}, {P6_YA}},				// やゆよ
{2,{ OSDK_Y ,OSDK_U  , 0     ,0}, {P6_YU}},
{2,{ OSDK_Y ,OSDK_O  , 0     ,0}, {P6_YO}},

{3,{ OSDK_L ,OSDK_Y  ,OSDK_A ,0}, {P6_LYA}},    	// ゃ
{3,{ OSDK_L ,OSDK_Y  ,OSDK_U ,0}, {P6_LYU}},    	// ゅ
{3,{ OSDK_L ,OSDK_Y  ,OSDK_O ,0}, {P6_LYO}},    	// ょ

{2,{ OSDK_R ,OSDK_A  , 0     ,0}, {P6_RA}},				// らりるれろ
{2,{ OSDK_R ,OSDK_I  , 0     ,0}, {P6_RI}},
{2,{ OSDK_R ,OSDK_U  , 0     ,0}, {P6_RU}},
{2,{ OSDK_R ,OSDK_E  , 0     ,0}, {P6_RE}},
{2,{ OSDK_R ,OSDK_O  , 0     ,0}, {P6_RO}},

{3,{ OSDK_R ,OSDK_Y  ,OSDK_A ,0}, {P6_RI,P6_LYA}},	// りゃりぃりゅりぇりょ
{3,{ OSDK_R ,OSDK_Y  ,OSDK_I ,0}, {P6_RI,P6_LI }},
{3,{ OSDK_R ,OSDK_Y  ,OSDK_U ,0}, {P6_RI,P6_LYU}},
{3,{ OSDK_R ,OSDK_Y  ,OSDK_E ,0}, {P6_RI,P6_LE }},
{3,{ OSDK_R ,OSDK_Y  ,OSDK_O ,0}, {P6_RI,P6_LYO}},

{2,{ OSDK_W ,OSDK_A  , 0    ,0}, {P6_WA}},				// わ うぃ う うぇ
{2,{ OSDK_W ,OSDK_I  , 0    ,0}, {P6_U ,P6_LI}},
{2,{ OSDK_W ,OSDK_U  , 0    ,0}, {P6_U}},
{2,{ OSDK_W ,OSDK_E  , 0    ,0}, {P6_U,P6_LE}},


{1,{ OSDK_MINUS       ,0  ,0 ,0}  	, {P6_CYOUON}},	//  -
//{1,{ OSDK_BACKSLASH   ,0  ,0 ,0}  	, {0x00}},	//  -
{1,{ OSDK_SEMICOLON   ,0  ,0 ,0}    , {';'}},	// ;
{1,{ OSDK_COLON       ,0  ,0 ,0}    , {':'}},	// :
//{1,{ OSDK_RIGHTBRACKET,0  ,0 ,0}  	, {0x00}},	//  ]
{1,{ OSDK_1           ,0  ,0 ,0}  	, {'1'}},	//  1
{1,{ OSDK_2           ,0  ,0 ,0}  	, {'2'}},	//  2
{1,{ OSDK_3           ,0  ,0 ,0}  	, {'3'}},	//  3
{1,{ OSDK_4           ,0  ,0 ,0}  	, {'4'}},	//  4
{1,{ OSDK_5           ,0  ,0 ,0}  	, {'5'}},	//  5
{1,{ OSDK_6           ,0  ,0 ,0}  	, {'6'}},	//  6
{1,{ OSDK_7           ,0  ,0 ,0}  	, {'7'}},	//  7
{1,{ OSDK_8           ,0  ,0 ,0}  	, {'8'}},	//  8
{1,{ OSDK_9           ,0  ,0 ,0}  	, {'9'}},	//  9
{1,{ OSDK_0           ,0  ,0 ,0}  	, {'0'}},	//  0
{1,{ OSDK_UPPER       ,0  ,0 ,0}  	, {'^'}},	//  ^

{1,{ OSDK_AT          ,0  ,0 ,0}  	, {P6_DD}},	//  @ 濁点
{1,{ OSDK_LEFTBRACKET ,0  ,0 ,0}  	, {P6_HD}},	//  | 半濁点

{1,{ OSDK_COMMA       ,0  ,0 ,0}  	, {P6_KUTOUTEN}},	//  、
{1,{ OSDK_PERIOD      ,0  ,0 ,0}  	, {P6_DOKUTEN}},	//  。
{1,{ OSDK_SLASH       ,0  ,0 ,0}  	, {'/'}},	//  /
{1,{ OSDK_UNDERSCORE  ,0  ,0 ,0}  	, {'_'}},	//  _

                                                                // をん
{ 2,{ OSDK_W ,OSDK_O  , 0    ,0}    , {P6_WO} },
{ 2,{ OSDK_N ,OSDK_N  , 0    ,0}    , {P6_N} },
{ 3,{ OSDK_N ,OSDK_N  ,OSDK_N,0}    , {P6_N} },

{-1,{ -1     ,-1      , -1   },{0  , 0,0,0}},
};



// ****************************************************************************
// 　母音かどうか？
// 非0  :はい    0:いいえ
// ****************************************************************************
int Romaji::isBoin( int osdkeycode)
{
    return (osdkeycode==OSDK_A || osdkeycode==OSDK_I || osdkeycode==OSDK_U || osdkeycode==OSDK_E || osdkeycode==OSDK_O );
}

// ****************************************************************************
// 　子音かどうか？
// 非0  :はい    0:いいえ
// ****************************************************************************
int Romaji::isShin( int osdkeycode)
{
    return (osdkeycode==OSDK_K || osdkeycode==OSDK_S || osdkeycode==OSDK_T || osdkeycode==OSDK_H || osdkeycode==OSDK_M || osdkeycode==OSDK_Y
    || osdkeycode==OSDK_R || osdkeycode==OSDK_W || osdkeycode==OSDK_P || osdkeycode==OSDK_F 
    || osdkeycode==OSDK_G || osdkeycode == OSDK_D || osdkeycode == OSDK_Z || osdkeycode == OSDK_B);
}

// ****************************************************************************
// 		convert_search:ローマ字の綴りをマッチングする (romaji_convert_romaji2kana から呼ばれる)
//
//   In:  buff    変換したい文字列
//        line    変換結果(romaji_tbl テーブルのインデックス)
//
//   Out: HENKAN_SUCCESS   変換成功
//        HENKAN_DOING     変換中
//        HENKAN_FAILED    変換失敗
//        HENKAN_SUCCESS_LTU っ変換成功
// ****************************************************************************
int Romaji::convertSearch( char *buff , int *line)
{
    int i;
    int found =HENKAN_FAILED;

    *line = 0;
    
    if( buff[0]== buff[1])				// 子音が重なって入力されたら、「っ」に変換
        if( isShin( buff[0]) && isShin(buff[1]))
            {
             return HENKAN_SUCCESS_LTU;
            }


    for(i=0; romaji_tbl[i].num !=-1 ; i++)
        {
            {
            if( strncmp( romaji_tbl[i].romaji, buff ,strlen(buff))==0)
                {
                if( romaji_tbl[i].num == strlen(buff))
                    found= HENKAN_SUCCESS;		// complete match
                else
                    found= HENKAN_DOING;		// part  match
                *line = i;
                break;
                }
            }
        }
    return found;
}




// ****************************************************************************
// 		convertRomaji2kana:
//		ローマ字から、かなに変換する
//
//  OSキーイベントのkeydown のところで、かなモードかつ、ローマ字変換モードなら、これを呼ぶ。
//
//
//	処理：ローマ字変換できるかチェックして、変換に成功したら、HENKAN_SUCCESS か、HENKAN_SUCCESS_LTUを返す。
//       getResult() で、変換結果を取得する。
//
//
// Out: HENKAN_SUCCESS: ローマ字変換に成功した
//      HENKAN_FAILED:  変換失敗
//      HENKAN_DOING  : 変換中
//      HENKAN_CANCEL : 無変換
//      HENKAN_SUCCESS_LTU っ変換成功
//***************************************************************
int Romaji::convertRomaji2kana( int osdkeycode )
{
    static char buff[4];
    static int  idx=0;
    int   line=0;
    int   found=0;


    if( !(( OSDK_A <= osdkeycode && osdkeycode <= OSDK_Z) || osdkeycode == OSDK_AT || osdkeycode == OSDK_LEFTBRACKET) ) // 使えるキー判定
        {
        idx=0;
        memset(buff,0, sizeof(buff));
        return HENKAN_CANCEL;
        }

    if(idx <3 )
        {
         buff[ idx++ ]= osdkeycode;

         found = convertSearch( buff , &line);	// convert to romaji ローマ字変換してみる

         PRINTDEBUG(KEY_LOG,"[romaji][convert_romaji2kana] input buff= '%s' \n", buff);

        if( !found )			// not match
            {
            PRINTDEBUG(KEY_LOG,"[romaji][convert_romaji2kana] convert searching  '%s'  not found \n", buff);
            memset(buff, 0, sizeof(buff));
            idx=0;
            }
        else if( found ==HENKAN_SUCCESS || found == HENKAN_SUCCESS_LTU)		// match
            {
            int j;
            int output_length=0;

            if( found == HENKAN_SUCCESS_LTU)
                line =0;        // 子音がダブルで来たときは、強制的に、「っ」に変換する

            PRINTDEBUG(KEY_LOG,"[romaji][convert_romaji2kana] convert_success '%s' -> \t",buff);


	        memcpy(result , romaji_tbl[line].keycode, MAX_RESULT);

            if (found == HENKAN_SUCCESS_LTU)        // 子音ダブルできたとき（例えば、KKのときは、KK -> K にして、次の母音を待つ
                {
                 buff[0]= buff[1]; buff[1] = buff[2]; buff[2]= buff[3]; buff[3]=0;
                 idx--;
                }
            else 
                {
                memset(buff,0, sizeof(buff));
                idx=0;
                }
            }
        else	// part match , continue buffaling...
            {
            PRINTDEBUG(KEY_LOG,"[romaji][convert_romaji2kana] convert: part match '%s'  line=%d \n", buff ,line);
            }
        }

    if( found ==HENKAN_FAILED)	// かな変換キー以外は、そのまま返す。
        {
         idx=0;
         memset( buff, 0,  sizeof( buff));
        }
    return found;
}

// ****************************************************************************
//  ひらがな→カタカナに変換する
//      In: buff バッファ
//     Out: 変換結果
// ****************************************************************************
char * Romaji::convertKana2Katakana(char* buff)
{
    char *p;
    p= buff;

    for (int i = 0; i< (int)strlen(buff); i++) {
        unsigned char c = *p;
        if ((0x86 <= c && c <= 0x9f) || (0xe0 <= c && c <= 0xfd)) {   // kana?
            *p ^= 0x20;
        }
        p++;
    }
    return buff;
}

// ****************************************************************************
//   コンストラクター
// ****************************************************************************
Romaji::Romaji(void)
{
    init();
}

// ****************************************************************************
//   初期化
// ****************************************************************************
void Romaji::init(void)
{
    memset(result,0,sizeof(result));
}

// ****************************************************************************
//   結果を取得
// ****************************************************************************
char *Romaji::getResult(void)
{
    return result;
}
