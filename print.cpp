#include "types.hpp"
#include "ports.hpp"

void print(const char *_message)
{
  unsigned short offset =0;
  unsigned long i;
  unsigned char *vidmem = (unsigned char *)0xB8000;

  // Read cursor position
  out(0x3D4, 14);
  offset = in(0x3D5) << 8;
  out(0x3D4, 15);
  offset |= in(0x3D5);

  // Start at writing at cursor position
  vidmem += offset*2;

  // Continue until we reach null character
  i = 0;
  while (_message[i] != 0) {
    *vidmem = _message[i];
    i++;
	vidmem += 2;
  }
  // Set new cursor position
  offset += i;
  out(0x3D5, (unsigned char)(offset));
  out(0x3D4, 14);
  out(0x3D5, (unsigned char)(offset >> 8));
}

void printfHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    print(foo);
}
void printfHex16(uint16_t key)
{
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}
void printfHex32(uint32_t key)
{
    printfHex((key >> 24) & 0xFF);
    printfHex((key >> 16) & 0xFF);
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}



void clrscr()
{
  unsigned char *vidmem = (unsigned char *)0xB8000;
  int loop;
  const int size = 80*25;
  // Clear visible video memory
  for (loop=0; loop<size; loop++)
  {
    *vidmem = 0x00;
    vidmem++;
    *vidmem = 0x0F;
    vidmem++;
  }
    // Set cursor position to 0,0
  out(0x3D4, 14);
  out(0x3D5, 0);
  out(0x3D4, 15);
  out(0x3D5, 0);
}

