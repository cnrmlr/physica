#include "instance.h"

int main(int argc, char **argv)
{
   computational_physics_engine::Instance* engine = new computational_physics_engine::Instance();

   engine->run();

   delete engine;

   return 0;
}
