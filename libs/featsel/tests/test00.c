#include <stdio.h>
#include <featsel.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

double feat0 (void *elem, void *udata)
{
    return (double) (int)elem;
}

double feat1 (void *elem, void *udata)
{
    return (double) ((int)elem * 2);
}

int main (int argc, char **argv)
{
    featsel_t *fsel;
    feat_tuple_t *t0, *t1, *t2;

    fsel = featsel_new(NULL);
    featsel_add(fsel, feat0);
    featsel_add(fsel, feat1);

    t0 = featsel_analyze(fsel, (void *)1);
    t1 = featsel_analyze(fsel, (void *)2);
    t2 = featsel_analyze(fsel, (void *)3);

    assert((int)(sqrt(5) * 1000) ==
           (int)(featsel_tuple_distance(t0, t1) * 1000));
    assert((int)(featsel_tuple_distance(t0, t1) * 1000) ==
           (int)(featsel_tuple_distance(t1, t2) * 1000));
    assert(featsel_tuple_distance(t0, t0) == 0);
    assert(featsel_tuple_distance(t1, t1) == 0);
    assert(featsel_tuple_distance(t2, t2) == 0);

    featsel_free(fsel);

    exit(0);
}

