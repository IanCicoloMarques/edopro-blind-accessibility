--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Extra Deck
Debug.AddCard(74157028,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(84058253,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(70095154,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(3659803,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(24094653,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(70095154,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(75878039,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(70095154,0,0,LOCATION_MZONE,2,1,true)

Debug.AddCard(70095154,0,0,LOCATION_GRAVE,2,1)
--Monster Zones
local a=Debug.AddCard(5186893,1,1,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(84171830,1,1,LOCATION_SZONE,5,5)
Debug.AddCard(18235309,1,1,LOCATION_SZONE,3,5)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()

Debug.PreSummon(a,SUMMON_TYPE_ADVANCE)
