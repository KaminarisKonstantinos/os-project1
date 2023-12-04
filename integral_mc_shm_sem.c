// integral_mc_seq.c: Monte Carlo integration - sequential code
// https://en.wikipedia.org/wiki/Monte_Carlo_integration
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>

double get_wtime(void) {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1.0e-6;
}

inline double f(double x) {
  return sin(cos(x));
}

// WolframAlpha: integral sin(cos(x)) from 0 to 1 = 0.738643
// 0.73864299803689018
// 0.7386429980368901838000902905852160417480209422447648518714116299

int main(int argc, char *argv[]) {
  double a = 0.0;
  double b = 1.0;
  int n_proc = 1;
  unsigned long n = 24e7;  // or e8
  const double ref = 0.73864299803689018;
  double res = 0;
  double t0, t1;
  pid_t pid;   

  typedef struct
  {
      double value;
      pthread_mutex_t mutex;
  } shared_data;

  if (argc == 2 && atoi(argv[1]) != 0) {
    n_proc = atoi(argv[1]);
    n = n / n_proc;
  }

  static shared_data* ptr = NULL;

  ptr = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0); 
  ptr->value = 0;

  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
  pthread_mutex_init(&ptr->mutex, &attr);

  t0 = get_wtime();

  for (int i=0; i<n_proc; i++) {
      pid = fork();
      switch (pid) {
          case -1:
              perror("fork");
              exit(EXIT_FAILURE);
          case 0:
              srand48(time(NULL) + i);
              double partial_res = 0;
              for (unsigned long j = 0; j < n; j++) {
                  double xi;
                  xi = drand48();
                  partial_res += f(xi);
              }
              // critical region protected
              pthread_mutex_lock(&ptr->mutex);
              ptr->value += partial_res;
              pthread_mutex_unlock(&ptr->mutex);
              exit(EXIT_SUCCESS);
          default:
              break;
      }
  }

  for (int i=0; i<n_proc; i++) {
      wait(NULL);
  }

  t1 = get_wtime();

  res = ptr->value;

  munmap(ptr, sizeof(ptr));

  res *= (b-a)/(n*n_proc);

  printf("Result=%.16f Error=%e Rel.Error=%e Time=%lf seconds\n", res, fabs(res-ref), fabs(res-ref)/ref, t1-t0);
  return 0;
}
