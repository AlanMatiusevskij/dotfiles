// Desktop Manager Config List
// Save and select configs to replace for use

#include <customCPP.h>
using namespace customcpp;

std::string CONFIGPATH = "";

char* cpCMD(const char *WHAT, const char* WHERE, bool PRESERVe){
    const char *str;
    if(PRESERVe) str = "cp -Ru ~/.config/";
    else str = "cp -r ~/.config/";
    char *str_1 = append_char_p(str, WHAT);
    char *str_2 = append_char_p(str_1, " ~/.config/configlist/");
    delete str_1;
    char *cmd = append_char_p(str_2, WHERE);
    delete str_2;
    return cmd;
}

int main(int argc, char *argv[]){
    CONFIGPATH = "/home/" + customcpp::getCurrentUserName() + "/.config/";
    /* Create necessary directories */
    std::string _tmp = CONFIGPATH + "configlist/last_replaced";
    std::filesystem::create_directories(CONFIGPATH.c_str());
    if(argc == 1)
        std::cout << ACLR.BRIGHT_RED << "Must specify a flag. Type `configlist -h` for help.\n" << ACLR.RESET;
    else{
        std::string __tmp = CONFIGPATH + "configlist";
        std::vector<std::string> list = listDirectories(__tmp.c_str());

        if(argv[1][0] == '-' && argv[1][1] == 'c'){
            if(argc > 3){
                /* Create a config list directory */
                const char *str = "mkdir ~/.config/configlist/";
                char *cmd = append_char_p(str, argv[2]);

                int returnCode = std::system(cmd); 
                
                if(returnCode > 0){
                    std::cout << ACLR.BRIGHT_RED << "Config list exists. Update it based on file modification times? (y/n): " << ACLR.YELLOW;
                    char chr;
                    std::cin >> chr;
                    if(chr != 'y'){
                        std::cout << ACLR.RESET;
                        return 0;
                    }
                }
                else std::cout << ACLR.GREEN << "Created a directory: " << cmd  << ACLR.RESET << "\n"; 

                /* Copy specified config directories */
                for(int i = 3; i < argc; i++){
                    std::cout << ACLR.BRIGHT_YELLOW << "    Copying: ~/.config/" << argv[i] << ACLR.YELLOW << " | " << ACLR.BRIGHT_RED << std::flush;

                    char *cmd = cpCMD(argv[i], argv[2], true);
                    int returnCode = std::system(cmd);
                    delete cmd;

                    if(returnCode == 0)
                        std::cout << ACLR.GREEN << "'" << argv[i] << "' was copied.\n" << ACLR.RESET;
                }

                delete cmd;
            }
        }
        else if(argv[1][0] == '-' && argv[1][1] == 'h'){
            std::cout << ACLR.ORANGE << " -h             " << ACLR.YELLOW << " -print help message\n"; 
            std::cout << ACLR.ORANGE << " -c $NAME $DIR[]" << ACLR.YELLOW << " -create a config list with specified $NAME and a list of directories to include\n                  example: configlist -c mountains hypr waybar wofi kitty\n"; 
            std::cout << ACLR.ORANGE << " -s $NAME       " << ACLR.YELLOW << " -switch to specified config list\n"; 
            std::cout << ACLR.ORANGE << " -l             " << ACLR.YELLOW << " -give config list's list\n"; 
        }
        else if(argv[1][0] == '-' && argv[1][1] == 'l'){
            std::cout << ACLR.ORANGE << "Configlist list:\n";
            for(std::string &str : list)
                if(str != "last_replaced"){
                    std::cout << ACLR.GREEN << "   " << str << ACLR.YELLOW << ": ";

                    std::string pth =CONFIGPATH + "configlist/" + str + "/"; 
                    std::vector<std::string> saved_list = listDirectories(pth.c_str());
                    for(std::string &saved_dir : saved_list) std::cout << saved_dir << " ";
                    std::cout << ACLR.RESET << "\n";
                }        
        }
        else if(argv[1][0] == '-' && argv[1][1] == 's'){
            if(argc < 3){
                std::cout << ACLR.BRIGHT_RED << "Must specify a name.\n" << ACLR.RESET;
                return 1;
            }

            bool found = false;
            for(std::string &str : list) if(str != "last_replaced") if(!strcmp(argv[2], str.c_str())){
                found = true;
                break;
            }

            if(!found){
                std::cout << ACLR.BRIGHT_RED << "Config list name not found\n" << ACLR.RESET;
                return 1;
            }

            std::cout << ACLR.ORANGE << "Making config backup (find at ~/.config/configlist/last_replaced/) | " << ACLR.BRIGHT_RED;

            /* Load specified config list by removing (making a copy in CACHE folder just in case) and replacing config folders. */
            std::vector<std::string> configList = listDirectories(CONFIGPATH.c_str());
            std::string __str = CONFIGPATH + "configlist/";
            char* _str = append_char_p(__str.c_str(), argv[2]);
            std::vector<std::string> dirList = listDirectories(_str);
            delete _str;
                /* Copying backup and removing copied folders */
            for(std::string &str : configList)
                for(std::string &obj : dirList)
                    if(obj == str){
                        char *cmd = cpCMD(str.c_str(), "last_replaced", true);
                        int returnCode = std::system(cmd);
                        delete cmd;
                        if(returnCode > 0) clearLine(1);
                        
                        std::string _cmd = "rm -r ~/.config/" + str;
                        std::system(_cmd.c_str());
                        str = "";
                    }
            
            std::cout << ACLR.GREEN << "Backup complete\n" << ACLR.RESET;

            /* Copy saved folders to .config */
            for(std::string &obj : dirList){
                std::cout << ACLR.YELLOW << "   Copying saved config files | " << ACLR.BRIGHT_RED;
                const char *str = "cp -r ~/.config/configlist/";
                char *str_1 = append_char_p(str, argv[2]);
                char *str_2 = append_char_p(str_1, "/*");
                delete str_1;
                char *cmd = append_char_p(str_2, " ~/.config");
                delete str_2;
                int returnCode = std::system(cmd);
                delete cmd;
                if(returnCode == 0) std::cout << ACLR.GREEN << "Config '" << obj << "' was copied.\n" << ACLR.RESET;
            }

            /* Reload SOME things */
            std::cout << ACLR.ORANGE << "Reloading processes: \n";

            int returnCode = std::system("nohup bash ~/waybar.sh > /dev/null 2>&1 &"); SLEEP(50);
            std::cout << ACLR.YELLOW << "   Waybar: " << ACLR.BRIGHT_YELLOW << std::flush; SLEEP(50);
            if(returnCode > 0) std::cout << ACLR.BRIGHT_RED << "Failed. Launch manually waybar.sh for details.\n" << ACLR.RESET;
            else std::cout << ACLR.GREEN << "ok\n" << ACLR.RESET;

            std::cout << ACLR.YELLOW << "   Hyprland: " << ACLR.GREEN << std::flush; SLEEP(50);
            std::system("hyprctl reload"); SLEEP(50);

            returnCode = std::system("nohup bash ~/hyprpaper.sh > /dev/null 2>&1 &"); SLEEP(50);
            std::cout << ACLR.YELLOW << "   Hyprpaper: " << ACLR.BRIGHT_YELLOW << std::flush; SLEEP(50);
            if(returnCode > 0) std::cout << ACLR.BRIGHT_RED << "Failed. Launch manually waybar.sh for details.\n" << ACLR.RESET;
            else std::cout << ACLR.GREEN << "ok\n" << ACLR.RESET;

            std::cout << ACLR.BRIGHT_GREEN << "done\n" << ACLR.RESET;
        }
        else{
            std::cout << ACLR.BRIGHT_RED << "'" << argv[1] << "' is an invalid flag, use -h for help\n" << ACLR.RESET;
            return 1;
        }
    }

    std::cout << ACLR.RESET;
    return 0;
}
