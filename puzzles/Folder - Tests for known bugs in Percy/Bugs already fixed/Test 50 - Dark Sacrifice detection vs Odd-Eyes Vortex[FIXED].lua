--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[
Dark Sacrifice should only be able to negate an effect like Odd-Eyes Vortex Dragon's if the card is in a location where it can be destroyed.
]]
--Main Deck
Debug.AddCard(26202165,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(65446452,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(51028231,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(78310590,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(78310590,1,1,LOCATION_EXTRA,0,POS_FACEUP)
Debug.AddCard(60643553,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(53262004,1,1,LOCATION_MZONE,2,1,true)
Debug.AddCard(85431040,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(39260991,0,0,LOCATION_MZONE,1,1,true)
--Spell & Trap Zones
Debug.AddCard(76045757,0,0,LOCATION_SZONE,1,10)
Debug.AddCard(78310590,0,0,LOCATION_PZONE,1,5)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()