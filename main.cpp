// Main source file
/* Authors:
    James Armstrong,
    Minh-Hieu Le,
    Ethan Lee
    Julian Hernandez,
    Devesh Naidu,
    Pratham Saldhi
*/

#include <iostream>
#include <string>
#include <pthread.h>
#include <stdio.h>
#include <sstream>
#include <cstring>


using namespace std;

// EXAMPLE THREAD FUNCTION, WILL BE CALLED BY pthread_create()
void *threadDummyFunc(void *arg)
{
    string *str = (string *)arg;
    std::cout << "dummy function\n";
    std::cout << "argument 1 passed: " << str[0] << endl;

    pthread_exit(0);
}

void *path(void *arg)
{
    std::cout << "Printing path env\n";
    system("echo \"$PATH\"");
    pthread_exit(0);
}

void *notepad(void *arg)
{
    std::cout << "Launching text editor\n";
    system("nano");
    pthread_exit(0);
}

void *vol(void *arg)
{
    std::cout << "Volume information\n";
    system("lsblk");
    pthread_exit(0);
}

void *ping(void *arg)
{
    string *str = (string *)arg;
    std::cout << "Ping statistics\n";
    const char* address = str[0].c_str();
    char cmd[256];
    strcpy(cmd, "ping -c 4 ");
    strcat(cmd, address);
}

void *dir(void *arg)
{
    std::cout << "Files in current working directory\n";
    system("dir");
    pthread_exit(0);
}

void *echo(void *arg)
{
    string *str = (string *)arg;
    std::cout << "Server says:\n";
    const char *arg1 = str[0].c_str();
    const char *arg2 = str[1].c_str();
    const char *arg3 = str[2].c_str();
    const char *arg4 = str[3].c_str();
    char cmd[256];
    strcpy(cmd, "echo ");
    strcat(cmd, arg1);
    strcat(cmd, " ");
    strcat(cmd, arg2);
    strcat(cmd, " ");
    strcat(cmd, arg3);
    strcat(cmd, " ");
    strcat(cmd, arg4);
    system(cmd);
    pthread_exit(0);
}

void *tasklist(void *arg)
{
    std::cout << "All the task running currently \n";
    system("tasklist");
    pthread_exit(0);
}


void *color(void *arg)
{
    string *str = (string *)arg;
    std::cout << "Select the color\n";
    const char *arg1 = str[0].c_str();
    const char *arg2 = str[1].c_str();

    char cmd[256];
    strcpy(cmd, "color ");
    strcat(cmd, arg1);
    strcat(cmd, " ");
    strcat(cmd, arg2);
    strcat(cmd, " ");
    system(cmd);
    pthread_exit(0);
}

int main()
{
    string *args = new string[4];
    while (1)
    {
        string cmd;

        cout << "Enter command: ";
        getline(cin, cmd);

        std::cout << "Enter at most 4 arguments separated with spaces: ";
        string input;
        getline(cin, input);

        // Parse input and place arguments in the args array
        istringstream ss(input);
        string w;
        int i = 0;
        while (ss >> w)
        {
            args[i] = w;
            i++;
        }

        pthread_t thread;
        int error;
        if (cmd == "dummy")
            error = pthread_create(&thread, NULL, &threadDummyFunc, args);
        // Print system enviroment PATH
        else if (cmd == "path")
            error = pthread_create(&thread, NULL, &path, NULL);
        // Launch a text editor
        else if (cmd == "notepad")
            error = pthread_create(&thread, NULL, &notepad, NULL);


        else if (cmd == "vol")
                    error = pthread_create(&thread, NULL, &vol, NULL);

        else if (cmd == "ping")
                    error = pthread_create(&thread, NULL, &ping, args);

        else if (cmd == "dir")
            error = pthread_create(&thread, NULL, &dir, NULL);

        else if (cmd == "echo")
            error = pthread_create(&thread, NULL, &echo, args);
        
        else if (cmd == "color")
            error = pthread_create(&thread, NULL, &color, NULL);
        
        else if (cmd == "tasklist")
            error = pthread_create(&thread, NULL, &color, NULL);

        /*
                        else if (cmd == "help")
                            error = pthread_create(&thread, NULL, &help, NULL);

                        else if (cmd == "color")
                            error = pthread_create(&thread, NULL, &color, NULL);

                        else if (cmd == "path")
                            error = pthread_create(&thread, NULL, &path, NULL);

                        else if (cmd == "notepad")
                            error = pthread_create(&thread, NULL, &notepad, NULL);
                */

        if (error)
            cout << "Failed to create thread\n";
        else
            cout << "Thread created\n";

        // Wait for thread to stop
        pthread_join(thread, NULL);
    }
    return 0;
}
