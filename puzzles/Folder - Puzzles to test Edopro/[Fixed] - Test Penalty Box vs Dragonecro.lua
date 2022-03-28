--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand
Debug.AddCard(5318639,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(34614289,0,0,LOCATION_MZONE,1,1,true)
--Spell & Trap Zones
Debug.AddCard(70043345,0,0,LOCATION_SZONE,1,5)
Debug.AddCard(70043345,0,0,LOCATION_SZONE,2,10)
--Monster Zones
Debug.AddCard(8198620,1,1,LOCATION_MZONE,3,1,true)
Debug.AddCard(34968834,1,1,LOCATION_MZONE,2,1,true)
Debug.ReloadFieldEnd()
