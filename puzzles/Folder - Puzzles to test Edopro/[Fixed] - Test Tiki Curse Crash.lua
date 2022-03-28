--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Spell & Trap Zones
Debug.AddCard(49514333,0,0,LOCATION_SZONE,1,10)
Debug.AddCard(49514333,0,0,LOCATION_SZONE,2,10)
Debug.AddCard(92092092,0,0,LOCATION_SZONE,3,10)
--Monster Zones
Debug.AddCard(55885348,1,1,LOCATION_MZONE,1,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()