Scriptname BakaPowerArmorStorageTokenScript extends ObjectReference Hidden Const

Event OnContainerChanged(ObjectReference akNewContainer, ObjectReference akOldContainer)
	If (akNewContainer == None)
		BakaPowerArmorStorage.HandleToken(Self)
	EndIf
EndEvent

Event OnEquipped(Actor akActor)
	If (akActor == Game.GetPlayer())
		Drop(True)
	Else
		akActor.UnequipItem(Self, True, True)
	EndIf
EndEvent
