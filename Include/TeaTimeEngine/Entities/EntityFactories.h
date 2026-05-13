#pragma once

#include "IGameEntityFactory.h"

class TextEntityFactory : public IGameEntityFactory
{
public:
  ~TextEntityFactory() = default;

  IGameEntityPtr Create(const Json& data) override;
};