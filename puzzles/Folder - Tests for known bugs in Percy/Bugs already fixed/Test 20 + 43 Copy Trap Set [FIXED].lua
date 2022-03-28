Debug.ReloadFieldBegin(DUEL_TEST_MODE+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,3000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
Trap of Darkness should set itself after copying Final Battle. Also test if Final Battle itself is correct, regarding setting itself

]]

Debug.AddCard(42713844,0,0,LOCATION_MZONE,0,POS_FACEUP_ATTACK)
Debug.AddCard(42713844,1,1,LOCATION_MZONE,0,POS_FACEUP_ATTACK)

Debug.AddCard(63356631,0,0,LOCATION_SZONE,2,POS_FACEDOWN)

Debug.AddCard(79766336,0,0,LOCATION_SZONE,0,POS_FACEDOWN)
Debug.AddCard(79766336,0,0,LOCATION_SZONE,0,POS_FACEDOWN)
Debug.AddCard(74640994,1,1,LOCATION_SZONE,2,POS_FACEDOWN)
Debug.AddCard(74640994,1,1,LOCATION_SZONE,2,POS_FACEDOWN)

Debug.AddCard(74640994,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(74640994,0,0,LOCATION_HAND,0,POS_FACEUP)


Debug.ReloadFieldEnd()