@tool
extends Control

@export var test:bool:
	set(val):
		print(get_tree().root)
