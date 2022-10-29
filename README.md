# godot-ai

AI module for Godot 4.

# Download

AI module need to be compiled with Godot. So you need to clone Godot, then clone this repo to godot/modules/ai.

```bash
$ git clone https://github.com/godotengine/godot.git
$ git clone https://github.com/kdada/godot-ai.git godot/modules/ai
```

# Build

Godot's build system automatically involves this module and builds it into Godot editor or template.

```bash
$ cd godot
$ scons platform=windows target=editor optimize=debug debug_symbols=true
```


