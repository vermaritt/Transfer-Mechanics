## Transfer-Mechanics

Provides a simple mechanism for passing/transferring objects and weapons from one player to another.

`Note: This is a work in progress and It needs to be tested with 2-3 players.`

### Requirements

* San Andreas Multiplayer Client 0.3.7 .
* zcmd (for demo script)

### Include Focus

This include focuses mainly on Roleplay and Cops and Robberers servers.

### Situational Uses

* [CnR/RP] If an unarmed robberer is being chased by an armed police officer, then another robberer(his/her partner) can help him by passing a weapon to him. This makes the gameplay look better.
* [Fun/CnR/RP] You can even have some fun with this include. Imagine if your friend wants to use your hat object for just a time being, you would just have to pass your hat to him and that's it. (**Attachments of objects has to be coded manually, as this include just provides the mechanism**).
* There are lots of uses rather than the mentioned uses.

### Application Programming Interface

#### Macros

```PAWN
#define TFR_SPEED_MULT           	55.0

Optimal speed/velocity multiplier.
```

#### Functions

 ```PAWN
TFR_ObjectInit(cell, objectid)

Used to initialize object to the cell.( **Used only for passing objects not weapons**)

cell - cell is a data handler in the script which ranges from 0-99 by default, that is 100 objects can be used to pass/transfer. Thus, it can be increased to user's choice.(**100 cells are more than enough as cells become automatically vacant when player ctaches the object or the object gets get destroyed by the include itself if any of the players does not catches the object**)
objectid - The ID of the object to be initialized.

```

 ```PAWN
TFR_PassObject(cell, playerid, Float:velx, Float:vely, Float:velz = 0.0, Float:limit = 5.0)
 
Used to pass the object.

cell - In which the objectid has been initialized. (put 0, if you stored in 0, put 1 if you stored in 1 ...)
playerid - The passer.
velx - Passing/transferring velocity in the X axis.
vely - Passing/transferring velocity in the Y axis.
velz - Passing/transferring velocity in the Z axis. (** for now Z in not considered**)
limit - Range in which the player should be in to catch the object.
```

```PAWN
TFR_PassWeapon(cell, playerid, color, error[], Float:velx, Float:vely, Float:velz = 0.0, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, Float:limit = 5.0)

Used to transfer/pass weapons.

cell - Same as the above function.
playerid - Same as the above function.
color - Color of the error message.
error - This gets printed for the player if he tries to transfer/pass an invalid weapon.
velx - Same as the above function.
vely - Same as the above function.
velz - Same as the above function.
rx - Rotation in the X axis for the weapon object which will be created to function the mechanism.
ry - Rotation in the Y axis for the weapon object which will be created to function the mechanism.
rz - Rotation in the z axis for the weapon object which will be created to function the mechanism.
limit - Same as the above function.
```

```PAWN
TFR_SetRotVelocity(cell, Float:rx, Float:ry, Float:rz)

Used to set the objects rotational velocity.

cell - Same as the above function.
rx - Rotational Velocity in the X axis.
ry - Rotational Velocity in the Y axis.
rz - Rotational Velocity in the Z axis.
```

#### Callbacks

```PAWN
OnObjectTransfer(playerid, objectid)

Gets called when a player passes an object.
```

```PAWN
OnWeaponTransfer(playerid, weaponid, ammo)

Gets called when a player passes an weapon.
```

```PAWN
OnPlayerCatchObject(playerid, objectid)

Gets called when a player catches an object.
```

```PAWN
OnPlayerCatchWeapon(playerid, weaponid, ammo)

Gets called when a player catches an weapon.
```

##### Use the Demo script to know more about the functioning

### Bugs/Glitches

If you get any create an issue in this repository.

### Development Log

`     • Created tfrmech.inc`
