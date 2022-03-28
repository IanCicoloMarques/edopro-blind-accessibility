--[[message
How they should resolve in case of mutiple Chain Links:
(format is "CL1/CL2")

If CL2 ACTIVATION is negated
Cost/cost: CL1 works
cost/effect: CL1 works
effect/effect: CL1 works
effect/cost: CL1 works

If CL2 EFFECT is negated:
cost/cost: nothing
cost/effect: CL1 works
effect/effect: CL1 works
effect/cost: nothing

Give up as the cost (if the effect is negated, you don't normal draw, but if the activation is negated you normal draw [OATH effects in the cost]):
Skull Flame, Flame Tiger, Gearbreed, Iron Core of Koa'ki Meiru, Malefic World,  Spirit Burner,  Sylvan Waterslide, Tachyon Chaos Hole
Meteor Flare, Rank-Up-Magic Astral Force
Give up in the effect (if effect or activation is negated, you normal draw [effect in the operation]):
Magical Blast,  Flying Saucer Muusik'i, Freed the Matchless General, Dark General Freed, Fandora, the Flying Furtress
Legacy of the Duelist, 


]]

--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,1,0)
Debug.SetPlayerInfo(1,8000,0,0)

--GY
Debug.AddCard(67750322,0,0,LOCATION_HAND,0,POS_FACEUP)

Debug.AddCard(36623431,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(36623431,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(45950291,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(45950291,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
--Debug.AddCard(97697678,0,0,LOCATION_MZONE,1,4,true)
--Debug.AddCard(97697678,0,0,LOCATION_MZONE,0,4,true)
Debug.AddCard(61257789,0,0,LOCATION_MZONE,4,1,true)
Debug.AddCard(15936370,0,0,LOCATION_MZONE,2,4,true)
--Debug.AddCard(15936370,0,0,LOCATION_MZONE,3,4,true)


Debug.AddCard(15936370,0,0,LOCATION_DECK,0,4)
Debug.AddCard(15936370,0,0,LOCATION_DECK,0,4)
Debug.AddCard(58012107,0,0,LOCATION_DECK,0,4)
Debug.AddCard(58012107,0,0,LOCATION_DECK,0,4)
Debug.AddCard(97697678,0,0,LOCATION_DECK,0,4)
Debug.AddCard(61257789,0,0,LOCATION_DECK,0,4)
Debug.AddCard(45950291,0,0,LOCATION_DECK,0,4)
Debug.AddCard(36623431,0,0,LOCATION_DECK,0,4)
--Spell & Trap Zones
Debug.AddCard(47355498,0,0,LOCATION_SZONE,5,10)
Debug.AddCard(82732705,0,0,LOCATION_SZONE,1,10)
Debug.ReloadFieldEnd()


Debug.ShowHint("Assault Mode and Necrovalley are here to negate activations and effects, respectively")