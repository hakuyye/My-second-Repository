#include <REG51.H>
#define uchar unsigned char
sbit beepIO=P2^5;
uchar m,n; 
uchar code T[49][2]={{0,0},
{0xF8,0x8B},{0xF8,0xF2},{0xF9,0x5B},{0xF9,0xB7},{0xFA,0x14},{0xFA,0x66},{0xFA,0xB9},{0xFB,0x03},{0xFB,0x4A},{0xFB,0x8F},{0xFB,0xCF},{0xFC,0x0B},
{0xFC,0x43},{0xFC,0x78},{0xFC,0xAB},{0xFC,0xDB},{0xFD,0x08},{0xFD,0x33},{0xFD,0x5B},{0xFD,0x81},{0xFD,0xA5},{0xFD,0xC7},{0xFD,0xE7},{0xFE,0x05},
{0xFE,0x21},{0xFE,0x3C},{0xFE,0x55},{0xFE,0x6D},{0xFE,0x84},{0xFE,0x99},{0xFE,0xAD},{0xFE,0xC0},{0xFE,0x02},{0xFE,0xE3},{0xFE,0xF3},{0xFF,0x02},
{0xFF,0x10},{0xFF,0x1D},{0xFF,0x2A},{0xFF,0x36},{0xFF,0x42},{0xFF,0x4C},{0xFF,0x56},{0xFF,0x60},{0xFF,0x69},{0xFF,0x71},{0xFF,0x79},{0xFF,0x81}
};
uchar code music[][2]={{0,4},
{24,4},{26,4},{28,12},{26,4},{27,8},{31,8},{26,24},{19,4},{19,4},{25,12},{22,4},{24,8},{27,8},{22,24},{19,8},{20,12},{19,4},{20,8},{27,8},{19,16},{0,4},{27,4},{27,4},{27,4},{26,12},{20,4},{20,8},{26,8},{26,16},{0,8},{24,4},{26,4},{27,12},{26,4},{27,8},{27,8},{31,8},{26,24},{19,4},{19,4},{24,12},{22,4},{24,8},{27,8},{22,24},{17,4},{19,4},{20,8},{27,4},{26,4},{26,4},{27,4},{27,8},{29,4},{29,4},{31,4},{27,4},{27,16},{27,4},{26,4},{24,4},{24,4},{26,8},{22,8},{24,24},{27,4},{29,4},{31,12},{29,4},{31,8},{34,8},{29,24},{22,4},{22,4},{27,12},{26,4},{27,8},{31,8},{31,24},{31,16},{24,4},{26,4},{27,8},{26,8},{29,4},{29,4},{27,12},{22,4},{22,16},{32,8},{31,8},{29,8},{27,8},{31,24},{31,8},{36,16},{34,8},{34,8},{31,4},{29,4},{27,16},{0,4},{27,4},{29,8},{27,4},{29,4},{29,8},{34,8},{31,24},{31,8},{36,16},{34,16},{31,4},{29,4},{27,16},{0,4},{27,4},{29,8},{27,4},{29,4},{29,8},{26,8},{24,24},{24,4},{26,4},
{0xFF,0xFF}};

void delay(uchar p)
{
    uchar i,j; 
    for(;p>0;p--)
    for(i=181;i>0;i--)
    for(j=181;j>0;j--);
}

void pause()
{
    uchar i,j;
    for(i=150;i>0;i--)
    for(j=150;j>0;j--);
}

void T0_int() interrupt 1
{
 beepIO=!beepIO;
 TH0=T[m][0]; TL0=T[m][1];
}

void main()
{
 uchar i=0; 
 TMOD=0x01;  EA=1; ET0=1; 
 while(1) 
      {
        m=music[i][0];n=music[i][1]; 
           if(m==0x00)
             {TR0=0;delay(n);i++;} 
           else if(m==0xFF)
             {TR0=0;delay(30);i=0;} 
           else if(m==music[i+1][0]) 
             {TR0=1;delay(n);TR0=0;pause();i++;}
           else
             {TR0=1;delay(n);i++;}
      }
}