#include "advent_day.h"

class Day_7 : public AdventDay
{
public:
    Day_7() : AdventDay(7) {}

    void part_one()
    {
    }

    void part_two()
    {
    }
};

class FileSytemEntry
{
public:
    FileSytemEntry(std::string name) : name(name) {}
    virtual ~FileSytemEntry() {}
    std::string get_name() { return name; }

private:
    std::string name;
};

class File : public FileSytemEntry
{
public:
    File(std::string name, int size) : FileSytemEntry(name), size(size) {}
    virtual ~File() {}
    int get_size() { return size; }

private:
    int size;
};

class Folder : public FileSytemEntry
{
public:
    Folder(std::string name) : FileSytemEntry(name) {}
    virtual ~Folder() {}
    std::vector<FileSytemEntry *> get_content;

private:
    std::vector<FileSytemEntry *> content;
};

int main()
{
    Day_7 day;
    day.part_one();
    day.part_two();
    return 0;
}