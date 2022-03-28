--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Extra Deck
Debug.AddCard(96380700,0,0,LOCATION_EXTRA,0,8)
--GY
Debug.AddCard(1861629,0,0,LOCATION_GRAVE,0,POS_FACEUP,true)
Debug.AddCard(6622715,0,0,LOCATION_GRAVE,0,POS_FACEUP,true)
--Monster Zones
Debug.AddCard(24154052,0,0,LOCATION_MZONE,2,4,true)
Debug.AddCard(92176681,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(1861629,0,0,LOCATION_MZONE,1,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()