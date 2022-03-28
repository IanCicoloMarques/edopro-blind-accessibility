--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
Setup:
1-Activate Super Agent in the Hand
2-MER equips a Super Agent
3-Link Summon Double Agent
4-Try to equip it with Fully Armed

You will notice that you cannot because the name changing effect was negated, which is wrong.

]]

--Main Deck
Debug.AddCard(30979619,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(20584712,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Extra Deck
Debug.AddCard(1322368,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(41091257,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(73828446,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(83764718,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(41091257,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(41091257,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(41091257,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(41091257,0,0,LOCATION_MZONE,3,1,true)
--Main Deck
Debug.AddCard(35699,1,1,LOCATION_DECK,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(41578483,1,1,LOCATION_MZONE,2,1,true)
Debug.ReloadFieldEnd()
