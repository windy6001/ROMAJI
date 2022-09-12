/*
Copyright (c) 2020 Windy

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
*/

/** iP6: PC-6000/6600 series emualtor ************************/
/**          ���[�}���ϊ�                                   **/
/**          name is romaji.c                               **/
/**                                                         **/
/**          by Windy                                       **/
/*************************************************************/
#ifndef _ROMAJI_H
#define _ROMAJI_H

#define HENKAN_SUCCESS  1		// ���[�}���ϊ�����
#define HENKAN_FAILED   0		// ���[�}���ϊ����s
#define HENKAN_DOING   -1		// ���[�}���ϊ���
#define HENKAN_CANCEL   2		// ���[�}���ϊ����Ȃ��@& �L�����Z��
#define HENKAN_SUCCESS_LTU 3	// ���[�}���ϊ�����(��)



void autokeyin_func(void);
int convert_search( char *buff , int *line);
int convert_romaji2kana( int osdkeycode );


#endif // ROMAJI_H
