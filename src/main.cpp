#include <iostream>
#include <CoreServices/CoreServices.h>

void mycallback(
    ConstFSEventStreamRef streamRef,
    void *clientCallBackInfo,
    size_t numEvents,
    void *eventPaths,
    const FSEventStreamEventFlags eventFlags[],
    const FSEventStreamEventId eventIds[])
{
		std::cout << "It worked!" << std::endl;
    int i;
    // char **paths = eventPaths;

    for (i=0; i<numEvents; i++) {
        int count;
        /* flags are unsigned long, IDs are uint64_t */
        // printf("Change %llu in %s, flags %lu\n", eventIds[i], paths[i], eventFlags[i]);
		}
		char const **paths = (char const**)eventPaths;
		for(int i = 0; i < numEvents; ++i) {
			std::cout << (unsigned long long)eventIds[i] << "\t" <<
				eventFlags[i] << "\t" <<
				paths[i] << "\n"
				;
		}
}

int main()
{
  /* Define variables and create a CFArray object containing
     CFString objects containing paths to watch.
   */
  CFStringRef mypath = CFSTR("/tmp/test");
  CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&mypath, 1, NULL);

  FSEventStreamRef stream;
  CFAbsoluteTime latency = 3.0; /* Latency in seconds */

  /* Create the stream, passing in a callback */
  stream = FSEventStreamCreate(NULL,
      &mycallback,
      NULL,
      pathsToWatch,
      kFSEventStreamEventIdSinceNow, /* Or a previous event ID */
      latency,
			kFSEventStreamCreateFlagFileEvents
			// kFSEventStreamEventFlagItemCreated
      // kFSEventStreamCreateFlagNone /* Flags explained in reference */
  );


	FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
	FSEventStreamStart(stream);

	std::cout << "eventID\tFlag\tPath\n";

	CFRunLoopRun();

  FSEventStreamInvalidate(stream);
  FSEventStreamRelease(stream);

  return 0;
}
