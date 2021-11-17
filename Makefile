# Flags
NAME?="AwesomeEngineTestCompile"
OTHER?="inputFileName"
PR="Aws_"

compile:
	clear
	echo ">-- Compiling engine --<"
	echo "Executable file name (NAME= to change): ${NAME}"
	echo "Other files compiling with engine (OTHER= to change): ${OTHER}"
	echo ""

	g++ -o ${NAME} src/Window/${PR}Window.cpp src/Buffers/${PR}Buffer.cpp src/Square/${PR}Square.cpp src/Cube/${PR}Cube.cpp src/Camera/${PR}Camera.cpp src/BatchRenderer/${PR}BatchRenderer.cpp ${OTHER} -lGL -lGLEW -lglut -lglfw -lpthread

	echo ">-- Compilation end --<"

	./${NAME}

.SILENT: