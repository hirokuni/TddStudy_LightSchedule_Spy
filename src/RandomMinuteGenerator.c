//- Copyright (c) 2008-2013 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net



#include "RandomMinuteGenerator.h"
#include <stdlib.h>
#include <string.h>

//static local variables

static int bound = 0;

void RandomMinuteGenerator_Create(int b)
{
    bound = b;
}

int RandomMinuteGenerator_Get(void)
{
    return bound - rand() % (bound * 2 + 1);
}

