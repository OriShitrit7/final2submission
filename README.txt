Project: Text Adventure World
Students:
 Ori Shitrit - 322997438
 Elior Chen - 313138893

Notes:
- Implemented all required features.
Screen Files:
Each screen file represents a room in the game (format at the end).
The file is composed of two main parts:
1.  Map Layout
A textual grid representing the room map, using characters to denote walls, players, doors, obstacles, springs, etc.

2. Additional Data Section
Metadata describing properties of specific objects that cannot be fully represented by a single character on the map (such as doors, switches, keys etc.).

Legend:
-The legend may be placed on external walls (W).
-Aside from external walls, the legend must not overlap or overwrite any other objects or map elements.

Doors:
Doors are represented on the map by numeric characters (2-9).
The numeric character represents the index of the destination room to which the door leads.
In the data section of the screen file, each door is assigned an explicit door index (out of all doors in the room).
This index is required for associating doors with keys and/or switches.
A room may contain multiple doors leading to the same destination room, as well as doors leading to different rooms.

Final Room Door:
A door that leads to the final room is marked using the value:
(number of loaded screen files + 1).

Springs:
 - Springs that are not attached to a wall are considered invalid by design and are not supported.
-In the case of a player in acceleration bumping into a wall the player's movement is stopped.
-Also, in the case of player making contact with the body of a spring (not compressing the spring), the same thing happens.

Riddles File:
The riddles file contains all riddles used throughout the game.
For each riddle, the file specifies:
-The room number to which the riddle belongs
-The riddle’s position within the room
-The riddle text
-The expected solution (or solutions)

Screen Files Format:

DARK <x> <y> <x> <y>
DOOR <x> <y> DoorID <doorID> OPEN <0|1> KEYS <neededkeys> RULE <rule>
KEY <x> <y> DoorID <doorID>
SWITCH <x> <y> DoorID <doorID>
TELEPORT <x1> <y1>  <x2> <y2>


