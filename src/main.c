#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf[4096];
	int status;
	while (fgets(buf, 4096, stdin)) {
	    // scenario 1
		if (strncmp(buf, "pwd", 3) == 0) {
      			pid_t pid = fork();

		if (pid == -1) {
			fprintf(stderr, "Error occured during process creation\n");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			char working_directory_name[4096];
			getcwd(working_directory_name, 4096);

			printf("%s\n", working_directory_name);
			fflush(stdin);
			exit(EXIT_SUCCESS);
		} else {
			fflush(stdin);
			waitpid(pid, &status, 0);
		}
	} else if (!strncmp(buf, "/bin", 4)) {
      		char* path = strtok(buf, "\n");
      		char binBuf[4096];
      		strcpy(binBuf, path);
      		strtok(binBuf, "/");

      		char* command = strtok(NULL, "/");
      		command[strlen(command) - 1] = '\0';
     		 pid_t pid = fork();
      		if (pid == -1) {
        		fprintf(stderr, "Error occured during process creation\n");
        		exit(EXIT_FAILURE);
      		} else if (pid == 0) {
        		if(execl(path, command, NULL) == -1)
        		{
          			fprintf(stderr, "error: %s\n", path);
          			exit(EXIT_FAILURE);
        		}
      		} else {
        		waitpid(pid, &status, 0);
		}
    	} else if (!strncmp(buf, "~/", 2)) {
      		char full_path[4096];
      		char home_path[4096];
      		char current_path[4096];
      		getcwd(current_path, 4096);

      		char* input = strtok(buf, "\n");
      		for(int i = 1; i < strlen(input) + 1; i++)
      		{
        		input[i-1] = input[i];
      		}
      		strcat(full_path, "/");
      		strcat(full_path, strtok(current_path, "/"));
      		strcat(full_path, "/");
      		strcat(full_path, strtok(NULL, "/"));
      		strcat(full_path, input);
      		
		pid_t pid = fork();

      		if (pid == -1) {
        		fprintf(stderr, "Error occured during process creation\n");
			exit(EXIT_FAILURE);
      		} else if (pid == 0) {
        		if(execl(full_path, "course_sched", NULL) == -1)
        		{
          			fprintf(stderr, "error: %s\n", full_path);
          			exit(EXIT_FAILURE);
        		};
      		} else {
        		waitpid(pid, &status, 0);
      		}

    		} else if (!strncmp(buf, "cd", 2)) {
   	 	// scenario 2
      			char full_path[4096];
			full_path[0] = '\0';
      			char home_path[4096];
      			char current_path[4096];
		        getcwd(current_path, 4096);
      
      			strtok(buf, " ");
      			char* input = strtok(NULL, "\n");
      
			int i;
		        for(i = 1; i < strlen(input) + 1; i++)
      			{
        			input[i-1] = input[i];
      			}
      			strcat(full_path, "/");
      			strcat(full_path, strtok(current_path, "/"));
      			strcat(full_path, "/");
      			strcat(full_path, strtok(NULL, "/"));
      			strcat(full_path, input);
      			
			if (chdir(full_path) == -1)
      			{
        			fprintf(stderr, "change dir error: %s\n", full_path);
        			exit(EXIT_FAILURE);
      			}
    		} else if (!strncmp(buf, "make run", 8)) {
      			pid_t pid = fork();

      			if (pid == -1) {
        		fprintf(stderr, "Error occured during process creation\n");
        		exit(EXIT_FAILURE);
      			} else if (pid == 0) {
        			if(execl("/usr/bin/make", "make", "run", NULL) == -1)
        			{
          				fprintf(stderr, "make run error\n");
          				exit(EXIT_FAILURE);
        			};
      			} else {
        			waitpid(pid, &status, 0);
      			}
    		} else if (!strncmp(buf, "make test", 9)) {
     		// scenario 4
      			pid_t pid = fork();

      			if (pid == -1) {
        			fprintf(stderr, "Error occured during process creation\n");
        			exit(EXIT_FAILURE);
      			} else if (pid == 0) {
        			if(execl("/usr/bin/make", "make", "test", NULL) == -1)
        			{
          				fprintf(stderr, "make test error\n");
          				exit(EXIT_FAILURE);
        			};
      			} else {
        			waitpid(pid, &status, 0);
      			}
    		} else if (!strncmp(buf, "make", 4)) {
      			pid_t pid = fork();

      			if (pid == -1) {
        			fprintf(stderr, "Error occured during process creation\n");
        			exit(EXIT_FAILURE);
      			} else if (pid == 0) {
        			if(execl("/usr/bin/make", "make", NULL) == -1)
        			{
          				fprintf(stderr, "make error\n");
          				exit(EXIT_FAILURE);
        			};
      			} else {
        			waitpid(pid, &status, 0);
      			}

    		} else if (!strncmp(buf, "echo \"", 6)) {
    			// scenario 3
      			strtok(buf, " ");
      			char* input_str = strtok(NULL, "\"");
      			char* redirection = strtok(NULL, " ");
      			char* output_file = strtok(NULL, "\n");
      
      			pid_t pid = fork();

		        if (pid == -1) {
        			fprintf(stderr, "Error occured during process creation\n");
        			exit(EXIT_FAILURE);
      			} else if (pid == 0) {
        			char output_path[1024];
        			strcat(output_path, "./");
        			strcat(output_path, output_file);
       	 
        			close(1); // stdout을 닫음
        			
        			int fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 777);
        
        			if (fd == -1) {
          				fprintf(stderr, "file open failed\n");
          				exit(EXIT_FAILURE);
        			}
        
        			printf("%s", input_str);
				fflush(stdout);
        			close(0);
				close(1);
				close(2);
				exit(0);
      			} else {
        			wait(&status);
      			}

    		} else if (!strncmp(buf, "ls ", 3)) {
      			strtok(buf, " ");
      			strtok(NULL, " ");
      			char* output_file = strtok(NULL, "\n");
      
      			pid_t pid = fork();
			
      			if (pid == -1) {
        			fprintf(stderr, "Error occured during process creation\n");
        			exit(-1);
      			} else if (pid == 0) {

        			char output_path[1024];
        			strcat(output_path, "./");
        			strcat(output_path, output_file);

        			close(1); // stdout을 닫음

        			int fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 777);

        			if (fd == -1) {
          				fprintf(stderr, "file open failed\n");
          				exit(-1);
        			}
        			execl("/bin/ls", "ls", NULL);
        			exit(-1);
      			} else {
        			wait(&status);
      			}

    		} else if (!strncmp(buf, "grep ", 5)) {
      		  // grep 
      			strtok(buf, " ");
      			char* pattern = strtok(NULL, " ");
      			strtok(NULL, " ");
      			char* input_file = strtok(NULL, "\n");
    
      			pid_t pid = fork();

      			if (pid == -1) {
        			fprintf(stderr, "Error occured during process creation\n");
        			exit(EXIT_FAILURE);
      			} else if (pid == 0) {
        			char input_path[1024];
        			strcat(input_path, "./");
        			strcat(input_path, input_file);

        			close(0); // stdin을 닫음
			        int fd = open(input_path, O_RDONLY);
        			if (fd == -1) {
        	  			fprintf(stderr, "file open failed\n");
          				exit(EXIT_FAILURE);
        			}
				fflush(stdin);
        			// mac => /usr/bin/grep
        			// ubuntu => /bin/grep
        			if(execl("/bin/grep", "grep", pattern, NULL) == -1)
        			{
        				  fprintf(stderr, "grep error\n");
        				  exit(EXIT_FAILURE);
        			};
			} else {
        			wait(&status);
      			}

    		} else if (!strncmp(buf, "echo $PATH", 9)) {
      			char* pathvar = getenv("PATH");
      			printf("%s\n",pathvar);
		} else if (!strncmp(buf, "ls", 2)) {
                	pid_t pid = fork();
                	if (pid == -1) {
                	        fprintf(stderr, "Error occured during process creation\n");
                	        exit(EXIT_FAILURE);
                	} else if (pid == 0) {
                	        if(execl("/bin/ls", "ls", NULL) == -1)
                	        {
                	                fprintf(stderr, "ls error\n");
                	                exit(EXIT_FAILURE);
                        	}	
                	} else {
                	        waitpid(pid, &status, 0);
                	}
        	} else if (!strncmp(buf, "ready-to-score", 14)){
			pid_t pid = fork();
			if (pid == -1) {
                        fprintf(stderr, "Error occured during process creation\n");
                        exit(EXIT_FAILURE);
                	} else if (pid == 0) {
                        	execlp("python", "python", "./scripts/ready-to-score.py", "./2019-1-PA0", NULL);
                        	fprintf(stderr, "ready-to-score error\n");
                        	exit(EXIT_FAILURE);
                	} else {
                	        waitpid(pid, &status, 0);
                	}
	
		} else if (!strncmp(buf, "auto-grade-pa0", 14)) {
		        pid_t pid = fork();
                        if (pid == -1) {
                        	fprintf(stderr, "Error occured during process creation\n");                   
                        	exit(EXIT_FAILURE);
                        } else if (pid == 0) {
                                execlp("python", "python", "./scripts/auto-grade-pa0.py", "./2019-1-PA0", NULL);
                                fprintf(stderr, "auto-grade-pa0 error\n");
                                exit(EXIT_FAILURE);
                        } else {
                                waitpid(pid, &status, 0);
                        }

		} else if (!strncmp(buf, "report-grade", 12)) {
                        pid_t pid = fork();
                        if (pid == -1) {
                                fprintf(stderr, "Error occured during process creation\n");         
                                exit(EXIT_FAILURE);
                        } else if (pid == 0) {
                                execlp("python", "python", "./scripts/report-grade.py", "./2019-1-PA0", NULL);
                                fprintf(stderr, "report-grade error\n");
                                exit(EXIT_FAILURE);
                        } else {
                                waitpid(pid, &status, 0);
                        }

                }

		else {
			printf("I don't know what you said: %s", buf);
    		}
		
	}

	return 0;
}
