--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
Debug.ShowHint('Normal Summoning MalicousMagnet in the presence of an unaffected monster crashes the game. Use the Kaijus to remove the unaffected monster to test')

--Extra Deck
Debug.AddCard(5772618,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(6766208,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(62899696,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(48770333,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(48770333,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(10817524,1,1,LOCATION_MZONE,1,1,true)
Debug.AddCard(52687916,1,1,LOCATION_MZONE,2,1,true)
--Debug.AddCard(40061558,1,1,LOCATION_MZONE,3,1,true)
--Debug.AddCard(40061558,1,1,LOCATION_MZONE,5,1,true)
--Debug.AddCard(40061558,1,1,LOCATION_MZONE,4,1,true)

local c=Debug.AddCard(40061558,1,1,LOCATION_MZONE,3,1,true)


Debug.ReloadFieldEnd()
Debug.PreSummon(c,SUMMON_TYPE_NORMAL)