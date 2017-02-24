/* Header File for PEPSI MIDI Audio */

#if     !defined(__MIDI_H)
#define __MIDI_H

#include "sosm.h"

#define MIDI_PATH "MIDI\\"

#define BANK_SIZE 5404
#define MT32_SIZE 1404

extern short int InitialiseMIDI(void);
extern short int UnInitialiseMIDI(void);
extern short int StartSong(char *song,short int vol);
extern void PauseSong();
extern void ResumeSong();
extern void StopSong();
extern short int CheckSong();
extern void SetMIDIVolume(short int Music);

extern WORD MIDIDriverHandle;				// Handle of driver for playing samples
extern WORD SongHandle;

#endif  /* __MIDI_H */
