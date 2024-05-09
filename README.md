# Documentation

## Entity

The Entity struct is responsible for containing information of all types of objects in the game.
Everything from player to items is an Entity.

Since entities might need different properties, the Entity struct contains a void pointer "extraModule"
that can point to a separate struct.

## Entity Container

The engine holds all entities in a single linked list which is accessed through the EntityContainer struct.
It contains two pointers to Entity, one to the first item in the list and one to the last.