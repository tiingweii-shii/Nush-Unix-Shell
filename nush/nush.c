// Attribution: Code for piping is modified from "Implementation of redirection and pipe operators in shell"
// URL: http://www.sarathlakshman.com/2012/09/24/implementation-overview-of-redirection-and-pipe-operators-in-shell
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "tokenize.h"
#include "seq.h"
#include "ast.h"
#include "parse.h"

//char* OPS_ALL[7] = {"<", ">", "|", "&", ";", "&&", "||"};

int
indexof(char** args, long len, const char* op)
{
	int nn = 0;
	for (int ii = 0; ii < len; ii++) {
		if (strcmp(args[ii], op) == 0) {
			return nn;
		}
		nn++;
	}
	return -1;
}

int
cmd_eval(char* cmd) {
	int cpid;
    	seq* tokens = 0;
    
    	for (int ii = 0; ii < strlen(cmd) - 1; ++ii) {	
		if (cmd[ii] == '\n') {
            		cmd[ii] = 0;
            		break;
		}
    	}
    
    	tokens = tokenize(cmd);
    	int len = length(tokens);

	char* args[len + 1];	
	memset(args, ' ', len + 1);

    	seq* copy = tokens;
    	for (int ii = 0; ii < len; ii++) {
	    args[ii] = (copy->first);
	    copy = copy->rest;
    	}
    	free_seq(copy);
    	args[len] = 0;
    	int sleep = indexof(args, len, "&");
	int pip = indexof(args, len, "|");
	
	int status = 0;

	if ((pip > -1) && (len - pip > 1)) {

		char* pipe_arg2[len - pip];
		memset(pipe_arg2, '\0', len - pip);
		int jj = 0;
		for (int ii = pip + 1; ii <= len; ii++) {
			pipe_arg2[jj] = args[ii];
			jj++;
		}

		char* pipe_arg1[pip + 1];
		for (int ii = 0; ii < pip; ii++) {
			pipe_arg1[ii] = args[ii];
		}

		pipe_arg1[pip] = 0;

		int pfd[2];
		pipe(pfd);

		int id1;
		int id2;
		if ((id1 = fork())) {
			close(1);
			dup(pfd[1]);
			close(pfd[0]);
			close(pfd[1]);
			if (pipe_arg1[0]) {
			execvp(pipe_arg1[0], pipe_arg1);
			}
		}
		if ((id2 = fork())) {
			close(0);
			dup(pfd[0]);
			close(pfd[1]);
			close(pfd[0]);
			if (pipe_arg2[0]) {
			execvp(pipe_arg2[0], pipe_arg2);
			}
		}	
		close(pfd[0]);
		close(pfd[1]);
		wait(0);
		wait(0);
	} else if ((cpid = fork())) {

		if (sleep == -1) {
		waitpid(cpid, &status, 0);
		} 
		if (WIFEXITED(status)) {
			free_seq(tokens);
		return WEXITSTATUS(status);
        	} 
	} else {
       
	int redirin = indexof(args, len, "<");
	int redirout = indexof(args, len, ">");
	int cd = indexof(args, len, "cd");
	int exit1 = indexof(args, len, "exit");

	if ( exit1 == 0) {
		exit(22);
	} else if (cd == 0) {
		if (args[1]) {
			chdir(args[1]);
		}
	} else if (redirin > -1 || redirout > -1) {
		int redir;
		if (redirin > -1) {
			redir  = redirin;
		} else {
			redir = redirout;
		}
		char* redir_args[redir + 1];
		for (int ii = 0; ii < redir; ii++) {
			redir_args[ii] = args[ii];
		}
		redir_args[redir] = 0;
		if (strcmp(args[redir],">") == 0) {
			if (args[redir + 1]) {
			int fd = open(args[redir + 1], O_CREAT | O_WRONLY, 0644);
			close(STDOUT_FILENO);
			dup(fd);
			close(fd);
			}
		} else if (strcmp(args[redir],"<") == 0) {
			if (args[redir + 1]) {
			int fd = open(args[redir + 1], O_RDONLY);
			close(0);
			dup(fd);
			close(fd);
			}
		}
		if (redir_args[0]){
			execvp(redir_args[0], redir_args);
			printf("exec only returns on error.");
		}
	} else if (sleep > -1) {
		char* sleep_args[sleep + 1];
		for (int ii = 0; ii < sleep; ii++) {
			sleep_args[ii] = args[ii];
		}
		sleep_args[sleep] = 0;

		if(sleep_args[0]) {
			execvp(sleep_args[0], sleep_args);
			printf("exec only returns on error.");
		}
	} else {
		if(args[0]) {
		execvp(args[0], args);
		}
	} 
    }
}

int
ast_eval(ast* ast){
	char tmp[120];
	memset(tmp, '\0', 120);
	if (ast->op == 0) {
		seq* xs = ast->value;
		seq* cp = xs;
		int len = 0;
		for (; cp; cp = cp->rest) {
			len += sprintf(tmp + len, "%s ", cp->first);
		}
		free_seq(cp);
		cmd_eval(tmp);
	} else {
		int rv = -1;
		rv = ast_eval(ast->arg1);

		if (strcmp(ast->op, ";") == 0) {
			if (rv != 22) {
				ast_eval(ast->arg2);
			}
		} else if (strcmp(ast->op, "&&") == 0) {
			if (rv == 0) {
				ast_eval(ast->arg2);
			}
		} else if (strcmp(ast->op, "||") == 0) {
			if (rv != 0) {
				ast_eval(ast->arg2);
			}
		} 			
	}
}

void
execute(char* cmd)
{
    seq* tokens = 0;
    
    for (int ii = 0; ii < strlen(cmd) - 1; ++ii) {	
        if (cmd[ii] == '\n') {
            cmd[ii] = 0;
            break;
	}
    }
    
    tokens = tokenize(cmd);
    long len = length(tokens);
    char* args[len + 1];
    seq* copy = tokens;
    for (int ii = 0; ii < len; ii++) {
	    args[ii] = (copy->first);
	    copy = copy->rest;
    }
    free_seq(copy);
    args[len] = 0;
    int and = indexof(args, len, "&&");
    int or = indexof(args, len, "||");
    int div = indexof(args, len, ";");
    
    if ( div > -1 || and > -1 || or > -1) {
	    ast* tree = parse(tokens);
	    ast_eval(tree);
    } else {
	    cmd_eval(cmd);
    }
    free_seq(tokens);
}

int
main(int argc, char* argv[]) { 

    char cmd[256];
    char* line;
    
    if (argc == 1) {
	    while(1) {
		printf("nush$ ");
		fflush(stdout);
		line = fgets(cmd, 256, stdin);
		if (!line) {
			exit(0);
		} 
		execute(cmd);
	    }
    } else {
	    FILE* fh = fopen(argv[1], "r");
	    if (!fh) {
		    perror("failed");
		    exit(1);
	    } 

	    long nn = 0;
	    while (1) {
	    	line = fgets(cmd, 256, fh);
	   	if (!line) {
			break;
	    	} 
	   	execute(cmd);
		nn++;
	    }
	    fclose(fh);
   }
    return 0;
}
