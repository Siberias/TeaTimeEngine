#pragma once

#include "IGameEntityFactory.h"

class TextEntityFactory : public IGameEntityFactory
{
public:
  ~TextEntityFactory() = default;

  IGameEntityPtr Create(const Json& data) override;
};

class FPSDisplayEntityFactory : public IGameEntityFactory
{
public:
  ~FPSDisplayEntityFactory() = default;

  IGameEntityPtr Create(const Json& data) override;
};