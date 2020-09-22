{
  "targets": [
    {
    	"target_name": "NodeSDL",
    	"sources": [
			"src/NodeSDL.cpp",
			"src/Window.cpp"
		],
		"include_dirs" : [
			"<!(node -e \"require('nan')\")"
		],
		"libraries": ["-lSDL2"]
    }
  ]
}