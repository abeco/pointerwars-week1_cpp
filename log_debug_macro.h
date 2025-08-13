// #ifdef DEBUG
// #define LOG_DEBUG(msg,...) \
// printf("File %s Line %d :: ", __FILE__, __LINE__ )
// printf((msg), ##__VA_ARGS__)
// #else
// #define LOG_DEBUG(msg,...) ((void)0)
// #endif

#ifdef DEBUG
#define LOG_DEBUG(msg,...) \
// use do while in macros to have compiler consider it a single statement
do \
{ \
	printf("File %s Line %d :: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
	fflush(stdout); \
} while (0)
#else
#define LOG_DEBUG(msg,...) ((void)0)
#endif