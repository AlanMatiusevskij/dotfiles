#include <customCPP.h>
using namespace customcpp;

int main(int argc, char *argv[]){
    std::string HOME = "/home/" + getCurrentUserName() + "/";
    std::string tmp = "";
    
    /* Create config directories */
    tmp = HOME + ".config/configlist/last_replaced";
    std::filesystem::create_directories(tmp.c_str());

    if(argc == 1) std::cout << ACLR.BRIGHT_RED << "Must specify a flag. Use `-h` for help\n" << ACLR.RESET;
    else{
        /* Saved config list */
        tmp = HOME+".config/configlist";
        std::vector<std::string> list = listDirectories(tmp.c_str());

        /* -c (CREATE) flag*/
        if(argv[1][0] == '-' && argv[1][1] == 'c'){
            if(argc < 4){
                std::cout << ACLR.BRIGHT_RED << "Not enough parameters. Must provide a name and names of directories to copy.\n" << ACLR.RESET;
                return 1;
            }
            else{
                /* Create a directory where copied configs will be stored */
                tmp = "mkdir ~/.config/configlist/" + std::string(argv[2]);
                int returnCode = std::system(tmp.c_str());
                
                if(returnCode > 0){
                    std::cout << ACLR.BRIGHT_RED << "Config list exists. Update it based on file modification times? (y/n): " << ACLR.YELLOW;
                    char input;
                    std::cin >> input;
                    if(input != 'y'){
                        std::cout << ACLR.RESET;
                        return 0;
                    }
                }
                else std::cout << ACLR.GREEN << "Created a directory: " << tmp  << ACLR.RESET << "\n"; 
                
                /* Copy the specified directories */
                for(int i = 3; i < argc; i++){
                    std::cout << ACLR.BRIGHT_YELLOW << "    Copying: ~/.config/" << argv[i] << ACLR.YELLOW << " | " << ACLR.BRIGHT_RED << std::flush;
                    
                    tmp = "cp -Ru " + HOME + ".config/" + std::string(argv[i]) + " " + HOME + ".config/configlist/" + std::string(argv[2]) + "/";  
                    returnCode = std::system(tmp.c_str());

                    if(returnCode == 0) std::cout << ACLR.GREEN << "'" << argv[i] << "' was copied.\n" << ACLR.RESET;
                }
            }
        }
        else if(argv[1][0] == '-' && argv[1][1] == 'h'){
            /* Help text */
            std::cout << ACLR.ORANGE << " -h             " << ACLR.BRIGHT_YELLOW << " -print this help message\n"; 
            std::cout << ACLR.ORANGE << " -c $NAME $DIR[]" << ACLR.BRIGHT_YELLOW << " -create a config list with specified $NAME and a list of directories to include\n                  example: configlist -c mountains hypr waybar wofi kitty\n"; 
            std::cout << ACLR.ORANGE << " -s $NAME       " << ACLR.BRIGHT_YELLOW << " -switch to specified config list\n"; 
            std::cout << ACLR.ORANGE << " -l             " << ACLR.BRIGHT_YELLOW << " -give configlist's list\n"; 
        }
        else if(argv[1][0] == '-' && argv[1][1] == 'l'){
            /* Print names of directories in .config/configlist and names of directories within them as well. */
            std::cout << ACLR.ORANGE << "Configlist list:\n";
            for(std::string &str : list) if(str != "last_replaced"){
                std::cout << ACLR.ORANGE << "   " << str << ACLR.WHITE << ": ";

                tmp = HOME + ".config/configlist/" + str + "/";
                std::vector<std::string> dirs = listDirectories(tmp.c_str());
                for(std::string &dirstr : dirs) std::cout << dirstr << " ";
                std::cout << ACLR.RESET << "\n";
            }
        }
        else if(argv[1][0] == '-' && argv[1][1] == 's'){
            /* Makes a copy of to-be-replaced directories within last_replaced directory.
             * Copies the 'saved' directories to .config.
             * Restarts processes, changes configs of running ones, too */
                
            if(argc < 3){
                std::cout << ACLR.BRIGHT_RED << "Must specify a name.\n" << ACLR.RESET;
                return 1;
            }

            /* Find the directory that user want's to switch to */
            bool found = false;
            for(std::string &str : list) if(str != "last_replaced") if(!strcmp(argv[2], str.c_str())){
                found=true;
                break;
            }
            if(!found){
                std::cout << ACLR.BRIGHT_RED << "Config list name not found\n" << ACLR.RESET;
                return 1;
            }


            std::cout << ACLR.ORANGE << "Making config backup (find at ~/.config/configlist/last_replaced/) | " << ACLR.BRIGHT_RED;
            
            tmp = HOME + ".config/configlist/" + std::string(argv[2]) + "/";
            std::vector<std::string> list_to_copy = listDirectories(tmp.c_str());
            tmp = HOME + ".config/";
            std::vector<std::string> config_dir_list = listDirectories(tmp.c_str());

            for(std::string &str : config_dir_list) 
                for(std::string &obj : list_to_copy)
                    if(obj == str){
                        tmp = "cp -r " + HOME + ".config/" + str + " " + HOME + ".config/configlist/last_replaced/";   
                        int returnCode = std::system(tmp.c_str());
                        
                        /* Remove copied directory */
                        tmp = "rm -r " + HOME + ".config/" + str;
                        std::system(tmp.c_str());

                        str = "";
                    }
            std::cout << ACLR.GREEN << "Backup complete\n" << ACLR.RESET;
        
            int i = 1;
            /* Copy saved configs to .config */
            for(std::string &str : list_to_copy){
                std::cout << ACLR.YELLOW << "   Replacing config files (" + intToString(i) + "/" + intToString(int(list_to_copy.size())) + ") | " << ACLR.BRIGHT_RED;
                
                tmp = "cp -r " + HOME + ".config/configlist/" + std::string(argv[2]) + "/" + str + " " + HOME + ".config";
                int returnCode = std::system(tmp.c_str());
                if(returnCode == 0) std::cout << ACLR.GREEN << "Config '" << str << "' was copied.\n" << ACLR.RESET;

                i++;
            }


            /* Reload processes or their used configs */
            std::cout << ACLR.ORANGE << "Reloading processes: \n";
            int returnCode;

                /* Hyprland */
            std::cout << ACLR.YELLOW << "   Hyprland: " << ACLR.GREEN << std::flush; SLEEP(50);
            std::system("hyprctl reload"); SLEEP(50);

                /* Hypraper */
            std::cout << ACLR.YELLOW << "   Hyprpaper: " << std::flush; SLEEP(50);
            std::system("killall -q hyprpaper"); SLEEP(250);
            returnCode = std::system("nohup hyprpaper > /dev/null 2>&1 &"); SLEEP(50);
            if(returnCode > 0) std::cout << ACLR.BRIGHT_RED << "    Failed. Try to execute 'hypraper' command.\n" << ACLR.RESET;
            else std::cout << ACLR.GREEN << "ok\n" << ACLR.RESET;

                /* Waybar */
            std::cout << ACLR.YELLOW << "   Waybar: " << std::flush; SLEEP(50);
            std::system("killall -q waybar"); SLEEP(250);
            returnCode = std::system("nohup waybar > /dev/null 2>&1 &"); SLEEP(50);
            if(returnCode > 0) std::cout << ACLR.BRIGHT_RED << "    Failed. Try to execute 'waybar' command.\n" << ACLR.RESET;
            else std::cout << ACLR.GREEN << "ok\n" << ACLR.RESET;

                /* Kitty */
            std::cout << ACLR.YELLOW << "   Kitty: " << std::flush; SLEEP(50);
            returnCode = std::system("kitty -e kill -SIGUSR1 $(pidof kitty) > /dev/null 2>&1"); SLEEP(50);
            if(returnCode > 0) std::cout << ACLR.BRIGHT_RED << "    Failed. Investigate why 'kill -SIGUSR1 $(pidof kitty)' failed.\n" << ACLR.RESET;
            else std::cout << ACLR.GREEN << "ok\n" << ACLR.RESET;

            ///////////////////////////////////////////////////////////
            std::cout << ACLR.BRIGHT_GREEN << "done\n" << ACLR.RESET;
        }
        else{
            std::cout << ACLR.BRIGHT_RED << "'" << argv[1] << "' is an invalid flag, type -h for help\n" << ACLR.RESET;
            return 1;
        }
    }

    std::cout << ACLR.RESET;
    return 0;
} 
