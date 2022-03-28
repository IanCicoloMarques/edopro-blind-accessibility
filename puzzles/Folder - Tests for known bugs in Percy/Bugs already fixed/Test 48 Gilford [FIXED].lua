--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
His effect isn't being negated by Necrovalley
]]

--Hand
Debug.AddCard(36354007,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(69933858,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(19508728,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(19508728,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(19508728,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(19578592,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(19578592,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(19578592,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(75878039,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,4,1,true)
--Spell & Trap Zones
Debug.AddCard(47355498,0,0,LOCATION_SZONE,5,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()