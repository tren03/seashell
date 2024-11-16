# Seashell
Its a Cshell
https://brennan.io/2015/01/16/write-a-shell-in-c/

With these two system calls, we have the building blocks for how most programs are run on Unix. First, an existing process forks itself into two separate ones.
Then, the child uses exec() to replace itself with a new program. 
The parent process can continue doing other things, and it can even keep tabs on its children, using the system call wait().
