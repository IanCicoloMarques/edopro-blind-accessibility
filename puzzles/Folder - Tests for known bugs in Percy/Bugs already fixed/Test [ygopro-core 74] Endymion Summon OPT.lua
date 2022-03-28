--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(71413901,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(14558127,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(16006416,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
local c=Debug.AddCard(92559258,0,0,LOCATION_PZONE,0,5)
Debug.PreAddCounter(c,0x1,6)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()