# Flags
NAME?="AwesomeEngineTestCompile"
PR="Aws_"

compile:
	clear
	echo ">-- Compiling engine --<"
	echo "Executable file name (NAME= to change): ${NAME}"
	echo ""

	g++ -o ${NAME} src/Window/${PR}Window.cpp src/Buffers/${PR}Buffer.cpp src/Square/${PR}Square.cpp template.cpp -lGL -lGLEW -lglut -lglfw -lpthread

	echo ">-- Compilation end --<"

	./${NAME}

.SILENT: