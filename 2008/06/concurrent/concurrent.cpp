/**
 * Code written by Rafael Fernández López, 2008.
 *
 * This code is licensed under the terms of GPLv3
 * or later.
 *
 * ereslibre@kde.org
 */

#include <pthread.h>
#include <iostream>

using namespace std;


//==============================================================================


/**
 * @short Let you execute code in a different thread.
 */
class Concurrent
{
public:
  Concurrent(void *content = 0);

  /**
   * Creates the new thread and calls to run(), which will
   * be executed into the new created thread.
   */
  void exec();

  void waitForMe();

  static void *entryPoint(void *param);

protected:
  /**
   * @short The code you place here will be in the new thread.
   */
  virtual void run() = 0;

protected:
  void *m_content;

private:
  pthread_t m_pthread;
};

Concurrent::Concurrent(void *content)
  : m_content(content)
{
}

void Concurrent::exec()
{
  pthread_create(&m_pthread, NULL, Concurrent::entryPoint, this);
}

void Concurrent::waitForMe()
{
  pthread_join(m_pthread, NULL);
}

void *Concurrent::entryPoint(void *param)
{
  Concurrent *concurrent = static_cast<Concurrent*>(param);
  concurrent->run();
}


//==============================================================================


class ConcurrentMutex
{
  // so it can access m_mutex
  friend class ConcurrentConditionVariable;

public:
  ConcurrentMutex();

  void lock();
  void unlock();

private:
  pthread_mutex_t m_mutex;
};

ConcurrentMutex::ConcurrentMutex()
{
  pthread_mutex_init(&m_mutex, NULL);
}

void ConcurrentMutex::lock()
{
  pthread_mutex_lock(&m_mutex);
}

void ConcurrentMutex::unlock()
{
  pthread_mutex_unlock(&m_mutex);
}


//==============================================================================


class ConcurrentConditionVariable
{
public:
  ConcurrentConditionVariable();

  void wait(ConcurrentMutex *mutex);
  void signal();
  void broadcast();

private:
  pthread_cond_t m_condition;
};

ConcurrentConditionVariable::ConcurrentConditionVariable()
{
  pthread_cond_init(&m_condition, NULL);
}

void ConcurrentConditionVariable::wait(ConcurrentMutex *mutex)
{
  pthread_cond_wait(&m_condition, &mutex->m_mutex);
}

void ConcurrentConditionVariable::signal()
{
  pthread_cond_signal(&m_condition);
}

void ConcurrentConditionVariable::broadcast()
{
  pthread_cond_broadcast(&m_condition);
}


//==============================================================================


#ifdef ORDER_ODD_THREADS_EXIT
ConcurrentMutex myMutex;
#endif

class MyConcurrent
  : public Concurrent
{
public:
  MyConcurrent(void *content)
    : Concurrent(content)
  {
  }

protected:
  virtual void run()
  {
    cout << "This is a new thread ! with content " << (int) m_content << endl;
    if (((int) m_content) % 2) {
#ifdef ORDER_ODD_THREADS_EXIT
      myMutex.lock();
#endif
      int j = 0;
      for (int i = 0; i < 100000000; i++){
        j++;
      }
#ifdef ORDER_ODD_THREADS_EXIT
      myMutex.unlock();
#endif
    }
    cout << "Exiting thread with content " << (int) m_content << endl;
  }
};


//==============================================================================


int main(int argc, char **argv)
{

  MyConcurrent *concurrent[10];
  for (int i = 0; i < 10; ++i) {
    concurrent[i] = new MyConcurrent((void*) i);
    concurrent[i]->exec();
#ifndef WAIT_AFTER
    concurrent[i]->waitForMe();
#endif
  }

#ifdef WAIT_AFTER
  for (int i = 0; i < 10; ++i) {
    concurrent[i]->waitForMe();
  }
#endif

  return 0;
}
