--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand

Debug.AddCard(92182447,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(92182447,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(92182447,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(95308449,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY

--Monster Zones
Debug.AddCard(46701379,0,0,LOCATION_MZONE,1,1,true)
--Spell & Trap Zones
Debug.AddCard(1082946,0,0,LOCATION_SZONE,0,10)


Debug.ReloadFieldEnd()
