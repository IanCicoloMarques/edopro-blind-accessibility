--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand
Debug.AddCard(93377803,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(22046459,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Banished
Debug.AddCard(75878039,0,0,LOCATION_REMOVED,0,5)
--Spell & Trap Zones
Debug.AddCard(27174286,0,0,LOCATION_SZONE,1,10)
--Monster Zones
Debug.AddCard(13959634,1,1,LOCATION_MZONE,3,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()