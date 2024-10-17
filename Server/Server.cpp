
#include "ServerHeaders.h"
#include "ClientHandler.h"


int main(int argc, char *argv[]) {

    if(argc != 2) {
        printArgsErr();
        return 1;
    }
    list<string> ls;
    ls.push_back(argv[1]); 
    if(!isDouble(ls)) {  
        cout << "Invalid input." << endl; 
        return 1;
    }
    const int portNum = stoi(argv[1]); 
    if(portNum < 1025 || 65536 < portNum) {
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
    sin.sin_addr.s_addr = INADDR_ANY; 
    sin.sin_port = htons(portNum); 
    if(bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) { 
        perror("Failed to bind socket.");
        return 1;
    }      
        if(listen(sock, 5) < 0) { // check if succeeded to listen to outer connections
            perror("Listening to socket failed.");
            close(sock);
            return 1;
        }
       

        while(true) {
            struct sockaddr_in clientSin; 
            unsigned int lenClientSin = sizeof(clientSin);
            int clientSock = accept(sock, (struct sockaddr *) &clientSin, &lenClientSin);  
            if (clientSock < 0) {
                perror("Failed to accept client");
                continue;
            }
            // handleClinet(clientSock);
            thread t(handleClinet, clientSock);
            t.detach();
        }    

    close(sock); // close the socket of the server
    return 0;
}