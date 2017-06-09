#ifndef TIMER_H
#define TIMER_H

#include "globals.hxx"

/*! \brief  Timer class.
 *          To be used for timing movement based on framerate.
 */
class Timer
{
  public:

    Timer(IrrlichtDevice &device);

    virtual ~Timer();

    void Reset(void);

    void Update(void);

    __inline f32 getTimeFactor(void){
      return m_timeFactor;
    }

    f32 m_step;
    f32 m_accumulator;
    f32 m_delta;

  protected:
  private:

    f32 m_time;
    f32 m_deltaTime;
    f32 m_timeFactor;

    IrrlichtDevice *m_irrDevice;
};

#endif // TIMER_H
