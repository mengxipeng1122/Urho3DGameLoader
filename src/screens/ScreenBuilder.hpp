
#pragma once

class Screen;

#include "../Global.h"

//! Base Builder class to create Game Stages via a ScreenFactory
class ScreenBuilder
{
public:
  virtual ~ScreenBuilder() {} //empty virtual destructor
  //! Virtual Build call that must be overloaded by all Derived Builders
  virtual Screen* Build(Context* context) = 0;
};

/*! Templated builder derived class so I don't need to create a Builder for each
Stage type*/
template <typename T>
class ScreenTBuilder : public ScreenBuilder
{
public:
	virtual Screen* Build(Context* context);
};


//! Creates a new Screen of type T
template <typename T>
Screen* ScreenTBuilder<T>::Build(Context* context)
{
	return new T(context);
}

