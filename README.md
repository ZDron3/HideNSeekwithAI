# HideNSeekwithAI

This Game consists of 4 major game entities listed as follows:

###### 1) The LevelManager 
###### 2) LevelElements
###### 3) Player Character 
###### 4) AI Character

The Expected gameplay consists of player starting on start spot.Bots and level elements spawn around the map randomly in such a way that provide a safe player start position.
The player passes the level if he reaches the end position without being detected by the bots.He can use the pickup items spawned as part of level to create a distraction and
sneak past the bots.The above game entities are used for the gameplay as follows :

## The LevelManager 
This is singleton actor create by gamemode which takes care of spawning the entire level with certain level elements and ai bots in a particular bound. The level elements
consists of Obstacle (AObstacle) and Distraction pickup item (AItem) which derive their functionality from AGameSpawnActor. This helps us utilize polymorphism at its best 
throughout the game.The LevelManager also takes care of spawing the ai bots in the level. All the elements and AI bots are spawned at random location within a bounding box
which is set in the game using ObjectSpawnDimension actor. As this actor provides a particular bound (which might be extended by the desginer as per their needs) to spawn
level elements.

## LevelElements
The level elements consists of the actors spawned by the levelmanager other than AI bots. The level elements consists of obstacles(AObstacle) and pickup items(AItem) both derived from
gamespawnactor which consists of declared Attributes that are required by the elements to spawn in level, consists of the visual orientation of the actors as well as the 
amount which the levelmanager uses for spawing. The designer may directly make change to the level elements using their respective blueprint which would reflect in all the 
level element actors(obstacle/pickup) spawned by levelmanager.This functionality can futher be used to create new "type" of element or "modify/update" the existing ones.

## Player Character 
The player character is the main entity of the game that drives it. This character is derived from basecharacter(ABase_GameCharacter). The base character provides attributes
such as visuals, teams and controllers which define the derived character.Player character is one of the child character which derives from base character and personifies as 
player character i.e character played by the player.It is controlled by a player controller which includes functionality for the player to navigate through the game
and utilize trigger the pickup(PickUp_Implementation) and throw(Throw_Implementation) of items (AItem) which triggers a distraction in AI Character. 

## AI Character
The AI character(AEnemyAI) is an entity that derives the attributes if basecharacter and personifies them with traits used to oppose the player and try him from completing his
objective. Unlike the Player Character the AI Character is controlled by an AI controller(AEnemyAIController) which in turn implements certain behaviour tree's i.e certain 
Finite State Machine which changes the AI Character states making it behave a certain way not beneficial to player character in completing his objective.AI Controller also
implements certain Perception components which helps the AI Character have a sense to see(AISenseConfig_Sight) and sense to hear(AISenseConfig_Hearing) which helps it look at
player character and catch him or hear the distraction created by player character to investigate it which in turn helps the underlying game mechanic. 

