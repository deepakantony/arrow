
#ifndef Time_h
#define Time_h

class Time {
 public:
  static double currentSeconds();
 private:
  Time();
  Time(const Time&);
  Time& operator=(const Time&);

  static void initialize();
};

#endif
