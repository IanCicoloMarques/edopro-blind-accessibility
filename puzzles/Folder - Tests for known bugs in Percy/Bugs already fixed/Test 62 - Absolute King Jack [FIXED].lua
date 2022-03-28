--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
You cannot activate the first effect of Absolute King Back Jack if the player is affected by the "cannot Set" effect of Set Rotation, even though that only prevents you from Setting Field Spells, not Trap Cards.
]]
--Main Deck
Debug.AddCard(35371948,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(22702055,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(22702055,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(59919307,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(59919307,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(59919307,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(73468603,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(60990740,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(60990740,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(75878039,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Spell & Trap Zones
Debug.AddCard(24294108,1,1,LOCATION_SZONE,3,5)
Debug.ReloadFieldEnd()
