#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stack>

int main()
{
  int n = 10;
  pid_t child_pid;
  std::stack<pid_t> ancestors;		

  for ( int i = 0; i < n; ++i ) 
  {
    if ( child_pid = fork() )
        break;          		
    ancestors.push ( getppid() );	
  }
  wait ( NULL );			
  std::cout << "Process: " << getpid() << " with kid: " << child_pid << 
	" and ancestors: ";
  while ( !ancestors.empty() ) 
  {	
    std::cout << ancestors.top() << " ";
    ancestors.pop();			
  }
  std::cout <<  std::endl;
  return 0;
}
