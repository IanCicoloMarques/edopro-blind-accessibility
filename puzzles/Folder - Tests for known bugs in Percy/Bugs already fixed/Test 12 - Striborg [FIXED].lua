Debug.ReloadFieldBegin(DUEL_TEST_MODE,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
Bug 1
If the effect of "Degenerate Circuit" is applying, any monster Tributed for the face-up Tribute Summon of "Fantastic Striborg" should be banished. (Currently the monster returns to the hand.)

Bug 2
If the effect of "Macro Cosmos" is applying, any monster Tributed for the face-up Tribute Summon of "Fantastic Striborg" should return to the hand. (Currently the monster is banished.)
]]

Debug.AddCard(55784832,0,0,LOCATION_MZONE,0,POS_FACEUP_ATTACK)

Debug.AddCard(36995273,0,0,LOCATION_SZONE,0,POS_FACEDOWN) --Circuit
Debug.AddCard(30241314,0,0,LOCATION_SZONE,1,POS_FACEDOWN) --Macro

Debug.AddCard(79176962,0,0,LOCATION_HAND,0,POS_FACEUP) --Striborg

Debug.ReloadFieldEnd()