#pragma once

#include <string>

class IEvent
{
public:
  virtual ~IEvent() = default;

  virtual std::string GetName() const = 0;
};