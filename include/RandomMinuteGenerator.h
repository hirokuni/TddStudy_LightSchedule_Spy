//- Copyright (c) 2008-2013 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net

#ifndef RANDOM_MINUTE_GENERATOR_INCLUDED
#define RANDOM_MINUTE_GENERATOR_INCLUDED

#include <stdlib.h>

void RandomMinuteGenerator_Create(int bound);
extern int RandomMinuteGenerator_Get(void);

#endif
