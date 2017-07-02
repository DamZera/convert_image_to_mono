all: ConvertMono
	
test: tProcess

ConvertMono: ConvertMono.o
	g++ ConvertMono.o -o ConvertMono -lopencv_core -lopencv_highgui -lopencv_imgproc

ConvertMono.o: ./src/ConvertMono.C
	g++ ./src/ConvertMono.C -c

tProcess: tProcess.o
	g++ tProcess.o -o tProcess -lopencv_core -lopencv_highgui -lopencv_imgproc

tProcess.o: ./tests/tProcess.C
	g++ ./tests/tProcess.C -c

clean:
	rm -rf *.o
mrproper: clean
	rm -rf tJpegToPpm