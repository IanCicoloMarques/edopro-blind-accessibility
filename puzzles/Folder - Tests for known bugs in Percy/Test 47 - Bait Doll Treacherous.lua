--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
Bait Doll, a Spell, is the one aplying Treacherous effects, which makes Horus (unaffected by spells) survive and Wildheart(unaffected by traps) is destroyed.
The interaction should be the opposite.
]]

--Hand
Debug.AddCard(7165085,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(11224103,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(86188410,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(99590524,1,1,LOCATION_SZONE,3,10)
Debug.AddCard(99590524,0,0,LOCATION_SZONE,3,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()