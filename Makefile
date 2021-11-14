# Flags
NAME?="AwesomeEngineTestCompile"
PR="Aws_"

compile:
	clear
	echo ">-- Compiling engine --<"
	echo "Executable file name (NAME= to change): ${NAME}"
	echo ""

	g++ -o ${NAME} src/Window/${PR}Window.cpp src/Buffers/${PR}Buffer.cpp src/Square/${PR}Square.cpp src/Cube/${PR}Cube.cpp src/Camera/${PR}Camera.cpp template.cpp -lGL -lGLEW -lglut -lglfw -lpthread

	echo ">-- Compilation end --<"

	./${NAME}

.SILENT: