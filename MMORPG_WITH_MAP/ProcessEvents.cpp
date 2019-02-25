#include "ProcessEvents.h"
void processEvents(Scene* &scene, Player* &player)
{
	for (int i = 0, j = scene->items_count; i < j; i++)
	{//if player position == item position
		if (scene->sceneItems[i].x == player->x && scene->sceneItems[i].y == player->y)
		{
			player->inventory.addItem(scene->sceneItems[i]);//add to inventary
			scene->deleteItem(i, scene->sceneItems[i]);//delete item from scene items array
		}
	}
}