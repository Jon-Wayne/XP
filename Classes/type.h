//
//  type.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__type__
#define __XP__type__

/*
 *  base integer type
 */
typedef     unsigned char       U8;
typedef     signed char         S8;
typedef     unsigned short      U16;
typedef     signed short        S16;
typedef     unsigned int        U32;
typedef     signed int          S32;
typedef     unsigned long long  U64;
typedef     signed long long    S64;

/*
 *  base float type
 */
typedef     float               F32;
typedef     double              F64;

/*
 *  base bool type
 */
typedef     bool                B8;

/*
 *  base string type
 */
typedef     unsigned char       UTF8;
typedef     unsigned short      UTF16;
typedef     unsigned int        UTF32;
typedef     std::string         STR;

#endif /* defined(__XP__type__) */
