#include <a_samp>
#include <zcmd>
#include <tfrmech>

main()
{
	print("\n----------------------------------");
	print("   Transfer Mechanics Demo Script   ");
	print("----------------------------------\n");
}


public OnGameModeInit()
{
	SetGameModeText("TFR Demo");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

new obj;
CMD:getweapon(playerid, params[])
{
	GivePlayerWeapon(playerid, 24, 100);
	return 1;
}

CMD:passobject(playerid, params[])
{
    ApplyAnimation(playerid, "KNIFE", "KNIFE_PART", 4.1, 0, 0, 0, 0, 500, 1);
	new Float:x, Float:y, Float:z, Float:angle;
	GetPlayerFacingAngle(playerid, angle);
	GetPlayerPos(playerid, x, y, z);
	obj = CreateObject(19352, x, y, z + 0.9, 0.0, 0.0, 0.0);
	TFR_ObjectInit(0, obj);
	TFR_SetRotVelocity(0, 0.0, 0.0, 100.0);
	TFR_PassObject(0, playerid, TFR_OPT_VEL*floatsin(-angle, degrees), TFR_OPT_VEL*floatcos(-angle, degrees));
	return 1;
}

CMD:passweapon(playerid, params[])
{
	if(GetPlayerWeapon(playerid) != 0)
	{
		ApplyAnimation(playerid, "KNIFE", "KNIFE_PART", 4.1, 0, 0, 0, 0, 500, 1);
		new Float:angle;
		GetPlayerFacingAngle(playerid, angle);
		TFR_SetRotVelocity(0, 0.0, 150.0, 0.0);
		TFR_PassWeapon(0, playerid, -1, "SERVER: You cannot tansfer/pass this weapon.", TFR_OPT_VEL*floatsin(-angle, degrees), TFR_OPT_VEL*floatcos(-angle, degrees), 0.0, 100.0);
	}
	return 1;
}
