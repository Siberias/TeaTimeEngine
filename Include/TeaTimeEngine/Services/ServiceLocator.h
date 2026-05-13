#pragma once

#include <memory>
#include <unordered_map>
#include <stdexcept>

class ServiceLocator
{
private:
  static ServiceLocator* _instance;

  //Services are looked up by their typeid hash code, and stored as void 
  //pointers to allow for any type of service to be registered
  std::unordered_map<size_t, std::shared_ptr<void>> _services;

public:
  ServiceLocator();
  ~ServiceLocator() { _instance = nullptr; }

  static ServiceLocator* GetInstance()
  {
    return _instance;
  }

  template<typename T>
  void RegisterService(std::shared_ptr<T> service)
  {
    const size_t typeHash = typeid(T).hash_code();
    _services[typeHash] = service;
  }

  template<typename T>
  std::shared_ptr<T> GetService()
  {
    const size_t typeHash = typeid(T).hash_code();
    if (_services.find(typeHash) != _services.end())
    {
      return std::static_pointer_cast<T>(_services[typeHash]);
    }

    throw std::runtime_error("Service not found: " +
      std::string(typeid(T).name()));
  }
};