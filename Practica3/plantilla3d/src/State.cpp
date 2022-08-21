#include "State.h"

State* State::GetState()
{
   static auto state = new State();

   return state;
}
