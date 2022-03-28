--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand
Debug.AddCard(96227613,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(22211622,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(33833230,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(69228245,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(75878039,1,1,LOCATION_MZONE,2,4,true)
--Spell & Trap Zones
Debug.AddCard(38120068,1,1,LOCATION_SZONE,3,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()