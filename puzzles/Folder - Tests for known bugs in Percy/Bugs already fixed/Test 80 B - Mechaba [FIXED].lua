--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand
Debug.AddCard(39672388,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(75286621,0,0,LOCATION_MZONE,2,1,true)
--Main Deck
Debug.AddCard(22499034,1,1,LOCATION_DECK,0,POS_FACEDOWN)
--Monster Zones
local a=Debug.AddCard(94982447,1,1,LOCATION_MZONE,3,1,true)
Debug.ReloadFieldEnd()
Debug.PreSummon(a,SUMMON_TYPE_ADVANCE)
aux.BeginPuzzle()