/*

	* Include: tfrmech.inc

	* Created On: 3/13/2015

	* Development Log:
						- Created trfmech.inc (3/13/2015)

*/

/* macros */
#define TFR_MAX_CELL       			100
#define TFR_SPEED_MULT           	50.0
#define TFR_OPT_VEL                 55.0

#define TFR_COLT_45					346
#define TFR_SILENCED_PISTOL			347
#define TFR_DESERT_EAGLE			348
#define TFR_SHOTGUN     			349
#define TFR_SAWN_OFF_SHOTGUN    	350
#define TFR_COMBAT_SHOTGUN      	351
#define TFR_MICRO_UZI   			352
#define TFR_MP5     				353
#define TFR_AK47    				355
#define TFR_M4      				356
#define TFR_COUNTRY_RIFLE       	357
#define TFR_SNIPER              	358
#define TFR_TEC9                    372
/*      */

/* forward declarations */
#if defined OnObjectTransfer
forward OnObjectTransfer(playerid, objectid);
#endif

#if defined OnWeaponTransfer
forward OnWeaponTransfer(playerid, weaponid, ammo);
#endif

#if defined OnPlayerCatchObject
forward OnPlayerCatchObject(playerid, objectid);
#endif

#if defined OnPlayerCatchWeapon
forward OnPlayerCatchWeapon(playerid, weaponid, ammo);
#endif
/*      */

/* enumerator */
enum TFR_DATA
{
	TFR_objectid,
	TFR_weaponid,
	TFR_playerid,
	TFR_ammo,
	TFR_modelid,
	Float:TFR_px,
	Float:TFR_py,
	Float:TFR_pz,
	Float:TFR_vx,
	Float:TFR_vy,
	Float:TFR_vz,
	Float:TFR_rvx,
	Float:TFR_rvy,
	Float:TFR_rvz,
	Float:TFR_limit
}
/*      */

/* globalized 2D array */
new TFR_Objects[TFR_MAX_CELL][TFR_DATA];
/*      */

/* APIs */
stock TFR_ObjectInit(cell, objectid)
{
	if(IsValidObject(objectid))
	{
		TFR_Objects[cell][TFR_objectid] = objectid;
		TFR_Objects[cell][TFR_modelid] = GetObjectModel(objectid);
		TFR_Objects[cell][TFR_weaponid] = 0;
	}
	return 0;
}

stock TFR_PassObject(cell, playerid, Float:velx, Float:vely, Float:velz = 0.0, Float:limit = 5.0)
{
	if(IsValidObject(TFR_Objects[cell][TFR_objectid]) && playerid != INVALID_PLAYER_ID)
	{
	    new Float:x, Float:y, Float:z;
	    TFR_Objects[cell][TFR_playerid] = playerid;
		TFR_Objects[cell][TFR_vx] = velx;
		TFR_Objects[cell][TFR_vy] = vely;
		TFR_Objects[cell][TFR_vz] = velz;
		TFR_Objects[cell][TFR_limit] = limit;
		GetPlayerPos(playerid, x, y, z);
		TFR_Objects[cell][TFR_px] = x;
		TFR_Objects[cell][TFR_py] = y;
		TFR_Objects[cell][TFR_pz] = z;
		#if defined OnObjectTransfer
		OnObjectTransfer(playerid, TFR_Objects[cell][TFR_objectid]);
		#endif
		return 1;
	}
	return 0;
}

stock TFR_PassWeapon(cell, playerid, color, error[], Float:velx, Float:vely, Float:velz = 0.0, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, Float:limit = 5.0)
{
    new weaponid = GetPlayerWeapon(playerid);
	if(!IsValidObject(TFR_Objects[cell][TFR_objectid]) && playerid != INVALID_PLAYER_ID && weaponid != 0)
	{
	    if(CheckWeapon(weaponid))
	    {
	    	new Float:x, Float:y, Float:z;
	    	StoreWeaponModel(cell, weaponid);
    		TFR_Objects[cell][TFR_weaponid] = weaponid;
    		TFR_Objects[cell][TFR_ammo] = GetPlayerAmmo(playerid);
    		TFR_Objects[cell][TFR_playerid] = playerid;
			TFR_Objects[cell][TFR_vx] = velx;
			TFR_Objects[cell][TFR_vy] = vely;
			TFR_Objects[cell][TFR_vz] = velz;
			TFR_Objects[cell][TFR_limit] = limit;
			GetPlayerPos(playerid, x, y, z);
			TFR_Objects[cell][TFR_px] = x;
			TFR_Objects[cell][TFR_py] = y;
			TFR_Objects[cell][TFR_pz] = z;
			TFR_Objects[cell][TFR_objectid] = CreateObject(TFR_Objects[cell][TFR_modelid], x, y, z + 0.4, rx, ry, rz);
			SetPlayerAmmo(playerid, weaponid, 0);
			#if defined OnWeaponTransfer
			OnWeaponTransfer(playerid, TFR_Objects[cell][TFR_weaponid], TFR_Objects[cell][TFR_ammo]);
			#endif
		}
		else
		{
		    SendClientMessage(playerid, color, error);
		}
		return 1;
	}
	return 0;
}

stock TFR_SetRotVelocity(cell, Float:rx, Float:ry, Float:rz)
{
    if(IsValidObject(TFR_Objects[cell][TFR_objectid]))
	{
		TFR_Objects[cell][TFR_rvx] = rx;
		TFR_Objects[cell][TFR_rvy] = ry;
		TFR_Objects[cell][TFR_rvz] = rz;
		return 1;
	}
	return 0;
}
/*      */

/* core */

stock IsObjectWithinLimit(cell, Float:x, Float:y, Float:z)
{
	new Float:delx = TFR_Objects[cell][TFR_px] - x;
	new Float:dely = TFR_Objects[cell][TFR_py] - y;
	new Float:delz = TFR_Objects[cell][TFR_pz] - z;
	new Float:dist = ((delx * delx) +(dely * dely) + (delz * delz));
	if(dist <= (TFR_Objects[cell][TFR_limit] * TFR_Objects[cell][TFR_limit])) return true;
	return false;
}

stock StoreWeaponModel(cell, weaponid)
{
	if(weaponid == 22) TFR_Objects[cell][TFR_modelid] = TFR_COLT_45;
	else if (weaponid == 23) TFR_Objects[cell][TFR_modelid] = TFR_SILENCED_PISTOL;
	else if (weaponid == 24) TFR_Objects[cell][TFR_modelid] = TFR_DESERT_EAGLE;
	else if (weaponid == 25) TFR_Objects[cell][TFR_modelid] = TFR_SHOTGUN;
	else if (weaponid == 26) TFR_Objects[cell][TFR_modelid] = TFR_SAWN_OFF_SHOTGUN;
	else if (weaponid == 27) TFR_Objects[cell][TFR_modelid] = TFR_COMBAT_SHOTGUN;
	else if (weaponid == 28) TFR_Objects[cell][TFR_modelid] = TFR_MICRO_UZI;
	else if (weaponid == 29) TFR_Objects[cell][TFR_modelid] = TFR_MP5;
	else if (weaponid == 30) TFR_Objects[cell][TFR_modelid] = TFR_AK47;
	else if (weaponid == 31) TFR_Objects[cell][TFR_modelid] = TFR_M4;
	else if (weaponid == 32) TFR_Objects[cell][TFR_modelid] = TFR_TEC9;
	else if (weaponid == 33) TFR_Objects[cell][TFR_modelid] = TFR_COUNTRY_RIFLE;
	else if (weaponid == 34) TFR_Objects[cell][TFR_modelid] = TFR_SNIPER;
	else return 0;
	return 1;
}

stock CheckWeapon(weaponid)
{
	for(new i = 22; i < 35; i++)
	{
	    if(weaponid == i) return 1;
	}
	return 0;
}
/*      */

/* mechanism for tranferring */
forward TFR_Mechanism();
public TFR_Mechanism()
{
	new Float:ox,
	Float:oy,
	Float:oz,
	Float:rx,
	Float:ry,
	Float:rz;
	
	for(new i = 0; i < TFR_MAX_CELL; i++)
	{
     	if(IsValidObject(TFR_Objects[i][TFR_objectid]))
  		{
   			GetObjectPos(TFR_Objects[i][TFR_objectid], ox, oy, oz);
			GetObjectRot(TFR_Objects[i][TFR_objectid], rx, ry, rz);

			if(IsObjectWithinLimit(i, ox, oy, oz))
			{
				for(new j = 0; j < MAX_PLAYERS; j++)
				{
				    if(j != TFR_Objects[i][TFR_playerid] && j != INVALID_PLAYER_ID && IsValidObject(TFR_Objects[i][TFR_objectid]))
	    			{
						if(IsPlayerInRangeOfPoint(j, 1.7, ox, oy, oz))
						{
						    if(TFR_Objects[i][TFR_weaponid] == 0)
						    {
					    		#if defined OnPlayerCatchObject
					    		OnPlayerCatchObject(j, TFR_Objects[i][TFR_objectid]);
					   			#endif
					    		DestroyObject(TFR_Objects[i][TFR_objectid]);
							}
							else
							{
							    GivePlayerWeapon(j, TFR_Objects[i][TFR_weaponid], TFR_Objects[i][TFR_ammo]);
							    #if defined OnPlayerCatchWeapon
					    		OnPlayerCatchWeapon(j, TFR_Objects[i][TFR_weaponid], TFR_Objects[i][TFR_ammo]);
					   			#endif
					    		DestroyObject(TFR_Objects[i][TFR_objectid]);
					    		TFR_Objects[i][TFR_objectid] = -1;
					    		TFR_Objects[i][TFR_ammo] = -1;
							}
						}
					}
				}
				ox = ox + TFR_Objects[i][TFR_vx]/1000;
				oy = oy + TFR_Objects[i][TFR_vy]/1000;
				oz = oz + TFR_Objects[i][TFR_vz]/1000;
				SetObjectRot(TFR_Objects[i][TFR_objectid], rx + (TFR_Objects[i][TFR_rvx]/10.0), ry + (TFR_Objects[i][TFR_rvy]/10.0), rz + (TFR_Objects[i][TFR_rvz]/10.0));
				SetObjectPos(TFR_Objects[i][TFR_objectid], ox, oy, oz);
			}
   			else
			{
			    DestroyObject(TFR_Objects[i][TFR_objectid]);
			}
		}
	}
	return 1;
}
/*      */

/* hooked callback */
public OnGameModeInit()
{
	print(" ***************************** ");
	print(" *   Transfer    Mechanics   * ");
	print(" *                           * ");
	print(" *    successfully loaded    * ");
	print(" *                           * ");
	print(" *       <c>vermaritt        * ");
	print(" ***************************** ");
	SetTimer("TFR_Mechanism", 10, true);

	#if defined TFR_OnGameModeInit
        TFR_OnGameModeInit();
    #endif
	return 1;
}

/* hook */
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit TFR_OnGameModeInit
#if defined TFR_OnGameModeInit
    forward TFR_OnGameModeInit();
#endif

/*      */
