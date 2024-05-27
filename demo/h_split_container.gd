extends HSplitContainer

@onready var center_container: CenterContainer = $CenterContainer

#func _ready() -> void:
	#dragged.connect(_dragged)

#func _dragged(offset:int):
	#if offset < center_container.size.x:
		#center_container.scale = Vector2.ONE * center_container.size.x
	#print(offset)

func _set(property: StringName, value: Variant) -> bool:
	if property == "split_offset":
		if value < center_container.size.x:
			center_container.scale = Vector2.ONE * value/center_container.size.x
		print(value)
	return false
