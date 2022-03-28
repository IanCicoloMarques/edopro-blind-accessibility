--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--GY
Debug.AddCard(48686504,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(73580471,0,0,LOCATION_MZONE,2,1,true)
--Banished
Debug.AddCard(55784832,1,1,LOCATION_REMOVED,0,5)
--Monster Zones
Debug.AddCard(36584821,1,1,LOCATION_MZONE,2,8,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()