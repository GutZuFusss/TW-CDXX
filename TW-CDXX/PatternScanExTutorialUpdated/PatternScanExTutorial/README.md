# PatternScanExTutorial

This is the code from my External Pattern Scan Youtube Tutorial

It is updated to fix the bugs

https://www.youtube.com/watch?v=jLfPdujSuRA

https://guidedhacking.com/showthread.php?8255-C-External-Signature-Scanning

## What does this do?

Searches through memory of a process and finds addresses that match a signature based on a pattern you provide

## Usage

Do the video tutorial, then clone this project to get the updated fixed code

## Important Changes

If the pattern contains \x00\ the strlen will stop prematurely because it's the null terminator
In patternscan.cpp we changed:
unsigned int patternLength = strlen(pattern);
to:
unsigned int patternLength = strlen(mask);

In the VirtualProtect calls, we changed the protection mask to the correct PAGE_EXECUTE_READWRITE

GetModule() now has error checking so it won't return the first module when no module is found
