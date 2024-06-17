extends Tree


func _ready():
	var root = create_item()
	root.set_text(0, "root")
	var child1 = create_item(root)
	child1.set_text(0, "child1")
	var child2 = create_item(root)
	child2.set_text(0, "child2")
	child2.add_button(0, preload("res://icon.svg"))
	var subchild1 = create_item(child1)
	subchild1.set_text(0, "Subchild1")

