#ifndef INCLUDE_CORE_MANAGERS_TRANSMANAGER_HPP_INCLUDED
#define INCLUDE_CORE_MANAGERS_TRANSMANAGER_HPP_INCLUDED

#include "../sing/trans.hpp"

class TransManager {
  private:
  public:
	static TransManager& Instance() {
		static TransManager inst;
		return inst;
	}
};

#endif