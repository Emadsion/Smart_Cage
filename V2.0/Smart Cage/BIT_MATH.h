/*********************************************************/
/* Author      : Nourhan mahmoud                            */
/* Date        : 29 JUL 2020                             */
/* Version     : V01                                     */
/*********************************************************/
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg,bitnum)          reg |=  (1 << (bitnum))
#define CLR_BIT(reg,bitnum)          reg &= ~(1 << (bitnum)) 
#define GET_BIT(reg,bitnum)          ((reg >> bitnum) & 1  )
#define TOG_BIT(reg,bitnum)          reg ^=  (1 << (bitnum))


#endif 