#include "advent_day.h"
#include <set>

class File
{
public:
    File(std::string name, int size) : name(name), size(size) {}
    virtual ~File() {}
    std::string get_name() { return name; }
    int get_size() { return size; }

private:
    std::string name;
    int size;
};

class Folder
{
public:
    Folder(std::string name, Folder *parent_directory) : name(name), parent_directory(parent_directory) {}
    virtual ~Folder()
    {
        for (auto p : content_files)
        {
            delete p;
        }
        for (auto p : content_folders)
        {
            delete p;
        }
    }
    std::string get_name() { return name; }
    std::set<File *> get_content_files() { return content_files; };
    Folder *get_parent_directory() { return parent_directory; };
    std::set<Folder *> get_content_folders() { return content_folders; };
    void add_content(File *new_entry) { content_files.insert(new_entry); }
    void add_content(Folder *new_entry) { content_folders.insert(new_entry); }

private:
    std::string name;
    Folder *parent_directory;
    std::set<Folder *> content_folders;
    std::set<File *> content_files;
};

class Day_7 : public AdventDay
{
public:
    Day_7() : AdventDay(7) {}

    void part_one()
    {
        Folder root = Folder("/", nullptr);
        create_dir_tree_from_input(root);
        int sum_folder_sizes = 0;
        int max_folder_size = 100000;
        recursive_sum_folders_with_max_size(&root, sum_folder_sizes, max_folder_size);
        std::cout << "Sum of folder sizes, each up to 1000000, is " << sum_folder_sizes << std::endl;
    }

    int recursive_sum_folders_with_max_size(Folder *current_directory, int &sum_folder_sizes, int &max_size)
    {
        int files_size_sum = 0;
        for (auto file : current_directory->get_content_files())
        {
            files_size_sum += file->get_size();
        }
        if (current_directory->get_content_folders().size() == 0 && files_size_sum <= max_size)
        {
            sum_folder_sizes += files_size_sum;
            return files_size_sum;
        }

        for (auto folder : current_directory->get_content_folders())
        {
            files_size_sum += recursive_sum_folders_with_max_size(folder, sum_folder_sizes, max_size);
        }
        if (files_size_sum <= max_size)
        {
            sum_folder_sizes += files_size_sum;
        }
        return files_size_sum;
    }

    void create_dir_tree_from_input(Folder &root)
    {
        std::vector<std::string> input = this->get_input();
        Folder *current_directory = &root;
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i].find("$ ls") != -1)
            {
                // iterate over the input until the next line with "$"
                while (i < input.size() - 1)
                {
                    if (input[i + 1].find("$") != -1)
                    {
                        break;
                    }
                    else
                    {
                        i++;
                        if (input[i].find("dir ") != -1)
                        {
                            current_directory->add_content(new Folder(input[i].substr(4), current_directory));
                        }
                        else
                        {
                            int split_index = input[i].find(" ");
                            std::string name = input[i].substr(split_index + 1);
                            int size = std::stoi(input[i].substr(0, split_index));
                            current_directory->add_content(new File(name, size));
                        }
                    }
                }
            }
            else if (input[i].find("$ cd") != -1)
            {
                std::string destination = input[i].substr(5);
                if (destination == "/")
                {
                    current_directory = &root;
                }
                else if (destination == ".." && current_directory->get_parent_directory() != nullptr)
                {
                    current_directory = current_directory->get_parent_directory();
                }
                else
                {
                    std::set<Folder *> folders = current_directory->get_content_folders();
                    for (Folder *folder : folders)
                    {
                        if (folder->get_name() == destination)
                        {
                            current_directory = folder;
                            break;
                        }
                    }
                }
            }
        }
    }

    void part_two()
    {
        Folder root = Folder("/", nullptr);
        create_dir_tree_from_input(root);
        int total_disk_space = 70000000;
        int needed_disk_space = 30000000;
        std::set<int> all_folder_sizes;
        int root_directory_size = recursive_get_folder_sizes(&root, all_folder_sizes);

        int current_free_disk_space = total_disk_space - root_directory_size;
        int min_space_to_be_deleted = needed_disk_space - current_free_disk_space;

        for (int folder_size : all_folder_sizes)
        {
            if (folder_size >= min_space_to_be_deleted)
            {
                std::cout << "Size of the folder to be deleted is " << folder_size << std::endl;
                break;
            }
        }
    }

    int recursive_get_folder_sizes(Folder *current_directory, std::set<int> &all_folder_sizes)
    {
        int files_size_sum = 0;
        for (auto file : current_directory->get_content_files())
        {
            files_size_sum += file->get_size();
        }
        if (current_directory->get_content_folders().size() == 0)
        {
            all_folder_sizes.insert(files_size_sum);
            return files_size_sum;
        }

        for (auto folder : current_directory->get_content_folders())
        {
            files_size_sum += recursive_get_folder_sizes(folder, all_folder_sizes);
        }
        all_folder_sizes.insert(files_size_sum);
        return files_size_sum;
    }
};

int main()
{
    Day_7 day;
    day.part_one();
    day.part_two();
    return 0;
}