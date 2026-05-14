#include "Services/SynchronousEventService.h"

#include "Events/EventListener.h"

void SynchronousEventService::ReceiveEvent(const IEvent& event)
{
  const std::string& eventName = event.GetName();

  auto it = _listenersByEventName.find(eventName);
  if (it == _listenersByEventName.end())
  {
    return;
  }

  EventListener* currentListener = it->second;
  do
  {
    currentListener->OnEventTriggered(event);
    currentListener = currentListener->GetNextListener();
  } while (currentListener != nullptr);
}

void SynchronousEventService::RegisterListener(const std::string& eventName,
  EventListener* listener)
{
  auto it = _listenersByEventName.find(eventName);
  if (it != _listenersByEventName.end())
  {
    EventListener* currentListener = it->second;
    
    currentListener->SetPreviousListener(listener);
    listener->SetNextListener(currentListener);
  }

  _listenersByEventName[eventName] =listener;
}

void SynchronousEventService::UnregisterListener(const std::string& eventName,
  EventListener* listener)
{
  auto it = _listenersByEventName.find(eventName);
  if (it == _listenersByEventName.end())
  {
    return;
  }

  EventListener* currentListener = it->second;

  while (currentListener != listener && currentListener->GetNextListener() 
    != nullptr)
  {
    currentListener = currentListener->GetNextListener();
  }

  if (currentListener == listener)
  {
    if (currentListener->GetPreviousListener() != nullptr)
    {
      currentListener->GetPreviousListener()->SetNextListener(
        currentListener->GetNextListener());
    }

    if (currentListener->GetNextListener() != nullptr)
    {
      currentListener->GetNextListener()->SetPreviousListener(
        currentListener->GetPreviousListener());
    }
  }
}