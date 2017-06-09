#include "Timer.h"

Timer::Timer(IrrlichtDevice &device) :
  m_step(0),
  m_accumulator(0),
  m_time(0),
  m_deltaTime(0),
  m_timeFactor(0),
  m_irrDevice(&device)
{
  if(m_irrDevice == NULL)
    throw "Failed to initalize timer class.";
  //ctor

  if(m_irrDevice->getTimer()->isStopped())
    printf("Virtual timer is stopped\n");
}

Timer::~Timer()
{
  //dtor
}

void Timer::Reset(void)
{
  m_time = m_irrDevice->getTimer()->getRealTime();
}

void Timer::Update(void)
{
  m_deltaTime = m_irrDevice->getTimer()->getRealTime() - m_time;
  m_time += m_deltaTime;
  m_timeFactor = m_deltaTime * 0.001f;
}
