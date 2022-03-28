--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_TEST_MODE,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(92377303,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(73628505,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(71625222,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(46986414,0,0,LOCATION_MZONE,1,1,true)
--Monster Zones
Debug.AddCard(66413481,1,1,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(73628505,1,1,LOCATION_SZONE,2,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()