#staticFileServer01() 
staticFileServer01: main.c \
	tcp/configureHints/configureHints.o \
	tcp/gai/gai.o \
	tcp/getSocketFD/getSocketFD.o \
	tcp/registerSigHandler/registerSigHandler.o \
	tcp/listenLoop/listenLoop.o \
	http/handleClient/handleClient.o \
	http/recvReq/recvReq.o \
	http/handleFileGet/handleFileGet.o \
	http/parseGetUri/parseGetUri.o \
	http/checkNameIsValid/checkNameIsValid.o \
	http/checkNameHasPeriod/checkNameHasPeriod.o \
	http/notFound404/notFound404.o \
	http/sendTextFile/sendTextFile.o \
	http/sendBinaryFile/sendBinaryFile.o \
	http/end/end.o 
	gcc -Wall -Wextra -o staticFileServer01 \
		main.c \
		tcp/configureHints/configureHints.o \
		tcp/gai/gai.o \
		tcp/getSocketFD/getSocketFD.o \
		tcp/registerSigHandler/registerSigHandler.o \
		tcp/listenLoop/listenLoop.o \
		http/handleClient/handleClient.o \
		http/recvReq/recvReq.o \
		http/handleFileGet/handleFileGet.o \
		http/parseGetUri/parseGetUri.o \
		http/checkNameIsValid/checkNameIsValid.o \
		http/checkNameHasPeriod/checkNameHasPeriod.o \
		http/notFound404/notFound404.o \
		http/sendTextFile/sendTextFile.o \
		http/sendBinaryFile/sendBinaryFile.o \
		http/end/end.o 

#configureHints()
configureHints.o: tcp/configureHints/configureHints.c
	cd tcp/configureHints && gcc -Wall -Wextra -c configureHints.c

#gai()
gai.o: tcp/gai/gai.c
	cd tcp/gai && gcc -Wall -Wextra -c gai.c

#getSocketFD()
getSocketFD.o: tcp/getSocketFD/getSocketFD.c
	cd tcp/getSocketFD && gcc -Wall -Wextra -c getSocketFD.c

#registerSigHandler()
registerSigHandler.o: tcp/registerSigHandler/registerSigHandler.c
	cd tcp/registerSigHandler && gcc -Wall -Wextra -c registerSigHandler.c

#listenLoop()
listenLoop.o: tcp/listenLoop/listenLoop.c
	cd tcp/listenLoop && gcc -Wall -Wextra -c listenLoop.c

#handleClient()
handleClient.o: http/handleClient/handleClient.c
	cd http/handleClient && gcc -Wall -Wextra -c handleClient.c 

#recvReq()
recvReq.o: http/recvReq/recvReq.c
	cd http/recvReq && gcc -Wall -Wextra -c recvReq.c

#handleFileGet()
handleFileGet.o: http/handleFileGet/handleFileGet.c
	cd http/handleFileGet && gcc -Wall -Wextra -c handleFileGet.c

#parseGetUri()
parseGetUri.o: http/parseGetUri/parseGetUri.c
	cd http/parseGetUri && gcc -Wall -Wextra -c parseGetUri.c

#checkNameIsValid()
checkNameIsValid.o: http/checkNameIsValid/checkNameIsValid.c
	cd http/checkNameIsValid && gcc -Wall -Wextra -c checkNameIsValid.c

#checkNameHasPeriod()
checkNameHasPeriod.o: http/checkNameHasPeriod/checkNameHasPeriod.c
	cd http/checkNameHasPeriod && gcc -Wall -Wextra -c checkNameHasPeriod.c

#notFound404()
notFound404.o: http/notFound404/notFound404.c
	cd http/notFound404 && gcc -Wall -Wextra -c notFound404.c 

#sendTextFile()
sendTextFile.o: http/sendTextFile/sendTextFile.c
	cd http/sendTextFile && gcc -Wall -Wextra -c sendTextFile.c

#sendBinaryFile()
sendBinaryFile.o: http/sendBinaryFile/sendBinaryFile.c
	cd http/sendBinaryFile && gcc -Wall -Wextra -c sendBinaryFile.c

#end()
end.o: http/end/end.c
	cd http/end && gcc -Wall -Wextra -c end.c
clean: 
	rm staticFileServer01 \
		tcp/configureHints/configureHints.o \
		tcp/gai/gai.o \
		tcp/getSocketFD/getSocketFD.o \
		tcp/registerSigHandler/registerSigHandler.o \
		tcp/listenLoop/listenLoop.o \
		http/handleClient/handleClient.o \
		http/recvReq/recvReq.o \
		http/handleFileGet/handleFileGet.o \
		http/parseGetUri/parseGetUri.o \
		http/checkNameIsValid/checkNameIsValid.o \
		http/checkNameHasPeriod/checkNameHasPeriod.o \
		http/notFound404/notFound404.o \
		http/sendTextFile/sendTextFile.o \
		http/sendBinaryFile/sendBinaryFile.o \
		http/end/end.o 
