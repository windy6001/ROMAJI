/*
name is romaji.c

Copyright (c) 2020 Windy
Version 1.0

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

based on https://github.com/windy6001/ROMAJI/
*/


#include "keys.h"
#include "conv.h"
#include "romaji.h"


// ****************************************************************************
//      functions
// ****************************************************************************
static void convertKana2Katakana(char* buff);


// ****************************************************************************
//          ���[�}���ϊ��e�[�u��
// ****************************************************************************
struct _romaji_tbl {
    int num;
    char romaji[4];
    char keycode[7];
};

static struct _romaji_tbl romaji_tbl[] = {

{2,{ OSDK_L ,OSDK_L  ,0      ,0}, {"��"}},	// ��        ��ԍŏ��̃f�[�^�́A�u���v�łȂ��Ƃ����Ȃ�
{3,{ OSDK_L ,OSDK_T  ,OSDK_U ,0}, {"��"}},	// ��

{1,{ OSDK_A , 0      , 0    ,0}, {"��" }},		// ����������
{1,{ OSDK_I , 0      , 0    ,0}, {"��" }},
{1,{ OSDK_U , 0      , 0    ,0}, {"��" }},
{1,{ OSDK_E , 0      , 0    ,0}, {"��" }},
{1,{ OSDK_O , 0      , 0    ,0}, {"��" }},


{2,{ OSDK_L ,OSDK_A  ,0      ,0}, {"��"}},	// ��
{2,{ OSDK_L ,OSDK_I  ,0      ,0}, {"��"}},	// ��
{2,{ OSDK_L ,OSDK_U  ,0      ,0}, {"��"}},	// ��
{2,{ OSDK_L ,OSDK_E  ,0      ,0}, {"��"}},	// ��
{2,{ OSDK_L ,OSDK_O  ,0      ,0}, {"��"}},	// ��


{ 2,{ OSDK_X ,OSDK_A  ,0      ,0 },{"��"} },	// ��
{ 2,{ OSDK_X ,OSDK_I  ,0      ,0 },{"��"} },	// ��
{ 2,{ OSDK_X ,OSDK_U  ,0      ,0 },{"��"} },	// ��
{ 2,{ OSDK_X ,OSDK_E  ,0      ,0 },{"��"} },	// ��
{ 2,{ OSDK_X ,OSDK_O  ,0      ,0 },{"��"} },	// ��

{ 3,{ OSDK_W ,OSDK_H  ,OSDK_A ,0 },{"����"} },	// ����
{ 3,{ OSDK_W ,OSDK_H  ,OSDK_I ,0 },{"����"} },	// ����
{ 2,{ OSDK_W ,OSDK_I  ,0      ,0 },{"����"} },	// ����
{ 2,{ OSDK_W ,OSDK_U  ,0      ,0 },{"��"  } },  // ��
{ 3,{ OSDK_W ,OSDK_H  ,OSDK_E ,0 },{"����"} },	// ����
{ 2,{ OSDK_W ,OSDK_E  ,0      ,0 },{"����"} },	// ����
{ 3,{ OSDK_W ,OSDK_H  ,OSDK_O ,0 },{"����"} },	// ����


{2,{ OSDK_K ,OSDK_A  , 0    ,0}, {"��"}},		// ����������
{2,{ OSDK_K ,OSDK_I  , 0    ,0}, {"��"}},
{2,{ OSDK_K ,OSDK_U  , 0    ,0}, {"��"}},
{2,{ OSDK_K ,OSDK_E  , 0    ,0}, {"��"}},
{2,{ OSDK_K ,OSDK_O  , 0    ,0}, {"��"}},

{3,{ OSDK_K ,OSDK_Y  ,OSDK_A ,0}, {"����"}},	// ���Ⴋ�����カ������
{3,{ OSDK_K ,OSDK_Y  ,OSDK_I ,0}, {"����"}},
{3,{ OSDK_K ,OSDK_Y  ,OSDK_U ,0}, {"����"}},
{3,{ OSDK_K ,OSDK_Y  ,OSDK_E ,0}, {"����"}},
{3,{ OSDK_K ,OSDK_Y  ,OSDK_O ,0}, {"����"}},

{2,{ OSDK_G ,OSDK_A  ,0      ,0}, {"��"}},	// ����������
{2,{ OSDK_G ,OSDK_I  ,0      ,0}, {"��"}},
{2,{ OSDK_G ,OSDK_U  ,0      ,0}, {"��"}},
{2,{ OSDK_G ,OSDK_E  ,0      ,0}, {"��"}},
{2,{ OSDK_G ,OSDK_O  ,0      ,0}, {"��"}},

{3,{ OSDK_G ,OSDK_Y  ,OSDK_A ,0}, {"����"}},// ���Ⴌ�����ガ������
{3,{ OSDK_G ,OSDK_Y  ,OSDK_I ,0}, {"����"}},
{3,{ OSDK_G ,OSDK_Y  ,OSDK_U ,0}, {"����"}},
{3,{ OSDK_G ,OSDK_Y  ,OSDK_E ,0}, {"����"}},
{3,{ OSDK_G ,OSDK_Y  ,OSDK_O ,0}, {"����"}},

{3,{ OSDK_G ,OSDK_W  ,OSDK_A ,0}, {"����"}},// ��������������������
{3,{ OSDK_G ,OSDK_W  ,OSDK_I ,0}, {"����"}},
{3,{ OSDK_G ,OSDK_W  ,OSDK_U ,0}, {"����"}},
{3,{ OSDK_G ,OSDK_W  ,OSDK_E ,0}, {"����"}},
{3,{ OSDK_G ,OSDK_W  ,OSDK_O ,0}, {"����"}},

{2,{ OSDK_S ,OSDK_A  , 0     ,0}, {"��"}},		// ����������
{2,{ OSDK_S ,OSDK_I  , 0     ,0}, {"��"}},
{3,{ OSDK_S ,OSDK_H  ,OSDK_I ,0}, {"��"}},
{2,{ OSDK_S ,OSDK_U  , 0     ,0}, {"��"}},
{2,{ OSDK_S ,OSDK_E  , 0     ,0}, {"��"}},
{2,{ OSDK_S ,OSDK_O  , 0     ,0}, {"��"}},

{3,{ OSDK_S ,OSDK_Y  ,OSDK_A ,0}, {"����"}},	// ���Ⴕ�����サ������
{3,{ OSDK_S ,OSDK_Y  ,OSDK_I ,0}, {"����"}},
{3,{ OSDK_S ,OSDK_Y  ,OSDK_U ,0}, {"����"}},
{3,{ OSDK_S ,OSDK_Y  ,OSDK_E ,0}, {"����"}},
{3,{ OSDK_S ,OSDK_Y  ,OSDK_O ,0}, {"����"}},

{3,{ OSDK_S ,OSDK_H  ,OSDK_A ,0}, {"����"}},	// ���Ⴕ��@��������
{3,{ OSDK_S ,OSDK_H  ,OSDK_U ,0}, {"����"}},
{3,{ OSDK_S ,OSDK_H  ,OSDK_E ,0}, {"����"}},
{3,{ OSDK_S ,OSDK_H  ,OSDK_O ,0}, {"����"}},

{3,{ OSDK_S ,OSDK_W  ,OSDK_A ,0}, {"����"}},	// ��������������������
{3,{ OSDK_S ,OSDK_W  ,OSDK_I ,0}, {"����"}},
{3,{ OSDK_S ,OSDK_W  ,OSDK_U ,0}, {"����"}},
{3,{ OSDK_S ,OSDK_W  ,OSDK_E ,0}, {"����"}},
{3,{ OSDK_S ,OSDK_W  ,OSDK_O ,0}, {"����"}},

{2,{ OSDK_Z ,OSDK_A  ,0      ,0}, {"��"}},	// ����������
{2,{ OSDK_Z ,OSDK_I  ,0      ,0}, {"��"}},
{2,{ OSDK_J ,OSDK_I  ,0      ,0}, {"��"}},
{2,{ OSDK_Z ,OSDK_U  ,0      ,0}, {"��"}},
{2,{ OSDK_Z ,OSDK_E  ,0      ,0}, {"��"}},
{2,{ OSDK_Z ,OSDK_O  ,0      ,0}, {"��"}},

{3,{ OSDK_Z ,OSDK_Y  ,OSDK_A ,0}, {"����"}},	// ���Ⴖ�����ザ������
{3,{ OSDK_Z ,OSDK_Y  ,OSDK_I ,0}, {"����"}},
{3,{ OSDK_Z ,OSDK_Y  ,OSDK_U ,0}, {"����"}},
{3,{ OSDK_Z ,OSDK_Y  ,OSDK_E ,0}, {"����"}},
{3,{ OSDK_Z ,OSDK_Y  ,OSDK_O ,0}, {"����"}},

{2,{ OSDK_J ,OSDK_A  ,0      ,0}, {"����"}},	// ���Ⴖ�ザ������
{2,{ OSDK_J ,OSDK_U  ,0      ,0}, {"����"}},
{2,{ OSDK_J ,OSDK_E  ,0      ,0}, {"����"}},
{2,{ OSDK_J ,OSDK_O  ,0      ,0}, {"����"}},

{3,{ OSDK_J ,OSDK_Y  ,OSDK_A ,0}, {"����"} },	// ���Ⴖ�����ザ������
{3,{ OSDK_J ,OSDK_Y  ,OSDK_I ,0}, {"����"} },
{3,{ OSDK_J ,OSDK_Y  ,OSDK_U ,0}, {"����"} },
{3,{ OSDK_J ,OSDK_Y  ,OSDK_E ,0}, {"����"} },
{3,{ OSDK_J ,OSDK_Y  ,OSDK_O ,0}, {"����"}},



{2,{ OSDK_T ,OSDK_A  , 0    ,0},  {"��"} },		// �����Ă�
{2,{ OSDK_T ,OSDK_I  , 0    ,0},  {"��"} },
{3,{ OSDK_C ,OSDK_H  ,OSDK_I,0},  {"��"} },
{2,{ OSDK_C ,OSDK_I  , 0    ,0},  {"��"} },
{2,{ OSDK_T ,OSDK_U  , 0    ,0},  {"��"}},
{3,{ OSDK_T ,OSDK_S  ,OSDK_U,0},  {"��"} },
{2,{ OSDK_T ,OSDK_E  , 0    ,0},  {"��"} },
{2,{ OSDK_T ,OSDK_O  , 0    ,0},  {"��"}},

{3,{ OSDK_T ,OSDK_Y  ,OSDK_A  ,0}, {"����"}},	// ���Ⴟ�����タ������
{3,{ OSDK_T ,OSDK_Y  ,OSDK_I  ,0}, {"����"}},
{3,{ OSDK_T ,OSDK_Y  ,OSDK_U  ,0}, {"����"}},
{3,{ OSDK_T ,OSDK_Y  ,OSDK_E  ,0}, {"����"} },
{3,{ OSDK_T ,OSDK_Y  ,OSDK_O  ,0}, {"����"} },

{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_A  ,0}, {"����"} },	// ���Ⴟ�����タ������
{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_I  ,0}, {"����"} },
{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_U  ,0}, {"����"} },
{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_E  ,0}, {"����"} },
{ 3,{ OSDK_C ,OSDK_Y  ,OSDK_O  ,0}, {"����"}},

{ 3,{ OSDK_T ,OSDK_S  ,OSDK_A  ,0}, {"��"}},	// ��������
{ 3,{ OSDK_T ,OSDK_S  ,OSDK_I  ,0}, {"��"}},
{ 3,{ OSDK_T ,OSDK_S  ,OSDK_E  ,0}, {"��"}},
{ 3,{ OSDK_T ,OSDK_S  ,OSDK_O  ,0}, {"��"}},

{ 3,{ OSDK_T ,OSDK_H  ,OSDK_A  ,0}, {"�Ă�"} },	// �Ă�Ă��Ă�Ă��Ă�
{ 3,{ OSDK_T ,OSDK_H  ,OSDK_I  ,0}, {"�Ă�"} },
{ 3,{ OSDK_T ,OSDK_H  ,OSDK_U  ,0}, {"�Ă�"} },
{ 3,{ OSDK_T ,OSDK_H  ,OSDK_E  ,0}, {"�Ă�"} },
{ 3,{ OSDK_T ,OSDK_H  ,OSDK_O  ,0}, {"�Ă�"}},

{3,{ OSDK_T ,OSDK_W  ,OSDK_A  ,0}, {"�Ƃ�"}},	// �Ƃ��Ƃ��Ƃ��Ƃ��Ƃ�
{3,{ OSDK_T ,OSDK_W  ,OSDK_I  ,0}, {"�Ƃ�"}},
{3,{ OSDK_T ,OSDK_W  ,OSDK_U  ,0}, {"�Ƃ�"}},
{3,{ OSDK_T ,OSDK_W  ,OSDK_E  ,0}, {"�Ƃ�"}},
{3,{ OSDK_T ,OSDK_W  ,OSDK_O  ,0}, {"�Ƃ�"}},

{2,{ OSDK_D ,OSDK_A  ,0      ,0}, {"��"}},	// �����Âł�
{2,{ OSDK_D ,OSDK_I  ,0      ,0}, {"��"}},
{2,{ OSDK_D ,OSDK_U  ,0      ,0}, {"��"}},
{2,{ OSDK_D ,OSDK_E  ,0      ,0}, {"��"}},
{2,{ OSDK_D ,OSDK_O  ,0      ,0}, {"��"}},

{3,{ OSDK_D ,OSDK_Y  ,OSDK_A  ,0}, {"����"}},	// ������������������
{3,{ OSDK_D ,OSDK_Y  ,OSDK_I  ,0}, {"����"}},
{3,{ OSDK_D ,OSDK_Y  ,OSDK_U  ,0}, {"����"}},
{3,{ OSDK_D ,OSDK_Y  ,OSDK_E  ,0}, {"����"}},
{3,{ OSDK_D ,OSDK_Y  ,OSDK_O  ,0}, {"����"}},


            // DHA...
            // DWA...

{2,{ OSDK_N ,OSDK_A  , 0    ,0}, {"��"}},		// �Ȃɂʂ˂�
{2,{ OSDK_N ,OSDK_I  , 0    ,0}, {"��"}},
{2,{ OSDK_N ,OSDK_U  , 0    ,0}, {"��"}},
{2,{ OSDK_N ,OSDK_E  , 0    ,0}, {"��"}},
{2,{ OSDK_N ,OSDK_O  , 0    ,0}, {"��"}},

{3,{ OSDK_N ,OSDK_Y  ,OSDK_A ,0}, {"�ɂ�"}},	// �ɂ�ɂ��ɂ�ɂ��ɂ�
{3,{ OSDK_N ,OSDK_Y  ,OSDK_I ,0}, {"�ɂ�"}},
{3,{ OSDK_N ,OSDK_Y  ,OSDK_U ,0}, {"�ɂ�"}},
{3,{ OSDK_N ,OSDK_Y  ,OSDK_E ,0}, {"�ɂ�"}},
{3,{ OSDK_N ,OSDK_Y  ,OSDK_O ,0}, {"�ɂ�"}},

{2,{ OSDK_H ,OSDK_A  , 0    ,0}, {"��"}},		//  �͂Ђӂւ�
{2,{ OSDK_H ,OSDK_I  , 0    ,0}, {"��"}},
{2,{ OSDK_H ,OSDK_U  , 0    ,0}, {"��"}},
{2,{ OSDK_H ,OSDK_E  , 0    ,0}, {"��"}},
{2,{ OSDK_H ,OSDK_O  , 0    ,0}, {"��"}},

{3,{ OSDK_H ,OSDK_Y  ,OSDK_A ,0}, {"�Ђ�"}},	// �Ђ�Ђ��Ђ�Ђ��Ђ�
{3,{ OSDK_H ,OSDK_Y  ,OSDK_I ,0}, {"�Ђ�"}},
{3,{ OSDK_H ,OSDK_Y  ,OSDK_U ,0}, {"�Ђ�"}},
{3,{ OSDK_H ,OSDK_Y  ,OSDK_E ,0}, {"�Ђ�"}},
{3,{ OSDK_H ,OSDK_Y  ,OSDK_O ,0}, {"�Ђ�"}},

{3,{ OSDK_B ,OSDK_Y  ,OSDK_A  ,0}, {"�т�"}},	// �т�т��т�т��т�
{3,{ OSDK_B ,OSDK_Y  ,OSDK_I  ,0}, {"�т�"}},
{3,{ OSDK_B ,OSDK_Y  ,OSDK_U  ,0}, {"�т�"}},
{3,{ OSDK_B ,OSDK_Y  ,OSDK_E  ,0}, {"�т�"}},
{3,{ OSDK_B ,OSDK_Y  ,OSDK_O  ,0}, {"�т�"}},

{3,{ OSDK_P ,OSDK_Y  ,OSDK_A ,0}, {"�҂�"}},    // �҂�҂��҂�҂��҂�
{3,{ OSDK_P ,OSDK_Y  ,OSDK_I ,0}, {"�҂�"}},
{3,{ OSDK_P ,OSDK_Y  ,OSDK_U ,0}, {"�҂�"}},
{3,{ OSDK_P ,OSDK_Y  ,OSDK_E ,0}, {"�҂�"}},
{3,{ OSDK_P ,OSDK_Y  ,OSDK_O ,0}, {"�҂�"}},

                // FWA....

{2,{ OSDK_F ,OSDK_A  , 0     ,0}, {"�ӂ�"}},	//�ӂ��ӂ��ӂӂ��ӂ�
{2,{ OSDK_F ,OSDK_I  , 0     ,0}, {"�ӂ�"}},
{2,{ OSDK_F ,OSDK_U  , 0     ,0}, {"��"}},
{2,{ OSDK_F ,OSDK_E  , 0     ,0}, {"�ӂ�"}},
{2,{ OSDK_F ,OSDK_O  , 0     ,0}, {"�ӂ�"}},


{2,{ OSDK_B ,OSDK_A  ,0      ,0}, {"��"}},	// �΂тԂׂ�
{2,{ OSDK_B ,OSDK_I  ,0      ,0}, {"��"}},
{2,{ OSDK_B ,OSDK_U  ,0      ,0}, {"��"}},
{2,{ OSDK_B ,OSDK_E  ,0      ,0}, {"��"}},
{2,{ OSDK_B ,OSDK_O  ,0      ,0}, {"��"}},

{2,{ OSDK_P ,OSDK_A  ,0      ,0}, {"��"}},	// �ς҂Ղ؂�
{2,{ OSDK_P ,OSDK_I  ,0      ,0}, {"��"}},
{2,{ OSDK_P ,OSDK_U  ,0      ,0}, {"��"}},
{2,{ OSDK_P ,OSDK_E  ,0      ,0}, {"��"}},
{2,{ OSDK_P ,OSDK_O  ,0      ,0}, {"��"}},


{2,{ OSDK_M ,OSDK_A  ,0      ,0}, {"��"}},		// �܂݂ނ߂�
{2,{ OSDK_M ,OSDK_I  ,0      ,0}, {"��"}},
{2,{ OSDK_M ,OSDK_U  ,0      ,0}, {"��"}},
{2,{ OSDK_M ,OSDK_E  ,0      ,0}, {"��"}},
{2,{ OSDK_M ,OSDK_O  ,0      ,0}, {"��"}},

{3,{ OSDK_M ,OSDK_Y  ,OSDK_A ,0}, {"�݂�"}},	// �݂�݂��݂�݂��݂�
{3,{ OSDK_M ,OSDK_Y  ,OSDK_I ,0}, {"�݂�"}},
{3,{ OSDK_M ,OSDK_Y  ,OSDK_U ,0}, {"�݂�"}},
{3,{ OSDK_M ,OSDK_Y  ,OSDK_E ,0}, {"�݂�"}},
{3,{ OSDK_M ,OSDK_Y  ,OSDK_O ,0}, {"�݂�"}},

{2,{ OSDK_Y ,OSDK_A  , 0     ,0}, {"��"}},				// ����
{2,{ OSDK_Y ,OSDK_U  , 0     ,0}, {"��"}},
{2,{ OSDK_Y ,OSDK_O  , 0     ,0}, {"��"}},

{3,{ OSDK_L ,OSDK_Y  ,OSDK_A ,0}, {"��"}},	// ��
{3,{ OSDK_L ,OSDK_Y  ,OSDK_U ,0}, {"��"}},	// ��
{3,{ OSDK_L ,OSDK_Y  ,OSDK_O ,0}, {"��"}},	// ��

{2,{ OSDK_R ,OSDK_A  , 0     ,0}, {"��"}},				// ������
{2,{ OSDK_R ,OSDK_I  , 0     ,0}, {"��"}},
{2,{ OSDK_R ,OSDK_U  , 0     ,0}, {"��"}},
{2,{ OSDK_R ,OSDK_E  , 0     ,0}, {"��"}},
{2,{ OSDK_R ,OSDK_O  , 0     ,0}, {"��"}},

{3,{ OSDK_R ,OSDK_Y  ,OSDK_A ,0}, {"���"}},	// ���股���肥���
{3,{ OSDK_R ,OSDK_Y  ,OSDK_I ,0}, {"�股"}},
{3,{ OSDK_R ,OSDK_Y  ,OSDK_U ,0}, {"���"}},
{3,{ OSDK_R ,OSDK_Y  ,OSDK_E ,0}, {"�肥"}},
{3,{ OSDK_R ,OSDK_Y  ,OSDK_O ,0}, {"���"}},

{2,{ OSDK_W ,OSDK_A  , 0    ,0}, {"��"}},				// �키��������
{2,{ OSDK_W ,OSDK_I  , 0    ,0}, {"����"}},
{2,{ OSDK_W ,OSDK_U  , 0    ,0}, {"��"}},
{2,{ OSDK_W ,OSDK_E  , 0    ,0}, {"����"}},



{1,{ OSDK_MINUS       ,0  ,0 ,0}  	, {"�["}},	//  -
{1,{ OSDK_BACKSLASH   ,0  ,0 ,0}  	, {""}},	//  -
//{1,{ OSDK_Q           ,0  ,0 ,0}    , {"�p"}},	// Q
{1,{ OSDK_SEMICOLON   ,0  ,0 ,0}    , {"�G"}},	// ;
{1,{ OSDK_COLON       ,0  ,0 ,0}    , {"�F"}},	// :
{1,{ OSDK_RIGHTBRACKET,0  ,0 ,0}  	, {""}},	//  ]
{1,{ OSDK_1           ,0  ,0 ,0}  	, {"�P"}},	//  1
{1,{ OSDK_2           ,0  ,0 ,0}  	, {"�Q"}},	//  2
{1,{ OSDK_3           ,0  ,0 ,0}  	, {"�R"}},	//  3
{1,{ OSDK_4           ,0  ,0 ,0}  	, {"�S"}},	//  4
{1,{ OSDK_5           ,0  ,0 ,0}  	, {"�T"}},	//  5
{1,{ OSDK_6           ,0  ,0 ,0}  	, {"�U"}},	//  6
{1,{ OSDK_7           ,0  ,0 ,0}  	, {"�V"}},	//  7
{1,{ OSDK_8           ,0  ,0 ,0}  	, {"�W"}},	//  8
{1,{ OSDK_9           ,0  ,0 ,0}  	, {"�X"}},	//  9
{1,{ OSDK_0           ,0  ,0 ,0}  	, {"�O"}},	//  0
{1,{ OSDK_UPPER       ,0  ,0 ,0}  	, {"�O"}},	//  ^

{1,{ OSDK_AT          ,0  ,0 ,0}  	, {"�J"}},	//  @ ���_
{1,{ OSDK_LEFTBRACKET ,0  ,0 ,0}  	, {"�K"}},	//  | �����_

{1,{ OSDK_UPPER       ,0  ,0 ,0}  	, {"�O"}},	//  ^

{1,{ OSDK_COMMA       ,0  ,0 ,0}  	, {"�A"}},	//  ,
{1,{ OSDK_PERIOD      ,0  ,0 ,0}  	, {"�B"}},	//  .
{1,{ OSDK_SLASH       ,0  ,0 ,0}  	, {"�^"}},	//  /
{1,{ OSDK_UNDERSCORE  ,0  ,0 ,0}  	, {"�Q"}},	//  _

                                                                // ����
{ 2,{ OSDK_W ,OSDK_O  , 0    ,0}    , {"��"} },
{ 2,{ OSDK_N ,OSDK_N  , 0    ,0}    , {"��"} },
{ 3,{ OSDK_N ,OSDK_N  ,OSDK_N,0}    , {"��"} },

{-1,{ -1     ,-1      , -1   },{-1  , 0,0,0}},

};



// ****************************************************************************
// �@�ꉹ���ǂ����H
// ��0  :�͂�    0:������
// ****************************************************************************
int isBoin( int osdkeycode)
{
    return (osdkeycode==OSDK_A || osdkeycode==OSDK_I || osdkeycode==OSDK_U || osdkeycode==OSDK_E || osdkeycode==OSDK_O );
}

// ****************************************************************************
// �@�q�����ǂ����H
// ��0  :�͂�    0:������
// ****************************************************************************
int isShin( int osdkeycode)
{
    return (osdkeycode==OSDK_K || osdkeycode==OSDK_S || osdkeycode==OSDK_T || osdkeycode==OSDK_H || osdkeycode==OSDK_M || osdkeycode==OSDK_Y
    || osdkeycode==OSDK_R || osdkeycode==OSDK_W || osdkeycode==OSDK_P || osdkeycode==OSDK_F 
    || osdkeycode==OSDK_G || osdkeycode == OSDK_D || osdkeycode == OSDK_Z || osdkeycode == OSDK_B);
}

// ****************************************************************************
// 		convert_search:���[�}���̒Ԃ���}�b�`���O���� (convert_romaji2kana ����Ă΂��)
//
//   In:  buff    �ϊ�������������
//        line    �ϊ�����(romaji_tbl �e�[�u���̃C���f�b�N�X)
//
//   Out: HENKAN_SUCCESS   �ϊ�����
//        HENKAN_DOING     �ϊ���
//        HENKAN_FAILED    �ϊ����s
//        HENKAN_SUCCESS_LTU ���ϊ�����
// ****************************************************************************
int convert_search( char *buff , int *line)
{
    int i;
    int found =HENKAN_FAILED;

    *line = 0;
    
    if( buff[0]== buff[1])				// �q�����d�Ȃ��ē��͂��ꂽ��A���ɕϊ�
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
// 		convert_romaji2kana:
//		���[�}������A���Ȃɕϊ�����
//
//  OS�L�[�C�x���g��keydown �̂Ƃ���ŁA���ȃ��[�h���A���[�}���ϊ����[�h�Ȃ�A������ĂԁB
//
//
//	�����F���[�}���ϊ��ł��邩�`�F�b�N���āA�ϊ��ɐ���������A�L�[���͂���悤�ɁA�X�P�W���[���ɓo�^����B
//
//
// Out: HENKAN_SUCCESS: ���[�}���ϊ������A�L�[���͂���悤�ɁA�X�P�W���[���ɓo�^����
//      HENKAN_FAILED:  �ϊ����s
//      HENKAN_DOING  : �ϊ���
//      HENKAN_CANCEL : ���ϊ�
//      HENKAN_SUCCESS_LTU ���ϊ�����
//***************************************************************
int convert_romaji2kana( int osdkeycode )
{
    static char buff[4];
    static int  idx=0;
    int   line=0;
    int   found=0;

    int   saihenkan_flag=0;


    if(  osdkeycode < 0x20 || osdkeycode == OSDK_LEFT || osdkeycode == OSDK_RIGHT || osdkeycode== OSDK_UP
       || osdkeycode== OSDK_DOWN || osdkeycode==OSDK_SCROLLOCK || osdkeycode == OSDK_PAGEUP 
        || osdkeycode == OSDK_PAGEDOWN|| (osdkeycode >= OSDK_F1 && osdkeycode <= OSDK_F10) || osdkeycode==OSDK_END 
        || osdkeycode ==OSDK_SHIFT || osdkeycode == OSDK_ALT || osdkeycode == OSDK_SPACE)
        {
        idx=0;
        memset(buff,0, sizeof(buff));
        return HENKAN_CANCEL;
        }

    if(idx <3  && 0xd <= osdkeycode && osdkeycode <0x7f)
        {
         buff[ idx++ ]= osdkeycode;

         found = convert_search( buff , &line);	// convert to romaji ���[�}���ϊ����Ă݂�

         PRINTDEBUG1(KEY_LOG,"[P6][convert_romaji2kana] input buff= '%s' \n ", buff);

        if( !found )			// not match
            {
            PRINTDEBUG1(KEY_LOG,"[P6][convert_romaji2kana] convert searching  '%s'  not found \n", buff);
            memset(buff, 0, sizeof(buff));
            idx=0;
            }
        else if( found ==HENKAN_SUCCESS || found == HENKAN_SUCCESS_LTU)		// match
            {
            int j;
            int output_length=0;

            if( found == HENKAN_SUCCESS_LTU)
                line =0;        // �q�����_�u���ŗ����Ƃ��́A�����I�ɁA�u���v�ɕϊ�����

            PRINTDEBUG1(KEY_LOG,"[P6][convert_romaji2kana] convert_success '%s' -> ",buff);


           {
            char tmp[10];
            convertSjis2p6( romaji_tbl[line].keycode, tmp);  // convert shift JIS -> P6 code
            convertKana2Katakana( tmp);
            putAutokeyMessage( tmp);                         // register autokey
           }



            PRINTDEBUG(KEY_LOG,"\n");
            //if( !saihenkan_flag) {idx =0;	memset( buff , 0,  sizeof( buff));}
            //saihenkan_flag=0;
            if (found == HENKAN_SUCCESS_LTU)        // �q���_�u���ł����Ƃ��i�Ⴆ�΁AKK�̂Ƃ��́AKK -> K �ɂ��āA���̕ꉹ��҂�
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
            PRINTDEBUG2(KEY_LOG,"[P6][convert_romaji2kana] convert: part match '%s'  line=%d \n ", buff ,line);
            }
        }

    if( found ==HENKAN_FAILED)	// ���ȕϊ��L�[�ȊO�́A���̂܂ܕԂ��B
        {
         idx=0;
         memset( buff, 0,  sizeof( buff));
        }
    return found;
}

// ****************************************************************************
//  �J�^�J�i�����͂�����Ԃ��ƁA�Ђ炪�ȁ��J�^�J�i�ɕϊ�����
//      In: Out: buff �o�b�t�@ 
// ****************************************************************************
void convertKana2Katakana(unsigned char* buff)
{
    unsigned char *p;
    p= buff;
    for (int i = 0; i< strlen(buff); i++) {
        if (kanaMode && katakana) {
            if ((0x86 <= *p && *p <= 0x9f) || (0xe0 <= *p && *p <= 0xfd)) {   // kana?
                *p ^= 0x20;
            }
        p++;
        }
    }
}
