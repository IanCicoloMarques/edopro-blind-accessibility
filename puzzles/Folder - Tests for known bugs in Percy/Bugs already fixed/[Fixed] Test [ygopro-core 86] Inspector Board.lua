--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand
Debug.AddCard(83764718,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(15397015,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(75878039,0,0,LOCATION_MZONE,2,1,true)
--GY
Debug.AddCard(15397015,1,1,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
--Debug.AddCard(99668578,1,1,LOCATION_MZONE,3,1,true)

Debug.AddCard(83764718,1,1,LOCATION_SZONE,0,POS_FACEDOWN)
Debug.ReloadFieldEnd()