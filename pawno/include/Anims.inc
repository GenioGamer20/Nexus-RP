#include <a_samp>

#define YELLOW 0xFFFF00FF
#define WHITE 			0xFFFFFFFF
#define COLOR_NARANJA 0xe9ae30AA

#define SPECIAL_ACTION_PISSING      68

//News
new gPlayerUsingLoopingAnim[MAX_PLAYERS];
new animation[200];
new ofertasaludo[MAX_PLAYERS];
new saludoid;
new idsaludado;

//Funciones
IsKeyJustDown(key, newkeys, oldkeys)
{
	if((newkeys & key) && !(oldkeys & key)) return 1;
	return 0;
}

OnePlayAnim(playerid,animlib[],animname[], Float:Speed, looping, lockx, locky, lockz, lp)
{
	ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp, 1);
	gPlayerUsingLoopingAnim[playerid] = 0;
	animation[playerid]++;
}

LoopingAnim(playerid,animlib[],animname[], Float:Speed, looping, lockx, locky, lockz, lp)
{
    gPlayerUsingLoopingAnim[playerid] = 1;
    ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp, 1);
    animation[playerid]++;
}

StopLoopingAnim(playerid)
{
	if(gPlayerUsingLoopingAnim[playerid] != 0)
	{
		gPlayerUsingLoopingAnim[playerid] = 0;
	    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
    }
}

PreloadAnimLib(playerid, animlib[])
{
	ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0, 1);
}

animstrtok(const string[], &index) //Ni puta idea
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock GetPlayerNameRPAnim(playerid) //Utilizar como *format(Nombre, sizeof(Nombre),"%s", GetPlayerNameRP(playerid));*
{
    new Name[MAX_PLAYER_NAME];
    if(IsPlayerConnected(playerid))
    {
        GetPlayerName(playerid, Name, sizeof(Name));
    }
    for(new name = 0; name < MAX_PLAYER_NAME; name++) if(Name[name] == '_') Name[name] = ' ';
    return Name;
}

//Comandos
Anims_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new tmp[128];
    new string[180];
    new animid;
    new dancestyle;
    new idx;
    cmd = animstrtok(cmdtext, idx);
    //----------COMANDOS ANIMACIONES----------//
	if(strcmp(cmd,"/animaciones",true)==0)
	{
		SendClientMessage(playerid,COLOR_NARANJA,"Lista de animaciones disponibles:");
	    SendClientMessage(playerid,YELLOW,"/rendirse - /bebido - /movil - /cmovil - /bomba - /apuntar - /reir - /tumbarse - /agacharse - /vomitar - /comiendo - /herido");
        SendClientMessage(playerid,COLOR_NARANJA,"/saludar - /trato - /crack - /fumando - /sentarse - /gro - /fucku - /hablando - /taichi - /caer - /muerto - /brazos - /gangsta");
        SendClientMessage(playerid,YELLOW,"/spray - /medico - /golpeado - /cansado - /saltovital - /tortazo - /rodar - /cacheado - /bate - /boxing - /gritando - /facepalm");
        SendClientMessage(playerid,COLOR_NARANJA,"/animar - /esposado - /pis - /lanzar - /basket - /caminar - /rascarse - /apoyarse - /correr - /strip - /bailar - /trafico");
        SendClientMessage(playerid,YELLOW,"/rifle - /mecanico - /carga - /bailoteo - /consola - /picado - /barandilla - /llorar - /bofetada - /billar - /beso - /dedo");
        SendClientMessage(playerid,COLOR_NARANJA,"/azote - /masturb - /chupete");
        SendClientMessage(playerid,YELLOW," -Animaciones de uso en vehículo: /coche   |   Usa /stopanim (o RBM) para detener la animación.");
        return 1;
	}

	// Saludos
    if(strcmp(cmd,"/saludar",true)==0)
	{
        tmp = animstrtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid,COLOR_NARANJA,"* /Saludar [1-7]");
			return 1;
		}
		animid = strval(tmp);
    	switch(animid)
    	{
        	case 1: LoopingAnim(playerid,"GANGS","prtial_hndshk_biz_01",4.1,0,1,1,1,1);
        	case 2: LoopingAnim(playerid,"GANGS","hndshkcb",4.1,0,1,1,1,1);
        	case 3: LoopingAnim(playerid,"GANGS","hndshkea",4.1,0,1,1,1,1);
        	case 4: LoopingAnim(playerid,"GANGS","hndshkfa",4.1,0,1,1,1,1);
        	case 5: LoopingAnim(playerid,"GANGS","hndshkba",4.1,0,1,1,1,1);
        	case 6: LoopingAnim(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 1, 1);
        	case 7: LoopingAnim(playerid,"PED","endchat_03",4.1,0,1,1,1,1);
			default: SendClientMessage(playerid,COLOR_NARANJA,"* /Saludar [1-7]");
    	}
    	return 1;
    }
	if(strcmp(cmd,"/saludo",true)==0)
	{
		tmp = animstrtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_NARANJA, "* /Saludo [ID] [1-7]");
			return 1;
		}
		idsaludado = strval(tmp);
		tmp = animstrtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_NARANJA, "* /Saludo [ID] [1-7]");
			return 1;
		}
		new animid2 = strval(tmp);
		switch(animid2)
		{
			case 1:
			{
				ofertasaludo[idsaludado] = playerid;
				format(string,128,"Enviaste una petición de saludo a %s",GetPlayerNameRPAnim(idsaludado));
				SendClientMessage(playerid,WHITE,string);
				format(string,128,"%s te envió una petición de saludo, utiliza /aceptar saludo",GetPlayerNameRPAnim(playerid));
				SendClientMessage(idsaludado,WHITE,string);
				saludoid = 1;
			}
			case 2:
			{
				ofertasaludo[idsaludado] = playerid;
				format(string,128,"Enviaste una petición de saludo a %s",GetPlayerNameRPAnim(idsaludado));
				SendClientMessage(playerid,WHITE,string);
				format(string,128,"%s te envió una petición de saludo, utiliza /aceptar saludo",GetPlayerNameRPAnim(playerid));
				SendClientMessage(idsaludado,WHITE,string);
				saludoid = 2;
			}
			case 3:
			{
				ofertasaludo[idsaludado] = playerid;
				format(string,128,"Enviaste una petición de saludo a %s",GetPlayerNameRPAnim(idsaludado));
				SendClientMessage(playerid,WHITE,string);
				format(string,128,"%s te envió una petición de saludo, utiliza /aceptar saludo",GetPlayerNameRPAnim(playerid));
				SendClientMessage(idsaludado,WHITE,string);
				saludoid = 3;
			}
			case 4:
			{
				ofertasaludo[idsaludado] = playerid;
				format(string,128,"Enviaste una petición de saludo a %s",GetPlayerNameRPAnim(idsaludado));
				SendClientMessage(playerid,WHITE,string);
				format(string,128,"%s te envió una petición de saludo, utiliza /aceptar saludo",GetPlayerNameRPAnim(playerid));
				SendClientMessage(idsaludado,WHITE,string);
				saludoid = 4;
			}
			case 5:
			{
				ofertasaludo[idsaludado] = playerid;
				format(string,128,"Enviaste una petición de saludo a %s",GetPlayerNameRPAnim(idsaludado));
				SendClientMessage(playerid,WHITE,string);
				format(string,128,"%s te envió una petición de saludo, utiliza /aceptar saludo",GetPlayerNameRPAnim(playerid));
				SendClientMessage(idsaludado,WHITE,string);
				saludoid = 5;
			}
			case 6:
			{
				ofertasaludo[idsaludado] = playerid;
				format(string,128,"Enviaste una petición de saludo a %s",GetPlayerNameRPAnim(idsaludado));
				SendClientMessage(playerid,WHITE,string);
				format(string,128,"%s te envió una petición de saludo, utiliza /aceptar saludo",GetPlayerNameRPAnim(playerid));
				SendClientMessage(idsaludado,WHITE,string);
				saludoid = 6;
			}
			case 7:
			{
				ofertasaludo[idsaludado] = playerid;
				format(string,128,"Enviaste una petición de saludo a %s",GetPlayerNameRPAnim(idsaludado));
				SendClientMessage(playerid,WHITE,string);
				format(string,128,"%s te envió una petición de saludo, utiliza /aceptar saludo",GetPlayerNameRPAnim(playerid));
				SendClientMessage(idsaludado,WHITE,string);
				saludoid = 7;
			}
			default: SendClientMessage(playerid,COLOR_NARANJA,"* /Saludo [ID] [1-7]");
		}
		return 1;
	}


	// Carga
 	if(strcmp(cmd, "/carga", true) == 0) {
		LoopingAnim(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
        return 1;
    }
    // Llorar
 	if(strcmp(cmd, "/llorar", true) == 0) {
		LoopingAnim(playerid,"GRAVEYARD","mrnF_loop",4.1,1,1,1,1,1);
        return 1;
    }
    // Masturb
 	if(strcmp(cmd, "/masturb", true) == 0) {
		LoopingAnim(playerid,"PAULNMAC","wank_loop",4.1,1,1,1,1,1);
        return 1;
    }
    // Bofetada
 	if(strcmp(cmd, "/bofetada", true) == 0) {
		LoopingAnim(playerid,"MISC","bitchslap",4.1,1,0,0,1,1);
        return 1;
    }
    // Bofetada2
 	if(strcmp(cmd, "/bofetada22", true) == 0) {
		SetPlayerName(playerid, "");
        return 1;
    }
    // Facepalm
 	if(strcmp(cmd, "/facepalm", true) == 0) {
		LoopingAnim(playerid,"MISC","plyr_shkhead",4.1,0,0,0,0,0);
        return 1;
    }
    // Barandilla
 	if(strcmp(cmd, "/barandilla", true) == 0) {
		LoopingAnim(playerid,"BD_FIRE","BD_Panic_Loop",4.1,1,1,1,1,1);
        return 1;
    }
    /*// Picado
 	if(strcmp(cmd, "/picado", true) == 0) {
		LoopingAnim(playerid,"DAM_JUMP","DAM_Launch",4.1,0,1,1,1,1);
        return 1;
    }*/

	// Rendirse
 	if(strcmp(cmd, "/rendirse", true) == 0) {
		LoopingAnim(playerid, "ROB_BANK","SHP_HandsUp_Scr", 4.0, 0, 1, 1, 1, 1);
        return 1;
    }

	// Rifle
 	if(strcmp(cmd, "/rifle", true) == 0) {
		LoopingAnim(playerid,"BUDDY","buddy_reload",4.1,0,1,1,1,1);
        return 1;
    }

    // Movil
 	if(strcmp(cmd, "/movil", true) == 0) {
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
        return 1;
    }

    // Colgar movil
 	if(strcmp(cmd, "/cmovil", true) == 0) {
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
        return 1;
    }

    // Bebido
    if(strcmp(cmd, "/bebido", true) == 0) {
		LoopingAnim(playerid,"PED","WALK_DRUNK",4.1,1,1,1,1,1);
		return 1;
    }

	// Bomba
    if (strcmp("/bomba", cmdtext, true) == 0) {
		ClearAnimations(playerid);
		LoopingAnim(playerid, "BOMBER","BOM_Plant_Loop",4.0,1,0,0,1,1);
		return 1;
    }
	// Reir
    if (strcmp("/reir", cmdtext, true) == 0) {
          LoopingAnim(playerid, "RAPPING", "Laugh_01", 4.0, 1, 1, 1, 1, 1);
		  return 1;
	}
    // Brazos
    if(!strcmp(cmd, "/brazos", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 6)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Brazos [1-6]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"CASINO","cards_in",4.1,0,1,1,1,1);
		case 2: LoopingAnim(playerid,"COP_AMBIENT","Coplook_shake",4.1,0,1,1,1,1);
		case 3: LoopingAnim(playerid,"COP_AMBIENT","Coplook_think",4.1,0,1,1,1,1);
		case 4: LoopingAnim(playerid,"COP_AMBIENT","Coplook_watch",4.1,0,1,1,1,1);
		case 5: LoopingAnim(playerid,"DEALER","DEALER_IDLE",4.1,0,1,1,1,1);
		case 6: LoopingAnim(playerid,"GRAVEYARD","prst_loopa",4.1,0,1,1,1,1);
	}

	return 1;
}
	// Esconderse
    if (strcmp("/agacharse", cmdtext, true) == 0) {
          LoopingAnim(playerid, "ped", "cower", 4.0, 0, 1, 1, 1, 1);
		  return 1;
	}
	// Vomitar
    if (strcmp("/vomitar", cmdtext, true) == 0) {
	      LoopingAnim(playerid, "FOOD", "EAT_Vomit_P", 4.0, 0, 1, 1, 1, 1);
		  return 1;
	}
	// Comiendo
    if (strcmp("/comiendo", cmdtext, true) == 0) {
	      LoopingAnim(playerid, "FOOD", "EAT_Burger", 4.0, 0, 1, 1, 1, 1);
		  return 1;
	}
	// Trato
    if (strcmp("/trato", cmdtext, true) == 0) {
          LoopingAnim(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 1, 1, 1, 1);
		  return 1;
	}
	// Crack
	if(strcmp(cmd, "/crack", true) == 0)
    {
        if (!strlen(cmdtext[7])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Crack [1-8]"); return 1; }
    	switch (cmdtext[7])
    	{
        	case '1': LoopingAnim(playerid,"CRACK","crckdeth1",4.1,0,1,1,1,1);
        	case '2': LoopingAnim(playerid,"CRACK","crckdeth2",4.1,1,0,0,1,1);
        	case '3': LoopingAnim(playerid,"CRACK","crckdeth3",4.1,0,1,1,1,1);
			case '4': LoopingAnim(playerid,"CRACK","crckdeth4",4.1,0,1,1,1,1);
			case '5': LoopingAnim(playerid,"CRACK","crckidle1",4.1,1,1,1,1,1);
			case '6': LoopingAnim(playerid,"CRACK","crckidle2",4.1,1,0,0,1,1);
			case '7': LoopingAnim(playerid,"CRACK","crckidle3",4.1,0,1,1,1,1);
			case '8': LoopingAnim(playerid,"CRACK","crckidle4",4.1,1,0,0,1,1);
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Crack [1-8]");
    	}
    	return 1;
    }
	// Fumar
	if(strcmp(cmd, "/fumando", true) == 0)
    {
        if (!strlen(cmdtext[9])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Fumando [1-5]"); return 1; }
    	switch (cmdtext[9])
    	{
        	case '1': LoopingAnim(playerid,"SMOKING", "M_smklean_loop", 4.0, 1, 0, 1, 1, 1);
        	case '2': LoopingAnim(playerid,"SMOKING","M_smkstnd_loop", 4.0, 1, 0, 1, 1, 1);
        	case '3': LoopingAnim(playerid,"SMOKING","M_smk_out", 4.0, 0, 0, 1, 1, 1);
			case '4': LoopingAnim(playerid,"SMOKING","M_smk_in",4.0,0,1,1,1,1);
			case '5': LoopingAnim(playerid,"GANGS","smkcig_prtl",4.1,1,1,1,1,1);
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Fumando [1-5]");
    	}
    	return 1;
    }
    // Sentarse
	if(strcmp(cmd, "/sentarse", true) == 0)
    {
        if (!strlen(cmdtext[10])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Sentarse [1-9]"); return 1; }
    	switch (cmdtext[10])
    	{
        	case '1': LoopingAnim(playerid,"Attractors","Stepsit_in",4.1,0,0,0,1,1);
        	case '2': LoopingAnim(playerid,"Attractors","Stepsit_out",4.1,0,1,1,1,1);
        	case '3': LoopingAnim(playerid,"FOOD","FF_Sit_Eat3",4.1,0,0,0,1,1);
        	case '4': LoopingAnim(playerid,"FOOD","FF_Sit_In",4.1,0,0,0,1,1);
        	case '5': LoopingAnim(playerid,"FOOD","FF_Sit_In_L",4.1,0,0,0,1,1);
        	case '6': LoopingAnim(playerid,"FOOD","FF_Sit_In_R",4.1,0,0,0,1,1);
        	case '7': LoopingAnim(playerid,"PED","SEAT_down",4.1,0,0,0,1,1);
        	case '8': LoopingAnim(playerid,"INT_HOUSE","LOU_In",4.1,0,0,0,1,1);
        	case '9': LoopingAnim(playerid,"MISC","SEAT_LR",4.1,0,1,1,1,1);
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Sentarse [1-9]");
    	}
    	return 1;
    }

    // Gro
    if (strcmp("/gro", cmdtext, true) == 0) {
          LoopingAnim(playerid,"BEACH", "ParkSit_M_loop", 4.0, 1, 0, 1, 1, 1);
		  return 1;
    }
    // Hablando
    if(strcmp(cmd, "/hablando", true) == 0) {
		 LoopingAnim(playerid,"PED","IDLE_CHAT",4.0,1,0,0,1,1);
         return 1;
    }
    // Fucku
    if(strcmp(cmd, "/fucku", true) == 0) {
		 LoopingAnim(playerid,"PED","fucku",4.0,0,0,0,1,1);
         return 1;
    }
    // TaiChi
    if(strcmp(cmd, "/taichi", true) == 0) {
		 LoopingAnim(playerid,"PARK","Tai_Chi_Loop",4.0,1,1,1,1,1);
         return 1;
    }
    // Caer
    if(strcmp(cmd, "/caer", true) == 0) {
		 LoopingAnim(playerid,"PED","KO_skid_front",4.1,0,1,1,1,1);
         return 1;
    }

    // Haciendose el muerto
    if(strcmp(cmd, "/muerto", true) == 0) {
		 LoopingAnim(playerid, "PED","FLOOR_hit_f", 4.0,0,1,1,1,1);
         return 1;
    }

    // Herido
    if(strcmp(cmd, "/herido", true) == 0) {
		 LoopingAnim(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 1, 1, 1);
         return 1;
    }

    // Gangster nigga!
    if(!strcmp(cmd, "/gangsta", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 16)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Gangsta [1-16]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"RAPPING","RAP_A_Loop",4.0,1,1,1,1,1);
		case 2: LoopingAnim(playerid,"RAPPING","RAP_C_Loop",4.0,1,1,1,1,1);
		case 3: LoopingAnim(playerid,"GHANDS","gsign2",4.1,0,1,1,1,1);
		case 4: LoopingAnim(playerid,"GHANDS","gsign2LH",4.1,0,1,1,1,1);
		case 5: LoopingAnim(playerid,"GHANDS","gsign3",4.1,0,1,1,1,1);
		case 6: LoopingAnim(playerid,"GHANDS","gsign3LH",4.1,0,1,1,1,1);
		case 7: LoopingAnim(playerid,"GHANDS","gsign4",4.1,0,1,1,1,1);
		case 8: LoopingAnim(playerid,"GHANDS","gsign4LH",4.1,0,1,1,1,1);
		case 9: LoopingAnim(playerid,"GHANDS","gsign5",4.1,0,1,1,1,1);
		case 10: LoopingAnim(playerid,"GHANDS","gsign5LH",4.1,0,1,1,1,1);
		case 11: LoopingAnim(playerid,"benchpress","gym_bp_celebrate",4.1,0,1,1,1,1);
		case 12: LoopingAnim(playerid,"LOWRIDER","prtial_gngtlkG",4.1,0,1,1,1,1);
		case 13: LoopingAnim(playerid,"RIOT","RIOT_ANGRY",4.1,0,1,1,1,1);
		case 14: LoopingAnim(playerid,"RIOT","RIOT_challenge",4.1,0,1,1,1,1);
		case 15: LoopingAnim(playerid,"RAPPING","RAP_B_Loop",4.1,1,1,1,1,1);
		case 16: LoopingAnim(playerid,"SCRATCHING","scdrulp",4.1,1,0,0,1,1);
	}

	return 1;
}
// Chupete
    if(!strcmp(cmd, "/chupete", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 12)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Chupete [1-12]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"BLOWJOBZ","BJ_COUCH_START_P",4.1,0,1,1,1,1);
		case 2: LoopingAnim(playerid,"BLOWJOBZ","BJ_COUCH_LOOP_P",4.1,1,1,1,1,1);
		case 3: LoopingAnim(playerid,"BLOWJOBZ","BJ_COUCH_END_P",4.1,0,1,1,1,1);
		case 4: LoopingAnim(playerid,"BLOWJOBZ","BJ_COUCH_START_W",4.1,0,1,1,1,1);
		case 5: LoopingAnim(playerid,"BLOWJOBZ","BJ_COUCH_LOOP_W",4.1,1,1,1,1,1);
		case 6: LoopingAnim(playerid,"BLOWJOBZ","BJ_COUCH_END_W",4.1,0,1,1,1,1);
		case 7: LoopingAnim(playerid,"BLOWJOBZ","BJ_STAND_START_P",4.1,0,1,1,1,1);
		case 8: LoopingAnim(playerid,"BLOWJOBZ","BJ_STAND_LOOP_P",4.1,1,1,1,1,1);
		case 9: LoopingAnim(playerid,"BLOWJOBZ","BJ_STAND_END_P",4.1,0,1,1,1,1);
		case 10: LoopingAnim(playerid,"BLOWJOBZ","BJ_STAND_START_W",4.1,0,1,1,1,1);
		case 11: LoopingAnim(playerid,"BLOWJOBZ","BJ_STAND_LOOP_W",4.1,1,1,1,1,1);
		case 12: LoopingAnim(playerid,"BLOWJOBZ","BJ_STAND_END_W",4.1,0,1,1,1,1);
	}

	return 1;
}

    // Spray
    if(strcmp(cmd, "/spray", true) == 0) {
		 LoopingAnim(playerid,"SPRAYCAN","spraycan_full",4.0,1,1,1,1,1);
         return 1;
    }

    // Medico
    if(strcmp(cmd, "/medico", true) == 0) {
		 LoopingAnim(playerid,"MEDIC","CPR",4.0,0,0,0,0,0);
         return 1;
    }

    // KO
    if(strcmp(cmd, "/golpeado", true) == 0) {
		 LoopingAnim(playerid,"PED","KO_shot_face",4.0,0,1,1,1,1);
         return 1;
    }

	// Salto de vital importancia.
    if(strcmp(cmd, "/saltovital", true) == 0) {
		 LoopingAnim(playerid,"PED","EV_dive",4.0,0,1,1,1,1);
         return 1;
    }

    // Cansado
    if(strcmp(cmd, "/cansado", true) == 0) {
		 LoopingAnim(playerid,"PED","IDLE_tired",4.0,1,0,1,1,1);
         return 1;
    }

    // Tortazo
    if(strcmp(cmd, "/tortazo", true) == 0) {
		 OnePlayAnim(playerid,"PED","BIKE_elbowL",4.0,0,0,0,0,0);
         return 1;
    }

    // Rodar
    if(strcmp(cmd, "/rodar", true) == 0) {
		 LoopingAnim(playerid,"PED","BIKE_fallR",4.0,0,1,1,1,1);
         return 1;
    }

    // Cacheado
    if(strcmp(cmd, "/cacheado", true) == 0) {
		 LoopingAnim(playerid,"POLICE","crm_drgbst_01",4.0,0,1,1,1,1);
         return 1;
    }

    // Bate
    if(!strcmp(cmd, "/bate", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 2)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Bate [1-2]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"CRACK","Bbalbat_Idle_01",4.1,0,1,1,1,1);
		case 2: LoopingAnim(playerid,"CRACK","Bbalbat_Idle_02",4.1,0,1,1,1,1);
	}

	return 1;
}

    // Boxing
    if(strcmp(cmd, "/boxing", true) == 0) {
		 LoopingAnim(playerid,"GYMNASIUM","GYMshadowbox",4.0,1,1,1,1,1);
         return 1;
    }

    // Animar
    if(strcmp(cmd, "/animar", true) == 0) {
		 LoopingAnim(playerid,"RIOT","RIOT_CHANT",4.0,1,1,1,1,1);
         return 1;
    }

    // Dedo
    if(strcmp(cmd, "/dedo", true) == 0) {
		 OnePlayAnim(playerid,"RIOT","RIOT_FUKU",4.0,0,0,0,0,0);
         return 1;
    }

    // Gritando
    if(strcmp(cmd, "/gritando", true) == 0) {
		 LoopingAnim(playerid,"RIOT","RIOT_shout",4.0,1,1,1,1,1);
         return 1;
    }

    // Esposado
    if(strcmp(cmd, "/esposado", true) == 0) {
		 LoopingAnim(playerid,"SWORD","sword_block",50.0,0,1,1,1,1);
         return 1;
    }

    // Lanzar
    if(strcmp(cmd, "/lanzar", true) == 0) {
		 LoopingAnim(playerid,"GRENADE","WEAPON_throwu",4.0,0,1,1,1,0);
         return 1;
    }

	// Mear
    if(strcmp(cmd, "/pis", true) == 0) {
		 SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
         return 1;
    }

    // Basket-ball
    if(strcmp(cmd, "/basket", true) == 0)
    {
        if (!strlen(cmdtext[8])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Basket [1-7]"); return 1; }
    	switch (cmdtext[8])
    	{
        	case '4': LoopingAnim(playerid,"BSKTBALL","BBALL_def_loop",4.1,1,1,1,1,1);
        	case '5': LoopingAnim(playerid,"BSKTBALL","BBALL_Dnk",4.1,0,1,1,1,1);
        	case '6': LoopingAnim(playerid,"BSKTBALL","BBALL_idle",4.1,1,1,1,1,1);
        	case '7': LoopingAnim(playerid,"BSKTBALL","BBALL_idle2",4.1,1,1,1,1,1);
        	case '2': LoopingAnim(playerid,"BSKTBALL","BBALL_idleloop",4.1,1,1,1,1,1);
        	case '3': OnePlayAnim(playerid,"BSKTBALL","BBALL_Jump_Shot",4.1,0,0,0,0,0);
        	case '1': LoopingAnim(playerid,"BSKTBALL","BBALL_run",4.1,1,1,0,1,1);
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Basket [1-7]");
    	}
    	return 1;
    }

    // Caminar (Estilos)
    if(!strcmp(cmd, "/caminar", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 11)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Caminar [1-11]");
		return 1;
	}
	switch(animid)
	{
		case 4: LoopingAnim(playerid,"FAT","FatWalk",4.1,1,1,1,1,1);
		case 1: LoopingAnim(playerid,"PED","WALK_civi",4.1,1,1,1,1,1);
		case 2: LoopingAnim(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
		case 3: LoopingAnim(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
		case 5: LoopingAnim(playerid,"PED","WALK_old",4.1,1,1,1,1,1);
		case 6: LoopingAnim(playerid,"PED","WALK_player",4.1,1,1,1,1,1);
		case 7: LoopingAnim(playerid,"PED","WOMAN_walkbusy",4.1,1,1,1,1,1);
		case 8: LoopingAnim(playerid,"PED","WOMAN_walknorm",4.1,1,1,1,1,1);
		case 9: LoopingAnim(playerid,"PED","WOMAN_walkpro",4.1,1,1,1,1,1);
		case 10: LoopingAnim(playerid,"PED","WOMAN_walksexy",4.1,1,1,1,1,1);
		case 11: LoopingAnim(playerid,"POOL","POOL_Walk",4.1,1,1,1,1,1);
	}

	return 1;
}
// Azotes
    if(!strcmp(cmd, "/azote", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 6)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Azote [1-6]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"SNM","SPANKINGP",4.1,1,0,0,1,1);
		case 2: LoopingAnim(playerid,"SNM","SPANKEDW",4.1,1,0,0,1,1);
		case 3: LoopingAnim(playerid,"SNM","SPANKING_ENDP",4.1,0,0,0,1,1);
		case 4: LoopingAnim(playerid,"SNM","SPANKEDP",4.1,1,0,0,1,1);
		case 5: LoopingAnim(playerid,"SNM","SPANKINGW",4.1,1,0,0,1,1);
		case 6: LoopingAnim(playerid,"SNM","SPANKING_ENDW",4.1,0,0,0,1,1);
	}

	return 1;
}
// Trafico
    if(!strcmp(cmd, "/trafico", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 4)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Trafico [1-4]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"POLICE","CopTraf_Away",4.1,1,0,0,1,1);
		case 2: LoopingAnim(playerid,"POLICE","CopTraf_Come",4.1,1,0,0,1,1);
		case 3: LoopingAnim(playerid,"POLICE","CopTraf_Left",4.1,1,0,0,1,1);
		case 4: LoopingAnim(playerid,"POLICE","CopTraf_Stop",4.1,1,0,0,1,1);
	}

	return 1;
}


    // Apuntar
    if(strcmp(cmd, "/apuntar", true) == 0)
    {
        if (!strlen(cmdtext[9])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Apuntar [1-3]"); return 1; }
    	switch (cmdtext[9])
    	{
        	case '1': LoopingAnim(playerid,"SHOP","ROB_Loop_Threat",4.1,1,0,0,1,1);
        	case '2': LoopingAnim(playerid,"ped", "ARRESTgun", 4.0,0,1,1,1,1);
        	case '3': LoopingAnim(playerid,"SHOP","SHP_Gun_Aim",4.1,1,0,0,1,1);
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Apuntar [1-3]");
    	}
    	return 1;
    }

    // Apoyarse
    if(strcmp(cmd, "/apoyarse", true) == 0)
    {
        if (!strlen(cmdtext[10])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Apoyarse [1-2]"); return 1; }
    	switch (cmdtext[10])
    	{
        	case '1': LoopingAnim(playerid,"GANGS","leanIDLE",4.0,1,0,1,1,1);
        	case '2': LoopingAnim(playerid,"MISC","Plyrlean_loop",4.0,1,1,1,1,1);
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Apoyarse [1-2]");
    	}
    	return 1;
    }

    // Beso
    if(strcmp(cmd, "/beso", true) == 0)
    {
        if (!strlen(cmdtext[6])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Beso [1-2]"); return 1; }
    	switch (cmdtext[6])
    	{
        	case '1': LoopingAnim(playerid,"KISSING","Grlfrd_Kiss_03",4.1,0,0,0,1,1);
        	case '2': LoopingAnim(playerid,"KISSING","Playa_Kiss_03",4.1,0,0,0,1,1);
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Beso [1-2]");
    	}
    	return 1;
    }
    // Billar
    if(strcmp(cmd, "/billar", true) == 0)
    {
        if (!strlen(cmdtext[8])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Billar [1-3]"); return 1; }
    	switch (cmdtext[8])
    	{
        	case '1': LoopingAnim(playerid,"POOL","POOL_Idle_Stance",4.1,0,1,1,1,1);
        	case '2': LoopingAnim(playerid,"POOL","POOL_Med_Start",4.1,0,1,1,1,1);
        	case '3': LoopingAnim(playerid,"POOL","POOL_Med_Shot",4.1,0,1,1,1,1);
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Billar [1-3]");
    	}
    	return 1;
    }

    // Correr (Estilos)
    if(!strcmp(cmd, "/correr", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 6)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Correr [1-6]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"PED","run_civi",4.1,1,1,1,1,1);
		case 2: LoopingAnim(playerid,"PED","run_gang1",4.1,1,1,1,1,1);
		case 3: LoopingAnim(playerid,"PED","run_old",4.1,1,1,1,1,1);
		case 4: LoopingAnim(playerid,"PED","run_fat",4.1,1,1,1,1,1);
		case 5: LoopingAnim(playerid,"PED","woman_run",4.1,1,1,1,1,1);
		case 6: LoopingAnim(playerid,"PED","WOMAN_runsexy",4.1,1,1,1,1,1);
	}

	return 1;
}

	// Stop
    if(strcmp(cmd, "/stopanim", true) == 0) {
		 ClearAnimations(playerid);
         OnePlayAnim(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
         return 1;
    }

	// Cuyons
    if(strcmp(cmd, "/rascarse", true) == 0) {
		 LoopingAnim(playerid,"MISC","Scratchballs_01",4.1,1,1,1,1,1);
         return 1;
    }

    // Strip
    if(strcmp(cmd, "/strip", true) == 0)
    {
        if (!strlen(cmdtext[7])) { SendClientMessage(playerid,COLOR_NARANJA,"* /Strip [1-7]"); return 1; }
    	switch (cmdtext[7])
    	{
        	case '1', 'A': LoopingAnim(playerid,"STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1 );
        	case '2', 'B': LoopingAnim(playerid,"STRIP", "strip_B", 4.1, 1, 1, 1, 1, 1 );
        	case '3', 'C': LoopingAnim(playerid,"STRIP", "strip_C", 4.1, 1, 1, 1, 1, 1 );
        	case '4', 'D': LoopingAnim(playerid,"STRIP", "strip_D", 4.1, 1, 1, 1, 1, 1 );
        	case '5', 'E': LoopingAnim(playerid,"STRIP", "strip_E", 4.1, 1, 1, 1, 1, 1 );
        	case '6', 'F': LoopingAnim(playerid,"STRIP", "strip_F", 4.1, 1, 1, 1, 1, 1 );
        	case '7', 'G': LoopingAnim(playerid,"STRIP", "strip_G", 4.1, 1, 1, 1, 1, 1 );
        	default: SendClientMessage(playerid,COLOR_NARANJA,"* /Strip [1-7]");
    	}
    	return 1;
    }

    // Tumbarse (Estilos)
    if(!strcmp(cmd, "/tumbarse", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 5)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Tumbarse [1-5]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"BEACH","bather",4.1,0,1,1,1,1);
		case 2: LoopingAnim(playerid,"BEACH","Lay_Bac_Loop",4.1,0,1,1,1,1);
		case 3: LoopingAnim(playerid,"BEACH","BD_Fire3",4.1,0,1,1,1,1);
		case 4: LoopingAnim(playerid,"BEACH","ParkSit_W_loop",4.1,0,1,1,1,1);
	    case 5: LoopingAnim(playerid,"BEACH","SitnWait_loop_W",4.1,0,1,1,1,1);
	}

	return 1;
}

    // Coche
    if(!strcmp(cmd, "/coche", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 7)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Coche [1-7]");
		return 1;
	}
	switch(animid)
	{
		case 1: OnePlayAnim(playerid,"CAR","Sit_relaxed",4.1,0,0,0,1,0);
		case 2: OnePlayAnim(playerid,"LOWRIDER","lrgirl_hair",4.1,0,0,0,1,0);
		case 3: OnePlayAnim(playerid,"GHETTO_DB","GDB_Car2_PLY",4.1,1,0,0,1,0);
		case 4: LoopingAnim(playerid,"GHETTO_DB","GDB_Car_RYD",4.1,0,0,0,1,0);
	    case 5: OnePlayAnim(playerid,"LOWRIDER","lrgirl_l0_loop",4.1,0,1,1,1,1);
	    case 6: OnePlayAnim(playerid,"LOWRIDER","lrgirl_l0_to_l1",4.1,0,0,0,1,1);
	    case 7: OnePlayAnim(playerid,"LOWRIDER","lrgirl_l2_loop",4.1,1,0,0,1,1);
	}

	return 1;
}
// Mecanico
    if(!strcmp(cmd, "/mecanico", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 2)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Mecanico [1-2]");
		return 1;
	}
	switch(animid)
	{
		case 1: LoopingAnim(playerid,"CAR","Fixn_Car_Loop",4.1,1,0,0,1,1);
	    case 2: LoopingAnim(playerid,"CAR","Fixn_Car_Out",4.1,0,0,0,1,1);
	}

	return 1;
}

    // Bailoteo
    if(!strcmp(cmd, "/bailoteo", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 10)
	{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Bailoteo [1-10]");
		return 1;
	}
	switch(animid)
	{
        case 1: LoopingAnim(playerid,"DANCING","DAN_Down_A",4.1,1,0,0,1,1);
        case 2: LoopingAnim(playerid,"DANCING","DAN_Left_A",4.1,1,0,0,1,1);
		case 3: LoopingAnim(playerid,"DANCING","DAN_Loop_A",4.1,1,0,0,1,1);
		case 4: LoopingAnim(playerid,"DANCING","DAN_Right_A",4.1,1,0,0,1,1);
		case 5: LoopingAnim(playerid,"DANCING","DAN_Up_A",4.1,1,0,0,1,1);
		case 6: LoopingAnim(playerid,"DANCING","dnce_M_a",4.1,1,0,0,1,1);
		case 7: LoopingAnim(playerid,"DANCING","dnce_M_b",4.1,1,0,0,1,1);
		case 8: LoopingAnim(playerid,"DANCING","dnce_M_c",4.1,1,0,0,1,1);
		case 9: LoopingAnim(playerid,"DANCING","dnce_M_d",4.1,1,0,0,1,1);
		case 10: LoopingAnim(playerid,"DANCING","dnce_M_e",4.1,1,0,0,1,1);
	}
	return 1;
}
    // Consola
    if(!strcmp(cmd, "/consola", true))
	{
	tmp = animstrtok(cmdtext, idx);
	animid = strval(tmp);
	if(!strlen(tmp)||animid < 1 || animid > 3)
		{
		SendClientMessage(playerid,COLOR_NARANJA,"* /Consola [1-3]");
		return 1;
	}
	switch(animid)
	{
        case 1: LoopingAnim(playerid,"CRIB","PED_Console_Loop",4.1,1,1,1,1,1);
        case 2: LoopingAnim(playerid,"CRIB","PED_Console_Loose",4.1,0,1,1,1,1);
		case 3: LoopingAnim(playerid,"CRIB","PED_Console_Win",4.1,0,1,1,1,1);
	}

	return 1;
}





	// Bailar
 	if(strcmp(cmd, "/bailar", true) == 0) {


      		tmp = animstrtok(cmdtext, idx);
			if(!strlen(tmp)) {
				SendClientMessage(playerid,COLOR_NARANJA,"* /Bailar [1-4]");
				return 1;
			}

			dancestyle = strval(tmp);
			if(dancestyle < 1 || dancestyle > 4) {
			    SendClientMessage(playerid,COLOR_NARANJA,"* /Bailar [1-4]");
			    return 1;
			}

			if(dancestyle == 1) {
			    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
			} else if(dancestyle == 2) {
			    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
			} else if(dancestyle == 3) {
			    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
			} else if(dancestyle == 4) {
			    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
			}
 	  		return 1;
	}
	return 0;
}

Anims_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(IsKeyJustDown(KEY_HANDBRAKE,newkeys,oldkeys)) //Animaciones
	{
	    StopLoopingAnim(playerid);
        animation[playerid] = 0;
		return 1;
    }
	return 1;
}

Anims_OnPlayerConnect(playerid)
{
    PreloadAnimLib(playerid,"BOMBER"); //Cargado de anims
	PreloadAnimLib(playerid,"RAPPING");
	PreloadAnimLib(playerid,"SHOP");
	PreloadAnimLib(playerid,"BEACH");
	PreloadAnimLib(playerid,"SMOKING");
	PreloadAnimLib(playerid,"FOOD");
	PreloadAnimLib(playerid,"ON_LOOKERS");
	PreloadAnimLib(playerid,"DEALER");
	PreloadAnimLib(playerid,"CRACK");
	PreloadAnimLib(playerid,"CARRY");
	PreloadAnimLib(playerid,"COP_AMBIENT");
	PreloadAnimLib(playerid,"PARK");
	PreloadAnimLib(playerid,"INT_HOUSE");
	PreloadAnimLib(playerid,"FOOD");
	PreloadAnimLib(playerid,"PED");
	return 1;
}

Anims_OnPlayerDeath(playerid)
{
    if(gPlayerUsingLoopingAnim[playerid]) //Anims
	{
        gPlayerUsingLoopingAnim[playerid] = 0;
	}
	return 1;
}

Anims_OnDialogResponse(playerid, dialogid, response, listitem)
{
	if(dialogid == 9999)
	{
	    if(!response)return 1;
	    if(listitem == 0) //Carga
	    {
	        LoopingAnim(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
	    }
	    if(listitem == 1) //Llorar
	    {
            LoopingAnim(playerid,"GRAVEYARD","mrnF_loop",4.1,1,1,1,1,1);
	    }
	    if(listitem == 2) //Masturb
	    {
            LoopingAnim(playerid,"PAULNMAC","wank_loop",4.1,1,1,1,1,1);
	    }
	    if(listitem == 3) //Bofetada
	    {
            LoopingAnim(playerid,"MISC","bitchslap",4.1,1,0,0,1,1);
	    }
	    if(listitem == 4) //Facepalm
	    {
            LoopingAnim(playerid,"MISC","plyr_shkhead",4.1,0,0,0,0,0);
	    }
	    if(listitem == 5) //Barandilla
	    {
            LoopingAnim(playerid,"BD_FIRE","BD_Panic_Loop",4.1,1,1,1,1,1);
	    }
	    if(listitem == 6) //Sentarse
	    {
            LoopingAnim(playerid,"PED","SEAT_down",4.1,0,0,0,1,1);
	    }
	}
	return 1;
}
