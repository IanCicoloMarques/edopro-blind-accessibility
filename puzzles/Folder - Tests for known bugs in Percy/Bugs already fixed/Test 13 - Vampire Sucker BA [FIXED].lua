--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
If a Burning Abyss monster is special summoned by Vampire Sucker's effect, it should trigger Sucker's effect to draw, since the BA will be treated as a Zombie monster.
Currently, it does not if the BA monster gets destroyed by its own effect.
]]
--Main Deck
Debug.AddCard(32626733,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(37129797,0,0,LOCATION_MZONE,1,1,true)
--GY
Debug.AddCard(36553319,1,1,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(84764038,1,1,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(27552504,1,1,LOCATION_MZONE,3,4,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()