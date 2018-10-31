/* 
 * ansics.h
 * 
 * https://github.com/ChuOkupai/ansics
 *
 * Copyright (c) 2018 Adrien Soursou
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef	_ANSICS_H
#define	_ANSICS_H	1

/* SECTION */
#define COLOR	0
#define FORMAT	1

/* TYPE */
/** FORMAT TYPE **/
#define ALL				0
#define BLINK			1
#define BOLDBRIGHT		2
#define DIM				3
#define HIDDEN			4
#define REVERSE			5
#define STRIKETHROUGH	6
#define UNDERLINED		7
/** COLOR TYPE **/
#define BACKGROUND	0
#define FOREGROUND	1

/* VALUE */
#define RESET	0
/** FORMAT **/
#define SET	1
/** COLOR **/
#define BLACK		1
#define RED			2
#define GREEN		3
#define YELLOW		4
#define BLUE		5
#define MAGENTA		6
#define CYAN		7
#define LGRAY		8
#define DGRAY		9
#define LRED		10
#define LGREEN		11
#define LYELLOW		12
#define LBLUE		13
#define LMAGENTA	14
#define LCYAN		15
#define WHITE		16

#define _ACS_000	"\e[49m"
#define _ACS_001	"\e[40m"
#define _ACS_002	"\e[41m"
#define _ACS_003	"\e[42m"
#define _ACS_004	"\e[43m"
#define _ACS_005	"\e[44m"
#define _ACS_006	"\e[45m"
#define _ACS_007	"\e[46m"
#define _ACS_008	"\e[47m"
#define _ACS_009	"\e[100m"
#define _ACS_0010	"\e[101m"
#define _ACS_0011	"\e[102m"
#define _ACS_0012	"\e[103m"
#define _ACS_0013	"\e[104m"
#define _ACS_0014	"\e[105m"
#define _ACS_0015	"\e[106m"
#define _ACS_0016	"\e[107m"
#define _ACS_010	"\e[39m"
#define _ACS_011	"\e[30m"
#define _ACS_012	"\e[31m"
#define _ACS_013	"\e[32m"
#define _ACS_014	"\e[33m"
#define _ACS_015	"\e[34m"
#define _ACS_016	"\e[35m"
#define _ACS_017	"\e[36m"
#define _ACS_018	"\e[37m"
#define _ACS_019	"\e[90m"
#define _ACS_0110	"\e[91m"
#define _ACS_0111	"\e[92m"
#define _ACS_0112	"\e[93m"
#define _ACS_0113	"\e[94m"
#define _ACS_0114	"\e[95m"
#define _ACS_0115	"\e[96m"
#define _ACS_0116	"\e[97m"
#define _ACS_100	"\e[0m"
#define _ACS_110	"\e[25m"
#define _ACS_120	"\e[21m"
#define _ACS_130	"\e[22m"
#define _ACS_140	"\e[28m"
#define _ACS_150	"\e[27m"
#define _ACS_160	"\e[29m"
#define _ACS_170	"\e[24m"
#define _ACS_111	"\e[5m"
#define _ACS_121	"\e[1m"
#define _ACS_131	"\e[2m"
#define _ACS_141	"\e[8m"
#define _ACS_151	"\e[7m"
#define _ACS_161	"\e[9m"
#define _ACS_171	"\e[4m"

#define _ACS_CONCAT(S,T,V) _ACS_##S##T##V

/* Macro to use in your code */
#define ACS(SECTION,TYPE,VALUE) _ACS_CONCAT(SECTION,TYPE,VALUE)

/* Or you can use some useful shortcuts */
/** Reset all **/
#define ACS_R			ACS(FORMAT,ALL,RESET)
/** Reset color type **/
#define ACS_RC(TYPE)	ACS(COLOR,TYPE,RESET)
/** Reset format type **/
#define ACS_RF(TYPE)	ACS(FORMAT,TYPE,RESET)
/** Set format **/
#define ACS_F(TYPE)		ACS(FORMAT,TYPE,SET)
/** Set background color **/
#define ACS_BC(VALUE)	ACS(COLOR,BACKGROUND,VALUE)
/** Set foreground color **/
#define ACS_FC(VALUE)	ACS(COLOR,FOREGROUND,VALUE)

#endif /* ansics.h  */
