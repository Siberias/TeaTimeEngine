#pragma once

#include "IEvent.h"

class EventListener
{
private:
  EventListener* _nextListener = nullptr;
  EventListener* _previousListener = nullptr;

public:
  virtual ~EventListener() = default;
  virtual void OnEventTriggered(const IEvent& event) = 0;

  EventListener* GetNextListener() const
  {
    return _nextListener;
  }
  void SetNextListener(EventListener* nextListener)
  {
    _nextListener = nextListener;
  }
  EventListener* GetPreviousListener() const 
  {
    return _previousListener;
  }
  void SetPreviousListener(EventListener* previousListener) 
  {
    _previousListener = previousListener;
  }
};