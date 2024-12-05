#include "_types.h"
void _delay_ms(_U16 dly)
{
  _U16 i;
  for(;dly>0;dly--)
  {
    for(i=122;i>0;i--);
  }
}