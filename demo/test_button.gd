@tool
extends Control

@export var test:bool:
	set(val):
		f(EditorInterface.get_editor_main_screen())

func f(node:Node):
	if node is Control:
		node.visible = true
	for child in node.get_children():
		f(child)
