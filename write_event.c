// //
// // Created by william on 07/01/2026.
// //
//
// #include "write_event.h"
//
// // struct _Event {
// //     // char description[2048];
// //     // char title[128];
// //     // time_t start_in_seconds;
// //     // time_t duration_in_seconds;
// //
// //     char Description[200];
// //     char Title[50];
// //     time_t StartTime;
// //     time_t EndTime;
// // };
//
//
//
// //                       title, start_in_seconds, duration_in_seconds, description
// # define EVENT_FORMAT  "[%s] (%ld-%ld)\n\t\"%s\""
//
// /* Returns total bytes written. */
// size_t WriteEvent(FILE *const stream, const Event *const event)
// {
//     if (!stream || !event) {
//         return 0;
//     }
//
//     return fprintf(stream, EVENT_FORMAT,
//         event->Title, event->StartTime,
//         event->EndTime, event->Description
//     );
// }
//
// size_t ReadEvent(FILE *const stream, Event *const event)
// {
//     if (!stream || !event) {
//         return 0;
//     }
//
//     return fscanf(stream, EVENT_FORMAT,
//         event->Title, &event->StartTime, &event->EndTime, event->Description
//     );
// }
