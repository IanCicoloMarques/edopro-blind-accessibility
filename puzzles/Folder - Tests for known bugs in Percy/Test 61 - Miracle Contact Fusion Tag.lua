--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Extra Deck
Debug.AddCard(78734254,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(5128859,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(55171412,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(48996569,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(89943723,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(80344569,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(89943723,0,0,LOCATION_MZONE,1,1,true)
--Spell & Trap Zones
Debug.AddCard(35255456,0,0,LOCATION_SZONE,2,10)
Debug.AddCard(59432181,0,0,LOCATION_SZONE,1,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()