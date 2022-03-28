--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
	Judgment Arrows
	Check the lines commented for different scenarios
	Test Extra Link with Topologic
	Test the zone placement with the Decode Talkers
	Teest MST
]]
--Extra Deck
Debug.AddCard(53413628,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(46947713,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(15844566,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(36033786,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(33897356,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(40669071,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(1861629,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(22593417,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(2347477,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(2347477,1,1,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(511009503,0,0,LOCATION_HAND,0,POS_FACEDOWN)

--GY
Debug.AddCard(9523599,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
--Debug.AddCard(40669071,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(1861629,0,0,LOCATION_MZONE,1,1,true)
--Debug.AddCard(33897356,0,0,LOCATION_MZONE,3,1,true)
Debug.AddCard(1861629,0,0,LOCATION_MZONE,3,1,true)
--Debug.AddCard(15844566,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(36033786,0,0,LOCATION_MZONE,4,1,true)
Debug.AddCard(46947713,0,0,LOCATION_MZONE,5,1,true)
Debug.AddCard(53413628,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(53413628,0,0,LOCATION_MZONE,2,1,true)

Debug.AddCard(5318639,0,0,LOCATION_SZONE,4,10)
--Debug.AddCard(5318639,0,0,LOCATION_SZONE,1,10)
--Debug.AddCard(5318639,0,0,LOCATION_SZONE,2,10)
--Debug.AddCard(5318639,0,0,LOCATION_SZONE,0,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()