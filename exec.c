# include "minishell.h"

void execute(t_list *list, char **path_tab)
{
    char *redirect_path;
    char *pwd = getenv("PWD");
    char *right_path;

    t_list_simple_cmd *actuel = list->premier;
    int i;
    int numsimplecommands;
    //save in/out
    int tmpin=dup(0);
    int tmpout=dup(1);
  
    //set the initial input 
    int fdin;
    // if (infile)
    //   fdin = open(infile,O_READ); 
    // else {
      // Use default input
      fdin=dup(tmpin);
    // }
  
    int ret;
    int fdout;

    redirect_path = NULL;
    i = 0;
    numsimplecommands = list_len(list);
    while (actuel != NULL)
    {
        //redirect input
        dup2(fdin, 0);
        close(fdin);
        //setup output
        if (actuel->next == NULL)
        {
            // Last simple command 
            if(actuel->outfile == 1)
            {
                printf("buzz\n");
                redirect_path = find_path_redirect_file(getenv("PWD"), actuel->outfile_name, redirect_path);
                fdout = open(redirect_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXO | S_IRWXU | S_IRWXG);
            }
            else if (actuel->outfile == 2)
            {
                printf("buzz2\n");
                redirect_path = find_path_redirect_file(getenv("PWD"), actuel->outfile_name, redirect_path);
                fdout = open(redirect_path, O_APPEND | O_CREAT | O_WRONLY, S_IRWXO | S_IRWXU | S_IRWXG);
                // write(fdout, "end", ft_strlen("end"));
            }
            else
            {
            // Use default output
            fdout = dup(tmpout);
            }
        }
  
        else 
        {
            // Not last 
            //simple command
            //create pipe
            int fdpipe[2];
            pipe(fdpipe);
            fdout = fdpipe[1];
            fdin = fdpipe[0];
        }
  
        // Redirect output
        dup2(fdout,1);
        close(fdout);
    
        // Create child process
        ret = fork(); 
        if(ret == 0)
        {
            right_path = find_right_path(path_tab, actuel->cmd[0], right_path);
            execve(right_path, actuel->cmd, NULL);
            
            strerror(errno);
            _exit(1);
        }
        i++;
        actuel = actuel->next;
    }
   
     //restore in/out defaults
    dup2(tmpin,0);
    dup2(tmpout,1);
    close(tmpin);
    close(tmpout);
    redirect_path = NULL;
  
    // if (!background)
    // {
        // Wait for last command
    waitpid(ret, NULL, 0);
    // }
}