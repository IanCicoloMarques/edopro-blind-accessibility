--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(83269557,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(27354732,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Spell & Trap Zones
local a=Debug.AddCard(92559258,0,0,LOCATION_PZONE,0,5)
Debug.ReloadFieldEnd()
Debug.PreAddCounter(a,COUNTER_SPELL,7)