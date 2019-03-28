//------------------------------------------------------------------------
// GameTest.cpp
// 
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"

// initial variables
static const int MAP_SIZE = 20;
static const int NUM_PACMANS = 2;
static const int NUM_AI = 4;
static float elapsedTimeForPlayer = 0;
static float fixedUpdateForPlayer = 500;
static float elapsedTimeForAI = 0;
static float fixedUpdateForAI = 1500;
static int playerIndex = 0;

GTileMap map(MAP_SIZE);
std::vector<Pacman> player;
std::vector<Ghost> AI;

//----------------------Useful functions---------------------------------

// This template used to set An agents tag value onto the game Tile map
template<typename T>
void SetAgentLocationOnMap(T p)
{
	map.SetTileValue(p.GetX(), p.GetY(), p.GetTag());
}
// This function controls the Control Scheme for the player
// Current supports up to 2 Pacman
void playerControls()
{
	switch (player.size())
	{
	case 2:
		if (App::GetController().GetLeftTrigger() > 0.0f)
			playerIndex = 0;
		if (App::GetController().GetRightTrigger() > 0.0f)
			playerIndex = 1;
		break;
	}
}
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	/*
		initalizes and contructs the set of Pacmen(Player)
		and set of Ghosts(AI)
	*/
	std::vector<std::pair<int, int>> tunnels = map.GetTunnelLocations();

	auto initP = [&](Pacman& p) 
	{
		int spawn_location_index = rand() % tunnels.size();
		p = { tunnels[spawn_location_index].first, tunnels[spawn_location_index].second };
		spawn_location_index = rand() % tunnels.size();
		SetAgentLocationOnMap(p);
	};

	auto initA = [&](Ghost& g)
	{
		int spawn_location_index = rand() % tunnels.size();
		g = { tunnels[spawn_location_index].first, tunnels[spawn_location_index].second };
		SetAgentLocationOnMap(g);
	};

	player.resize(NUM_PACMANS);
	std::for_each(player.begin(), player.end(), initP);
	
	AI.resize(NUM_AI);
	std::for_each(AI.begin(), AI.end(), initA);

}


/* 
	update the simulation on fixed times relative to the funtion Update
*/
void FixedUpdateForPlayer(Pacman& p)
{
	map.SetTileValue(p.GetX(), p.GetY(), mapValue::FLOOR);
	p.Move(map, App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY());
	SetAgentLocationOnMap(p); 
}
void FixedUpdateForAI(Ghost& g, int ghost_index)
{
	if (g.GetMoves().size() == 0)
	{
		g.SetList(FindPath(g.GetX(), g.GetY(), player[ghost_index % NUM_PACMANS].GetX(), player[ghost_index % NUM_PACMANS].GetY(), map));
	}
	map.SetTileValue(g.GetX(), g.GetY(), mapValue::FLOOR);
	g.Move(map, player[ghost_index % NUM_PACMANS]);
	SetAgentLocationOnMap(g); 
}
//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------

void Update(float deltaTime)
{
    static const float MIN_FRAMERATE = (1000 / 20);
    if (deltaTime > MIN_FRAMERATE)
        deltaTime = MIN_FRAMERATE; 
	elapsedTimeForPlayer += deltaTime;
	elapsedTimeForAI += deltaTime;

	playerControls();

	if (elapsedTimeForPlayer > fixedUpdateForPlayer)
	{
		elapsedTimeForPlayer = 0;
		FixedUpdateForPlayer(player[playerIndex]);
	}

	if (elapsedTimeForAI > fixedUpdateForAI)
	{
		elapsedTimeForAI = 0;
		for(int i = 0; i < NUM_AI; i++)
			FixedUpdateForAI(AI[i], i);
	}
	
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	 
   // g_map.Render();
	map.RenderMap();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
}