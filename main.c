/*
 * NOTE: DO NOT JUST COPY ANY OF THIS CODE FOR FUTURE HW/LABS
 * YOU MUST UNDERSTAND AND RE-WRITE FOR YOURSELF ANYTHING YOU
 * FIND USEFUL IN THIS FILE!
 */

#include "mylib.h"
#include "dummyBg.h"
#include "thriller.h"

#define START_ON_FIFO_EMPTY 0x30000000

unsigned int vBlankCount;
unsigned int start;
unsigned int songLength;

void playThriller() {
  songLength = VBLANK_FREQ * thriller_length / thriller_sampleRate;

  REG_TM0D = 65536 - (1 << 24) / thriller_sampleRate;
  REG_TM0CNT = TIMER_ON;

  DMANow(1, thriller_data, REG_FIFO_A,
    START_ON_FIFO_EMPTY |
    DMA_DESTINATION_FIXED |
    DMA_32 |
    DMA_REPEAT
  );
  start = vBlankCount;
}

/*
 * NOTE: DO NOT JUST COPY ANY OF THIS CODE FOR FUTURE HW/LABS
 * YOU MUST UNDERSTAND AND RE-WRITE FOR YOURSELF ANYTHING YOU
 * FIND USEFUL IN THIS FILE!
 */

void interruptHandler(void) {
   REG_IME = 0;  // Disable interrupts
   if(REG_IF & INT_VBLANK)  {
      vBlankCount++;
      if (vBlankCount % 8 == 0) PALETTE[1]++; // vBlankCountingIsWorking
      if((vBlankCount - start) > songLength)  {
        playThriller(); // loop the song forever
      }
   }
   REG_IF = REG_IF;
   REG_IME = 1;
}

void setupInterrupts(void) {
  REG_IME = 0;  //disable interrupts
  REG_INTERRUPT = interruptHandler;  //set int handler
  // enable vBlank Interrupts
  REG_IE |= INT_VBLANK;  // Enable vblank interrupt detection
  REG_DISPSTAT |= INT_VBLANK_ENABLE;  // Make display generate vblank interrupts

  REG_IME = 1;  //enable interrupts
}

/*
 * NOTE: DO NOT JUST COPY ANY OF THIS CODE FOR FUTURE HW/LABS
 * YOU MUST UNDERSTAND AND RE-WRITE FOR YOURSELF ANYTHING YOU
 * FIND USEFUL IN THIS FILE!
 */

int main(){
  REG_DISPCTL = MODE0 | BG0_ENABLE;

  // we don’t want to mess with sound channels 1-4
  REG_SOUNDCNT_L = 0;

  // Enable sound (Master control)
  REG_SOUNDCNT_X = SND_ENABLED;

  // enable and reset Direct Sound channel A, at full volume,
  // using Timer 0 to determine frequency
  REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 |
                   DSA_OUTPUT_RATIO_100 |
                   DSA_OUTPUT_TO_BOTH |
                   DSA_TIMER0 |
                   DSA_FIFO_RESET;

  // start counting vBlanks
  setupInterrupts();

  playThriller();
  
  // dummy background
  DMANow(3, dummyBgPal, PALETTE, 256);
  DMANow(3, dummyBgTiles, &CHARBLOCK[0], dummyBgTilesLen / 2);
  DMANow(3, dummyBgMap, &SCREENBLOCK[8], dummyBgMapLen / 2);
  REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(8);
  PALETTE[1] = 0; // black, initially 

  while(1){
    // Nothing in here this time.
  }
}

/*
 * NOTE: DO NOT JUST COPY ANY OF THIS CODE FOR FUTURE HW/LABS
 * YOU MUST UNDERSTAND AND RE-WRITE FOR YOURSELF ANYTHING YOU
 * FIND USEFUL IN THIS FILE!
 */