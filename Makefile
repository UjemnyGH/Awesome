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

	g++ -o ${NAME} src/Buffers/${PR}Buffer.cpp ${OTHER} -ldl -lGL -lGLEW -lglut -lglfw -lpthread -lsfml-system -lsfml-audio
#src/BatchRenderer/${PR}BatchRenderer.cpp
	echo ">-- Compilation end --<"

	./${NAME}

.SILENT: