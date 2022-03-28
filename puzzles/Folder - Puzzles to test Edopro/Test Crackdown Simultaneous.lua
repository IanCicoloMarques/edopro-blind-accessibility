--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
	If two Crawdowns, one of each player, that are active are negated by Royal Decree but then Royal Decree stops applying neither of the players can select which zone to get control of the monsters, which causes the behaviour demonstrated in this puzzle.
]]
--Monster Zones
Debug.AddCard(1641882,0,0,LOCATION_MZONE,5,1,true)
--Spell & Trap Zones
Debug.AddCard(51452091,0,0,LOCATION_SZONE,1,5)
Debug.AddCard(36975314,0,0,LOCATION_SZONE,0,10)
Debug.AddCard(5318639,0,0,LOCATION_SZONE,2,10)
--Monster Zones
Debug.AddCard(55784832,1,1,LOCATION_MZONE,1,1,true)
--Spell & Trap Zones
Debug.AddCard(36975314,1,1,LOCATION_SZONE,0,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()