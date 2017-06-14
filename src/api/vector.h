#ifndef _DTU_VECTOR_
#define _DTU_VECTOR_

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT );
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / (b) );



typedef struct
{
  long x;
  long y;
} Vector;

void flipX(Vector* vector);
void flipY(Vector* vector);

#endif /*! _DTU_VECTOR_ */
