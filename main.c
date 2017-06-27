#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    const char *first_name;
    const char *last_name;
    unsigned int age;
} MyEntry;

static MyEntry entries[] = {
    { "John", "Doe", 24 },
    { "Jane", "Doe", 54 },
};

static void
my_entry_display(const MyEntry *entry)
{
    printf("Entry:\n");
    printf("Name: %s %s\n", entry->first_name, entry->last_name);
    printf("Age: %u\n", entry->age);
    printf("\n");
}

static void
display_entries_bug1(const MyEntry *entry)
{
    int i;
    int n_entries = sizeof(entries);

    for (i = 0; i < n_entries; i++)
        my_entry_display(&entries[i]);
}

void
usage(const char *program_name)
{
    printf("Usage: %s <bug>\n", program_name);
    printf("available bug: bug1\n");
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "bug1") == 0) {
        display_entries_bug1(entries);
    }

    return 0;
}
