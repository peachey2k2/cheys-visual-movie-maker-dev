@tool
extends CenterContainer

@onready var svc: SubViewportContainer = $SubViewportContainer

func _ready() -> void:
	resized.connect(_resized)

func _resized():
	return
	#scale = Vector2.ONE * (size.x/svc.size.x)
	#print(scale, " ", Vector2.ONE * (size.x/svc.size.x))
	#print(":)")

func _set(property: StringName, value: Variant) -> bool:
	print(property)
	if property == "size":
		scale = Vector2.ONE * (value.x/svc.size.x)
		print("hey")
		return true
	return false
