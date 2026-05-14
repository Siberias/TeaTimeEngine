#pragma once

#include <TeaTimeEngine/Events/IEvent.h>

class EventListener;

class IEventService
{
public:
  virtual ~IEventService() = default;

  virtual void ReceiveEvent(const IEvent& event) = 0;

  virtual void RegisterListener(const std::string& eventName, EventListener* 
    listener) = 0;
  virtual void UnregisterListener(const std::string& eventName, EventListener* 
    listener) = 0;
};