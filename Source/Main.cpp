#include "Context.h"

int main(int argc, char **argv)
{
    Context context;
    if (context.initialize()) { context.runLoop(); }
    context.shutdown();
    return 0;
}
