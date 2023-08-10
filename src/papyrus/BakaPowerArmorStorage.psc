Scriptname BakaPowerArmorStorage extends ScriptObject Native

{ Create a Power Armor Token from a given Power Armor Frame Furniture Reference, returns True if successful }
bool Function CreateToken(ObjectReference akPAFrame) Native Global

{ If the passed Power Armor Token is valid, start the Workshop to place down the corresponding Frame, returns True if successful }
bool Function HandleToken(ObjectReference akPAToken) Native Global

{ Attach BakaPowerArmorStoragePlacedScript data to a placed Power Armor Frame Furniture, returns True if successful }
bool Function AttachScript(ObjectReference akPAFrame) Native Global

{ Remove BakaPowerArmorStoragePlacedScript data from a placed Power Armor Frame Furniture, returns True if successful }
bool Function RemoveScript(ObjectReference akPAFrame) Native Global

{ Display a notification showing how much time remains for a placed frame before recall }
Function ShowNotification(int aiTimeRemaining) Native Global

{ Update values from MCM settings files. }
Function UpdateSettings() Native Global
