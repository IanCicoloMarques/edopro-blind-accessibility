--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
EFFECT_MUST_BE_ATTACKED has been removed from the core, and instead EFFECT_MUST_ATTACK_MONSTER now takes a Value function that checks the validity of the attack target.
Includes number 13, number 31 and Hypnosister
]]
--Hand
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(5318639,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(5318639,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(2273734,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(59642500,0,0,LOCATION_MZONE,3,4,true)
--Spell & Trap Zones
Debug.AddCard(69351984,0,0,LOCATION_PZONE,0,5)
Debug.AddCard(69351984,0,0,LOCATION_PZONE,1,5)
Debug.AddCard(69351984,1,1,LOCATION_PZONE,1,5)
--Monster Zones
Debug.AddCard(69058960,1,1,LOCATION_MZONE,3,1,true)
Debug.AddCard(69058960,1,1,LOCATION_MZONE,3,1,true)
Debug.AddCard(69058960,1,1,LOCATION_MZONE,3,1,true)
Debug.AddCard(75878039,1,1,LOCATION_MZONE,1,1,true)
Debug.AddCard(95442074,1,1,LOCATION_MZONE,4,1,true)
Debug.AddCard(95442074,1,1,LOCATION_MZONE,4,1,true)
Debug.AddCard(22200403,1,1,LOCATION_MZONE,2,1,true)
Debug.ReloadFieldEnd()
