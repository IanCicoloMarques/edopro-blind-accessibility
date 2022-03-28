--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--GY
Debug.AddCard(68024506,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(68246154,0,0,LOCATION_MZONE,0,1,true)
--Spell & Trap Zones
Debug.AddCard(20745268,0,0,LOCATION_SZONE,0,10)
--Spell & Trap Zones
Debug.AddCard(24224830,1,1,LOCATION_SZONE,4,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()