#include "../Game/textWriter.h"
#include "randomnmbr.h"
#ifdef __cplusplus
extern "C" {
	#include "../Display/displayFunc.h"
	
	#endif
	#ifdef __cplusplus
}
#endif


void startScreen_init(){

	NumberGenerator ng = NumberGenerator();
	
	//SchwarzerHintergrund
	fillRect(0, 0, 125, 320, BLACK); 
	fillRect(100, 0, 200, 320, BLACK); 
	fillRect(200, 0, 220, 320, BLACK); 
	
	
	//Sterne
	for(int i = 0; i < 10; i++){
		uint8_t n1 = ng.getrndNo();
		uint8_t n2 = ng.getrndNo();
		for(int j = 0; j < 10; j++){
			
			drawStar(n1, n2);			
		}
	}



	//PRESS ANYWHERE TO START
	TextWriter tw1 = TextWriter();
	tw1.setCursorPos(45,240);
	tw1.drawString("PRESS ANYWHERE", 14);
	
	TextWriter tw2 = TextWriter();
	tw2.setCursorPos(80,250);
	tw2.drawString("TO MOVE", 7);
}





