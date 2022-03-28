--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
You shouldn't be able to apply both Shie En's and the Secret Six Sam's effect to redirect/prevent the destruction.
]]
--Main Deck
Debug.AddCard(5758500,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(7291576,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(29981921,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(49721904,0,0,LOCATION_MZONE,3,4,true)
--Spell & Trap Zones
Debug.AddCard(44095762,1,1,LOCATION_SZONE,3,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()