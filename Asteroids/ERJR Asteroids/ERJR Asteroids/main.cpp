/// 
/// Authors: Jack and Ethan
/// submitted 30/4/19
/// started sometime late january
///
/// ---
/// time taken records
/// Ethan:
/// I spent about 70ish hours on this. I spent a great deal of time 
///planning and re-writing old stuff to try improve it
/// I did the splash, licence, main menu, help screen, player movement, 
///asteroid movement, the collisions of both of those with each other
/// I did bullets, and their collisions with asteroids. i did the pause 
///button, the accessing and closing of the ingame upgrade menu
/// i did the levelling system of the ship skin changes and the reaching
///of the goals and ultimate end game win condition
/// i did the particles for big and little asteroids and the ship
///hitting either of them particles. I did the fuel meter
/// i put all those other little counters at the top, sorry they're so cramped >.< 
/// also did the sound effects and flashing warning upon contact with asteroid
/// i think that's everything logged that's in the game..? if there's other stuff, 
/// i probably did that too :c
///
/// sorry about lack of comments and stuff :c i kinda had to crunch loads of stuff that wasn't
/// done into the last week, and i hadn't time at the end to go over it and comment detailed stuff
///
/// I wrote all my bits of code by myself, and only had help from a friend of mine
/// to do the random generator which i used in asteroids, their spawning and their speed determining.
/// i assume jack wrote all his code too (assume)
/// 
/// Jack:
/// <input Jack's time> ??
/// Jack worked on the money and the purchasing of upgrades. He made the health 
/// and shield bars and did the mechanics behind them.
/// Jack also did the game over screen and the returning to main menu from there
/// jack also created the gameplay background sprite
/// jack also did the screen wrap of the player ship movement 
///-> (moving left and appearing right) , (moving up and appearing on bottom) etc
/// ---
/// description:
///
/// an assignment in lecturer pete's game studies class (games dev year 1)
/// our version of an asteroids clone
/// added some extra features
/// star wars themed for our pleasure
/// you must destroy asteroid fields to allow the rebel alliance to engage the death star
///
/// ---
/// bugs:
///
/// Jack's money will jump around if you destroy multiple small asteroids, 
///there is only one on screen at a time
///
/// my particles for the little asteroids decided not to function after
///jack's last merge, idk what the problem was
///
/// i tried to fix the above but wasn't able to.
///
/// to the best of my knowledge, those are the only two notable issues
/// 

#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include"Game.h"




/// <summary>
/// main enrtry point
/// </summary>
/// <returns>zero</returns>
int main()
{
	/* initialize random seed: */
	srand(time(NULL));
	Game game;
	
	game.run();
	return 0;
}