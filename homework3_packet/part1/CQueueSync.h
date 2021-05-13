// docker run -v ${pwd}:/assignments -it --rm reeselevine/cse113:latest

#include <atomic>
using namespace std;

class CQueue
{
public:
  CQueue()
  {
    // Implement me!
    flag.store(false);
  }

  void enq(float e)
  {
    // Implement me!

    // put value in box
    box.store(e);

    // set flag
    flag.store(true);

    // wait for flag to be reset (spin...)
    while (flag.load())
    {
      // spin...
    }
  }

  float deq()
  {
    // Implement me!

    // wait for flag to be set (aka spin)
    while (!flag.load())
    {
      // spin...
    }

    // read from the box
    float box_value = box.load();

    // reset flag
    flag.store(false);

    return box_value;
  }

private:
  // give me some variables!
  atomic_bool flag;
  atomic<float> box;
};
