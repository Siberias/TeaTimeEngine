#pragma once

#include <map>
#include <string>

#include "IEventService.h"

class SynchronousEventService : public IEventService
{
private:
  std::map<std::string, EventListener*> _listenersByEventName;

public:
  SynchronousEventService() = default;
  ~SynchronousEventService() = default;

  void ReceiveEvent(const IEvent& event) override;
  void RegisterListener(const std::string& eventName, EventListener*
    listener) override;
  void UnregisterListener(const std::string& eventName, EventListener*
    listener) override;
};