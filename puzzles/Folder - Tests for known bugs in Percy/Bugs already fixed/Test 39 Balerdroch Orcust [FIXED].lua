--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
The way Baledroch works is that if the monster was a Zombie when its effect was activated, you can use Baledroch's effect.
That's why you cannot negate Effect Veiler even if it becomes a Zombie in the Graveyard after discarding,
but you can negate an Orcust or a Kozmo because it was a Zombie in the Graveyard when its effect was activated (was a Zombie because of Zombie World)..
]]
--Monster Zones
Debug.AddCard(39185163,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(39185163,0,0,LOCATION_MZONE,3,1,true)
--Spell & Trap Zones
Debug.AddCard(4064256,0,0,LOCATION_SZONE,5,5)
--Main Deck
Debug.AddCard(21441617,1,1,LOCATION_DECK,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(57835716,1,1,LOCATION_GRAVE,2,1,true)
Debug.AddCard(90351981,1,1,LOCATION_SZONE,5,5)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()