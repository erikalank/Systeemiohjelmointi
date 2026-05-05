#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    printf(1, "Read count: %d\n", getreadcount(0));

    char buf[10];
    read(0, buf, 1);

    printf(1, "After read: %d\n", getreadcount(0));

    // reset
    getreadcount(1);

    printf(1, "After reset: %d\n", getreadcount(0));

    exit();
}