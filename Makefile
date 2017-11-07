
Header = global.h advanced_CMD.h
TriLayer = FBric_operator.h FA_tool.h FA_itfX.h

FA_Auto: $(Header) $(TriLayer) FA_Automator.cpp
	g++ -o ../FA_Auto FA_Automator.cpp

.PHONY:clean
clean:
	rm ../FA_Auto
