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

	g++ -o ${NAME} src/Buffers/${PR}Buffer.cpp src/imgui/imgui_demo.cpp src/imgui/imgui_draw.cpp src/imgui/imgui_impl_glfw.cpp src/imgui/imgui_impl_opengl3.cpp src/imgui/imgui_tables.cpp src/imgui/imgui_widgets.cpp src/imgui/imgui.cpp ${OTHER} -ldl -lGL -lGLEW -lglut -lglfw -lpthread -lsfml-system -lsfml-audio
#src/BatchRenderer/${PR}BatchRenderer.cpp
	echo ">-- Compilation end --<"

	./${NAME}

.SILENT: