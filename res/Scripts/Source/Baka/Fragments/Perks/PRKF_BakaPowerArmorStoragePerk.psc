;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
Scriptname Fragments:Perks:PRKF_BakaPowerArmorStoragePerk Extends Perk Hidden Const

;BEGIN FRAGMENT Fragment_Entry_00
Function Fragment_Entry_00(ObjectReference akTargetRef, Actor akActor)
;BEGIN CODE
BakaPowerArmorStoragePlacedScript PlacedForm = akTargetRef as BakaPowerArmorStoragePlacedScript
If (PlacedForm)
    PlacedForm.UnregisterAll()
EndIf
BakaPowerArmorStorage.ShowNotification(-1)
BakaPowerArmorStorage.CreateToken(akTargetRef)
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_Entry_01
Function Fragment_Entry_01(ObjectReference akTargetRef, Actor akActor)
;BEGIN CODE
BakaPowerArmorStoragePlacedScript PlacedForm = akTargetRef as BakaPowerArmorStoragePlacedScript
If (PlacedForm)
    PlacedForm.UnregisterAll()
EndIf
BakaPowerArmorStorage.RemoveScript(akTargetRef)
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_Entry_02
Function Fragment_Entry_02(ObjectReference akTargetRef, Actor akActor)
;BEGIN CODE
BakaPowerArmorStorage.AttachScript(akTargetRef)
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment
