# HideNSeekwithAI

This Game consists of 4 major game entities listed as follows:

###### 1) The LevelManager 
###### 2) LevelElements
###### 3) Player Character 
###### 4) AI Character

The Expected gameplay consists of a player starting on start spot. Bots and level elements spawn around the map randomly in such a way that provides a safe player start position.
The player passes the level if he reaches the end position without being detected by the bots. He can use the pickup items spawned as part of the level to create a distraction and
sneak past the bots. The above game entities are used for the gameplay as follows :

## The LevelManager 
This is a singleton actor create by gamemode which takes care of spawning the entire level with certain level elements and ai bots in a particular bound. The level elements
consist of Obstacle (AObstacle) and Distraction pickup item (AItem) which derive their functionality from AGameSpawnActor. This helps us utilize polymorphism at its best throughout the game. The LevelManager also takes care of spawning the ai bots in the level. All the elements and AI bots are spawned at a random location within a bounding box
which is set in the game using ObjectSpawnDimension actor. This actor provides a particular bound (which might be extended by the designer as per their needs) to spawn
level elements.

## LevelElements
The level elements consist of the actors spawned by the level manager other than AI bots. The level elements consist of obstacles(AObstacle) and pickup items(AItem) both derived from
gamespawnactor which consists of declared Attributes that are required by the elements to spawn in level, consists of the visual orientation of the actors as well as the amount which the level manager uses for spawning. The designer may directly make a change to the level elements using their respective blueprint which would reflect in all the level element actors(obstacle/pickup) spawned by level manager.This functionality can further be used to create a new "type" of an element or "modify/update" the existing ones.

## Player Character 
The player character is the main entity of the game that drives it. This character is derived from basecharacter(ABase_GameCharacter). The base character provides attributes
such as visuals, teams, and controllers that define the derived character. Player character is one of the child characters which derives from base character and personifies as player character i.e character played by the player. It is controlled by a player controller which includes functionality for the player to navigate through the game
and utilize trigger the pickup(PickUp_Implementation) and throw(Throw_Implementation) of items (AItem) which triggers a distraction in AI Character. The designer here has the
liberty to implement her own throw/ pickup and move functionality using blueprints

## AI Character
The AI character(AEnemyAI) is an entity that derives the attributes if basecharacter and personifies them with traits used to oppose the player and try him from completing his
objective. Unlike the Player Character, the AI Character is controlled by an AI controller(AEnemyAIController) which in turn implements certain behavior tree's i.e certain 
Finite State Machine which changes the AI Character states making it behave a certain way not beneficial to the player character in completing his objective.AI Controller also
implements certain Perception components which help the AI Character have the sense to see(AISenseConfig_Sight) and sense to hear(AISenseConfig_Hearing) which helps it look at
player character and catch him or hear the distraction created by player character to investigate it which in turn helps the underlying game mechanic. 

###### Assignment:
Introduction: Create a new Basic Code project, with starter content, named "Hide and seek with AI" The best approach is to use C++ for building base gameplay systems and performance-critical code with Blueprints used to customize behavior or create composite behaviors from C++ building blocks. Your goal is to create a simple game prototype with AI Bots and a character controller.  

###### Environment: 
1.Location - the big rectangular room 120m x 30m.  
2.Start spot - position where the player spawned at the beginning of the game. Located at the end of the room.
3.Win spot - a small green area, located at the opposite end of the room 1m x 1m. 
4.Small cubes - represent an abstract item player can pick up and throw forward. In the number of twenty-four pieces ​randomly spawned in the room 0.2m x 0.2m x 0.2m each. 5.Big static cube - represents an obstacle. AI bots can't see the player through the obstacles. In the number of twenty-four pieces ​randomly spawned in the room 3m x 3m x 3m each.   

###### Player: Abstract 1m height cylinder: 
1.First-Person camera view.
2.WASD movement.  
3.LMB - pick up / throw the items. 
4.Throwing power increases by holding the LMB down from min to max in 2 sec. The minimum throwing distance is 1m, and the maximum is 15m. 
5.No inventory system, the player can carry only one item at a time.
6.The player's goal is to get from one end of the room to the other. Whenever the player triggers the win spot - game is completed.  Bots: Abstract AI-driven 1 meter height cylinders in the number of six randomly spawned in the room. AI specifications below:  

1.AI's goal is to chase and catch the player. If the bot gets the player game is over and should be restarted automatically.
2.The AI's movement speed is twice faster than the player's speed, which makes the player pretty easy to catch. 
3.Bots chase after the player only when seeing him. The field of view angle is 70 degrees; raycast distance is 20 meters. The player should see the debug splines of FOV; 4.Whenever bots can't see the player, they slowly move to their spawn spot with 20% of chasing speed. 
5.Standing on the spawn spot bot constantly looks around with random intervals each time set in the range from 3 to 12 sec.
6.The player can distract bot by throwing items (small cubes) but only on the condition that bot can't see the player. The bot can hear how the item hits the floor, walls, or obstacles if the distance between him and the item's collision spot is less than 20 meters. Every time hearing item collision bot should go there with 50% of the chasing speed. On collision spot, the bot should look around, and if he can't see the player, he has to bring the item to its spawn spot and then go back to own spawn spot with 20% of chasing speed. Whenever bot sees the player, he should stop the current activity (holding the respawn spot, moving to collision spot or carrying item) and start chasing after the player. 
7.If bot lost sight of the player, he has to reach the point where he last saw player and look around there. If the player is disappeared, the bot should go back to his spawn position with 20% of chasing speed. 

###### Expected gameplay: Player placed on start spot.
Bots randomly spawned on the map in such a way that provides a safe start position for the player. If the start position isn't safe - restart the entire level automatically.  The player beats the game if he passes through the level without getting caught by bots. Player should throw the items to distract bots and sneak behind the obstacles to get to the win spot.  

###### Requirements:  
1.The test project must be completed using the latest version of the Unreal Engine.
2.The project’s archive should contain UE project and compiled desktop application for Windows.
3.Keep your code clean and readable, don't forget to leave the comments with sufficient information.
4.Consider this project as the early prototype for a Game Designer where all important parameters should be accessible and customizable on the fly.
