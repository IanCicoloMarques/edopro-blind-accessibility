--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--GY
Debug.AddCard(25533642,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(75878039,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(25533642,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(89091579,0,0,LOCATION_MZONE,3,1,true)
--Spell & Trap Zones
Debug.AddCard(6430659,0,0,LOCATION_SZONE,2,5)
--Hand
Debug.AddCard(14457896,1,1,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
--Debug.AddCard(14141448,1,1,LOCATION_MZONE,3,1,true)
--Debug.AddCard(28124263,1,1,LOCATION_MZONE,1,4,true)
Debug.ReloadFieldEnd()
