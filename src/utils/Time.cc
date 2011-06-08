
#include "Time.h"
#include <errno.h>
#ifdef _WIN32
#include <windows.h>
#else
#ifdef __linux
#include <time.h>
#endif
#include <sys/time.h>
#endif
#include <iostream>
#include <cstdlib>
using namespace std;

static bool initialized = false;
#ifdef _WIN32
static LARGE_INTEGER frequency;
static LARGE_INTEGER start_time;
#else
static struct timeval start_time;
#endif

void
Time::initialize()
{
  initialized=true;
#ifdef _WIN32
  if ( !QueryPerformanceFrequency( &frequency ) ) {
    cerr << "QueryPerformanceFrequency failed" << endl;
    exit( 1 );
  }
  if ( !QueryPerformanceCounter( &start_time ) ) {
    cerr << "QueryPerformanceCounter failed" << endl;
    exit( 1 );
  }
#else
  if(gettimeofday(&start_time, 0) != 0) {
    cerr << "gettimeofday failed: " << strerror(errno) << endl;
    exit( 1 );
  }
#endif
}

double Time::currentSeconds()
{
  if(!initialized)
    initialize();
#ifdef _WIN32
  LARGE_INTEGER now_time;
  if ( !QueryPerformanceCounter( &now_time ) ) {
    cerr << "QueryPerformanceCounter failed" << endl;
    exit( 1 );
  }
  return static_cast< double >(now_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
#else
  struct timeval now_time;
  if(gettimeofday(&now_time, 0) != 0) {
    cerr << "gettimeofday failed: " << strerror(errno) << endl;
    exit( 1 );
  }
  return (now_time.tv_sec-start_time.tv_sec)+(now_time.tv_usec-start_time.tv_usec)*1.e-6;
#endif
}
