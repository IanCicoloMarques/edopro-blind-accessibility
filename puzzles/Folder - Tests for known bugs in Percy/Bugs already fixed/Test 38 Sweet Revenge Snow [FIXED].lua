--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)


--[[message
Have the AI attack you directly, then respond with Snow's effect in the Graveyard, banishing the 1 card on your field and all the cards in your Graveyard.
Should then be able to Chain the effect of Goddess of Sweet Revenge.
]]
--Main Deck
Debug.AddCard(4035199,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(4035199,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(4035199,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(4035199,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(4035199,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(4035199,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(4035199,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(72589042,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(55623480,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(73628505,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(73628505,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(73628505,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(73628505,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(73628505,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(73628505,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Spell & Trap Zones
Debug.AddCard(67443336,0,0,LOCATION_SZONE,2,10)
--Monster Zones
Debug.AddCard(69247929,1,1,LOCATION_MZONE,0,1,true)
Debug.AddCard(69247929,1,1,LOCATION_MZONE,1,1,true)
Debug.AddCard(69247929,1,1,LOCATION_MZONE,2,1,true)
Debug.AddCard(69247929,1,1,LOCATION_MZONE,3,1,true)
Debug.AddCard(69247929,1,1,LOCATION_MZONE,4,1,true)
Debug.ReloadFieldEnd()
--aux.BeginPuzzle()
