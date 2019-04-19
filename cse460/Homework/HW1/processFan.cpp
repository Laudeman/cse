#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int n = 10;
  pid_t child_pid;

  for ( int i = 0; i < n; ++i ) 
  {
    if ( ( child_pid = fork()) <= 0 )
        break;
        sleep ( 1 );
  }
  std::cout << "Process: " << getpid() << " Parent: " << getppid() << std::endl;
 
  return 0;
}
