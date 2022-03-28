--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand
Debug.AddCard(92182447,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(66809920,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(2204038,0,0,LOCATION_MZONE,1,1,true)
--Spell & Trap Zones
Debug.AddCard(92182447,0,0,LOCATION_SZONE,1,10)
--GY
Debug.AddCard(75878039,1,1,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(21844576,1,1,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(21844576,1,1,LOCATION_MZONE,3,1,true)
Debug.AddCard(75878039,1,1,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(24294108,1,1,LOCATION_SZONE,2,5)
Debug.ReloadFieldEnd()
