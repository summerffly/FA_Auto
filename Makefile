
source = global.h advanced_CMD.h FBric_operator.h FA_tool.h FA_itfX.h FA_Automator.cpp

FA_Auto: $(source)
	g++ -o FA_Auto FA_Automator.cpp

FA_VeX.o: FA_VeX.cpp
	g++ -c FA_VeX.cpp

.PHONY:clean
clean:
	rm FA_Auto
