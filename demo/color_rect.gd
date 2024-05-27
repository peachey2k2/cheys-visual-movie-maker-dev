extends Control

@onready var svc: SubViewportContainer = $"../../../CanvasLayer/SubViewportContainer"

func _ready() -> void:
	get_parent().resized.connect(_update_svc)

func _update_svc():
	svc.position = position
	svc.scale = Vector2.ONE * size/svc.size
