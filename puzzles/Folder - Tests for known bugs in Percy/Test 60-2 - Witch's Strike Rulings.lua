--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand
Debug.AddCard(65247798,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(92246806,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Spell & Trap Zones
Debug.AddCard(41420027,0,0,LOCATION_SZONE,2,10)
--Monster Zones
Debug.AddCard(21123811,1,1,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(40605147,1,1,LOCATION_SZONE,2,10)
Debug.AddCard(98069388,1,1,LOCATION_SZONE,1,10)
Debug.AddCard(36458063,1,1,LOCATION_SZONE,3,10)
Debug.AddCard(29401950,1,1,LOCATION_SZONE,0,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()