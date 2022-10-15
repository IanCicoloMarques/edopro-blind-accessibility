--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand (yours)
Debug.AddCard(15025844,0,0,LOCATION_HAND,0,POS_FACEDOWN)

Debug.ReloadFieldEnd()
aux.BeginPuzzle()