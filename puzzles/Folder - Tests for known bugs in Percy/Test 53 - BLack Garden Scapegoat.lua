--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Spell & Trap Zones
Debug.AddCard(71645242,0,0,LOCATION_SZONE,5,5)
Debug.AddCard(73915051,0,0,LOCATION_SZONE,2,10)
--Hand
Debug.AddCard(43096270,1,1,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(9720537,1,1,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(43096270,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(9720537,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.ReloadFieldEnd()
--aux.BeginPuzzle()