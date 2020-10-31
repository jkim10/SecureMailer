#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <regex>
using namespace std;

void skipToNextMessage(string errorMessage){
    string line;
    std::cerr << errorMessage  << std::endl;
    while (getline(cin, line))
    {
        if(line == "."){
            break;
        }
    }
}
string toLower(string str){
    string newString = str;
    transform(newString.begin(), newString.end(), newString.begin(), ::tolower);
    return newString;
}

string get_username(string str){
    unsigned first = str.find("<");
    unsigned second = str.find(">");
    string username = str.substr(first+1,second-first-1);
    return username;
}
int main() {
    string line;
    while (getline(cin, line))
    {
        //Look for MAIL Header (if not, we exit)
        string sender_h = line;
        string sender;
        if(toLower(sender_h).rfind("mail from:",0) == 0){
            sender = get_username(sender_h);
            string mailbox_path = "./mail/" + sender;
            struct stat info;
            if ((stat(mailbox_path.c_str(), &info)) != 0){
                std::cerr << "Could not find the username (" + sender + "). Will continue..."  << std::endl;
            }else if ( info.st_mode & S_IFDIR){}
            else{
                std::cerr << "Could not find the username (" + sender + "). Will continue..."  << std::endl;
            }
        } else{skipToNextMessage("Expecting 'MAIL FROM:' control line. Skipping Message..."); continue;}
        
        //Parse Recipients
        string recips_h;
        string recips = " ";
        while(getline(cin,recips_h)){
            if(toLower(recips_h) == "data") {break;}
            if(toLower(recips_h).rfind("rcpt to:",0) == 0){
                recips += get_username(recips_h);
                recips += "> ";
            } else{skipToNextMessage("Expecting 'RCPT TO:' control line. Skipping Message"); continue;}
        }

        //DATA
        string body_l;
        string body;
        while(getline(cin,body_l)){
            if(body_l == "."){break;}
            if(body_l.rfind("..",0) == 0){
                body += body_l.substr(1);
            } else {body += body_l;}
            body += "\n";
        }
        if(body_l != "."){
            skipToNextMessage("Expecting '.' to end the message. Skipping Message");
            continue;
        }

        //Format "FROM" Line
        string from_line = "From: " + sender;

        //Format "TO" Line
        string to_line = "To:" + recips.substr(0,recips.length()-2);
        replace(to_line.begin(),to_line.end(),'>',',');

        //Message to Send
        string full_message = from_line + '\n' + to_line + '\n' + body;

        stringstream r(recips);
        string send_to;
        while(getline(r,send_to,'>')){
            if (send_to.length() == 1) {continue;}
            int fd[2];
            pid_t p;
            if (pipe(fd) == -1) {
                fprintf(stderr, "Pipe Failed\n");
                return 1;
            }

            p = fork();
            if (p < 0) {
                fprintf(stderr, "Fork Failed\n");
                return 1;
            }
            else if (p == 0) {
                // Child process
                close(fd[1]);  // Close the writing end of the pipe
                close(STDIN_FILENO);  // Close the current stdin
                dup2(fd[0], STDIN_FILENO);  // Replace stdin with the reading end of the pipe
                execl("./bin/mail-out", "./bin/mail-out", send_to.substr(1).c_str(), NULL);  // Invoke mail-out
            }
            else {
                // Parent process
                int status;
                close(fd[0]);  // Close the reading end of the pipe
                write(fd[1], full_message.c_str(), full_message.length());
                close(fd[1]);
                p = wait(&status);
                switch(WEXITSTATUS(status)){
                    case 2:
                        std::cerr << "Could not find the recipient: " + send_to.substr(1)  << std::endl;

                }
            }
        }
    }
    
    return 0;
}