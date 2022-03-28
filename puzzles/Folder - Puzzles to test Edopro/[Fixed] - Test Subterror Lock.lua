--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
	Subterror Nemesis Warrior makes the game freeze during the selection of the tributes.
]]
--Main Deck
Debug.AddCard(65976795,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(16428514,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(16719140,0,0,LOCATION_MZONE,4,1,true)
Debug.AddCard(42713844,0,0,LOCATION_MZONE,2,4,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()