--[[message
Testing what happens when multiple cards are Set at once by a card effect. In Percy they are revealed and the opponent knows which is which, and this is wrong.
]]
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_TEST_MODE,4)
Debug.SetAIName("ai name")
Debug.SetPlayerInfo(0,6000,0,0)
Debug.SetPlayerInfo(1,6000,0,0)

Debug.AddCard(83555666,1,1,LOCATION_SZONE,0,POS_FACEDOWN)

Debug.AddCard(88316955,0,0,LOCATION_MZONE,0,POS_FACEUP_DEFENSE)
Debug.AddCard(24010609,0,0,LOCATION_SZONE,0,POS_FACEUP)

Debug.AddCard(63166095,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(52340444,0,0,LOCATION_HAND,0,POS_FACEDOWN)

Debug.AddCard(15710054,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(51205763,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(24010609,0,0,LOCATION_DECK,0,POS_FACEDOWN)

Debug.ReloadFieldEnd()