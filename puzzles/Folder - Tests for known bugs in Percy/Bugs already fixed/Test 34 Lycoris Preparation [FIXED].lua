--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
According to rulings, if the opponent uses a card like Preparation of Rites, then should do 400 damage once by the effect of Trickstar Lycoris, and not 200 damage twice.
]]
--Main Deck
Debug.AddCard(99185129,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(53932291,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(99185129,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--GY
Debug.AddCard(14735698,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Spell & Trap Zones
Debug.AddCard(96729612,0,0,LOCATION_SZONE,2,10)
Debug.AddCard(5318639,0,0,LOCATION_SZONE,1,10)
--Monster Zones
Debug.AddCard(35199656,1,1,LOCATION_MZONE,2,1,true)
Debug.AddCard(35199656,1,1,LOCATION_MZONE,3,1,true)
--Spell & Trap Zones
Debug.AddCard(35371948,1,1,LOCATION_SZONE,5,5)
Debug.AddCard(59919307,1,1,LOCATION_SZONE,3,10)



Debug.AddCard(81275020,1,1,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(53932291,1,1,LOCATION_GRAVE,0,POS_FACEUP)

Debug.AddCard(19230407,0,0,LOCATION_HAND,5,5)
Debug.AddCard(19230407,0,0,LOCATION_HAND,5,5)
Debug.AddCard(24224830,0,0,LOCATION_HAND,5,5)
Debug.AddCard(24224830,0,0,LOCATION_HAND,5,5)
Debug.AddCard(23434538,0,0,LOCATION_HAND,5,5)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()