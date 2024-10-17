CC = g++
CFLAGS = -std=c++11 -g3 -O3 -pthread

VAL_CLNT_SRC = Validation/Authentication.cpp Validation/ArgsValidity.cpp
MAIN_CLNT_SRC = Client/Client.cpp Client/PackageReciever.cpp
VAL_SRVR_SRC = Validation/Authentication.cpp Validation/ArgsValidity.cpp Validation/FileIntegrity.cpp
MAIN_SRVR_SRC = Vector.cpp KNN.cpp Server/Server.cpp Server/ClientHandler.cpp
CMD_SRC = Commands/Command.cpp Commands/MenuCommand.cpp Commands/UploadCommand.cpp Commands/SettingsCommand.cpp Commands/ClassifyCommand.cpp Commands/DisplayCommand.cpp Commands/DownloadCommand.cpp Commands/ExitCommand.cpp
IO_SRC = IO/FileIO.cpp IO/SocketIO.cpp IO/StandardIO.cpp

CLNT_OBJ = $(VAL_CLNT_SRC:.cpp=.o) $(MAIN_CLNT_SRC:.cpp=.o) $(IO_SRC:.cpp=.o)
SRVR_OBJ = $(VAL_SRVR_SRC:.cpp=.o) $(MAIN_SRVR_SRC:.cpp=.o) $(CMD_SRC:.cpp=.o) $(IO_SRC:.cpp=.o)

CLNT_EXEC = Client/Client.out
SRVR_EXEC = Server/Server.out

CLNT_INCL = -I Headers/Client_Headers -I Headers/Validation_Headers -I Headers/IO_Headers -I Headers
SRVR_INCL = -I Headers/Server_Headers -I Headers/Validation_Headers -I Headers/Commands_Headers -I Headers/IO_Headers -I Headers

all: $(CLNT_EXEC) $(SRVR_EXEC)

$(CLNT_EXEC) : $(CLNT_OBJ)
	$(CC) $(CLNT_OBJ) -o $(CLNT_EXEC) $(CFLAGS) $(CLNT_INCL)

$(SRVR_EXEC): $(SRVR_OBJ)
	$(CC) $(SRVR_OBJ) -o $(SRVR_EXEC) $(CFLAGS) $(SRVR_INCL)

%.o: %.cpp
	$(CC) $(CFLAGS) $(CLNT_INCL) $(SRVR_INCL) -c $< -o $@

clean:
	rm -rf Server/*.o Client/*.o Validation/*.o IO/*.o Commands/*.o *.o Server/Server.out Client/Client.out
