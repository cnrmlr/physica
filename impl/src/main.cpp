#include "instance.h"

int main(int argc, char **argv)
{
   cpe::Instance* engine = new cpe::Instance();

   engine->run();

   delete engine;

   return 0;
}
