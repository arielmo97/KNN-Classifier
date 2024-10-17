# KNN classifier server
In this assignment, I took the classifier server and the client and added a commands based interaction between them using the **Command** design pattern. The interaction itself is done through a command menu which is prompted to the user on the client side.

## Implementation:
In this project, I implemented an abstract class called `Command` which is the base class of all the command classes.
In addition, since the I/O is initiated differently through the commands, I implemented another abstrcat class called `DefaultIO`.


### Commands classes
This is the `Command` base class:
```c++
class  Command {

public:
virtual  void  execute() =  0;
virtual  string  getDescription();
virtual  void  setNewK(int);
virtual  void  setNewMetric(string);
virtual  int  getK();
virtual  string  getDistanceMetric();
void  setDIO(DefaultIO*);

protected:
string  description;
int  K  =  5;
string  distanceMetric  =  "AUC";
DefaultIO*  dio;
vector<tuple<Vector, string>>  trainData;
vector<Vector>  testData;

};
```
The base class has its default members which will derive to the subclasses of the class. Note the only the `execute()` method is pure virtual and implemented differently in each subclass. The `setNewK()` and `setNewMetric()` methods are not pure virtual since they are implemented only by one subclass of `Command`. Since the rest of the methods have the exact same behavior in all the sublclasses, they were implemented in the base class and overrided by the subclasses. 
For further information, check out the source code of `Command` class and its subclasses.

### DefaultIO classes:
In this project, I implemented an abstract class called `DefaultIO`  which is the base class of all the I/O subclasses.
This abstract base class is in charge of the I/O of the entire program. In this case, the I/O can be:
1. Reading from the screen as an input from the user and writing to the screen as an output to the user.
2. Reading from file to extract data from it and writing to a file to update/create data.
3. Reading data from a TCP socket in order to recieve data and writing data to a TCP socket in order to send data.

This is the DefaultIO base class:
```c++
class  DefaultIO {

public:
virtual  string  read() =  0;
virtual  void  write(string) =  0;
virtual  void  setFilePath(string) =  0;
};
```
As can be seen, all the methods in `DefaultIO` class are pure virtual and implemented differently in each subcalss. For further information, check out the source code of `DefaultIO` class and its subclasses.

## Program flow:
When a user connects to the KNN classifier server, he is prompted with the menu:
```
Welcome to the KNN classifier server. Please choose an option:
1. upload unclassified csv data file
2. algorithm settings
3. classify data
4. display results
5. download results
8. exit
```
#### Option 1 - upload unclassified csv data file:
When choosing this option, the user is asked to upload a local train data in order to allow the server to learn the data he recieved. Once the train data is uploaded, the user will be asked to upload a test data of vectors - these vectors will be classified by the server when asked to.

#### Option 2 - algorithm settings:
When choosing this option, the user is prompted with the current algorithm parameters. The default parameters are `K = 5`, `distanceMetric = "AUC"`. If the user wants, he can modify these settings by just typing the values for each parameter. Note that if the user tries to modify the parameter by passing invalid arguments, the setting will not be updated and an error message will be displayed.

#### Option 3 - classify data:
When choosing this option, the server will classify all the vectors in the train data file based on the algorithm settings and the test data. **Pay attention to the following scenarios**:
1. Test and train data files were not uploaded by the user.
2. The value of `K` parameter of the algorithm is bigger than the number of vectors in the train data file.

If any of the above happens, the server will not classify the data and an error message will be prompted to the user.

#### Option 4 - display results:
When choosing this option, the server will send back to the user the classification results and they will be displayed on the users screen. **Pay attention to the following scenarios**:
1. Test and train data files were not uploaded by the user.
2. The test data was not classified by the server.

If any of the above happens, the server will not send the results and an error message will be prompted to user.

#### Option 5 - download results:
When choosing this option, The user will be asked to specify a path to the file he wants data to be downloaded to. After passing the file location, the server will send back to the user the classified results. After the results were sent, they will be written to a file on a different thread on the client side. **Pay attention to the following scenarios**:
1.  Test and train data files were not uploaded by the user.
2. The test data was not classified by the server.

If any of the above happens, the server will not send the results and an error message will be prompted to user.

#### Option 8 - exit:
When choosing this option, the server will detach the user from service and earese all the data that was transmitted between them through the interaction and the program on the client side will be terminated.

#### Important notes - READ BEFORE LAUNCHING THE PROGRAM:
In every time through the intercation between the client and the server, when the user is asked to provide a path to a file (i.e in option 1 and option 5), the user **has to specify the FULL PATH of the file and NOT a relative path!**
for example, when specifying the path of the file that user wants the results to be downloaded to, the correct way to do that is:
```
/u/students/moshaya/AP1-Ass4/Client/Test_Results.csv
```
and **NOT**:
```
/Client/Test_Results.csv
```
If you are not sure what is the full path to the directory of the file you wish to work with, navigate to that directory and once you are inside it, run the command `pwd` in the terminal. The full path of the directory you are currently located in will be displayed in the terminal.

## Compile and run:
I provided a Makefile in the project in order to build it and create executables for both the server and the client. Just follow these steps:
1. Download the projects files to an empty directory on your computer.
2. Open the terminal and navigate to the directory where the downloaded project files reside.
3. Run the command `make`.
4. After running the command, you will notice that inside the Client folder, an executable `Client.out` was created - this is the executable to run the Client side program. Inside the Server folder, an executable `Server.out` was created - this is the executable to run the Server side program.
5. Run the server first - In the terminal, navigate to the directory where `Server.out` resides and type the following command: 
```./Server.out port_num ``` 
where `port_num` is the number of the port you want to bind the server to.
7. After runnuning the server, you can run the client program - In the terminal, navigate to the directory where `Client.out` resides and type the following command:
```./Client.out ip_num port_num ```
where `ip_num` is the IP address of the server and `port_num` is the port that the server was binded to.
