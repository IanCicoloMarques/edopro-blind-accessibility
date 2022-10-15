--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

Debug.ShowHint("Press the key Q to look at the hand of the selected player.")
Debug.ShowHint("Press the key W to look at the monster field of the selected player.")
Debug.ShowHint("Press the key E to look at the spell field of the selected player.")
Debug.ShowHint("Press the key R to look at the extra deck of the selected player.")
Debug.ShowHint("Press the key T to look at the graveyard of the selected player.")
Debug.ShowHint("Press the key Y to look at the removed cards of the selected player.")
Debug.ShowHint("Press the key I to check the card information.")
Debug.ShowHint("Press the key ARROW UP to look at the enemy player cards.")
Debug.ShowHint("Press the key ARROW DOWN to look at your own cards.")
--Main Deck (yours)
Debug.AddCard(19050066,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(19050066,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(98585345,0,0,LOCATION_DECK,0,POS_FACEDOWN)

--Extra Deck (yours)
Debug.AddCard(41999284,0,0,LOCATION_EXTRA,0,POS_FACEDOWN)

--Hand (yours)
Debug.AddCard(57116034,0,0,LOCATION_HAND,0,POS_FACEDOWN)

--GY (yours)
Debug.AddCard(595626,0,0,LOCATION_GRAVE,0,POS_FACEUP)

--Banished (yours)
Debug.AddCard(7021574,0,0,LOCATION_REMOVED,0,POS_FACEUP)

--Monster Zones (yours)
Debug.AddCard(40640058,0,0,LOCATION_MZONE,0,POS_FACEUP_ATTACK,true)

--Spell & Trap Zones (yours)
Debug.AddCard(20065322,0,0,LOCATION_SZONE,0,POS_FACEDOWN)

--Extra Deck (opponent's)
Debug.AddCard(34031284,1,1,LOCATION_EXTRA,0,POS_FACEDOWN)

--Hand (opponent's)
Debug.AddCard(511005030,1,1,LOCATION_HAND,0,POS_FACEDOWN)

--GY (opponent's)
Debug.AddCard(42941100,1,1,LOCATION_GRAVE,0,POS_FACEUP)

--Banished (opponent's)
Debug.AddCard(12482652,1,1,LOCATION_REMOVED,0,POS_FACEUP)

--Monster Zones (opponent's)
Debug.AddCard(79335209,1,1,LOCATION_MZONE,0,POS_FACEUP_ATTACK,true)

--Spell & Trap Zones (opponent's)
Debug.AddCard(511000336,1,1,LOCATION_SZONE,0,POS_FACEDOWN)
Debug.AddCard(38395123,1,1,LOCATION_SZONE,1,POS_FACEUP)

Debug.ReloadFieldEnd()
aux.BeginPuzzle()