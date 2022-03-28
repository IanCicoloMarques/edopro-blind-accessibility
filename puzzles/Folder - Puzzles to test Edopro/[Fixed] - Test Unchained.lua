--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
Testing the Unchained monsters
Secure Guardna is now a Dark in the Extra Deck, so using the DNA Surgery, you can make the monsters Cyberse.
Still, Secure requires 1 material and should not be a valid monster to summon
]]
--Extra Deck
Debug.AddCard(29479265,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(93854893,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(35606858,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(93084621,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(38342335,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(49725936,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(5821478,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(67680512,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(23971061,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(2857636,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(85289965,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(31833038,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(71384012,0,0,LOCATION_EXTRA,0,8)
--Debug.AddCard(2220237,0,0,LOCATION_EXTRA,0,8)

local c=Debug.AddCard(2220237,0,0,LOCATION_EXTRA,0,8)
local e1=Effect.CreateEffect(c)
e1:SetType(EFFECT_TYPE_SINGLE)
e1:SetCode(EFFECT_CHANGE_ATTRIBUTE)
e1:SetValue(ATTRIBUTE_DARK)
e1:SetReset(RESET_EVENT+0x1fe0000)
c:RegisterEffect(e1)

--Monster Zones
Debug.AddCard(93084621,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(89019964,0,0,LOCATION_MZONE,4,4,true)
Debug.AddCard(67680512,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(19230407,0,0,LOCATION_SZONE,0,10)
Debug.AddCard(83778600,0,0,LOCATION_SZONE,2,10)
Debug.AddCard(74701381,0,0,LOCATION_SZONE,3,10)
--Monster Zones
Debug.AddCard(67680512,1,1,LOCATION_MZONE,2,1,true)
Debug.AddCard(81983656,1,1,LOCATION_MZONE,3,1,true)
Debug.AddCard(22835145,1,1,LOCATION_MZONE,4,1,true)
Debug.AddCard(146746,1,1,LOCATION_MZONE,0,1,true)
Debug.AddCard(30270176,1,1,LOCATION_MZONE,1,1,true)
Debug.ReloadFieldEnd()
