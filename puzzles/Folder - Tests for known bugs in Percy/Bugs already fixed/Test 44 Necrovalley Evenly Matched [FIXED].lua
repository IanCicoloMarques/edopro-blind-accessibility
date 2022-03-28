--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
If Full Force Virus is chained to the activation of Evenly Matched by tributing a monster,
Necrovalley then negates Evenly Matched, even though it's not banishing cards from the graveyard.
]]
--Spell & Trap Zones
Debug.AddCard(15693423,1,1,LOCATION_SZONE,2,10)
--Monster Zones
Debug.AddCard(25262697,0,0,LOCATION_MZONE,0,8,true)
Debug.AddCard(46986414,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(25262697,0,0,LOCATION_MZONE,2,8,true)
Debug.AddCard(25262697,0,0,LOCATION_MZONE,3,8,true)
Debug.AddCard(25262697,0,0,LOCATION_MZONE,4,8,true)
--Spell & Trap Zones
Debug.AddCard(47355498,0,0,LOCATION_SZONE,5,5)
Debug.AddCard(4931121,0,0,LOCATION_SZONE,2,10)
Debug.AddCard(4931121,0,0,LOCATION_SZONE,1,10)
Debug.AddCard(4931121,0,0,LOCATION_SZONE,0,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()