
//{{BLOCK(dummyBg)

//======================================================================
//
//	dummyBg, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 49 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1568 + 2048 = 4128
//
//	Time-stamp: 2020-04-06, 23:59:01
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_DUMMYBG_H
#define GRIT_DUMMYBG_H

#define dummyBgTilesLen 1568
extern const unsigned short dummyBgTiles[784];

#define dummyBgMapLen 2048
extern const unsigned short dummyBgMap[1024];

#define dummyBgPalLen 512
extern const unsigned short dummyBgPal[256];

#endif // GRIT_DUMMYBG_H

//}}BLOCK(dummyBg)
