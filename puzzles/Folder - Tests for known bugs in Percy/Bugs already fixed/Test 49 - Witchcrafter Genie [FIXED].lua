--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
EFFECT_MUST_BE_ATTACKED has been removed from the core, and instead EFFECT_MUST_ATTACK_MONSTER now takes a Value function that checks the validity of the attack target.
Includes number 13, number 31 and Hypnosister
]]
--GY
Debug.AddCard(21744288,0,0,LOCATION_MZONE,0,POS_FACEUP_ATTACK)
Debug.AddCard(64756282,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(83289866,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(19673561,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(83289866,0,0,LOCATION_GRAVE,0,POS_FACEUP)



Debug.ReloadFieldEnd()
aux.BeginPuzzle()