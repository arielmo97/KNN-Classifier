#include "ClientHeaders.h" 
#include "PackageReciever.h"




/// @brief main function of the client side
/// @param argc 
/// @param argv 
/// @return int
int main(int argc, char* argv[]) { 

    if(!argsLength(argc, 2)) { 
        printArgsErr();
        return 1;
    } 
    const char* ipAddr = argv[1];
    const int portNum = stoi(argv[2]); 
    if(portNum < 1025 || 65536 < portNum) { // check if port number is in legal range
        perror("Invalid input.");
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0); 
    if(sock < 0) {
        perror("Failed to create socket.");
        return 1;
    }
    struct sockaddr_in sin; 
    memset(&sin, 0, sizeof(sin)); 
    sin.sin_family = AF_INET; 
    sin.sin_addr.s_addr = inet_addr(ipAddr); 
    sin.sin_port = htons(portNum); 
    if(connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) { 
        perror ("Failed to connect to server.");
        close(sock); 
        return 1;
    }



    
    map<DIOS, DefaultIO*> dios;
    vector<string> dwnldRslts;
    initIODescriptors(dios, sock);
    string userInput, serverAns;
    bool connected = true;
    thread t;
    while (connected) {
        dios[_STD_]->write(dios[_SOK_]->read()); // prompt menu
        userInput = dios[_STD_]->read(); // user chooses option
        dios[_SOK_]->write(userInput); // user input being sent to server
        serverAns = dios[_SOK_]->read(); // get answer about input validity from server
        if (serverAns == "Invalid input") {
            dios[_STD_]->write(serverAns);
            continue;
        }
        switch (serverAns[0]) {
            case '1':
                uploadRequest(dios);
                continue;


            case '2':
                settingsRequest(dios);
                continue;


            case '3':
                classifyRequest(dios);
                continue;


            case '4':
                displayRequest(dios);
                continue;


            case '5':
                if (isReadyToDWNLD(dios)) {
                    downloadRequest(dios, dwnldRslts);
                    string filePath;
                    dios[_STD_]->write("please enter path to download results");
                    filePath = dios[_STD_]->read();
                    t = thread(writeToFile, ref(dios), ref(dwnldRslts), filePath);
                    t.detach();
                }
                continue;
            

            case '8':
                exitRequest(dios);
                connected = false;
                break;
        }
    }
    close(sock);
    return 0;
}
