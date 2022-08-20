/*
https://gitlab.com/gitlab-org/gitlab
https://git.uwaterloo.ca/ece650-f2021/cpp
 */

#include<iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include<vector>
#include <signal.h>
#include<cstring>
using namespace std;

int inputforA3(void) {
    while (!cin.eof()) {
        string line;
        getline(cin, line);
        if (line.size () > 0)
        {
            cout << line << endl;
        }
    }
    return 0;
}
void generating_s_l_n_c(int argc,char* arguement_array[],int *s,int* l, int *n,int *c)
{


    for(int i=1;i<argc;i+=2)
    {

        if(strcmp(arguement_array[i],"-s")==0)
        {
            *s=atoi(arguement_array[i+1]);
            if (*s<2)
            {
                cerr<<"Error: s value is less than 2"<<endl;
                exit(1);
            }


        }
        if(strcmp(arguement_array[i],"-l")==0)
        {
            *l=atoi(arguement_array[i+1]);

            if (*l<5)
            {
                cerr<<"Error: l value less than 5"<<endl;
                exit(1);
            }

        }
        if(strcmp(arguement_array[i],"-n")==0)
        {
            *n=atoi(arguement_array[i+1]);

            if(*n<1)
            {
                cerr<<"Error: n value less than 1"<<endl;
                exit(1);
            }

        }
        if(strcmp(arguement_array[i],"-c")==0)
        {
            *c=atoi(arguement_array[i+1]);

            if(*c<1)
            {
                cerr<<"Error: c value less than 1"<<endl;
                exit(1);
            }

        }
    }

}


int main(int argc, char* argv[])
{

        int s,l,n,c;
        generating_s_l_n_c(argc,argv,&s,&l,&n,&c);
    
        int rgentoA1[2],A1toA2[2];
        vector<pid_t> kids;
        pipe(rgentoA1);
        pipe(A1toA2);

        pid_t child_pid;
        child_pid=fork();
       
        if(child_pid==0)
        {
                dup2(rgentoA1[1],STDOUT_FILENO);
                close(rgentoA1[0]);
                close(rgentoA1[1]);

                int x=execv("./rgen",argv);

                if(x==-1)
                {
                        return -1;
                }
                return x;
        }


        else if(child_pid<0)
        {
                cerr<<"Error: could not fork\n";
                return 1;
        }

        kids.push_back(child_pid);

        child_pid=fork();
        if(child_pid==0)
        {
        dup2(rgentoA1[0],STDIN_FILENO);
        close(rgentoA1[1]);
        close(rgentoA1[0]);
        dup2(A1toA2[1],STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
                       

        char *argv1[3];
        argv1[0] = (char *)"python3";
        argv1[1] = (char *)"ece650-a1.py";
        argv1[2] = nullptr;
        int y=execvp("python3", argv1);


        
        if(y==-1)
        {
                return -1;
        }
        return y;
        }
        else if(child_pid<0)
        {
                cerr<<"Error: could not fork\n";
                return 1;
        }
        kids.push_back(child_pid);

        child_pid=fork();
        if(child_pid==0)
        {
        dup2(A1toA2[0],STDIN_FILENO);
        close(A1toA2[1]);
        close(A1toA2[0]);
                       

        int z=execv("./ece650-a2",argv);
                        
        if(z==-1)
        {
                return -1;
        }
        return z;
        }


        else if(child_pid<0)
        {
        cerr<<"Error: could not fork\n";
        return 1;
}
        kids.push_back(child_pid);
        


        dup2(A1toA2[1],STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
            

                while (!cin.eof()) {
        string line;
        getline(cin, line);
        if(cin.eof()){

            for (pid_t k : kids) {
                int status;
                kill (k, SIGTERM);          // kill signal to all children
                waitpid(k, &status, 0);
            }
            return 0;
        }
        cout << line << endl;
        cout.flush();
    }
    return 0;

}
