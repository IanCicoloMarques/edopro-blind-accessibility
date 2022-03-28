--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
Ostinato cannot be activated.
Maybe some other fusion Spells too?

]]
--Main Deck
Debug.AddCard(3395226,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(14763299,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(5908650,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Extra Deck
Debug.AddCard(24672164,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(57594700,0,0,LOCATION_EXTRA,0,8)

Debug.AddCard(57594700,0,0,LOCATION_GRAVE,0,8)
Debug.AddCard(9113513,0,0,LOCATION_GRAVE,0,8)
Debug.AddCard(57594700,0,0,LOCATION_GRAVE,0,8)
Debug.AddCard(5908650,0,0,LOCATION_GRAVE,0,8)
Debug.AddCard(5908650,0,0,LOCATION_GRAVE,0,8)
Debug.AddCard(14763299,0,0,LOCATION_GRAVE,0,8)
--Hand
Debug.AddCard(9113513,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(57594700,1,1,LOCATION_MZONE,0,POS_FACEUP_ATTACK)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()