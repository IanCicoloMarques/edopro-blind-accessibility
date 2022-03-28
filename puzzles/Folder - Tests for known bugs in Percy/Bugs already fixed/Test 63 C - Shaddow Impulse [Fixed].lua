--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Extra Deck
Debug.AddCard(81020646,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(50954680,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(81020646,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(81020646,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(53129443,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(74586817,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(50954680,0,0,LOCATION_MZONE,3,1,true)
Debug.AddCard(81020646,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(50954680,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(74997493,0,0,LOCATION_MZONE,5,1,true)
--Spell & Trap Zones
Debug.AddCard(35329581,0,0,LOCATION_SZONE,1,10)
Debug.AddCard(98431356,0,0,LOCATION_SZONE,2,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()