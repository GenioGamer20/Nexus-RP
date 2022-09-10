#include <a_samp>
#include <dns>

main()
{
    print("Anti-proxy cargado");
}

public OnPlayerConnect(playerid)
{
    GetPlayerHost(playerid);
    return 1;
}

public OnReverseDNS(ip[], host[], extra)
{
        if(strfind(host,"anchorfree.com", true) != -1) return BanEx(extra,"PROXY");
        return 1;
}
